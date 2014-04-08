<?php
/**
 * @file
 * Hooks provided by this module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Acts on call_center being loaded from the database.
 *
 * This hook is invoked during $call_center loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $call_center entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_call_center_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $call_center is inserted.
 *
 * This hook is invoked after the $call_center is inserted into the database.
 *
 * @param CallCenter $call_center
 *   The $call_center that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_call_center_insert(CallCenter $call_center) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('call_center', $call_center),
      'extra' => print_r($call_center, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $call_center being inserted or updated.
 *
 * This hook is invoked before the $call_center is saved to the database.
 *
 * @param CallCenter $call_center
 *   The $call_center that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_call_center_presave(CallCenter $call_center) {
  $call_center->name = 'foo';
}

/**
 * Responds to a $call_center being updated.
 *
 * This hook is invoked after the $call_center has been updated in the database.
 *
 * @param CallCenter $call_center
 *   The $call_center that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_call_center_update(CallCenter $call_center) {
  db_update('mytable')
    ->fields(array('extra' => print_r($call_center, TRUE)))
    ->condition('id', entity_id('call_center', $call_center))
    ->execute();
}

/**
 * Responds to $call_center deletion.
 *
 * This hook is invoked after the $call_center has been removed from the database.
 *
 * @param CallCenter $call_center
 *   The $call_center that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_call_center_delete(CallCenter $call_center) {
  db_delete('mytable')
    ->condition('pid', entity_id('call_center', $call_center))
    ->execute();
}

/**
 * Act on a call_center that is being assembled before rendering.
 *
 * @param $call_center
 *   The call_center entity.
 * @param $view_mode
 *   The view mode the call_center is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $call_center->content prior to rendering. The
 * structure of $call_center->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_call_center_view($call_center, $view_mode, $langcode) {
  $call_center->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for call_centers.
 *
 * @param $build
 *   A renderable array representing the call_center content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * call_center content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the call_center rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_call_center().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_call_center_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Acts on call_center_type being loaded from the database.
 *
 * This hook is invoked during call_center_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of call_center_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_call_center_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a call_center_type is inserted.
 *
 * This hook is invoked after the call_center_type is inserted into the database.
 *
 * @param CallCenterType $call_center_type
 *   The call_center_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_call_center_type_insert(CallCenterType $call_center_type) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('call_center_type', $call_center_type),
      'extra' => print_r($call_center_type, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a call_center_type being inserted or updated.
 *
 * This hook is invoked before the call_center_type is saved to the database.
 *
 * @param CallCenterType $call_center_type
 *   The call_center_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_call_center_type_presave(CallCenterType $call_center_type) {
  $call_center_type->name = 'foo';
}

/**
 * Responds to a call_center_type being updated.
 *
 * This hook is invoked after the call_center_type has been updated in the database.
 *
 * @param CallCenterType $call_center_type
 *   The call_center_type that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_call_center_type_update(CallCenterType $call_center_type) {
  db_update('mytable')
    ->fields(array('extra' => print_r($call_center_type, TRUE)))
    ->condition('id', entity_id('call_center_type', $call_center_type))
    ->execute();
}

/**
 * Responds to call_center_type deletion.
 *
 * This hook is invoked after the call_center_type has been removed from the database.
 *
 * @param CallCenterType $call_center_type
 *   The call_center_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_call_center_type_delete(CallCenterType $call_center_type) {
  db_delete('mytable')
    ->condition('pid', entity_id('call_center_type', $call_center_type))
    ->execute();
}

/**
 * Define default call_center_type configurations.
 *
 * @return
 *   An array of default call_center_type, keyed by machine names.
 *
 * @see hook_default_call_center_type_alter()
 */
function hook_default_call_center_type() {
  $defaults['main'] = entity_create('call_center_type', array(
    // …
  ));
  return $defaults;
}

/**
 * Alter default call_center_type configurations.
 *
 * @param array $defaults
 *   An array of default call_center_type, keyed by machine names.
 *
 * @see hook_default_call_center_type()
 */
function hook_default_call_center_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}
