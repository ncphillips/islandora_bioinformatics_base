<?php

    /**
     *
     * @file manage_project.inc
     *
     * @todo
     * This should return a page that lists the people associated with the project.
     * Each person row should link to the person object itself.
     */
    function islandora_project_people(AbstractObject $object) {

        var_dump($object);
        
        $tuque = new IslandoraTuque();
        $query = "SELECT ?pid
                    FROM <#ri>
                    WHERE {
                    ?pid <datarel_partOf> <info:fedora/islandora:person_cmodel> .
                    }
                    ";
        $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');

        $people = array();
        foreach ($result as $person) {
            $person_object = islandora_object_load($person["pid"]["value"]);
            
            
            //check if relationship exists and add to people array
            $relationship = $person_object->relationships->get(FEDORA_RELS_EXT_URI, 'isMemberOf', "");
            
            if (!empty($relationship)) {
                $people[$person_object->id] = $person_object->label;
            }
        }

        $people_string = "";
        foreach ($people as $person) {
          $people_string .= $person . "\n";
        }
        
        return $people_string;
    }
    
    function islandora_project_people_add_form(array $form, array &$form_state, AbstractObject $object){
        var_dump($object);
        
        $tuque = new IslandoraTque();
        $query = "SELECT ?pid
                    FROM <#ri>
                    WHERE {
                    ?pid <datarel_partOf><info:fedora/islandora:person_cmodel> .
                    }
                    ";
        $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');
        
        $people = array();
        foreach($result as $person){
            $person_object = islandora_object_load($person["pid"]["value"]);
            
            //check if relationship exists and add to people array
            $relationship = $person_object->relationships->get(FEDORA_RELS_EXT_URI, 'isMemberOf', $object->id);
            
            if(!empty($relationship)){
                $related_people[$person_object->id] = $person_object->label;
            }
        }
        
        $render = array(
            //list of people
            'people' => array(
                '#type' => 'checkboxes',
                '#default_value' => $related_people,
                '#options' => $people,
            ),
            //submit button
            'submit' =  array(
                '#type' => 'submit',
                '#value' => 'Submit',
            ),
        );
        
        var_dump($render);
        
        return $render;
    }
    
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
    
        foreach ($result as $person) {
          $person_object = islandora_object_load($person['pid']['value']);  //loads object
          $person_object->relationships->remove(FEDORA_RELS_EXT_URI, 'isMemberOf', $object->id);
        }
    
        //for each person checked, create a relationship between the person and the project
        foreach ($person_ids as $id)  {
          //create a relationship within the current person object to the project
          $person_object = islandora_object_load($id); //loads object
          $person_object->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOf', $object->id);
        }
        
    }
