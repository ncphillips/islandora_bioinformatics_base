<?php

function rel_lab_objects_form($form, &$form_state, $object) {
  $rel_cmodels = array('Example 1', 'Example 2');

  $form['object'] = array(
    '#type' => 'hidden',
    '#value' => $object,
  );

  foreach($rel_cmodels as $rel_cmodel){

    $form[$rel_cmodel] = array(
      '#prefix' => t("<h1>Related $rel_cmodel</h1><div id='form_$rel_cmodel'>"),
      '#suffix' => t('</div>'),
    );

    // Add Lab Object Button
    $form[$rel_cmodel]['add'] = array(
      '#type' => 'button',
      '#value' => t("Add $rel_cmodel"),
      '#name' => "add_$rel_cmodel",
    );

    // Possible actions in a dropdown menu.
    $form[$rel_cmodel]['selected'] = array(
      '#type' => 'select',
      '#title' => 'Actions',
      '#options' => array(
        'delete' => t('Delete'),
      ),
      '#description' => t('Actions'),
      '#name' => "selected_$rel_cmoedl",
    );

    // Submit button for actions.
    $form[$rel_cmodel]['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Submit',
      '#name' => "submit_$rel_cmodel",
    );

    // Table of Related Lab Objects.
    $header = array(
      'title' => t('Title'),
    );

    $options = array(
      '1' => array('title'=> "$rel_cmodel 1"),
      '2' => array('title'=> "$rel_cmodel 2"),
    );

    $form[$rel_cmodel]['table'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t("There is no related content of type $rel_cmodel."),
      '#name' => "table_$rel_cmodel",
    );
  }
  return $form;
}

function rel_lab_objects_form_submit(array $form, array &$form_state) {
  echo t("<h1>Clicked Button: " . $form_state['clicked_button']['#value'] . "</h1>");
  echo '<pre>';
  var_dump($form_state['values']);
  echo'</pre>';
  exit();

}
