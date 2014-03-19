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
  $project_object->relationships->add('islandora:388', 'hasModel', 'islandora:person_cmodel');
    
  $query = "SELECT ?pid
                    FROM <#ri>
                    WHERE {
                    ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
                    }";
  $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');
  
   $people = array();
   //$default_values = array();
   
   foreach($result as $person) {
	 $people[$person["pid"]["value"]] = $person["pid"]["value"];
   }
   
   $default_values = array_keys($people);
   echo '<pre>';
   echo var_dump(array_keys($people));
   echo '</pre>';
  
   return array(
	'form' => array(
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
  $person_ids = array_filter($form_state['values']['form']);
  
  //for each person selected, create a relationship between the person and the project
  foreach($person_ids as $id)  {
	$project_object->relationships->add($id, 'hasModel', 'islandora:person_cmodel');
	//$project_object->relationships->add($id, 'isPartOf', 'islandora:person_cmodel');
  }
}
