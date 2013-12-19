<?php
/**
 * @file
 * dm_core_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function dm_core_feature_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_dm_show_advanced|node|dm_task|form';
  $field_group->group_name = 'group_dm_show_advanced';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dm_task';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Show advanced',
    'weight' => '6',
    'children' => array(
      0 => 'field_dm_omfang',
      1 => 'field_dm_materiale',
      2 => 'field_dm_udf_relse',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Show advanced',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_dm_show_advanced|node|dm_task|form'] = $field_group;

  return $export;
}
