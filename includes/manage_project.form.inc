<?php

    /**
     *
     * @file manage_project.inc
     *
     * Presents a list of People that can be added to a Project
     */
   
    /**
     * The People add form
     * 
     * @param array $form
     * the Drupal form
     * @param array array &$form_state
     * the Drupal form state
     * @param AbstractObject $object
     * the Project object the form is associated with
     *
     * @return
     * $form - the Drupal form definition
     *
     */
    function islandora_project_people_add_form(array $form, array &$form_state, AbstractObject $object){
        
       // var_dump($object);
        
        $tuque = new IslandoraTuque();
        $query = "SELECT ?pid
                    FROM <#ri>
                    WHERE {
                    ?pid <fedora-model:hasModel><info:fedora/islandora:person_cmodel> .
                    }
                    ";
        $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');
        
        $people = array();
        $values = array();
        
        foreach($result as $person){
            $person_object = islandora_object_load($person["pid"]["value"]);
            //var_dump($person_object);
            
            //check if relationship exists and ignore if so
            $relationship = $person_object->relationships->get(FEDORA_RELS_EXT_URI, 'isMemberOf', $object->id);
           // var_dump($relationship);
            
            if(empty($relationship)){
                $values[$person_object->id] = $person_object->label;
            }
        }
        
        $form = array(
            //list of people
            'people' => array(
                '#type' => 'checkboxes',
                '#options' => $values,
            ),
        );
        
        //submit button
        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => 'Submit',
            '#executes_submit_callback' => TRUE,
        );
        
        //var_dump($form);
        
        return $form;
    }
    
    /**
     * The submit handler for the project_people_add_form
     *
     * @param array $form
     * the Drupal form
     * @param array &$form_state
     * the Drupal form state
     * @param AbstractObject $object
     * the Project object the form is associated with
     *
     */
    function islandora_project_people_add_submit(array $form, array &$form_state, AbstractObject $object) {
        $tuque = new IslandoraTuque();
    
        //get the checkboxes submitted (only those checked are submitted)  
        $person_ids = array_filter($form_state['values']['people']);
    
        //iterate over every person and remove their relationship (if it exists) with the project.
        $query = "SELECT ?pid
                  FROM <#ri>
                  WHERE {
                  ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
              }";
        $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');
    
     /*   foreach ($result as $person) {
          $person_object = islandora_object_load($person['pid']['value']);  //loads object
          $person_object->relationships->remove(FEDORA_RELS_EXT_URI, 'isMemberOf', $object->id);
        }*/
    
        //for each person checked, create a relationship between the person and the project
        foreach ($person_ids as $id)  {
          //create a relationship within the current person object to the project
          $person_object = islandora_object_load($id); //loads object
          $person_object->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOf', $object->id);
        }
        
    }
