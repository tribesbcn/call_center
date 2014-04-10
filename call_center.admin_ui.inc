<?php

function call_center_admin_view($form, &$form_state) {
  // Retrieve the user information.
  $user_call_info = _call_center_get_user_call_info();
  $center_tid = $user_call_info['center_tid'];
  $call_ids = $user_call_info['call_ids'];
  // Retrieve the last submited session values.
  $call_date_from_value = _call_center_session('date_from');
  $call_date_to_value = _call_center_session('date_to');
  $call_source_phone_value = _call_center_session('source_phone');
  $call_destination_phone_value = _call_center_session('destination_phone');
  $call_operator_value = _call_center_session('operator');
  $call_max_minutes_value = _call_center_session('max_minutes');
  $call_operator_ext_value = _call_center_session('operator_ext');
  $call_operator_ext_full = _call_center_session('operator_ext_full');
  
  $header = _call_center_table_header();  
  $results = _call_center_filtered_query(
    $call_ids,
    $call_date_from_value,
    $call_date_to_value,
    $call_source_phone_value, 
    $call_destination_phone_value, 
    $call_max_minutes_value, 
    $call_operator_value, 
    $call_operator_ext_value, 
    $call_operator_ext_full, 
    TRUE,
    $header
  );
  
  $html_table = _call_center_create_sortable_table($header, $results);
  _call_center_filter_form($form, $form_state, $center_tid, $call_ids);
  $form['#submit'][] = 'call_center_filter_form_submit';
  // Print the table result.
  $html = $html_table;
  $form['table'] = array(
    '#type' => 'markup',
    '#markup' => $html,
    '#weight' => 200,
  );
  //return $html;
  return $form;
}

function call_center_export_csv() {
  // Retrieve the user information.
  $user_call_info = _call_center_get_user_call_info();
  $center_tid = $user_call_info['center_tid'];
  $call_ids = $user_call_info['call_ids'];
  // Retrieve the last submited session values.
  $call_date_from_value = _call_center_session('date_from');
  $call_date_to_value = _call_center_session('date_to');
  $call_source_phone_value = _call_center_session('source_phone');
  $call_destination_phone_value = _call_center_session('destination_phone');
  $call_operator_value = _call_center_session('operator');
  $call_max_minutes_value = _call_center_session('max_minutes');
  $call_operator_ext_value = _call_center_session('operator_ext');
  $call_operator_ext_full = _call_center_session('operator_ext_full');
  
  $header = _call_center_csv_header();
  $results = _call_center_filtered_query(
    $call_ids,
    $call_date_from_value,
    $call_date_to_value,
    $call_source_phone_value, 
    $call_destination_phone_value, 
    $call_max_minutes_value, 
    $call_operator_value, 
    $call_operator_ext_value, 
    $call_operator_ext_full, 
    FALSE
  );
  $rows_array = _call_center_create_csv_rows($results);
  _call_center_export_to_excel_page($header, $rows_array);
}

function call_center_filter_form_submit($form, &$form_state) {
  // Retrieve the form_state values and save it in session.
  $call_date_from = (isset($form_state['values']['call_date_from'])) ? $form_state['values']['call_date_from'] : '';
  $call_date_to = (isset($form_state['values']['call_date_to'])) ? $form_state['values']['call_date_to'] : '';
  $call_source_phone_value = (isset($form_state['values']['call_source_phone'])) ? $form_state['values']['call_source_phone'] : '';
  $call_destination_phone_value = isset($form_state['values']['call_destination_phone']) ? $form_state['values']['call_destination_phone'] : '';
  $call_max_minutes_value = (isset($form_state['values']['max_minutes'])) ? $form_state['values']['max_minutes'] : '00';
  
  $call_operator_value = (isset($form_state['values']['call_operator'])) ? $form_state['values']['call_operator'] : 0;
  $call_operator_ext_value = (isset($form_state['values']['call_operator_extensions']) && $form_state['values']['call_operator_extensions'] != '0') ? array($form_state['values']['call_operator_extensions']) : array();
  if (!count($call_operator_ext_value)) {
    $operator_available_extensions = $form['call_operator_extensions']['#options'];
    foreach ($operator_available_extensions as $key => $value) {
      $call_operator_ext_value[] = $key;
    }
  }
  _call_center_session('date_from', $call_date_from);
  _call_center_session('date_to', $call_date_to);
  _call_center_session('source_phone', $call_source_phone_value);
  _call_center_session('destination_phone', $call_destination_phone_value);
  _call_center_session('max_minutes', $call_max_minutes_value);
  _call_center_session('operator', $call_operator_value);
  _call_center_session('operator_ext', $call_operator_ext_value);
}

