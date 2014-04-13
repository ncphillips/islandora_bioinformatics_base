<?php

/**
  * @file
  * Theme file for Base solution pack. Includes preprocess functions.
  */



function islandora_bioinformatics_base_preprocess_islandora_person(array &$variables) {


  $islandora_object = $variables['islandora_object'];
  // Thumbnail.
  if (isset($islandora_object['TN'])) {
    $thumbnail_size_url = url("islandora/object/{$islandora_object->id}/datastream/TN/view");
    $params = array(
      'title' => $islandora_object->label,
      'path' => $thumbnail_size_url,
    );
    $variables['islandora_thumbnail_img'] = theme('image', $params);
  }

  $variables["person"] = person_mads_to_array($islandora_object);

}


function islandora_bioinformatics_base_preprocess_islandora_project(array &$variables) {


  $islandora_object = $variables['islandora_object'];
  // Thumbnail.
  if (isset($islandora_object['TN'])) {
    $thumbnail_size_url = url("islandora/object/{$islandora_object->id}/datastream/TN/view");
    $params = array(
        'title' => $islandora_object->label,
        'path' => $thumbnail_size_url,
    );
    $variables['islandora_thumbnail_img'] = theme('image', $params);
  }

  $variables["project"] = project_mads_to_array($islandora_object);

}
