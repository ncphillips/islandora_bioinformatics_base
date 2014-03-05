<?php
/**
 * @file
 * This is the template file for the person object page.
 *
 * Here we build an html page using the variables passed in by
 * the islandora_bioinformatics_base_preprocess_islandora_person
 * function.  Elements such as labels and buttons can be added here
 */
 
 /**
 * 	Written by Quintin Dawson, based off of Islandora_Porcus solution pack
 */
 
$islandora_content = $islandora_object['PERSON']->content;
$path = drupal_get_path('module', 'islandora_bioinformatics_base');
?>

<div class="islandora-person-object islandora">
  <div class ="person_image">
    <?php print $variables['islandora_thumbnail_img'] ?>
  </div>
  <div class="islandora-basic-image-content-wrapper clearfix">
    <?php if (isset($islandora_content)): ?>
      <div class="islandora-person-content">
        <?php print $islandora_content; ?>
      </div>
    <?php endif; ?>
  </div>