function _call_center_filtered_query($call_ids, $date_from = '', $date_to = '', $source_phone = '', $destination_phone = '', $max_minutes = '00', $operator = 0, $operator_ext = 0, $operator_ext_full = 0, $paged = TRUE, $header = NULL) {
  global $user;
  $timezone = $user->timezone;
  // Execute query.  
  $query = db_select('call_center', 'cc')->extend('PagerDefault')->limit(25)->extend('TableSort')->orderByHeader($header);
  if (!$paged) {
    $query = db_select('call_center', 'cc');
  }
  $query->fields ('cc', array ('id', 'call_date', 'call_source_phone', 'call_destination_phone', 'call_duration', 'call_status'))
    ->condition('id', $call_ids,'IN');
  
  if ($date_from != '') {
    $date_from_info = new DateTime($date_from, new DateTimeZone($timezone));
    $date_from_timestamp = $date_from_info->getTimestamp();
    $query->condition('call_date', $date_from_timestamp, '>=');
  }
  if ($date_to != '') {
    $date_to_info = new DateTime($date_to, new DateTimeZone($timezone));
    $date_to_timestamp = $date_to_info->getTimestamp();
    $query->condition('call_date', $date_to_timestamp, '<=');
  } 
  
  if ($source_phone != '') $query->condition('call_source_phone', db_like($source_phone) . '%', 'LIKE');
  if ($destination_phone != '') $query->condition('call_destination_phone', db_like($destination_phone) . '%', 'LIKE');
  if ($max_minutes != '00') {
    $filter_time = '00:' . $max_minutes . ':00';
    $query->condition('call_duration', $filter_time, '>=');
  }
  if ($operator != 0) {
    if ($operator_ext != 0) {
      $query->condition('call_destination_phone', $operator_ext, '=');
    }
    else {
      // Retrieve all operator extensions and create the query.
      $or_condition = db_or();
      $num_extensions = 0;
      foreach($operator_ext_full as $ext) {
        if ($ext != '0') {
          $or_condition->condition('call_destination_phone', $ext, '=');
          $num_extensions++;
        }
      }
      if ($num_extensions) {
        $query->condition($or_condition);
      }
    }
  }
  //dpm((string) $query);
  //dpm($query->arguments());
  $results = $query->execute();
  return $results;
}

function _call_center_export_to_excel_page($column_titles, $row_array) {
  $filename = 'export.csv';
  drupal_set_header('Content-Type: text/csv');
  drupal_set_header('Content-Disposition: attachment; filename=' . $filename);

  foreach($column_titles as $key => $value) {
    $keys[] =$value;         
  }
  if($keys) print implode(',', $keys) ."\r\n";
  unset($keys);
  // Fetching the field values
  foreach($row_array as $key => $value) {
    $values[] =$value;
  }
  print implode(',', $values) ."\r\n";
  unset($values);
}

function _call_center_session($key, $value = NULL) {
  if (!is_null($value)) {
    $_SESSION['call_center'][$key] = $value;
  }
  else if (isset($_SESSION['call_center'][$key])) {
    $key_value = $_SESSION['call_center'][$key];
    // Return values (special tratement for operator_ext key)
    if ($key == 'operator_ext' && is_array($key_value) && count($key_value) > 0) {
      return (count($key_value) == 1) ? reset($key_value) : 0;
    }
    return $key_value;
  }
  else if ($key == 'operator_ext_full') {
    return isset($_SESSION['call_center']['operator_ext']) ? $_SESSION['call_center']['operator_ext'] : 0;
  }
}

function _call_center_table_header() {
  return array(
    array('data' => t('Id'), 'field' => 'id', 'sort' => 'asc'),
    array('data' => t('Date'), 'field' => 'call_date'),
    array('data' => t('Source'), 'field' => 'call_source_phone'),
    array('data' => t('Destination'), 'field' => 'call_destination_phone'),
    array('data' => t('Duration'), 'field' => 'call_duration'),
    array('data' => t('Status'), 'field' => 'call_status'),
    array('data' => t('Operations')),
  );
}

function _call_center_csv_header() {
  return array(
    t('Id'), 
    t('Date'), 
    t('Source phone'), 
    t('Detination phone'), 
    t('Duration'), 
    t('Status'),
  );
}

