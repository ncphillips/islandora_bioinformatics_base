<?php

/**
 * related_islandora_objects_form
 *
 * Constructs a form which has a select table of islandora objects related to the
 * $object. A related object is listed iff it's cmodel is in $cmodels and the
 * relationship to $object is in $relationships.
 *
 * @param $form
 * @param $form_state
 * @param $object
 * @param null $cmodels
 * @param null $relationships
 *
 * @author Nolan Phillips ncphillips@upei.ca
 *
 */
function related_islandora_objects_form($form, $form_state, $object, $cmodels=null, $relationships=null) {
  echo "Creating related_islandora_objects_form";

  // Find the list of related islandora objects.
  //$object = islandora_object_load('islandora:524');
  $related_objects = related_islandora_objects($object, $cmodels, $relationships);

  $form_state['object'] = $object;
  $form_state['related_objects'] = $related_objects;
  if(isset($cmodels)) $form_state['cmodels'] = $cmodels;
  if(isset($relationships)) $form_state['relationships'] = $relationships;

  // From our form there should be a list of specific operations that can be performed
  // on the objects in the list.
  $form['banana'] = array(
    '#markup' => '<h1>OH MY GOD</h1>',
  );
  $form['selected'] = array(
    '#type' => 'select',
    '#title' => 'Actions',
    '#options' => array(
      'delete' => t('Remove'),
    ),
    '#description' => t('Actions'),
  );

  // Submit button for form actions.
  $form['submit'] =  array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  $header = array(
    'id' => 'ID',
  );

  $options = array();

  foreach($related_objects as $related_object) {
    $options[$related_object->id] = array(
      'id' => $related_object->id,
    );
  }

  $form['table'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t("Null."),
  );

  return $form;
}




/**
 * related_islandora_objects
 *
 * @param IslandoraFedoraObject $object
 * @param string array | null $cmodels
 * An array of strings representing fedora IDs of Content Models.
 * @param array | null $relationships
 * An associative array whose keys are namespaces, and whose values
 * are arrays of relationships in that namespace.
 *
 * @return IslandoraFedoraObject array $related_objects
 * An array of IslandoraFedoraObjects that are related to the $object.
 *
 * @author Nolan Phillips ncphillips@upei.ca
 *
 * Dear Paul and Peter,
 *
 *    If you're reading this function...I am so sorry.
 *
 * Sincerely,
 * Nolan
 */
function related_islandora_objects($object, $cmodels=null, $relationships=null){
  /**
   * Example Query:
   *    PREFIX a: <info:fedora/fedora-system:def/relations-external#>
   *    PREFIX b: <info:fedora/fedora-system:def/model#>
   *    SELECT *
   *    FROM <#ri>
   *    WHERE {
   *      {
   *        {?pid b:hasModel <info:fedora/islandora:person_cmodel>}
   *        UNION
   *        {?pid b:hasModel <info:fedora/islandora:specimen_cmodel>}
   *      }
   *      {
   *        {?pid a:isMemberOf <info:fedora/islandora:524>}
   *      }
   *    }
   */

  /////Test Data/////
  //$object = islandora_object_load('islandora:524');
  //$cmodels = array('islandora:person_cmodel');
  //$relationships = array(FEDORA_RELS_EXT_URI=> array('isMemberOf'));


  $obj_id = $object->id;  // The Fedora PID of $object.
  $cmodel_query = '';  // A union of CModel tripples.

  $pre = array();  // An associative array of namespace => prefix.
  $pre_defs = array();  // An array of prefix definitions.

  // Default values for $pre and $pre_defs
  $pre[FEDORA_MODEL_URI] = 'fedora-model:';

  // Besides 'fedora-model', the first prefix being used is 'a'.
  $prefix = 'a';$pre_defs[] = 'PREFIX fedora-model: <info:fedora/fedora-system:def/model#>';

  /**
   * If any cmodels were passed in, then we accept an object if any of it's
   * cmodels is in the list of cmodels.
   *
   * else, if no cmodel was passed in, then any kind of object, regardless of cmodel,
   * will be accepted by the query.
   */
  if ($cmodels){
    $cmodel_tripples= array();
    foreach($cmodels as $cmodel)
      $cmodel_tripples[] = "{?pid fedora-model:hasModel <info:fedora/$cmodel>}";
    // Union all the cmodel tripple queries.
    $cmodel_query = '{'.implode(' UNION ', $cmodel_tripples).'}';
  }

  // Construct the set of prefix definitions.
  /**
   * If a list of relationships is defined, then we accept an object if
   * it has one of the defined relationships to the $object.
   *
   * else, if no relationships are defined, then we accept objects no matter
   * what kind of relationship it has with the $object.
   */
  if($relationships){
    // Define PREFIX statements
    foreach($relationships as $ns => $rel){
      $pre[$ns] = $prefix.':';
      $pre_defs[] = 'PREFIX ' . $prefix++ . ": <$ns>";
    }
    $pre_def = implode(' ', $pre_defs);

    // Define relationship tripples
    foreach($relationships as $ns => $rels){
      foreach($rels as $rel){
        $nsrel = $pre[$ns] . $rel;
        $rel_tripples[] = "{?pid $nsrel <info:fedora/$obj_id>}";
      }
    }
    // Union all the relationship tripples
    $rel_query = '{'.implode(' UNION ', $rel_tripples).'}';
  }
  else {
    $pre_def = $pre_defs[0];
    $rel_query = "{?pid ?any_rel <info:fedora/$obj_id>}";
  }

  $query = "
    $pre_def
    SELECT ?pid
    FROM <#ri>
    WHERE {
        $cmodel_query
        $rel_query
    }
  ";

  // For testing porpoises.
  //file_put_contents('/tmp/sparqlquery.txt', $query);

  // Run the query.
  $tuque = new IslandoraTuque();
  $result = $tuque->repository->ri->sparqlQuery($query);

  $related_objects = array();
  foreach($result as $related_object) {
    $obj = islandora_object_load($related_object['pid']['value']);
    $related_objects[] = $obj ;
  }

  return $related_objects;
}
