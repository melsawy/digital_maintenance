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
  $output = '<div class="dm-post-comment">' . 
    ctools_ajax_text_button(t('Add new comment'), 'dm_post/nojs/'. $node->nid .'/comment', t('Add new comment')) .'</div>';
  //$comments = drupal_render(comment_node_page_additions($node));
  $comments = '<div class="dm-comments-wrapper"><h4>'. t('Comments :') . '</h4>'. 
    '<div class="dm-view-node-comments-wrapper">'. views_embed_view('node_comments', 'default', $node->nid) .'</div></div>';
  $output .= '<div id="dm-comment-form-new"></div>'. $comments;
  $output .= '<div class="dm-post-file">' . 
    ctools_ajax_text_button(t('Add new file'), 'dm_post/nojs/'. $node->nid .'/file', t('Add new file')) .'</div>';
  $output .= '<div id="dm-file-form-new"></div>';
  $output .= '<div id="dm-attachments-wrapper">'. render(field_view_field('node', $node, 'field_dm_attachments', 'file_table')) .'</div>';
  return $output;
}

function dm_task_post_uploadfile($form, &$form_state, $nid) {
  //Add upload filed
    $form['task_nid'] = array(
      '#value' => $nid,
      '#type' => 'hidden',
    );
  $form['post_file'] = array(
    '#type' => 'file',
  );
  $form['upload'] = array(
    '#type' => 'submit',
    '#value' => 'upload',
    //'#submit' => array('upload_image'),
    '#ajax'=> array(
      'callback'=>'upload_image',
      'wrapper'=> 'dm-attachments-wrapper',
      'method'=> 'replace',
      'effect'=> 'fade',
    ),
  );
  return $form;
}  

function upload_image($form, $form_state) {
  $file = file_save_upload('post_file', 
    array('file_validate_extensions' => array('txt png jpg pdf doc')), "public://", $replace = FILE_EXISTS_RENAME);
  if ($file) {
    $file->status=FILE_STATUS_PERMANENT;
    file_save($file);
    $file->display = 0;
    $task_nid = $form_state['values']['task_nid'];
    if ($task_nid) {
      //relate execution to current task
      $node = node_load($task_nid);
      $node->field_dm_attachments[LANGUAGE_NONE][] = (array)$file;
      node_save($node);
      $files = '<div id="dm-attachments-wrapper">'. render(field_view_field('node', $node, 'field_dm_attachments', 'file_table')) .'</div>';
      $commands[] = ajax_command_replace('#dm-attachments-wrapper', $files);
      $commands[] = ajax_command_remove('#dm-file-form-new #dm-task-post-uploadfile');
    }
  }
  $output = array('#type' => 'ajax', '#commands' => $commands);
  return $output;
}

function ctools_ajax_modal_edit($ajax, $node) {
  global $user;
  if (!$ajax) return "Javascript required";
  ctools_include('node.pages', 'node', '');
  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'title' => t('Edit Execution'),
    'ajax' => TRUE,
  );
  $form_state['build_info']['args'] = array($node);
  // change this to your type node form
  $output = ctools_modal_form_wrapper($node->type . '_node_form', $form_state);
  // This means the form has been exectued
  if (!empty($form_state['executed'])) {
    $output = array();
    // Close the modal and reload page
    $output[] = ctools_modal_command_dismiss();
    $output[] = ctools_ajax_command_reload();
  }
  print ajax_render($output);
  exit;
}

function _dm_task_execution($node) {
  module_load_include('inc', 'node', 'node.pages');
  $form = node_add('dm_task_execution'); 
  $output = '<div class="dm-execution-list-wrapper">'. views_embed_view('dm_execution', 'default', $node->nid) .'</div>';
  $output .= drupal_render($form);
  return $output;
}

function ctools_ajax_dm_post($ajax, $node, $type) {
  if ($ajax) {
    ctools_include('ajax');
    $commands = array();
    if ($type == 'comment') {
      $form_build = drupal_get_form("comment_node_{$node->type}_form", (object) array('nid' => $node->nid));
      /*
      $form_build['actions']['cancel'] = array(
        '#markup' => '<a class=\'ajax-comments-reply-cancel\' href="#">' . t('Cancel') . '</a>', 
        '#weight' => 21, 
      );
      */  
      $form = drupal_render($form_build);
      $commands[] = ajax_command_html('#dm-comment-form-new', $form);
    }
    elseif ($type == 'file') {
      $form_build = drupal_get_form('dm_task_post_uploadfile', $node->nid);
      $form = drupal_render($form_build);
      $commands[] = ajax_command_html('#dm-file-form-new', $form);
    }
    print ajax_render($commands); 
    exit;

  }
  else {
    return NULL;
  }
}
