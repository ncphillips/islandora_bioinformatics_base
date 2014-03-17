<?php
/**
 * @file
 * Handles the uploading of the image file.
 */

/**
 * Defines a file upload form for uploading the basic image.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 *
 *	Written by Quintin Dawson - taken largely from the Islandora/islandora_solution_pack_image
 */
 function islandora_bioinformatics_base_image_upload_form(array $form, array &$form_state) {
  $upload_size = min((int) ini_get('post_max_size'), (int) ini_get('upload_max_filesize'));
  $extensions = array('gif png jpg jpeg');
  return array(
	'file' => array(
	  '#title' => t('Image'),
	  '#type' => 'managed_file',
	  '#required' => FALSE,
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
}

/**
 * Submit handler, adds uploaded file to ingest object.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_bioinformatics_base_image_upload_form_submit(array $form, array &$form_state) {
	if(isset($form_state['islandora']['objects'][0])) {
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
  
  
}
