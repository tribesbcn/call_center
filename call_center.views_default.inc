<?php

/**
 * Implements hook_views_default_views().
 */
function call_center_views_default_views() {
	$views = array();
	
  $view = new view();
  $view->name = 'call_center';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'call_center';
  $view->human_name = 'Call Center Administration';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Call Center Administration';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer call_center entities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'call_date' => array(
      'bef_format' => 'bef_slider',
      'slider_options' => array(
        'bef_slider_min' => '1395043283',
        'bef_slider_max' => '1396340066',
        'bef_slider_step' => '1',
        'bef_slider_animate' => '',
        'bef_slider_orientation' => 'horizontal',
      ),
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'call_date_1' => array(
      'bef_format' => 'bef_slider',
      'slider_options' => array(
        'bef_slider_min' => '1395043483',
        'bef_slider_max' => '1396340266',
        'bef_slider_step' => '1',
        'bef_slider_animate' => '',
        'bef_slider_orientation' => 'horizontal',
      ),
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'call_source_phone' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'call_destination_phone' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'call_status' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« primera';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ anterior';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'siguiente ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'última »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'call_date' => 'call_date',
    'php' => 'php',
    'call_source_phone' => 'call_source_phone',
    'call_destination_phone' => 'call_destination_phone',
    'call_duration' => 'call_duration',
    'call_status' => 'call_status',
    'created' => 'created',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing_1',
  );
  $handler->display->display_options['style_options']['default'] = 'id';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'call_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'call_source_phone' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'call_destination_phone' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'call_duration' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'call_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Call Center: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'call_center';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'Author';
  /* Field: Call Center: Call center ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'call_center';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Id';
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Call Center: Call_date */
  $handler->display->display_options['fields']['call_date']['id'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_date']['field'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['label'] = '';
  $handler->display->display_options['fields']['call_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['call_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['call_date']['separator'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Date';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'return format_date($row->call_date);';
  $handler->display->display_options['fields']['php']['php_output'] = '<?=$value?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '6';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = 'return $row1->call_date - $row2->call_date;';
  /* Field: Call Center: Call_source_phone */
  $handler->display->display_options['fields']['call_source_phone']['id'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_source_phone']['field'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['label'] = 'Source';
  $handler->display->display_options['fields']['call_source_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_destination_phone */
  $handler->display->display_options['fields']['call_destination_phone']['id'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_destination_phone']['field'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['label'] = 'Destination';
  $handler->display->display_options['fields']['call_destination_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_duration */
  $handler->display->display_options['fields']['call_duration']['id'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_duration']['field'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['label'] = 'Duration';
  $handler->display->display_options['fields']['call_duration']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_status */
  $handler->display->display_options['fields']['call_status']['id'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_status']['field'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['label'] = 'Status';
  $handler->display->display_options['fields']['call_status']['element_label_colon'] = FALSE;
  /* Field: Call Center: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'call_center';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Import date';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Edit */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Edit';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<img src="/sites/default/graphics/admin/application--pencil.png" title="Edit" alt="Edit"/>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'call_center/[id]/edit';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Delete */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Delete';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<img src="/sites/default/graphics/admin/cross-script.png" title="Delete" alt="Delete"/>';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'call_center/[id]/delete';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_destination_phone */
  $handler->display->display_options['fields']['call_destination_phone_1']['id'] = 'call_destination_phone_1';
  $handler->display->display_options['fields']['call_destination_phone_1']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_destination_phone_1']['field'] = 'call_destination_phone';
  /* Contextual filter: Call Center: Call_destination_phone */
  $handler->display->display_options['arguments']['call_destination_phone']['id'] = 'call_destination_phone';
  $handler->display->display_options['arguments']['call_destination_phone']['table'] = 'call_center';
  $handler->display->display_options['arguments']['call_destination_phone']['field'] = 'call_destination_phone';
  $handler->display->display_options['arguments']['call_destination_phone']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['call_destination_phone']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['call_destination_phone']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['call_destination_phone']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['call_destination_phone']['limit'] = '0';
  /* Contextual filter: Call Center: Call_source_phone */
  $handler->display->display_options['arguments']['call_source_phone']['id'] = 'call_source_phone';
  $handler->display->display_options['arguments']['call_source_phone']['table'] = 'call_center';
  $handler->display->display_options['arguments']['call_source_phone']['field'] = 'call_source_phone';
  $handler->display->display_options['arguments']['call_source_phone']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['call_source_phone']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['call_source_phone']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['call_source_phone']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['call_source_phone']['limit'] = '0';
  /* Filter criterion: Call Center: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'call_center';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'call' => 'call',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  
  
  
  /* Filter criterion: Operator: call_operator */
  
  /*
  $handler->display->display_options['filters']['call_operator']['id'] = 'call_operator';
  $handler->display->display_options['filters']['call_operator']['table'] = 'call_center';
  $handler->display->display_options['filters']['call_operator']['field'] = 'call_destination_phone';
  $handler->display->display_options['filters']['call_operator']['operator'] = 'contains';
  $handler->display->display_options['filters']['call_operator']['group'] = 1;
  $handler->display->display_options['filters']['call_operator']['exposed'] = TRUE;
  $handler->display->display_options['filters']['call_operator']['expose']['operator_id'] = 'call_destination_phone_op';
  $handler->display->display_options['filters']['call_operator']['expose']['label'] = 'Destination phone';
  $handler->display->display_options['filters']['call_operator']['expose']['operator'] = 'call_destination_phone_op';
  $handler->display->display_options['filters']['call_operator']['expose']['identifier'] = 'call_operator';
  $handler->display->display_options['filters']['call_operator']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['call_operator']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['call_operator']['expose']['autocomplete_field'] = 'call_operator';
  $handler->display->display_options['filters']['call_operator']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['call_operator']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['call_operator']['expose']['autocomplete_dependent'] = 0;
  */
  
  
  /* Filter criterion: Call Center: Call_destination_phone */
  $handler->display->display_options['filters']['call_destination_phone']['id'] = 'call_destination_phone';
  $handler->display->display_options['filters']['call_destination_phone']['table'] = 'call_center';
  $handler->display->display_options['filters']['call_destination_phone']['field'] = 'call_destination_phone';
  $handler->display->display_options['filters']['call_destination_phone']['operator'] = 'contains';
  $handler->display->display_options['filters']['call_destination_phone']['group'] = 1;
  $handler->display->display_options['filters']['call_destination_phone']['exposed'] = TRUE;
  $handler->display->display_options['filters']['call_destination_phone']['expose']['operator_id'] = 'call_destination_phone_op';
  $handler->display->display_options['filters']['call_destination_phone']['expose']['label'] = 'Destination phone';
  $handler->display->display_options['filters']['call_destination_phone']['expose']['operator'] = 'call_destination_phone_op';
  $handler->display->display_options['filters']['call_destination_phone']['expose']['identifier'] = 'call_destination_phone';
  $handler->display->display_options['filters']['call_destination_phone']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['call_destination_phone']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['call_destination_phone']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['call_destination_phone']['expose']['autocomplete_field'] = 'call_destination_phone';
  $handler->display->display_options['filters']['call_destination_phone']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['call_destination_phone']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['call_destination_phone']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Call Center: Call_source_phone */
  $handler->display->display_options['filters']['call_source_phone']['id'] = 'call_source_phone';
  $handler->display->display_options['filters']['call_source_phone']['table'] = 'call_center';
  $handler->display->display_options['filters']['call_source_phone']['field'] = 'call_source_phone';
  $handler->display->display_options['filters']['call_source_phone']['operator'] = 'contains';
  $handler->display->display_options['filters']['call_source_phone']['group'] = 1;
  $handler->display->display_options['filters']['call_source_phone']['exposed'] = TRUE;
  $handler->display->display_options['filters']['call_source_phone']['expose']['operator_id'] = 'call_source_phone_op';
  $handler->display->display_options['filters']['call_source_phone']['expose']['label'] = 'Source Phone';
  $handler->display->display_options['filters']['call_source_phone']['expose']['operator'] = 'call_source_phone_op';
  $handler->display->display_options['filters']['call_source_phone']['expose']['identifier'] = 'call_source_phone';
  $handler->display->display_options['filters']['call_source_phone']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['call_source_phone']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['call_source_phone']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['call_source_phone']['expose']['autocomplete_field'] = 'call_source_phone';
  $handler->display->display_options['filters']['call_source_phone']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['call_source_phone']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['call_source_phone']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  $handler->display->display_options['filters']['uid_current']['group'] = 1;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'call_destination_phone' => 'call_destination_phone',
    'call_destination_phone_1' => 'call_destination_phone_1',
  );
  
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Call Center: Call center ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'call_center';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Id';
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Call Center: Call_date */
  $handler->display->display_options['fields']['call_date']['id'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_date']['field'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['label'] = '';
  $handler->display->display_options['fields']['call_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['call_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['call_date']['separator'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Date';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'return format_date($row->call_date);';
  $handler->display->display_options['fields']['php']['php_output'] = '<?=$value?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '6';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = 'return $row1->call_date - $row2->call_date;';
  /* Field: Call Center: Call_source_phone */
  $handler->display->display_options['fields']['call_source_phone']['id'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_source_phone']['field'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['label'] = 'Source';
  $handler->display->display_options['fields']['call_source_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_destination_phone */
  $handler->display->display_options['fields']['call_destination_phone']['id'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_destination_phone']['field'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['label'] = 'Destination';
  $handler->display->display_options['fields']['call_destination_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_destination_phone */
  $handler->display->display_options['fields']['call_destination_phone_1']['id'] = 'call_destination_phone_1';
  $handler->display->display_options['fields']['call_destination_phone_1']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_destination_phone_1']['field'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone_1']['label'] = 'Destination 2';
  $handler->display->display_options['fields']['call_destination_phone_1']['exclude'] = TRUE;
  /* Field: Call Center: Call_duration */
  $handler->display->display_options['fields']['call_duration']['id'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_duration']['field'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['label'] = 'Duration';
  $handler->display->display_options['fields']['call_duration']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_status */
  $handler->display->display_options['fields']['call_status']['id'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_status']['field'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['label'] = 'Status';
  $handler->display->display_options['fields']['call_status']['element_label_colon'] = FALSE;
  /* Field: Call Center: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'call_center';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Import date';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Edit */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Edit';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<img src="/sites/default/graphics/admin/application--pencil.png" title="Edit" alt="Edit"/>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'call_center/[id]/edit';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Delete */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Delete';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<img src="/sites/default/graphics/admin/cross-script.png" title="Delete" alt="Delete"/>';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'call_center/[id]/delete';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/calls_old';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Calls';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Call Center: Call center ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'call_center';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Id';
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Call Center: Call_date */
  $handler->display->display_options['fields']['call_date']['id'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_date']['field'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['label'] = '';
  $handler->display->display_options['fields']['call_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['call_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['call_date']['separator'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Date';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'return format_date($row->call_date);';
  $handler->display->display_options['fields']['php']['php_output'] = '<?=$value?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '6';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = 'return $row1->call_date - $row2->call_date;';
  /* Field: Call Center: Call_source_phone */
  $handler->display->display_options['fields']['call_source_phone']['id'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_source_phone']['field'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['label'] = 'Source';
  $handler->display->display_options['fields']['call_source_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_destination_phone */
  $handler->display->display_options['fields']['call_destination_phone']['id'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_destination_phone']['field'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['label'] = 'Destination';
  $handler->display->display_options['fields']['call_destination_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_duration */
  $handler->display->display_options['fields']['call_duration']['id'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_duration']['field'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['label'] = 'Duration';
  $handler->display->display_options['fields']['call_duration']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_status */
  $handler->display->display_options['fields']['call_status']['id'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_status']['field'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['label'] = 'Status';
  $handler->display->display_options['fields']['call_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/calls_old/export_xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Call Center: Call center ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'call_center';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Id';
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Call Center: Call_date */
  $handler->display->display_options['fields']['call_date']['id'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_date']['field'] = 'call_date';
  $handler->display->display_options['fields']['call_date']['label'] = '';
  $handler->display->display_options['fields']['call_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['call_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['call_date']['separator'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Date';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'return format_date($row->call_date);';
  $handler->display->display_options['fields']['php']['php_output'] = '<?=$value?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '6';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = 'return $row1->call_date - $row2->call_date;';
  /* Field: Call Center: Call_source_phone */
  $handler->display->display_options['fields']['call_source_phone']['id'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_source_phone']['field'] = 'call_source_phone';
  $handler->display->display_options['fields']['call_source_phone']['label'] = 'Source';
  $handler->display->display_options['fields']['call_source_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_destination_phone */
  $handler->display->display_options['fields']['call_destination_phone']['id'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_destination_phone']['field'] = 'call_destination_phone';
  $handler->display->display_options['fields']['call_destination_phone']['label'] = 'Destination';
  $handler->display->display_options['fields']['call_destination_phone']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_duration */
  $handler->display->display_options['fields']['call_duration']['id'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_duration']['field'] = 'call_duration';
  $handler->display->display_options['fields']['call_duration']['label'] = 'Duration';
  $handler->display->display_options['fields']['call_duration']['element_label_colon'] = FALSE;
  /* Field: Call Center: Call_status */
  $handler->display->display_options['fields']['call_status']['id'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['table'] = 'call_center';
  $handler->display->display_options['fields']['call_status']['field'] = 'call_status';
  $handler->display->display_options['fields']['call_status']['label'] = 'Status';
  $handler->display->display_options['fields']['call_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/calls_old/export_csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
    
  
	$views['call_center'] = $view;
	
	return $views;
}
