<?php

    /**
     *
     * @file manage_project.form.inc
     * @author Natasha Squires <nsquires@upei.ca>
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
            
            //check if relationship exists and ignore if so
            $relationship = $person_object->relationships->get(FEDORA_RELS_EXT_URI, 'isPartOf', $object->id);
            
            if(empty($relationship)){
                $values[$person_object->id] = $person_object->label;
            }
        }
        
        $form['header'] = array(
            '#markup' => 'Add people to '.object->id.'.',
            '#prefix' => '<h1>',
            '#suffix' => '</h1>',
        );
        
        //list of people
        $form = array(
            'people' => array(
                '#type' => 'checkboxes',
                '#options' => $values,
            ),
        );
        
        //submit button
        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => 'Submit',
            '#submit' => array('islandora_project_people_add_submit'),
        );
        
        //back button
        $form['back'] = array(
            '#type' => 'submit',
            '#value' => 'Cancel',
            '#submit' => array('islandora_project_people_add_cancel'),
        );
        
        //saving the project object in the form
        $form['project_object'] = array(
            '#type' => 'value',
            '#value' => $object,
        );
        
        return $form;
    }
    
    /**
     * The submit handler for the project_people_add_form
     *
     * @param array $form
     * the Drupal form
     * @param array &$form_state
     * the Drupal form state
     *
     */
    function islandora_project_people_add_submit(array $form, array &$form_state) {
        $tuque = new IslandoraTuque();
    
        //get the checkboxes submitted (only those checked are submitted)  
        $person_ids = array_filter($form_state['values']['people']);
        
        //get the saved project object that will have people added to it
        $object = $form_state['values']['project_object'];
    
        //iterate over every person and remove their relationship (if it exists) with the project.
       /* $query = "SELECT ?pid
                  FROM <#ri>
                  WHERE {
                  ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
              }";
        $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');*/
    
        //for each person checked, create a relationship between the person and the project
        foreach ($person_ids as $id)  {
          //create a relationship within the current person object to the project
          $person_object = islandora_object_load($id); //loads object
          $person_object->relationships->add(FEDORA_RELS_EXT_URI, 'isPartOf', $object->id);
        }
        
        //redirects to the people menu for the object
        $form_state['redirect'] = array(
          'islandora/object/'.$object->id.'/people'
        );
    }
    
    /**
     * The handler for the cancel button
     *
     * @param array $form
     * the Drupal form
     *
     * @param array &$form_state
     * the Drupal form state
     *
     */
     function islandora_project_people_add_cancel(array $form, array &$form_state){
        $object = $form_state['values']['project_object'];
        $form_state['redirect'] = array(
            'islandora/object/'.$object->id.'/people'
        );
     }
