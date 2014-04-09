<?php

function call_center_admin_view($form, &$form_state) {
  $user_call_info = _call_center_get_user_call_info();
  $center_tid = $user_call_info['center_tid'];
  $call_ids = $user_call_info['call_ids'];
  $header = _call_center_table_header();
  // Execute query.
  $query = db_select('call_center', 'cc')
    ->condition('id', $call_ids,'IN')
    ->extend('PagerDefault')->limit(25)
    ->extend('TableSort')->orderByHeader($header)
    ->fields ('cc', array ('id', 'call_date', 'call_source_phone', 'call_destination_phone', 'call_duration', 'call_status'));
  $results = $query->execute();
  $html_table = _call_center_create_sortable_table($header, $results);
  
  //$exposed_filter_form = drupal_get_form('call_center_create_exposed_filter_admin_form', $center_tid, $call_ids);
  _call_center_filter_form($form, $form_state, $center_tid, $call_ids);
  $form['#submit'][] = 'call_center_filter_form_submit';
  // Print the table result.
  $html = render($exposed_filter_form);
  $html .= $html_table;
  $form['table'] = array(
    '#type' => 'markup',
    '#markup' => $html,
    '#weight' => 200,
  );
  //return $html;
  return $form;
}

function call_center_filter_form_submit($form, &$form_state) {
  // Retrieve the form_state values and save it in session.
  $call_source_phone_value = isset($form_state['values']['call_source_phone']) ? $form_state['values']['call_source_phone'] : '';
  $call_destination_phone_value = isset($form_state['values']['call_destination_phone']) ? $form_state['values']['call_destination_phone'] : '';
  $call_operator_value = (isset($form_state['values']['call_operator'])) ? $form_state['values']['call_operator'] : 0;
  $call_operator_ext_value = (isset($form_state['values']['call_operator_extensions']) && $form_state['values']['call_operator_extensions'] != '0') ? array($form_state['values']['call_operator_extensions']) : array();
  if (!count($call_operator_ext_value)) {
    $operator_available_extensions = $form['call_operator_extensions']['#options'];
    foreach ($operator_available_extensions as $key => $value) {
      $call_operator_ext_value[] = $key;
    }
  }
  _call_center_session('source_phone', $call_source_phone_value);
  _call_center_session('destination_phone', $call_destination_phone_value);
  _call_center_session('operator', $call_operator_value);
  _call_center_session('operator_ext', $call_operator_ext_value);
  /*
  $user_call_info = _call_center_get_user_call_info();
  $center_tid = $user_call_info['center_tid'];
  $call_ids = $user_call_info['call_ids'];
  $header = _call_center_table_header();
  // Execute query.
  $query = db_select('call_center', 'cc')
    ->condition('id', $call_ids,'IN')
    ->extend('PagerDefault')->limit(25)
    ->extend('TableSort')->orderByHeader($header)
    ->fields ('cc', array ('id', 'call_date', 'call_source_phone', 'call_destination_phone', 'call_duration', 'call_status'));
  $results = $query->execute();
  $html_table = _call_center_create_sortable_table($header, $results);
  
  //$exposed_filter_form = drupal_get_form('call_center_create_exposed_filter_admin_form', $center_tid, $call_ids);
  _call_center_filter_form($form, $form_state, $center_tid, $call_ids);
  $form['#submit'][] = 'call_center_filter_form_submit';
  // Print the table result.
  $html = render($exposed_filter_form);
  $html .= $html_table;
  $form['table'] = array(
    '#type' => 'markup',
    '#markup' => $html,
    '#weight' => 200,
  );
   */
  //return $html;
  //return $form;
}

function _call_center_session($key, $value = NULL) {
  static $storage;
  if ($value != NULL) {
    $storage[$key] = $value ;
    $_SESSION['call_center'][$key] = $value ;
  }
  else if (empty($storage[$key]) && isset($_SESSION['call_center'][$key])) {
    $storage[$key] = $_SESSION['call_center'][$key];
  }
  // Return values (special tratement for operator_ext key)
  if ($key == 'operator_ext' && is_array($storage[$key]) && count($storage[$key]) > 0) {
    return (count($storage[$key]) == 1) ? reset($storage[$key]) : 0;
  }
  return $storage[$key];
}

function _call_center_table_header() {
  return array(
    array('data' => 'Id', 'field' => 'id', 'sort' => 'asc'),
    array('data' => 'Date', 'field' => 'call_date'),
    array('data' => 'Source', 'field' => 'call_source_phone'),
    array('data' => 'Destination', 'field' => 'call_destination_phone'),
    array('data' => 'Duration', 'field' => 'call_duration'),
    array('data' => 'Status', 'field' => 'call_status'),
    array('data' => 'Operations'),
  );
}

