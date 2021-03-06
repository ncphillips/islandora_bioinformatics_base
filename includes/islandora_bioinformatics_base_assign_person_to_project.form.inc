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
  
  $project_object = $form_state['islandora']['objects'][0]; //this is NULL
  
  //query fedora to retrieve a list of all person objects
  $query = "SELECT ?pid
          FROM <#ri>
          WHERE {
          ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
        }";
  $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');
  
  //build the checkboxes form, with default values.
  $people = array();
  $default_values = array();  //determines which values are automatically selected
  foreach ($result as $person) {

      //load the current person object
      $person_object = islandora_object_load($person["pid"]["value"]);
      $people[$person_object->id] = $person_object->label;

      /*
      if($person_object->id == 'islandora:388') {
        $person_object->relationships->add(FEDORA_RELS_EXT_URI, 'isPartOf', $project_object->id);	//used for testing
      }
      */
      
      $relationship = $person_object->relationships->get(FEDORA_RELS_EXT_URI, 'isPartOf', $project_object->id);

      if (!empty($relationship)) {  //if relationship exists, add it to $default_values
        $default_values[$person_object->id] = $person_object->id;
      }
      
      /*
      if($person_object->id == 'islandora:388') {
        $person_object->relationships->remove(FEDORA_RELS_EXT_URI, 'isPartOf', $project_object->id);	//used for testing
      }
      */

  }

  $form['header'] = array(
    '#markup' => 'Manage People in this Project',
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',
  );
  
  /*return array(
    'people' => array(
      '#type' => 'checkboxes',
      '#default_value' => $default_values,
      '#options' => $people,
      ),
    );*/
    
    $form['people'] = array(
      '#type' => 'checkboxes',
      '#default_value' => $default_values,
      '#options' => $people,
    );
    
    return $form;
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

  //get the checkboxes submitted (only those checked are submitted)  
  $person_ids = array_filter($form_state['values']['people']);

  //iterate over every person and remove their relationship (if it exists) with the project.
  $query = "SELECT ?pid
            FROM <#ri>
            WHERE {
            ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
        }";
  $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');

  foreach ($result as $person) {
    $person_object = islandora_object_load($person['pid']['value']);  //loads object
    $person_object->relationships->remove(FEDORA_RELS_EXT_URI, 'isPartOf', $project_object->id);
  }

  //for each person checked, create a relationship between the person and the project
  foreach ($person_ids as $id)  {
    //create a relationship within the current person object to the project
    $person_object = islandora_object_load($id); //loads object
    $person_object->relationships->add(FEDORA_RELS_EXT_URI, 'isPartOf', $project_object->id);
  }
}
