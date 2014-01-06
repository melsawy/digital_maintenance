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

