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
    $fcost = number_format($cost, 0, '.', '.');
    $total += $cost;
    $output["'tr.data-nid-$nid td.data-year-$lyear'"] = "'<td class='data-year data-year-$year'>$fcost</td>'";
  }
  //add Total for col.
  $ftotal = number_format($total, 0, '.', '.');
  $output["'tr.dm-oxy-total-row td.data-year-$lyear'"] = "'<td class='data-year data-year-$year'>$ftotal</td>'";
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
  $output = '';
  $output .= _dm_render_update_task_form($node);
  $output .= '<div class="dm-post-comment">' . 
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

function ctools_ajax_modal_edit($ajax, $entity, $type) {
  global $user;
  if (!$ajax) return "Javascript required";
  ctools_include('node.pages', 'node', '');
  ctools_include('modal');
  ctools_include('ajax');
  $title = ($type == 'node') ? t('Edit @title', array('@title' => $entity->title )) : t('Edit post');
  $form_state = array(
    'title' => $title,
    'ajax' => TRUE,
  );
  $form_state['build_info']['args'] = array($entity);
  // change this to your type node form
  if ($type == 'node') {
    $output = ctools_modal_form_wrapper($entity->type . '_node_form', $form_state);
  }
  else {
    $node = node_load($entity->nid);
    $output = ctools_modal_form_wrapper("comment_node_{$node->type}_form", $form_state);
  }
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
  $output = '';
  $output .= _dm_render_update_task_form($node);
  $output .= '<div class="dm-execution-list-wrapper">'. views_embed_view('dm_execution', 'default', $node->nid) .'</div>';
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

/**
 *
 */
function _dm_update_task_status($ajax, $node, $status) {
  if ($ajax) {
    ctools_include('modal');
    ctools_include('ajax');
    $form_state = array(
      'title' => t('Update status'),
      'ajax' => TRUE,
    );
    $form_state['task_node'] = $node;
    $form_state['task_new_status'] = $status;
    $output = ctools_modal_form_wrapper('dm_update_task_status_form', $form_state);
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
  else {
    return NULL;
  }
}

function dm_update_task_status_form($form, &$form_state) {
  $node = $form_state['task_node'];
  $new_status = $form_state['task_new_status'];
  $default_value = $node->field_dm_task_status[LANGUAGE_NONE][0]['value'];
  $form['task_nid'] = array(
    '#value' => $node->nid,
    '#type' => 'hidden',
  );
  $form['task_old_status'] = array(
    '#value' => $default_value,
    '#type' => 'hidden',
  );
  $form['dm_task_status'] = array(
    '#type' => 'select',
    '#title' => t('Task status'),
    '#options' => array(1 => t('Not started'), 2 => t('In progress'), 3 => t('Finished')),
    '#default_value' => $new_status,
    '#prefix' => '<div class="dm-task-progress">',
    '#suffix' => '</div>',
  );
  $form['dm_task_comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#cols' => 30,
    '#attributes' => array('placeholder' => t('type your comment.')),
    '#prefix' => '<div class="dm-task-comment">',
    '#suffix' => '</div>',
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), '#',
    array ('attributes' => array(
      'class' => 'ctools-close-modal'),
    'external' => TRUE,
  )));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function dm_update_task_status_form_validate($form, &$form_state) {
  $values  = $form_state['values'];
  if ($values['dm_task_status'] == $values['task_old_status']) {
    form_set_error('dm_task_status', t('You should change task status to new one.'));
  }
}

function dm_update_task_status_form_submit($form, &$form_state) {
  //change task status.
  $nid = $form_state['values']['task_nid'];
  $status = $form_state['values']['dm_task_status'];
  $node = node_load($nid);
  $node->field_dm_task_status[LANGUAGE_NONE][0]['value'] = $status;
  node_save($node);
  //add a comment if exist.
  if (isset($form_state['values']['dm_task_comment'])) {
    global $user;
    $comment = new stdClass();
    $comment->nid = $nid; 
    $comment->cid = 0; 
    $comment->pid = 0; 
    $comment->uid = $user->uid;
    $comment->mail = $user->mail;
    $comment->name = $user->name; 
    $comment->is_anonymous = 0;
    $comment->status = COMMENT_PUBLISHED;
    $comment->language = LANGUAGE_NONE;
    $comment->subject = ''; 
    $comment->comment_body[$comment->language][0]['value'] = $form_state['values']['dm_task_comment']; 
    comment_submit($comment);
    comment_save($comment);
  }
}

function dm_show_tasklist() {
  $output = '';
  //add header
  $field = field_info_field('field_dm_task_status');
  $status = list_allowed_values($field);
  //build-filter options
  $foptions = array();
  $foptions['items_per_page'] = isset($_GET['items_per_page']) ? $_GET['items_per_page'] : 10;
  $foptions['from_year'] = isset($_GET['from_year']) ? $_GET['from_year'] : '';
  $foptions['to_year'] = isset($_GET['to_year']) ? $_GET['to_year'] : '';
  $foptions['status'] = $status;
  $filter = drupal_get_form('dm_tasklist_filter_form', $foptions);
  $output .= drupal_render($filter);
  $output .= drupal_render(drupal_get_form('dm_tasklist_form', $status));
  return $output;
}

function dm_tasklist_filter_form($form, &$form_state, $foptions) {
  $form['#method'] = 'get';
  $form['#action'] = '/dm-task-list';
  $form['#attributes'] = array('class' => array('mymod-search'));
  $query = db_select('taxonomy_vocabulary', 'tv');
  $query->join('taxonomy_term_data', 'td', 'tv.vid = td.vid');
  $query->fields('td', array('name'));
  $query->condition('tv.machine_name', 'dm_year_to_perform_task');
  $query->orderBy('td.name');
  $options = $query->execute()->fetchAllKeyed(0, 0);
  $items = array();
  foreach($foptions['status'] as $key => $value) {
    $items[] = '<span class="dm-task-status dm-task-status-'. $key .'"></span>'. t($value);
  }
  $form['task_status'] = array(
    '#prefix' => '<div class="task-status">',
    '#markup' => theme('item_list', array('items' => $items, 'title' => '', 'attributes' => array('class' => 'dm-tasklist-status'))),
    '#suffix' => '</div>',
  );
  $options = array('' => '- Select a value -') + $options;
  $form['items_per_page'] = array(
    '#title' => t('Number of years'),
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(5, 10, 20, 40, 60)) + array('all' => t('- All -')),
    '#default_value' => $foptions['items_per_page'],
  );
  $form['from_year'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $foptions['from_year'],
  );
  $form['to_year'] = array(
    '#type' => 'select', 
    '#title' => t('To'),
    '#options' => $options,
    '#default_value' => $foptions['to_year'],
  );
  $form['#after_build'] = array('_dm_unset_default_form_elements');
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

function dm_tasklist_filter_form_validate($form, &$form_state) {
  $values  = $form_state['values'];
  if ($values['to_year'] < $values['from_year']) {
    form_set_error('to_year', t('TO year should be greater than FROM year.'));
  }
}

function _dm_unset_default_form_elements($form){
  unset($form['#build_id'], $form['form_build_id'], $form['form_id'], $form['form_token']);
  return $form;
}

/**
 * Build new task list page
 */
function dm_tasklist_form($form, $form_state, $status) {
  if (!isset($form_state['storage']['confirm'])) { 
    //select years
    $query = db_select('taxonomy_vocabulary', 'tv');
    $query->join('taxonomy_term_data', 'td', 'tv.vid = td.vid');
    $query->fields('td', array('tid', 'name'));
    $query->condition('tv.machine_name', 'dm_year_to_perform_task');
    $query->orderBy('td.name');
    //apply filter conditions 
    if (isset($_GET['from_year']) && $_GET['from_year']) {
      $query->condition('td.name', $_GET['from_year'], '>=');
    }
    if (isset($_GET['to_year']) && $_GET['to_year']) {
      $query->condition('td.name', $_GET['to_year'], '<=');
    }
    if (isset($_GET['items_per_page'])) {
      $query = $query->extend('PagerDefault')->limit($_GET['items_per_page']);
    }

    $results = $query->execute()->fetchAllKeyed(0, 1);
    $header = array(
      t('Category'),
      t('Type'),
      t('Title'),
      t('Month'),
      t('Price'),
      t('Status'),
      t('Last activity'),
    );
    $mcosts = _dm_get_maintenance_cost();
    $options = array();
    $field = field_info_field('field_dm_category');
    $categories = list_allowed_values($field);
    $field = field_info_field('field_dm_month_to_perform_task');
    $months = list_allowed_values($field);
    foreach($results as $tid => $tname) {
      //add row for category
      $row = array();
      $row = array_fill(1, 6, '');
      $row[0] = array('data' => $tname, 'class' => array('sawy-test'));
      $row['#attributes'] = array('class' => array('dm-task-year'), 'data-year' => $tname);
      $options["tid_$tid"] = $row;
      _dm_generate_tasklist_rows($options, $tid, $tname, $categories, $months);
      $scost = _dm_get_subsequent_cost($tname);
      $total_cost = isset($mcosts[$tname]) ? $mcosts[$tname] : 0;
      $total_cost += isset($scost->scost) ? $scost->scost : 0;
      //add total price
      $row = array();
      $row = array_fill(0, 5, '');
      $row[5] = '';
      $row[6] = '<span class="total-cost">'. t('Total @total', array('@total' => number_format($total_cost, 0, '.', '.'))) .'</span>';
      $row['#attributes'] = array('class' => array('dm-task-totalcost'));
      $options["tidc_$tid"] = $row;
    }
    $form['table'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#sticky' => TRUE,
      '#empty' => t('No tasks found'),
    );
    $form['status'] = array(
      '#type' => 'select', 
      '#options' => array('' => t('Change Status')) + $status,
      '#weight' => -1,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#weight' => -99,
    );
    $form['years_pager'] = array(
      '#theme' => 'pager'
    );
    return $form;
  }
  else {
    //call confirm form before submit
    $values = $form_state['values'];
    $selected_items = array_filter($values['table']);
    $nodes = $items = array();
    foreach ($selected_items as $item) {
      $value = explode('_', $item);
      if (count($value) == 3 && !in_array($value[2], $nodes)) {
        $nodes[] = $value[2];
        $items[] = $form_state['complete form']['table']['#options'][$item][2];
      }
    }
    $count = format_plural(count($items), 'task', 'tasks');
    $output = theme('item_list', array('items' => $items, 'title' => t('You selected the following <strong>!count</strong>:', array('!count' => $count))));
    return confirm_form(
      $form,
      t('Are you sure you want to change status for selected tasks?'),
      'dm-task-list',
      $output,
      t('Change status'),
      t('cancel'));
  }
}

/**
 * Implements of hook_form_validate().
 */
function dm_tasklist_form_validate($form, &$form_state) {
  if (!isset($form_state['storage']['confirm'])) {
    $selected_items = array_filter($form_state['values']['table']);
    if (!count($selected_items)) {
      form_set_error('', t('You should select 1 item at least.'));
    }
    if (!$form_state['values']['status']) {
      form_set_error('status', t('You should select new status for selected items.'));
    }
  }
}

/**
 * Implements of hook_form_submit().
 */
function dm_tasklist_form_submit($form, &$form_state) {
  if (!isset($form_state['storage']['confirm'])) {
    $form_state['storage']['confirm'] = TRUE;
    $form_state['storage']['original_form'] = $form_state['values'];
    $form_state['rebuild'] = TRUE;
  }
  else {
    $values = $form_state['storage']['original_form'];
    $selected_items = array_filter($values['table']);
    $status = $values['status'];
    $nodes = array();
    foreach ($selected_items as $item) {
      $value = explode('_', $item);
      //make sure that selected item is task.
      if (count($value) == 3 && !in_array($value[2], $nodes)) {
        $nodes[] = $value[2];
        //save node with new status.
        $node = node_load($value[2]);
        $node->field_dm_task_status[LANGUAGE_NONE][0]['value'] = $status;
        node_save($node);
      }
    }
    drupal_goto('dm-task-list');
  }
}

function _dm_generate_tasklist_rows(&$options, $tid, $tname, $categories, $months) {
  $display = array(
    'block' => array('args' => $tid, 'type' => 'Maintenance', 'cost' => 'field_dm_maintenance_cost', 'key' => 'task'),
    'attachment_1' => array('args' => $tname, 'type' => 'Maintenance', 'cost' => 'field_dm_subsequent_cost', 'key' => 'mtask'),
    'attachment_2' => array('args' => $tname, 'type' => 'Inspection', 'key' => 'itask'),
  );
  //Add tasks which match year for perform tasks
  foreach($display as $k => $v) {
    $tasks = views_get_view_result('dm_task_list_row', $k, $v['args']);
    foreach($tasks as $task) {
      $row = array();
      $row[] = $categories[$task->_field_data['nid']['entity']->field_dm_category[LANGUAGE_NONE][0]['value']];
      $row[] = t($v['type']);
      $row[] = l($task->node_title, 'node/'. $task->nid);
      $row[] = isset($task->_field_data['nid']['entity']->field_dm_month_to_perform_task[LANGUAGE_NONE][0]['value']) ? $months[$task->_field_data['nid']['entity']->field_dm_month_to_perform_task[LANGUAGE_NONE][0]['value']] : '-';
      if (isset($v['cost'])) {
        $tcost = $task->_field_data['nid']['entity']->{$v['cost']}[LANGUAGE_NONE][0]['value'];
        $row[] = number_format($tcost, 0, '.', '.');
      }
      else {
        $row[] = 0;
      }
      $row[] = '<span class="dm-task-status dm-task-status-'. $task->_field_data['nid']['entity']->field_dm_task_status[LANGUAGE_NONE][0]['value']. '"></span>';
      $row[] = date('d-m-Y', $task->node_comment_statistics_last_updated);
      $row['#attributes'] = array('class' => array('dm-task-data', 'dm-task-year-'.$tname));
      //generate option key
      $key = "{$v['key']}_{$tname}_{$task->nid}";
      $options[$key] = $row;//array('data' => $row, 'class' => array('mewlsawy-test'));
    }
  }
}


