<?php
/**
 * @file
 * dm_core_feature.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function dm_core_feature_taxonomy_default_vocabularies() {
  return array(
    'dm_year_to_perform_task' => array(
      'name' => 'Year to perform task',
      'machine_name' => 'dm_year_to_perform_task',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
