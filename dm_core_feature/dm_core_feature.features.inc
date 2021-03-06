<?php
/**
 * @file
 * dm_core_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dm_core_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function dm_core_feature_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function dm_core_feature_node_info() {
  $items = array(
    'dm_task' => array(
      'name' => t('Task'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Sub category title'),
      'help' => '',
    ),
    'dm_task_execution' => array(
      'name' => t('Execution'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Company name'),
      'help' => '',
    ),
  );
  return $items;
}
