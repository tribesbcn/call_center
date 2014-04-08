<?php

/**
 * @file
 * Pathauto integration for MOH Premises
 */

/**
 * Implements hook_path_alias_types().
 *
 * Used primarily by the bulk delete form.
 */
function call_center_path_alias_types() {
  return array('call_center/' => t('Call'));
}

/**
 * Implements hook_pathauto().
 */
function call_center_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'call_center';
      $settings['token_type'] = 'call_center';
      $settings['groupheader'] = t('Call Center paths');
      $settings['patterndescr'] = t('Default path pattern');
      $settings['patterndefault'] = 'call_center/[call_center:name]';
      $settings['batch_update_callback'] = 'call_center_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'call_center') . '/call_center.pathauto.inc';

      $languages = array();
      if (module_exists('locale')) {
        $languages = array(LANGUAGE_NONE => t('language neutral')) + locale_language_list('name');
      }
      return (object) $settings;
    default:
      break;
  }
}

/**
 * Batch processing callback; Generate aliases for nodes.
 */
function call_center_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('call_center', 'e');
  $query->leftJoin('url_alias', 'ua', "CONCAT('call_center/', e.id) = ua.source");
  $query->addField('e', 'id');
  $query->isNull('ua.source');
  $query->condition('e.id', $context['sandbox']['current'], '>');
  $query->orderBy('e.id');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'call_center');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no nodes to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $pids = $query->execute()->fetchCol();

  call_center_update_alias_multiple($pids, 'bulkupdate');
  $context['sandbox']['count'] += count($pids);
  $context['sandbox']['current'] = max($pids);
  $context['message'] = t('Updated alias for premise @pid.', array('@pid' => end($pids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}

/**
 * Update the URL aliases for an individual my_entity.
 *
 * @param $my_entity
 *   A call_center object.
 * @param $op
 *   Operation being performed on the call_center ('insert', 'update' or 'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function call_center_update_alias($call_center, $op, array $options = array()) {
  // Skip processing if the user has disabled pathauto for the call_center.
  if (isset($call_center->path['pathauto']) && empty($call_center->path['pathauto'])) {
    return;
  }

  $options += array(
    'language' => isset($call_center->language) ? $call_center->language : LANGUAGE_NONE,
  );

  // Skip processing if the call_center has no pattern.
  if (!pathauto_pattern_load_by_entity('call_center', $call_center->type, $options['language'])) {
    return;
  }

  module_load_include('inc', 'pathauto');
  $uri = entity_uri('call_center', $call_center);
  pathauto_create_alias('call_center', $op, $uri['path'], array('call_center' => $call_center), $call_center->type, $options['language']);
}

/**
 * Update the URL aliases for multiple premises.
 *
 * @param $pids
 *   An array of premise IDs.
 * @param $op
 *   Operation being performed on the nodes ('insert', 'update' or
 *   'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function call_center_update_alias_multiple(array $pids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $entities = call_center_load_multiple($pids);
  foreach ($entities as $call_center) {
    call_center_update_alias($call_center, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($pids), 'Updated URL alias for 1 TRT Entity.', 'Updated URL aliases for @count galleries.'));
  }
}
