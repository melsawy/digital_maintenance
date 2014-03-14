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

  return $permissions;
}
