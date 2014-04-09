<?php

/**
 * Call center Entity view callback.
 */
function call_center_view($call_info, $view_mode = 'full') {
  drupal_set_title(entity_label('call_center', $call_info));
  $ev = entity_view('call_center', array(entity_id('call_center', $call_info) => $call_info), $view_mode);
  return $ev;
}
