<?php
/**
 * @file
 * Handles the assignment of person object to a  project object
 */

/**
 * Defines a checkbox form used to assign people to projects
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 *
 *	Written by Quintin Dawson
 */
function islandora_bioinformatics_base_assign_person_to_project_form(array $form, array &$form_state) {
  

  return array(
	'form' => array(
		'#type' => 'checkboxes',
		'#options' => array(1 => "One" + "Four", 2 => "Two", 3 => "Three"),
		'#default_values' => array(1,3),
	),
  );
  
  
  /*
  echo 'Test echo';
  $upload_size = min((int) ini_get('post_max_size'), (int) ini_get('upload_max_filesize'));
  $extensions = array('gif png jpg jpeg');
  return array(
	'file' => array(
	  '#title' => t('Image'),
	  '#type' => 'managed_file',
	  '#required' => TRUE,
	  '#description' => t('Select image to upload.<br/>Files must be less than <b>@size MB.</b><br/>Allowed file types: <b>@ext.</b>', array('@size' => $upload_size, '@ext' => $extensions[0])),
	  '#default_value' => isset($form_state['values']['files']) ? $form_state['values']['files'] : NULL,
	  '#upload_location' => 'temporary://',
	  '#upload_validators' => array(
		'file_validate_extensions' => $extensions,
		// Assume its specified in MB.
		'file_validate_size' => array($upload_size * 1024 * 1024),
	  ),
	),
  );
  */
  
}

/**
 * Submit handler, creates a relation between the person an any selected objects.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_bioinformatics_base_assign_person_to_project_form_submit(array $form, array &$form_state) {
  $object = $form_state['islandora']['objects'][0];
  if (empty($object['IMG'])) {
	$ds = $object->constructDatastream('IMG', 'M');
	$object->ingestDatastream($ds);
  }
  else {
	$ds = $object['IMG'];
  }
  $file = file_load($form_state['values']['file']);
  $path = drupal_realpath($file->uri);
  $ds->setContentFromFile($path, FALSE);
  $ds->label = $file->filename;
  $ds->mimetype = $file->filemime;
}
