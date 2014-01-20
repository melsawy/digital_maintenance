<?php
/**
 * @file
 * dm_core_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function dm_core_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'dm_execution';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Execution';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Execution';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_dm_maintenance_cost' => 'field_dm_maintenance_cost',
    'field_dm_date' => 'field_dm_date',
    'field_dm_payment_status' => 'field_dm_payment_status',
    'body' => 'body',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_dm_maintenance_cost' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_dm_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_dm_payment_status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_dm_execution_target_id']['id'] = 'field_dm_execution_target_id';
  $handler->display->display_options['relationships']['field_dm_execution_target_id']['table'] = 'field_data_field_dm_execution';
  $handler->display->display_options['relationships']['field_dm_execution_target_id']['field'] = 'field_dm_execution_target_id';
  $handler->display->display_options['relationships']['field_dm_execution_target_id']['label'] = 'field_dm_execution';
  $handler->display->display_options['relationships']['field_dm_execution_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_dm_execution_target_id';
  $handler->display->display_options['fields']['title']['label'] = 'Actor';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_dm_date']['id'] = 'field_dm_date';
  $handler->display->display_options['fields']['field_dm_date']['table'] = 'field_data_field_dm_date';
  $handler->display->display_options['fields']['field_dm_date']['field'] = 'field_dm_date';
  $handler->display->display_options['fields']['field_dm_date']['relationship'] = 'field_dm_execution_target_id';
  $handler->display->display_options['fields']['field_dm_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Field: Content: 1st time maintenance cost */
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['id'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['table'] = 'field_data_field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['field'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['relationship'] = 'field_dm_execution_target_id';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['label'] = 'Price';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Payment status */
  $handler->display->display_options['fields']['field_dm_payment_status']['id'] = 'field_dm_payment_status';
  $handler->display->display_options['fields']['field_dm_payment_status']['table'] = 'field_data_field_dm_payment_status';
  $handler->display->display_options['fields']['field_dm_payment_status']['field'] = 'field_dm_payment_status';
  $handler->display->display_options['fields']['field_dm_payment_status']['relationship'] = 'field_dm_execution_target_id';
  $handler->display->display_options['fields']['field_dm_payment_status']['label'] = 'Paid';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['relationship'] = 'field_dm_execution_target_id';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '50',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'execution';
  $translatables['dm_execution'] = array(
    t('Master'),
    t('Execution'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('field_dm_execution'),
    t('Actor'),
    t('Date'),
    t('Price'),
    t('Paid'),
    t('All'),
    t('Page'),
  );
  $export['dm_execution'] = $view;

  $view = new view();
  $view->name = 'dm_task_list_row';
  $view->description = 'Display tasks for selected year';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'task list row';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'task list row';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Task status */
  $handler->display->display_options['fields']['field_dm_task_status']['id'] = 'field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['table'] = 'field_data_field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['field'] = 'field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['label'] = '';
  $handler->display->display_options['fields']['field_dm_task_status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_task_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dm_task_status']['type'] = 'list_key';
  /* Field: Content: Month */
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['id'] = 'field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['table'] = 'field_data_field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['field'] = 'field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['label'] = '';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: 1st time maintenance cost */
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['id'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['table'] = 'field_data_field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['field'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['label'] = '';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['alter']['text'] = ' <span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-month">[field_dm_month_to_perform_task]</span><span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_maintenance_cost]) </span>
';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['settings'] = array(
    'thousand_separator' => '.',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Content: Month (field_dm_month_to_perform_task) */
  $handler->display->display_options['sorts']['field_dm_month_to_perform_task_value']['id'] = 'field_dm_month_to_perform_task_value';
  $handler->display->display_options['sorts']['field_dm_month_to_perform_task_value']['table'] = 'field_data_field_dm_month_to_perform_task';
  $handler->display->display_options['sorts']['field_dm_month_to_perform_task_value']['field'] = 'field_dm_month_to_perform_task_value';
  /* Contextual filter: Content: Year to perform task (field_dm_year_to_perform_task) */
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['id'] = 'field_dm_year_to_perform_task_tid';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['table'] = 'field_data_field_dm_year_to_perform_task';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['field'] = 'field_dm_year_to_perform_task_tid';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Scaffolding needed? (field_dm_scaffolding_needed) */
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['id'] = 'field_dm_scaffolding_needed_value';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['table'] = 'field_data_field_dm_scaffolding_needed';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['field'] = 'field_dm_scaffolding_needed_value';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['default_argument_options']['code'] = 'if (isset($_GET[\'schaffolding\'])) {
  return 1;
}
return \'all\';';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dm_scaffolding_needed_value']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'dm_task' => 'dm_task',
  );

  /* Display: Tasks */
  $handler = $view->new_display('block', 'Tasks', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;

  /* Display: MTasks */
  $handler = $view->new_display('attachment', 'MTasks', 'attachment_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Task status */
  $handler->display->display_options['fields']['field_dm_task_status']['id'] = 'field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['table'] = 'field_data_field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['field'] = 'field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['label'] = '';
  $handler->display->display_options['fields']['field_dm_task_status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_task_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dm_task_status']['type'] = 'list_key';
  /* Field: Content: Month */
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['id'] = 'field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['table'] = 'field_data_field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['field'] = 'field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['label'] = '';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Subsequent maintenance cost  */
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['id'] = 'field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['table'] = 'field_data_field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['field'] = 'field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['label'] = '';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['alter']['text'] = '<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-month">[field_dm_month_to_perform_task]</span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_subsequent_cost]) </span> <span class="dm-task-type"> | Maintenance </span>';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['settings'] = array(
    'thousand_separator' => '.',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = TRUE;
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'block' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: ITasks */
  $handler = $view->new_display('attachment', 'ITasks', 'attachment_2');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Task status */
  $handler->display->display_options['fields']['field_dm_task_status']['id'] = 'field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['table'] = 'field_data_field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['field'] = 'field_dm_task_status';
  $handler->display->display_options['fields']['field_dm_task_status']['label'] = '';
  $handler->display->display_options['fields']['field_dm_task_status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_task_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dm_task_status']['type'] = 'list_key';
  /* Field: Content: Month */
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['id'] = 'field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['table'] = 'field_data_field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['field'] = 'field_dm_month_to_perform_task';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['label'] = '';
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_month_to_perform_task']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-month">[field_dm_month_to_perform_task]</span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">(0) </span> <span class="dm-task-type"> | Inspection </span>';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = TRUE;
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'block' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $translatables['dm_task_list_row'] = array(
    t('Master'),
    t('task list row'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t(' <span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-month">[field_dm_month_to_perform_task]</span><span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_maintenance_cost]) </span>
'),
    t('All'),
    t('Tasks'),
    t('MTasks'),
    t('<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-month">[field_dm_month_to_perform_task]</span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_subsequent_cost]) </span> <span class="dm-task-type"> | Maintenance </span>'),
    t('ITasks'),
    t('<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-month">[field_dm_month_to_perform_task]</span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">(0) </span> <span class="dm-task-type"> | Inspection </span>'),
  );
  $export['dm_task_list_row'] = $view;

  $view = new view();
  $view->name = 'node_comments';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'comment';
  $view->human_name = 'node comments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Comments';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'name' => 'name',
    'created' => 'created',
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Relationship: Comment: Content */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'comment';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Field: Comment: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'comment';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Comment: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'comment';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Comment: Comment */
  $handler->display->display_options['fields']['comment_body']['id'] = 'comment_body';
  $handler->display->display_options['fields']['comment_body']['table'] = 'field_data_comment_body';
  $handler->display->display_options['fields']['comment_body']['field'] = 'comment_body';
  $handler->display->display_options['fields']['comment_body']['label'] = '';
  $handler->display->display_options['fields']['comment_body']['element_label_colon'] = FALSE;
  /* Sort criterion: Comment: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'comment';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Post date';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Comment: Approved */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'comment';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_node']['id'] = 'status_node';
  $handler->display->display_options['filters']['status_node']['table'] = 'node';
  $handler->display->display_options['filters']['status_node']['field'] = 'status';
  $handler->display->display_options['filters']['status_node']['relationship'] = 'nid';
  $handler->display->display_options['filters']['status_node']['value'] = 1;
  $handler->display->display_options['filters']['status_node']['group'] = 1;
  $handler->display->display_options['filters']['status_node']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'node-comments';

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Comment: ID */
  $handler->display->display_options['arguments']['cid']['id'] = 'cid';
  $handler->display->display_options['arguments']['cid']['table'] = 'comment';
  $handler->display->display_options['arguments']['cid']['field'] = 'cid';
  $handler->display->display_options['arguments']['cid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['cid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['cid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['cid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['cid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Comment: Approved */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'comment';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $translatables['node_comments'] = array(
    t('Master'),
    t('Comments'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<?php
?>'),
    t('Content'),
    t('Post date'),
    t('All'),
    t('Page'),
    t('Attachment'),
  );
  $export['node_comments'] = $view;

  $view = new view();
  $view->name = 'tasks_annual_overview';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Tasks Annual Overview';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Annual Overview';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Number of years';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'dm-annual-overview-row';
  $handler->display->display_options['style_options']['columns'] = array(
    'tid' => 'tid',
    'name' => 'name',
    'view' => 'view',
    'view_1' => 'view_1',
    'view_2' => 'view_2',
    'tid_1' => 'tid_1',
    'description' => 'description',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'tid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'description' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<?php
print l(t(\'Generate PDF\'), \'dm_pdf/annual_overview\');
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Tasks (view) */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Tasks (view)';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['empty'] = 'No tasks found';
  $handler->display->display_options['fields']['view']['view'] = 'dm_task_list_row';
  $handler->display->display_options['fields']['view']['display'] = 'block';
  $handler->display->display_options['fields']['view']['arguments'] = '[!tid]';
  /* Field: Maintenance Tasks (view) */
  $handler->display->display_options['fields']['view_1']['id'] = 'view_1';
  $handler->display->display_options['fields']['view_1']['table'] = 'views';
  $handler->display->display_options['fields']['view_1']['field'] = 'view';
  $handler->display->display_options['fields']['view_1']['ui_name'] = 'Maintenance Tasks (view)';
  $handler->display->display_options['fields']['view_1']['label'] = '';
  $handler->display->display_options['fields']['view_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_1']['view'] = 'dm_task_list_row';
  $handler->display->display_options['fields']['view_1']['display'] = 'attachment_1';
  $handler->display->display_options['fields']['view_1']['arguments'] = '[!name]';
  /* Field: Inspection Taks (view) */
  $handler->display->display_options['fields']['view_2']['id'] = 'view_2';
  $handler->display->display_options['fields']['view_2']['table'] = 'views';
  $handler->display->display_options['fields']['view_2']['field'] = 'view';
  $handler->display->display_options['fields']['view_2']['ui_name'] = 'Inspection Taks (view)';
  $handler->display->display_options['fields']['view_2']['label'] = '';
  $handler->display->display_options['fields']['view_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_2']['view'] = 'dm_task_list_row';
  $handler->display->display_options['fields']['view_2']['display'] = 'attachment_2';
  $handler->display->display_options['fields']['view_2']['arguments'] = '[!name]';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['alter']['text'] = '[view] 
[view_1]
[view_2]';
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'Samlet';
  $handler->display->display_options['fields']['description']['element_wrapper_class'] = 'container-inline';
  $handler->display->display_options['fields']['description']['empty'] = '0';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'dm_year_to_perform_task' => 'dm_year_to_perform_task',
  );
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Showing year';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'dm-annual-overview';

  /* Display: PDF version */
  $handler = $view->new_display('block', 'PDF version', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'dm_year_to_perform_task' => 'dm_year_to_perform_task',
  );
  $translatables['tasks_annual_overview'] = array(
    t('Master'),
    t('Annual Overview'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Number of years'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('<?php
print l(t(\'Generate PDF\'), \'dm_pdf/annual_overview\');
?>'),
    t('.'),
    t(','),
    t('No tasks found'),
    t('[view] 
[view_1]
[view_2]'),
    t('Samlet'),
    t('Showing year'),
    t('Page'),
    t('PDF version'),
  );
  $export['tasks_annual_overview'] = $view;

  return $export;
}
