<?php

function ctools_ajax_modal_createtask($ajax) {
  $callback = 'node_add';
  $args = array('dm_task');
  $_GET['q'] = 'node/add/dm-task';
  include_once(drupal_get_path('module', 'node') . '/node.pages.inc');
  if (function_exists($callback)) {
    $output = call_user_func_array($callback, $args);
    if ($ajax) {
      ctools_include('modal');
      ctools_include('ajax');
      if (is_array($output)) {
        $output = drupal_render($output);
      }
      $title = drupal_get_title();
      // If there are messages for the form, render them.
      if ($messages = theme('status_messages')) {
        $output = '<div class="messages">' . $messages . '</div>' . $output;
      }
      $command = array();
      $command[] = ctools_modal_command_display($title, $output);
      $commands = $command;
      if (empty($commands)) {
        $commands[] = ctools_modal_command_loading();
        if (!empty($_GET['destination'])) {
          $commands[] = ctools_ajax_command_redirect($_GET['destination']);
        }
      }
      print ajax_render($commands);
      exit();
    }
    else {
      return $output;
    }
  }
  else {
    return MENU_NOT_FOUND;
  }
}

/**
 *
 */
function _create_task_submit($form, &$form_state) {
  // Call the rest of submits, because after this submit script will end.
  $submits = $form['actions']['submit']['#submit'];
  // Find the rest of submits.
  foreach ($submits as $key => $item) {
    unset($submits[$key]);
    if ($item == '_create_task_submit') {
      break;
    }
  }
  // Call it.
  foreach ($submits as $function) {
    if (function_exists($function)) {
      $function($form, $form_state);
    }
  }
  // Redirect to destination, if set, or to node path.
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    _createtask_ajax_redirect($destination['destination']);
  }
  else if (isset($form_state['redirect'])) {
    _createtask_ajax_redirect($form_state['redirect']);
  }
}

/**
 *
 */
function _createtask_ajax_redirect($path) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  $commands[] = ctools_modal_command_dismiss();
  $commands[] = ctools_ajax_command_redirect($path);
  print ajax_render($commands);
  exit();
}

function ctools_ajax_show_graph($ajax, $action, $year) {
  $output = '';
  if ($ajax) {
    ctools_include('ajax');
    $x_year = variable_get('dm_x_year_period', 7);
    if ($action == 'next') {
      $eyear = $year + 1;
      $syear = $eyear - $x_year;
    }
    else {
      $syear = $year - 1;
      $eyear = $syear + $x_year;
    }
    $cost = _dm_years_cost_range($syear, $eyear);
    $output = dm_draw_x_year_graph($cost, $syear, $eyear);
    $commands = array();
    $commands[] = ajax_command_html('.dm-graph-container', $output);
    print ajax_render($commands);
    exit;
  }
  else {
    return $output;
  }
}

/**
 *
 */
function ctools_ajax_cost_oxy($action, $lyear) {
  $year = ($action == 'next') ? $lyear + 1 : $lyear - 1;
  $oxy_nids = $_POST['oxy_nids'];
  $query = db_select('taxonomy_term_data', 'td');
  $query->join('field_data_field_dm_year_to_perform_task', 'pt', 'td.tid = pt.field_dm_year_to_perform_task_tid');
  $query->join('field_data_field_dm_maintenance_cost', 'mc', 'pt.entity_id = mc.entity_id');
  $query->join('field_data_field_dm_maintenance_interval', 'mi', 'pt.entity_id=mi.entity_id');
  $query->join('field_data_field_dm_subsequent_cost', 'sc', 'pt.entity_id=sc.entity_id');
  $query->addField('pt', 'entity_id', 'nid');
  $query->addField('td', 'name', 'year');
  $query->addField('mc', 'field_dm_maintenance_cost_value', 'mcost');
  $query->addField('sc', 'field_dm_subsequent_cost_value', 'scost');
  $query->condition('pt.entity_id', $oxy_nids, 'IN');
  $query->condition('td.name', $year, '<=');
  $query->where('MOD((:year - td.name), mi.field_dm_maintenance_interval_value) = 0', array(':year' => $year));
  $result = $query->execute()->fetchAllAssoc('nid');
  $output["th.data-year-$lyear"] = "'<th class='data-year data-year-$year'>$year</th>'";
  $total = 0;
  foreach ($oxy_nids as $nid) {
    if (array_key_exists($nid, $result)) {
      $cost =  ($result[$nid]->year == $year) ? $result[$nid]->mcost : $result[$nid]->scost;
    }
    else {
      $cost = 0;
    }
    $total += $cost;
    $output["'tr.data-nid-$nid td.data-year-$lyear'"] = "'<td class='data-year data-year-$year'>$cost</td>'";
  }
  //add Total for col.
  $output["'tr.dm-oxy-total-row td.data-year-$lyear'"] = "'<td class='data-year data-year-$year'>$total</td>'";
  drupal_json_output($output);
}

