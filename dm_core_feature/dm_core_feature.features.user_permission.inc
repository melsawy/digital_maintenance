<?php
/**
 * @file
 * dm_core_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function dm_core_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: access digital maintenance.
  $permissions['access digital maintenance'] = array(
    'name' => 'access digital maintenance',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'digital_maintenance',
  );

  // Exported permission: create dm_task content.
  $permissions['create dm_task content'] = array(
    'name' => 'create dm_task content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: create dm_task_execution content.
  $permissions['create dm_task_execution content'] = array(
    'name' => 'create dm_task_execution content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any dm_task content.
  $permissions['delete any dm_task content'] = array(
    'name' => 'delete any dm_task content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: delete any dm_task_execution content.
  $permissions['delete any dm_task_execution content'] = array(
    'name' => 'delete any dm_task_execution content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own dm_task content.
  $permissions['delete own dm_task content'] = array(
    'name' => 'delete own dm_task content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own dm_task_execution content.
  $permissions['delete own dm_task_execution content'] = array(
    'name' => 'delete own dm_task_execution content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: edit any dm_task content.
  $permissions['edit any dm_task content'] = array(
    'name' => 'edit any dm_task content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: edit any dm_task_execution content.
  $permissions['edit any dm_task_execution content'] = array(
    'name' => 'edit any dm_task_execution content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own dm_task content.
  $permissions['edit own dm_task content'] = array(
    'name' => 'edit own dm_task content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own dm_task_execution content.
  $permissions['edit own dm_task_execution content'] = array(
    'name' => 'edit own dm_task_execution content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
