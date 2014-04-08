<?php

class CallCenterController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    $values += array(
      'name' => '',
      'call_date' => '',
      'call_source_phone' => '',
      'call_destination_phone' => '',
      'call_status' => '',
      'call_duration' => '',
      'uid' => $user->uid,
      'call_center' => NULL,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'status' => 1,
    );
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('call_center', $entity);
    
    //$content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));
    //$content['name'] = array('#markup' => $entity->name);
    
    /*
    // Make Description and Status themed like default fields.
    $content['description'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Description'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'call_center',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->description)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->description))
    );
    */

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
  
}

/**
 * CallCentetEntity Views Controller class.
 */
class CallCenterViewsController extends EntityDefaultViewsController {

	/**
	 * Edit or add extra fields to views_data().
	 */
	public function views_data() {
		$data = parent::views_data();

		// Add your custom data here

		/*
		 * Example: change the handler of a field
		* if the 'created' field is a unix timestamp in the database,
		* Entity API will set the handler to views_handler_field_numeric,
		* change this to the views date handler
		*/
		$data['call_center']['created']['field']['handler'] = 'views_handler_field_date';

		return $data;
	}
}

class CallCenterTypeController extends EntityAPIControllerExportable {
   public function create(array $values = array()) {
    $values += array(
      'label' => '',
      'description' => '',
    );
    return parent::create($values);
  }

  /**
   * Save Call Center Entity Type.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
    // Rebuild menu registry. We do not call menu_rebuild directly, but set
    // variable that indicates rebuild in the end.
    // @see http://drupal.org/node/1399618
    variable_set('menu_rebuild_needed', TRUE);
  }
}

/**
 * UI controller for Call Center Entity Type.
 */
class CallCenterTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Call Center Entities types.';
    return $items;
  }
}

/**
 * Call Center Entity class.
 */
class CallCenter extends Entity {
  protected function defaultLabel() {
    return $this->name;
  }

  protected function defaultUri() {
    return array('path' => 'call_center/' . $this->identifier());
  }
}

/**
 * Call Center Entity Type class.
 */
class CallCenterType extends Entity {
  public $type;
  public $label;
  public $weight = 0;

  public function __construct($values = array()) {
    parent::__construct($values, 'call_center_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}
