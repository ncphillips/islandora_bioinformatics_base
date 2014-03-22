<?php
/**
 * @file rel_cmodel_callbackso
 *
 * This file contains the various page callbacks
 */


/**
 * rel_cmodel_list($object, $cmodel=NULL)
 *
 * @param FedoraObject $object
 * @param FedoraObject|null $cmodel
 */
function rel_cmodel_list($object, $cmodel=NULL) {
  /*
   * @TODO rel_cmodel_list
   * Invokes hook_rel_list_alter and then hook_rel_SUBTYPE_list_alter,
   * where subtype is the cmodels partial id.
   */
}

/**
 * @param FedoraObject $object
 * @param FedoraObject $cmodel
 */
function rel_cmodel_ingest($object, $cmodel) {
  /*
   * @TODO
   */
}

/**
 * @param FedoraObject $object
 * @param FedoraObject $target
 */
function rel_cmodel_add_rel($object, $target) {
  /*
   * @TODO
   */
}

/**
 * @param FedoraObject $object
 * @param FedoraObject $cmodel
 */
function rel_cmodel_add_rel_ui($object, $cmodel) {
  /*
   * @TODO
   */
}

/**
 * @param FedoraObject $object
 * @param FedoraObject $target
 */
function rel_cmodel_remove_rel($object, $target) {
  /*
   * @TODO
   */
}

/**
 * @param $object
 * @param $cmodel
 */
function rel_cmodel_remove_rel_ui($object, $cmodel, $target) {
  /*
   * @TODO
   */
}
