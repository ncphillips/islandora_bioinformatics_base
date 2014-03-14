<?php

    function islandora_project_people(AbstractObject $object) {
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

        return "MY PEOPLE!";
    }