function _call_center_sum_duration_time($time1, $time2) {
  $times = array($time1, $time2);
  $seconds = 0;
  foreach ($times as $time) {
    list($hour,$minute,$second) = explode(':', $time);
    $seconds += $hour*3600;
    $seconds += $minute*60;
    $seconds += $second;
  }
  $hours = floor($seconds/3600);
  $seconds -= $hours*3600;
  $minutes  = floor($seconds/60);
  $seconds -= $minutes*60;
  // return "{$hours}:{$minutes}:{$seconds}";
  return sprintf('%02d:%02d:%02d', $hours, $minutes, $seconds);
}

function _call_center_create_sortable_table($header, $results) {
  // Prepare table rows.
  $rows = array();
  $num_calls = 0;
  $total_duration = '00:00:00';
  foreach ($results as $call) {
    $edit_link = l('<img src="/sites/default/graphics/admin/application--pencil.png" title="Edit" alt="Edit"/>', 'call_center/'. $call->id .'/edit', array('html' => TRUE));
    $delete_link = l('<img src="/sites/default/graphics/admin/cross-script.png" title="Delete" alt="Delete"/>', 'call_center/'. $call->id .'/delete', array('html' => TRUE));
    $call_duration = $call->call_duration;
    $rows[] = array(
      'data' => array(
        $call->id, 
        format_date($call->call_date), 
        $call->call_source_phone, 
        $call->call_destination_phone, 
        $call_duration,
        $call->call_status,
        $edit_link . ' ' . $delete_link,
      ),
    );
    $num_calls++;
    $total_duration = _call_center_sum_duration_time($total_duration, $call_duration);
  }
  $rows[] = array(
    'data' => array(
      $num_calls, 
      '', 
      '', 
      '', 
      $total_duration,
      '',
      '',
    ),
  );
  $html = theme('table', array(
    'header' => $header,
    'rows'=> $rows,
    'caption' => 'Calls administration',
    'sticky' => TRUE,
    'empty' => 'No calls to show',
  ));
  $html .= theme('pager', array(
    'tags' => array(),
  ));
  return $html;
}

function _call_center_create_csv_rows($results) {
  // Prepare table rows.
  $rows = array();
  foreach ($results as $call) {
    $rows[] = array(
      $call->id, 
      format_date($call->call_date), 
      $call->call_source_phone, 
      $call->call_destination_phone, 
      $call->call_duration,
      $call->call_status,
      $edit_link . ' ' . $delete_link,
    );
  }
  return $rows;
}

function _call_center_filter_form(&$form, &$form_state, $center_tid, $call_ids) {
  // Export CSV link
  $form['export_csv'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Export CSV'), 'admin/calls/export_csv', array('attributes' => array('target'=>'_blank'))),
    '#prefix' => '<div id="export-csv-link">',
    '#suffix' => '</div>',
    '#weight' => -20,
  );
  // Retrieve the last saved session values.
  $call_date_from_value = _call_center_session('date_from');
  $call_date_to_value = _call_center_session('date_to');
  $call_source_phone_value = _call_center_session('source_phone');
  $call_destination_phone_value = _call_center_session('destination_phone');
  $call_max_minutes_value = _call_center_session('max_minutes');
  $call_operator_value = _call_center_session('operator');
  $call_operator_ext_value = _call_center_session('operator_ext');
  // Regular filters.
  $form['call_date_from'] = array(
    '#title'=>t('Date from?'),
    '#default_value' => $call_date_from_value,
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '0:+1',
    '#type' => 'date_popup',
    '#weight'=> -2,
  );
  $form['call_date_to'] = array(
    '#title'=>t('Date to?'),
    '#default_value' => $call_date_to_value,
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '0:+1',
    '#type' => 'date_popup',
    '#weight'=> -1,
    '#suffix' => '<div id="break-line-div"></div>',
  );
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
  $max_minutes_exposed_filter = TRUE;
  if ($max_minutes_exposed_filter) {
    $form['max_minutes'] = array(
      '#type' => 'select',
      '#title' => t('Duration greater than'),
      '#options' => array(
        '00' => t('No limit'),
        '01' => t('1 minute'),
        '05' => t('5 minutes'),
        '10' => t('10 minutes'),
        '15' => t('15 minutes'),
        '30' => t('30 minutes'),
        '45' => t('45 minutes'),
        '60' => t('1 hour'),
      ),
      '#default_value' => _call_center_session('max_minutes'),
      '#weight' => 3,
    );
  }
  $operator_exposed_filter = TRUE;
  if ($operator_exposed_filter) {
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
