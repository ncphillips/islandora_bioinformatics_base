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
            $people[$person["pid"]["value"]] = $person["pid"]["value"];
        }

        $people_string = implode($people);

        return $people;
    }
