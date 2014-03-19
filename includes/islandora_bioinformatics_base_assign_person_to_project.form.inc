<?php
/**
 * @file
 * Handles the assignment of person object to a  project object
 *
 * @author Quintin Dawson
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
 */
function islandora_bioinformatics_base_assign_person_to_project_form(array $form, array &$form_state) {
	$tuque = new IslandoraTuque();
	  
	$project_object = $form_state['islandora']['objects'][0];
	$project_object->relationships->add("info:fedora/" . 'islandora:388', 'hasModel', 'islandora:person_cmodel');
		
	$query = 	"SELECT ?pid
					FROM <#ri>
					WHERE {
					?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
				}";
	$result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');	
 	
   //build the checkboxes form, with default values.
   $people = array();
   $default_values = array();	//determines which values are automatically selected
   foreach($result as $person) {
	$people[$person["pid"]["value"]] = islandora_object_load($person["pid"]["value"])->label; //$person["pid"]["value"];
	 
	$uri = "info:fedora/" . $person["pid"]["value"];
	$relationship = $project_object->relationships->get($uri, 'hasModel');
		
	if(!empty($relationship)) {	//if relationship exists, add it to $default_values
	 	$default_values[$person["pid"]["value"]] = $person["pid"]["value"];
	 }
   }
  
   return array(
	'people' => array(
		'#type' => 'checkboxes',
		'#default_value' => $default_values,
		'#options' => $people,
	),
   ); 	
}

/**
 * Submit handler, creates a relation between the project an any selected persons.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_bioinformatics_base_assign_person_to_project_form_submit(array $form, array &$form_state) {
	$tuque = new IslandoraTuque();
  
	//retrieves the relevant fedora project object
	$project_object = $form_state['islandora']['objects'][0];
	//echo $project_object->id;
	
	//get the checkboxes submitted (only those checked are submitted)  
	$person_ids = array_filter($form_state['values']['people']);
   
    
	//iterate over every person and remove their relationship (if it exists) with the project.
	$query = 	"SELECT ?pid
					FROM <#ri>
					WHERE {
					?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
				}";
	$result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');	
	
	foreach($result as $person) {
		$person_object = islandora_object_load($person['pid']['value']);	//loads object
		//$person_object->relationships->remove(FEDORA_MODEL_URI, 'isMemberOf', $project_object->id);
	}
	
	//for each person checked, create a relationship between the person and the project
	foreach($person_ids as $id)  {
		//create a relationship within the current person object to the project
		$person_object = islandora_object_load($id);	//loads object
		$person_object->relationships->add(FEDORA_MODEL_URI, 'isMemberOf', $project_object->id);
	}
}