function _call_center_create_sortable_table($header, $results) {
  // Prepare table rows.
  $rows = array();
  foreach ($results as $call) {
    $edit_link = l('<img src="/sites/default/graphics/admin/application--pencil.png" title="Edit" alt="Edit"/>', 'call_center/'. $call->id .'/edit', array('html' => TRUE));
    $delete_link = l('<img src="/sites/default/graphics/admin/cross-script.png" title="Delete" alt="Delete"/>', 'call_center/'. $call->id .'/delete', array('html' => TRUE));
    $rows[] = array(
      'data' => array(
        $call->id, 
        format_date($call->call_date), 
        $call->call_source_phone, 
        $call->call_destination_phone, 
        $call->call_duration,
        $call->call_status,
        $edit_link . ' ' . $delete_link,
      ),
    );
  }
  $html = theme('table', array(
    'header' => $header,
    'rows'=>$rows,
    'caption' => 'Calls administration',
    'sticky' => TRUE,
    'empty' => 'No calls to show',
  ));
  $html .= theme('pager', array(
    'tags' => array(),
  ));
  return $html;
}

function _call_center_get_user_call_info(){
  // Retrieve user center information.
  global $user;
  $user = user_load($user->uid);
  $center_tid = (isset($user->call_center) && is_array($user->call_center) && count($user->call_center) > 0) ? $user->call_center[LANGUAGE_NONE][0]['tid'] : 0;
  // Execute DB query.
  $field_query = new EntityFieldQuery;
  $center_calls = $field_query
    ->entityCondition('entity_type', 'call_center')
    ->propertyCondition('type', 'call')
    ->fieldCondition('call_center', 'tid', $center_tid, '=')
    ->execute();
  $call_ids = array();
  $call_ids[] = 0;
  if (is_array($center_calls) && isset($center_calls['call_center'])) {
    foreach ($center_calls['call_center'] as $call_id => $call_info) {
      $call_ids[] = $call_id;
    }
  }
  return array(
    'center_tid' => $center_tid,
    'call_ids' => $call_ids,
  );
}

function _call_center_filter_form(&$form, &$form_state, $center_tid, $call_ids) {
  // Retrieve the last saved session values.
  $call_source_phone_value = _call_center_session('source_phone');
  $call_destination_phone_value = _call_center_session('destination_phone');
  $call_operator_value = _call_center_session('operator');
  $call_operator_ext_value = _call_center_session('operator_ext');
  // Regular filters.
  $form['call_source_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#size' => 20,
    '#maxlength' => 18,
    '#autocomplete_path' => 'call_center/autocomplete_source',
    '#default_value' => $call_source_phone_value,
    '#weight' => 1,
  );
  $form['call_destination_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination'),
    '#size' => 20,
    '#maxlength' => 18,
    '#autocomplete_path' => 'call_center/autocomplete_destination',
    '#default_value' => $call_destination_phone_value,
    '#weight' => 2,
  );
  
  // Retrieve the center operators form DB.
  $field_query = new EntityFieldQuery;
  $center_operators = $field_query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'operator')
    ->fieldCondition('call_center', 'tid', $center_tid, '=')
    ->execute();
  $options = array();
  $options[0] = t('All operators');
  if(isset($center_operators['node'])) {
    foreach($center_operators['node'] as $key => $node_value) {
      $node_full = node_load($node_value->nid);
      $options[$key] = $node_full->title;
    }
  }
  
  $operator_exposed_field_active = TRUE;
  if ($operator_exposed_field_active) {
    // Add the operator filter form element.
    $call_operator_value = (isset($form_state['values']['call_operator'])) ? $form_state['values']['call_operator'] : $call_operator_value;
    $form['call_operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#options' => $options,
      '#default_value' => _call_center_session('operator'),
      '#weight' => 5,
      '#ajax' => array(
        'event' => 'change',
        'callback' => '_call_center_ajax_extensions',
        'wrapper' => 'operator-extensions',
        //'method' => 'replace',
        //'effect' => 'fade',
      ),
    );
    $form['call_operator_extensions'] = array(
      '#type' => 'select',
      '#title' => t('Operator extensions'),
      '#options' => _call_center_get_extensions($call_operator_value),
      '#default_value' => _call_center_session('operator_ext'),
      '#weight' => 6,
      '#prefix' => '<div id="operator-extensions">',
      '#suffix' => '</div>',
    );
  }
  
  
  $form['actions'] = array(
    '#weight' => 99,
  );

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),
    '#submit' => $submit + array('call_center_filter_form_submit'),
    '#weight' => 100,
  );
  return $form;
}

function _call_center_ajax_extensions($form, $form_state) {
  return $form['call_operator_extensions'];
}

function _call_center_get_extensions($key = '') {
  $options = array();
  $options[0] = t('All extensions');
  $operator = node_load($key);
  $op_ext = ($operator) ? $operator->field_operator_extension[LANGUAGE_NONE] : array();
  foreach ($op_ext as $ext) {
    $val = $ext['value'];
    $options[$val] = $val;
  }
  return $options;
}

/* Added drupal_get_form call to module hook_menu (Not used) */
function call_center_create_exposed_filter_admin_form($form, &$form_state, $center_tid, $call_ids) {
  $form = array();
  //$form['filter'] = _call_center_filter_form($form, $form_state, $center_tid, $call_ids);
  _call_center_filter_form($form, $form_state, $center_tid, $call_ids);
  $form['#submit'][] = 'call_center_filter_form_submit';
  return $form;
}
