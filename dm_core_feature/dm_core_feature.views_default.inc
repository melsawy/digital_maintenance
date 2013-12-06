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
  $view->name = 'task_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Task List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Task List';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_dm_subsequent_cost' => 'field_dm_subsequent_cost',
    'field_dm_year_to_perform_task' => 'field_dm_year_to_perform_task',
    'title' => 'title',
    'field_dm_maintenance_cost' => 'field_dm_maintenance_cost',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_dm_subsequent_cost' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'field_dm_year_to_perform_task' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 1,
      'aggr' => array(
        'views_aggregator_group_and_compress' => 'views_aggregator_group_and_compress',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 1,
      'aggr' => array(
        'views_aggregator_enumerate' => 'views_aggregator_enumerate',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_count',
      'aggr_par_column' => '',
    ),
    'field_dm_maintenance_cost' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['totals_row_position'] = array(
    0 => 0,
    1 => 0,
    2 => '2',
  );
  /* Field: Content: Subsequent maintenance cost  */
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['id'] = 'field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['table'] = 'field_data_field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['field'] = 'field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Year to perform task */
  $handler->display->display_options['fields']['field_dm_year_to_perform_task']['id'] = 'field_dm_year_to_perform_task';
  $handler->display->display_options['fields']['field_dm_year_to_perform_task']['table'] = 'field_data_field_dm_year_to_perform_task';
  $handler->display->display_options['fields']['field_dm_year_to_perform_task']['field'] = 'field_dm_year_to_perform_task';
  $handler->display->display_options['fields']['field_dm_year_to_perform_task']['type'] = 'date_plain';
  $handler->display->display_options['fields']['field_dm_year_to_perform_task']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] ([field_dm_subsequent_cost])';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: maintenance cost */
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['id'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['table'] = 'field_data_field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['field'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['group_type'] = 'sum';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Content: Year to perform task (field_dm_year_to_perform_task) */
  $handler->display->display_options['sorts']['field_dm_year_to_perform_task_value']['id'] = 'field_dm_year_to_perform_task_value';
  $handler->display->display_options['sorts']['field_dm_year_to_perform_task_value']['table'] = 'field_data_field_dm_year_to_perform_task';
  $handler->display->display_options['sorts']['field_dm_year_to_perform_task_value']['field'] = 'field_dm_year_to_perform_task_value';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'dm-task-list';
  $translatables['task_list'] = array(
    t('Master'),
    t('Task List'),
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
    t('Subsequent maintenance cost '),
    t('Year to perform task'),
    t('Title'),
    t('[title] ([field_dm_subsequent_cost])'),
    t('maintenance cost'),
    t('Page'),
  );
  $export['task_list'] = $view;

  return $export;
}
