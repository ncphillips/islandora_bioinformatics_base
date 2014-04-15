<?php
module_load_include('inc', 'islandora', 'islandora.rules');

/**
 * @file
 * These are some functions that will be used throughout the bioinf solution packs
 */

/**
 * @param $cmodel
 * An islandora object for the cmodel that we're going to add the rel to
 * @param $rel_to
 * A pid, that will be added in the relationship
 * @author Brent Mitton
 *
 * This function simply checks to make sure a relationship doesnt exist before adding it
 */
function add_hasPart($cmodel, $rel_to){
  if (!islandora_object_has_relationship($cmodel, '', 'datarel_hasPart', $rel_to, FALSE))
    $cmodel->relationships->add(FEDORA_RELS_EXT_URI, 'datarel_hasPart', $rel_to);
}

/**
 * @param $cmodel
 * An islandora object for the cmodel that we're going to add the rel to
 * @param $rel_to
 * A pid that will be added in the relationship
 * @author Brent Mitton
 * This function simply checks to make sure a relationship doesnt exist before adding it
 */
function add_isPartOf($cmodel, $rel_to){
  if (!islandora_object_has_relationship($cmodel, '', 'datarel_isPartOf', $rel_to, FALSE))
    $cmodel->relationships->add(FEDORA_RELS_EXT_URI, 'datarel_isPartOf', $rel_to);
}