/**
 *
 */
function ctools_ajax_modal_stamdata($ajax) {
  if ($ajax) {
    ctools_include('modal');
    ctools_include('ajax');
    $title = t('Master data');
    $output = t('x year period: @years years', array('@years' => variable_get('dm_x_year_period', 7)));
    $command = array();
    $command[] = ctools_modal_command_display($title, $output);
    $commands = $command;
    if (empty($commands)) {
      $commands[] = ctools_modal_command_loading();
      if (!empty($_GET['destination'])) {
        $commands[] = ctools_ajax_command_redirect($_GET['destination']);
      }
    }
    print ajax_render($commands);
    exit();
  }
  else {
    return $output;
  }
}

function _dm_generate_pdf($syear) {
  // Checking mPDF library existence.
  if (pdf_using_mpdf_library_exist() == TRUE) {
    $pdf_filename = 'budget-'. date('Y-m-d');
    $years = array('syear' => $syear);
    $view = _dm_show_cost_overxyears($years);
    $html = drupal_render($view);
    _pdf_using_mpdf_generator($view, $pdf_filename);
  }
  else {
    drupal_set_message(t('mPDF library is not included. Please check your "sites/all/libraries" directory or " /sites/your-domain-name/libraries/ directory " or "!default_module_path" directory.', array(
      '!default_module_path' => drupal_get_path('module', 'pdf_using_mpdf'),
    )), 'warning');
    drupal_goto('<front>');
    return;
  }
}

function _dm_generate_pdf_annual_overview() {
  // Checking mPDF library existence.
  if (pdf_using_mpdf_library_exist() == TRUE) {
    $pdf_filename = 'annual-overview-'. date('Y-m-d');
    $view = views_embed_view('tasks_annual_overview', 'block_1');
    _pdf_using_mpdf_generator($view, $pdf_filename);
  }
  else {
    drupal_set_message(t('mPDF library is not included. Please check your "sites/all/libraries" directory or " /sites/your-domain-name/libraries/ directory " or "!default_module_path" directory.', array(
      '!default_module_path' => drupal_get_path('module', 'pdf_using_mpdf'),
    )), 'warning');
    drupal_goto('<front>');
    return;
  }
}

function _dm_task_posts($node) {
  ctools_include('ajax');
  $output = ctools_ajax_text_button(t('Add new comment'), 'dm_comment/nojs/'. $node->nid, t('Post comment'));
  //$comments = drupal_render(comment_node_page_additions($node));
  $comments = '<div class="dm-comments-wrapper"><h4>comments:</h4>'. 
    '<div class="dm-view-node-comments-wrapper">'. views_embed_view('node_comments', 'default', $node->nid) .'</div></div>';
  $output .= '<div id="dm-comment-form-new"></div>'. $comments;
  $output .= '<div class="dm-attachments-wrapper">'. render(field_view_field('node', $node, 'field_dm_attachments', 'file_table')) .'</div>';
  return $output;
}

function _dm_task_execution($node) {
  module_load_include('inc', 'node', 'node.pages');
  $form = node_add('dm_task_execution'); 
  $output = '<div class="dm-execution-list-wrapper">'. views_embed_view('dm_execution', 'default', $node->nid) .'</div>';
  $output .= drupal_render($form);
  return $output;
}

function ctools_ajax_post_comment($ajax, $node) {
  if ($ajax) {
    ctools_include('ajax');
    $commands = array();
    $form_build = drupal_get_form("comment_node_{$node->type}_form", (object) array('nid' => $node->nid));
    /*
    $form_build['actions']['cancel'] = array(
      '#markup' => '<a id=\'ajax-comments-reply-' . $pid . '\' class=\'ajax-comments-reply-cancel\' href="#' . $form_build['#id'] . '">' . t('Cancel') . '</a>', 
      '#weight' => 21, 
    );  
    */
    $form = drupal_render($form_build);
    $commands[] = ajax_command_html('#dm-comment-form-new', $form);
    print ajax_render($commands); 
    exit;

  }
  else {
    return NULL;
  }
}
