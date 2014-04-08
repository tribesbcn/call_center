<?php

/**
 * Generates the Call Center Entity type editing form.
 */
function call_center_type_form($form, &$form_state, $callcenter_type, $op = 'edit') {

  if ($op == 'clone') {
    $callcenter_type->label .= ' (cloned)';
    $callcenter_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $callcenter_type->label,
    '#description' => t('The human-readable name of this Call Center Entity type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($callcenter_type->type) ? $callcenter_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $callcenter_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'call_center_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Call Center Entity type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($callcenter_type->description) ? $callcenter_type->description : '',
    '#description' => t('Description about the Call Center Entity type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Call Center Entity type'),
    '#weight' => 40,
  );

  if (!$callcenter_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Call Center Entity type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('call_center_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing callcenter_type.
 */
function call_center_type_form_submit(&$form, &$form_state) {
  $callcenter_type = entity_ui_form_submit_build_entity($form, $form_state);
  //dpm($callcenter_type);
  // Save and go back.
  call_center_type_save($callcenter_type);

  // Redirect user back to list of Call Center Entity types.
  $form_state['redirect'] = 'admin/structure/try_entity-types';
}

function call_center_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/try_entity-types/' . $form_state['call_center_type']->type . '/delete';
}

/**
 * Call Center Entity type delete form.
 */
function call_center_type_form_delete_confirm($form, &$form_state, $callcenter_type) {
  $form_state['callcenter_type'] = $callcenter_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['callcenter_type_id'] = array('#type' => 'value', '#value' => entity_id('call_center_type' ,$callcenter_type));
  return confirm_form($form,
    t('Are you sure you want to delete Call Center Entity type %title?', array('%title' => entity_label('callcenter_type', $callcenter_type))),
    'call_center/' . entity_id('call_center_type' ,$callcenter_type),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Call Center Entity type delete form submit handler.
 */
function call_center_type_form_delete_confirm_submit($form, &$form_state) {
  $callcenter_type = $form_state['callcenter_type'];
  call_center_type_delete($callcenter_type);

  watchdog('call_center_type', '@type: deleted %title.', array('@type' => $callcenter_type->type, '%title' => $callcenter_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $callcenter_type->type, '%title' => $callcenter_type->label)));

  $form_state['redirect'] = 'admin/structure/call_center-types';
}

/**
 * Page to select Call Center Entity Type to add new entity.
 */
function call_center_admin_add_page() {
  $items = array();
  foreach (call_center_types() as $callcenter_type_key => $callcenter_type) {
    $items[] = l(entity_label('call_center_type', $callcenter_type), 'call_center/add/' . $callcenter_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of Call Center Entity to create.')));
}

/**
 * Page to show import csv initial form.
 */
function call_center_admin_import_csv_form($form, &$form_state) {
  $form['csv_file'] = array(
    '#type' => 'file',
    '#title' => t('Upload CSV File'),
    '#description' => t('The CSV file exported from the unit. Only CSV extension allowed.'),
    '#title_display' => 'before',
    '#weight' => 1,
    '#upload_validators' => array(
      'file_validate_extensions' => array('csv'),
    ),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import CSV File'),
    '#weight' => 40,
  );
  
  return $form;
}

/**
 * Page to show import csv initial form submit.
 */
function call_center_admin_import_csv_form_validate($form, &$form_state) {
  global $user;
  $user = user_load($user->uid);
  $center_tid = (isset($user->call_center) && is_array($user->call_center) && count($user->call_center) > 0) ? $user->call_center[LANGUAGE_NONE][0]['tid'] : 0;
  if(!$center_tid) form_set_error('csv_file', t('Only call center users can import CSV file.'));
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('csv_file', $validators, FALSE);
  if(!$file){
    form_set_error('csv_file', t('CSV file is required.'));
  }
}

/**
 * Page to show import csv initial form submit.
 */
function call_center_admin_import_csv_form_submit($form, &$form_state) {
  global $user;
  $user = user_load($user->uid);
  $center_tid = $user->field_user_call_center[LANGUAGE_NONE][0]['tid'];
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('csv_file', $validators, FALSE);
  //dpm($file);
  $file_path = drupal_realpath($file->uri);
  $handle = fopen($file_path, "r");
  $csv_info = array();
  while (!feof($handle)) {
    $csv_line = fgetcsv($handle, 0, ",");
    if(count($csv_line) == 8){
      //$csv_info[] = $csv_line;
      $csv_line_date = $csv_line[1];
      $csv_line_time = $csv_line[2];
      $csv_line_date_array = explode('/', $csv_line_date);
      $submittedDate = "{$csv_line_date_array[0]}-{$csv_line_date_array[1]}-{$csv_line_date_array[2]} {$csv_line_time}";
      $timezone = $user->timezone;
      $call_date_info = new DateTime($submittedDate, new DateTimeZone($timezone));
      $call_date_timestamp = $call_date_info->getTimestamp();
      $call_source_phone = $csv_line[3];
      $call_destination_phone = $csv_line[4];
      $call_status = $csv_line[5];
      $call_duration = $csv_line[6];
      $entity_name = 'Call from ' . $call_source_phone;
      $call_info = new StdClass();
      $call_info->type = 'call';
      $call_info->name = $entity_name;
      $call_info->call_date = $call_date_timestamp;
      $call_info->call_source_phone = $call_source_phone;
      $call_info->call_destination_phone = $call_destination_phone;
      $call_info->call_status = $call_status;
      $call_info->call_duration = $call_duration;
      $call_info->uid = $user->uid;
      $call_info->status = TRUE;
      $call_info->call_center[LANGUAGE_NONE][0]['tid'] = $center_tid;
      $csv_info[] = $call_info;
      call_center_save($call_info);
    }
  }
  dpm($csv_info);
  //$contents = fread($handle, filesize($file_path));
  //dpm($contents);
  fclose($handle);
}

/**
 * JSON call for user autocomplete 
 */
function call_center_admin_system_user_autocomplete($callcenter_id, $json=TRUE) {
	$matches = array();
	$result = db_select('users')->fields('users', array('uid', 'name'))->condition('uid', 1, '>')->range(0, 50)->execute();
	//$subquery_string = 'SELECT gu.uid FROM {call_center_user_privilege} gu WHERE gu.id = :id';
	//$query_string = 'SELECT u.uid, u.name FROM {users} u WHERE u.uid > 1 AND u.uid NOT IN ('.$subquery_string.') ORDER BY u.name';
	//$result = db_query($query_string, array(':id' => $callcenter_id));
	foreach ($result as $user) {
		$matches[$user->uid] = check_plain($user->name);
	}
	if($json) drupal_json_output($matches);
	else return $matches;
}

/**
 * Add new Call Center Entity page callback.
 */
function call_center_add($type) {
  $callcenter_type = call_center_types($type);

  $callcenter = entity_create('call_center', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('callcenter_type', $callcenter_type))));

  $output = drupal_get_form('call_center_form', $callcenter);

  return $output;
}

/**
 * Call Center Form.
 */
function call_center_form($form, &$form_state, $callcenter) {
  //dpm($callcenter);
  $form_state['call_center'] = $callcenter;

  $form['name'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Entity name or title'),
  	'#weight' => 0,
    '#default_value' => $callcenter->name,
  );
  $form['call_date'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Call date'),
    '#weight' => 1,
    '#default_value' => $callcenter->call_date,
  );
  $form['call_source_phone'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Source phone'),
    '#weight' => 2,
    '#default_value' => $callcenter->call_source_phone,
  );
  $form['call_destination_phone'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Destination phone'),
    '#weight' => 3,
    '#default_value' => $callcenter->call_destination_phone,
  );
  $form['call_status'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Call status'),
    '#weight' => 4,
    '#default_value' => $callcenter->call_status,
  );
  $form['call_duration'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Call duration'),
    '#weight' => 5,
    '#default_value' => $callcenter->call_duration,
  );
    
  /*
    $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $callcenter->description,
    );
  */

  $form['uid'] = array(
    '#type' => 'value',
  	'#weight' => 15,
    '#value' => $callcenter->uid,
  );
  
  // Node author information for administrators
  $form['author'] = array(
  		'#type' => 'fieldset',
  		'#title' => t('Authoring information'),
  		'#collapsible' => TRUE,
  		'#collapsed' => TRUE,
  		'#attributes' => array(
  			'class' => array('callcenter-form-author'),
  		),
  		'#attached' => array(
  			'js' => array(
  				drupal_get_path('module', 'call_center') . '/js/callcenter.admin.js',
  				array(
  					'type' => 'setting',
  					'data' => array('anonymous' => variable_get('anonymous', t('Anonymous'))),
  			),
  		),
  	),
  	'#weight' => 90,
  );
  $callcenter_creator_user = ($callcenter->uid)? user_load($callcenter->uid) : FALSE;
  $username = ($callcenter_creator_user)? $callcenter_creator_user->name : '';
  $form['author']['uid'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Authored by'),
  	'#maxlength' => 60,
  	'#autocomplete_path' => 'user/autocomplete',
  	'#default_value' => $username,
  	'#weight' => -1,
  	'#description' => t('Leave blank for %anonymous.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
  );
  
  $form['options'] = array(
  	'#type' => 'fieldset',
  	'#title' => t('Call center options'),
  	'#collapsible' => TRUE,
  	'#collapsed' => FALSE,
  	'#attributes' => array(
  		'class' => array('callcenter-form-options'),
  	),
  		'#attached' => array(
  		'js' => array(drupal_get_path('module', 'call_center') . '/js/callcenter.admin.js'),
  	),
  	'#weight' => 95,
  );
  $form['options']['status'] = array(
  		'#type' => 'checkbox',
  		'#title' => t('Published'),
  		'#default_value' => $callcenter->status,
  );
  field_attach_form('call_center', $callcenter, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 99,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Call'),
    '#submit' => $submit + array('call_center_form_submit'),
  	'#weight' => 100,
  );

  // Show Delete button if we edit Call Center Entity.
  $callcenter_id = entity_id('call_center' ,$callcenter);
  if (!empty($callcenter_id) && call_center_access('edit', $callcenter)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('call_center_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'call_center_form_validate';
  return $form;
}

function call_center_form_validate($form, &$form_state) {

}

/**
 * Call Center Entity submit handler.
 */
function call_center_form_submit($form, &$form_state) {
  $callcenter = $form_state['call_center'];
  //dpm($callcenter);
  //dpm($form);
  //dpm($form_state);
  entity_form_submit_build_entity('call_center', $callcenter, $form, $form_state);
  call_center_save($callcenter);
  $callcenter_uri = entity_uri('call_center', $callcenter);
  $form_state['redirect'] = $callcenter_uri['path'];
  drupal_set_message(t('Call Center Entity %title saved.', array('%title' => entity_label('call_center', $callcenter))));
}

function call_center_form_submit_delete($form, &$form_state) {
  $callcenter = $form_state['call_center'];
  $callcenter_uri = entity_uri('call_center', $callcenter);
  $form_state['redirect'] = $callcenter_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function call_center_delete_form($form, &$form_state, $callcenter) {
  $form_state['call_center'] = $callcenter;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['callcenter_type_id'] = array('#type' => 'value', '#value' => entity_id('call_center' ,$callcenter));
  $callcenter_uri = entity_uri('call_center', $callcenter);
  return confirm_form($form,
    t('Are you sure you want to delete call %title?', array('%title' => entity_label('call_center', $callcenter))),
    'admin/calls',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete calls confirmation form.
 */
function call_center_delete_calls_form($form, &$form_state) {
  return confirm_form($form,
    t('Are you sure you want to delete all calls?'),
    'admin/calls',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function call_center_delete_form_submit($form, &$form_state) {
  $callcenter = $form_state['call_center'];
  //Call entity deletion
  call_center_delete($callcenter);
  drupal_set_message(t('Call %name deleted.', array('%name' => entity_label('call_center', $callcenter))));

  $form_state['redirect'] = 'admin/calls';
}

/**
 * Delete calls form submit handler.
 */
function call_center_delete_calls_form_submit($form, &$form_state) {
  //Call Center Entity entity deletion
  global $user;
  $user = user_load($user->uid);
  $center_tid = (isset($user->call_center) && is_array($user->call_center) && count($user->call_center) > 0) ? $user->call_center[LANGUAGE_NONE][0]['tid'] : 0;
  
  $all_call_center = entity_load('call_center');
  
  $field_query = new EntityFieldQuery;
  $center_calls = $field_query
    ->entityCondition('entity_type', 'call_center')
    ->propertyCondition('type', 'call')
    ->fieldCondition('call_center', 'tid', $center_tid, '=')
    ->execute();
  dpm($center_calls);
  //foreach($all_call_center as $entity_item){
    //entity_delete('call_center', entity_id('call_center', $entity_item));
  //}
  
  //db_delete('call_center')->condition('call_center', $center_tid);
  //call_center_delete($callcenter);
  drupal_set_message(t('All calls are deleted.'));

  $form_state['redirect'] = 'admin/calls';
}
