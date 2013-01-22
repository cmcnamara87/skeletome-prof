<?php

function _skeletome_statistics_menu() {
  return drupal_get_form('_skeletome_statistics_form');
}

function _skeletome_statistics_form() {
  $form['statistics-vocab-head'] = array(
    '#markup' => '<h2 class="title">Vocabulary information</h2>',
    '#weight' => 1
  );

  $form['statistics-bd'] = array(
    '#markup' => '<h3>Bone dysplasias: ' . count_tags('bone_dysplasia_vocabulary') . '</h3>',
    '#weight' => 2
  );

  $form['statistics-genes'] = array(
    '#markup' => '<h3>Genes: ' . count_tags('gene_vocabulary') . '</h3>',
    '#weight' => 3
  );

  $form['statistics-genemutationtypes'] = array(
    '#markup' => '<h3>Gene mutation types: ' . count_tags('gene_mutation_type_vocabulary') . '</h3>',
    '#weight' => 4
  );

  $form['statistics-vocab-skeletome'] = array(
    '#markup' => '<h3>Total tags in the SKELETOME vocabulary: ' . count_tags('skeletome_vocabulary') . '</h3>',
    '#weight' => 5
  );

  $form['statistics-skeletome-head'] = array(
    '#markup' => '<h2 class="title">SKELETOME general information</h2>',
    '#weight' => 6
  );

  $form['statistics-groups'] = array(
    '#markup' => '<h3>Total number of groups: ' . count_nodes('skeletome_group') . '</h3>',
    '#weight' => 7
  );

  $form['statistics-users'] = array(
    '#markup' => '<h3>Total number of users: ' . count_users() . '</h3>',
    '#weight' => 8
  );

  return $form;
}
