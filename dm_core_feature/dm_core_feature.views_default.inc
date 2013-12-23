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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_dm_task_type']['id'] = 'field_dm_task_type';
  $handler->display->display_options['fields']['field_dm_task_type']['table'] = 'field_data_field_dm_task_type';
  $handler->display->display_options['fields']['field_dm_task_type']['field'] = 'field_dm_task_type';
  $handler->display->display_options['fields']['field_dm_task_type']['label'] = '';
  $handler->display->display_options['fields']['field_dm_task_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_task_type']['element_label_colon'] = FALSE;
  /* Field: Content: 1st time maintenance cost */
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['id'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['table'] = 'field_data_field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['field'] = 'field_dm_maintenance_cost';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['label'] = '';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['alter']['text'] = '<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_maintenance_cost]) </span> <span class="dm-task-type"> | [field_dm_task_type] </span>
';
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dm_maintenance_cost']['settings'] = array(
    'thousand_separator' => '.',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Year to perform task (field_dm_year_to_perform_task) */
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['id'] = 'field_dm_year_to_perform_task_tid';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['table'] = 'field_data_field_dm_year_to_perform_task';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['field'] = 'field_dm_year_to_perform_task_tid';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dm_year_to_perform_task_tid']['summary_options']['items_per_page'] = '25';
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

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_dm_task_type']['id'] = 'field_dm_task_type';
  $handler->display->display_options['fields']['field_dm_task_type']['table'] = 'field_data_field_dm_task_type';
  $handler->display->display_options['fields']['field_dm_task_type']['field'] = 'field_dm_task_type';
  $handler->display->display_options['fields']['field_dm_task_type']['label'] = '';
  $handler->display->display_options['fields']['field_dm_task_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dm_task_type']['element_label_colon'] = FALSE;
  /* Field: Content: Subsequent maintenance cost  */
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['id'] = 'field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['table'] = 'field_data_field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['field'] = 'field_dm_subsequent_cost';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['label'] = '';
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dm_subsequent_cost']['alter']['text'] = '<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_subsequent_cost]) </span> <span class="dm-task-type"> | [field_dm_task_type] </span>';
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
    'block' => 'block',
    'default' => 0,
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
    t('<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_maintenance_cost]) </span> <span class="dm-task-type"> | [field_dm_task_type] </span>
'),
    t('All'),
    t('Block'),
    t('Attachment'),
    t('<span class="dm-task-status dm-task-status-[field_dm_task_status]"></span> <span class="dm-task-title"> [title] </span> <span class="dm-task-cost">([field_dm_subsequent_cost]) </span> <span class="dm-task-type"> | [field_dm_task_type] </span>'),
  );
  $export['dm_task_list_row'] = $view;

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
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Number of years';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'dm-annual-overview-row';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['empty'] = 'No tasks found';
  $handler->display->display_options['fields']['view']['view'] = 'dm_task_list_row';
  $handler->display->display_options['fields']['view']['display'] = 'block';
  $handler->display->display_options['fields']['view']['arguments'] = '[!tid]';
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
    t('.'),
    t(','),
    t('No tasks found'),
    t('Samlet'),
    t('Showing year'),
    t('Page'),
  );
  $export['tasks_annual_overview'] = $view;

  return $export;
}
