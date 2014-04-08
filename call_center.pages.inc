<?php

/**
 * Call center Entity view callback.
 */
function call_center_view($call_info, $view_mode = 'full') {
  //dpm($call_info);
  drupal_set_title(entity_label('call_center', $call_info));
  $ev = entity_view('call_center', array(entity_id('call_center', $call_info) => $call_info), $view_mode);
  //dpm($ev);
  return $ev;
}

function call_center_admin_view() {
  // Retrieve user center information.
  global $user;
  $user = user_load($user->uid);
  $center_tid = (isset($user->call_center) && is_array($user->call_center) && count($user->call_center) > 0) ? $user->call_center[LANGUAGE_NONE][0]['tid'] : 0;
  // Prepare table headers.
  $header = array(
    array('data' => 'Id', 'field' => 'id', 'sort' => 'asc'),
    array('data' => 'Date', 'field' => 'call_date'),
    array('data' => 'Source', 'field' => 'call_source_phone'),
    array('data' => 'Destination', 'field' => 'call_destination_phone'),
    array('data' => 'Duration', 'field' => 'call_duration'),
    array('data' => 'Status', 'field' => 'call_status'),
    array('data' => 'Operations'),
  );
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
  $query = db_select('call_center', 'cc')
    ->condition('id', $call_ids,'IN')
    ->extend('PagerDefault')->limit(25)
    ->extend('TableSort')->orderByHeader($header)
    ->fields ('cc', array ('id', 'call_date', 'call_source_phone', 'call_destination_phone', 'call_duration', 'call_status'));
  $results = $query->execute();
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
  $params = array(
    'center_tid' => $center_tid,
    'call_ids' => $call_ids,
  );
  $exposed_filter_form = drupal_get_form('call_center_create_exposed_filter_admin_form', $center_tid, $call_ids);
  $html = render($exposed_filter_form);
  $html .= theme('table', array(
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

function call_center_create_exposed_filter_admin_form($form, &$form_state, $center_tid, $call_ids) {
  $form = array();
  $form['filter'] = call_center_filter_form($form_state, $center_tid, $call_ids);
  $form['#submit'][] = 'call_center_filter_form_submit';
  return $form;
}

function call_center_filter_form($form_state, $center_tid, $call_ids) {
  $filters = array();
  // Regular filters
  $call_source_phone_value = isset($form_state['values']['call_source_phone']) ? $form_state['values']['call_source_phone'] : '';
  $filters['call_source_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#size' => 20,
    '#maxlength' => 18,
    '#autocomplete_path' => 'call_center/autocomplete_source',
    '#default_value' => $call_source_phone_value,
    '#weight' => 1,
  );
  $call_destination_phone_value = isset($form_state['values']['call_destination_phone']) ? $form_state['values']['call_destination_phone'] : '';
  $filters['call_destination_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination'),
    '#size' => 20,
    '#maxlength' => 18,
    '#autocomplete_path' => 'call_center/autocomplete_destination',
    '#default_value' => $call_destination_phone_value,
    '#weight' => 2,
  );
  
  // Retrieve the center operators form DB
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
    $call_operator_value = isset($form_state['values']['call_operator']) ? $form_state['values']['call_operator'] : key($options);
    // Add the operator filter form element.
    $html_suffix = '<div id="operator-extensions"></div>';
    $filters['call_operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#options' => $options,
      '#default_value' => $call_operator_value,
      '#weight' => 5,
      //'#suffix' => $html_suffix,
      '#ajax' => array(
        //'callback' => 'call_center_get_operator_extensions',
        'event' => 'change',
        'callback' => 'call_center_ajax_extensions',
        'wrapper' => 'operator-extensions',
        //'method' => 'replace',
        //'effect' => 'fade',
      ),
    );
    $filters['call_operator_extensions'] = array(
      '#type' => 'select',
      '#title' => t('Operator extensions'),
      '#options' => call_center_get_extensions($call_operator_value),
      '#default_value' => 0,
      '#weight' => 6,
      '#prefix' => '<div id="operator-extensions">',
      '#suffix' => '</div>',
    );
  }
  
  
  $filters['actions'] = array(
    '#weight' => 99,
  );

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  
  $filters['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),
    '#submit' => $submit + array('call_center_filter_form_submit'),
    '#weight' => 100,
  );

  return $filters;
}

function call_center_ajax_extensions($form, $form_state) {
  return $form['call_operator_extensions'];
}

function call_center_get_extensions($key = '') {
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

function call_center_filter_form_submit($form, &$form_state) {
  dpm($form_state);
  $form_state['redirect'] = 'admin/calls';
}
