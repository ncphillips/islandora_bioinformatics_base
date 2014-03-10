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
  //echo '<pre>';
  //echo  var_dump($form_state['islandora']['objects']);
  //echo '</pre>';
  
  //echo $form_state['islandora']['objects']['repository']['objectId'];
  echo $form_state['islandora'];
  
  //retrieves the relevant fedora project object
  //$project_object = $tuque->repository->getObject($form_state['values']['pid']); 
  //echo $form['values']['pid'];
  
  //echo '<pre>';
  //var_dump($form_state['values']); exit();
  //echo '<\pre>';	
	
  //get the checkboxes submitted (only those checked are submitted)
  $person_ids = array_filter($form_state['values']['form']);
  
  //for each person selected, create a relationship between the person and the project
  foreach($person_ids as $id)  {
	//$project_object->relationships->add($id, 'hasModel', 'islandora:person_cmodel');
	echo $id;
  }
}
