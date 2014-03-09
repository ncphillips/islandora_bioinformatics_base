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
  $tuque = new IslandoraTuque();
  $query = "SELECT ?pid
                    FROM <#ri>
                    WHERE {
                    ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
                    }";
  $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');
  
   $people = array();
   foreach($result as $person) {
	 $people[$person["pid"]["value"]] = $person["pid"]["value"];
   }
  
   return array(
	'form' => array(
		'#type' => 'checkboxes',
		'#options' => $people,
	),
   );    
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
  $tuque = new IslandoraTuque();
  $person_object = $tuque->repository->getObject("islandora:192");
  //echo $person_object->id;  //display the pid for the object
  
  $person_ids = array_filter($form_state['values']['form']);
  foreach($person_ids as $person)  {
	echo $person;
  }
  
  /*
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
  */
}
