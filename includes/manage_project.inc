<?php

    /**
     * @todo
     * This should return a page that lists the people associated with the project.
     * Each person row should link to the person object itself.
     */
    function islandora_project_people(AbstractObject $object) {

        $tuque = new IslandoraTuque();
        $query = "SELECT ?pid
                    FROM <#ri>
                    WHERE {
                    ?pid <fedora-model:hasModel> <info:fedora/islandora:person_cmodel> .
                    }
                    ";
        $result = $tuque->repository->ri->sparqlQuery($query, 'unlimited');

        $people = array();
        foreach($result as $person) {
            $person_object = islandora_object_load($person["pid"]["value"]);
            
            
            //check if relationship exists and add to people array
            $relationship = $person_object->relationships->get(FEDORA_RELS_EXT_URI, 'isMemberOf', "islandora:project_cm");
            
            if(!empty($relationship)){
                $people[$person_object->id] = $person_object->label;
            }
        }

        $people_string = "";
        foreach($people as $person){
          $people_string .= $person . "\n";
        }
        
        return $people_string;
    }
