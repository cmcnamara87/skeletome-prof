<?php

function get_generictags_callback() {
  $max_count = $_GET['max_count'];
  $term_startsWith = $_GET['tags_startsWith'];

  $vid = get_vid_for_vocabulary('generic_tags_vocabulary');
  $terms = get_terms_for_approx_name_with_limit($vid, $term_startsWith, $max_count);
  $s = create_taxonomy_result($terms);
  echo $s;
}

function get_bonedysplasias_callback() {
  $max_count = $_GET['max_count'];
  $term_startsWith = $_GET['tags_startsWith'];
  $vid = get_vid_for_vocabulary('bone_dysplasia_vocabulary');
  $terms = get_terms_for_approx_name_with_limit($vid, $term_startsWith, $max_count);
  $s = create_taxonomy_result($terms);
  echo $s;
}

function get_terms_for_approx_name_with_limit($vid, $name, $limit) {
  $terms = array();

  $sql = 'SELECT tid, vid, name FROM {taxonomy_term_data} WHERE vid = :vid AND name LIKE :name LIMIT 0, ' . $limit;
  $result = db_query($sql, array(':vid' => $vid, ':name' => '%' . $name . '%'));
  foreach ($result as $r) {
    $terms[$r->tid] = $r->name;
  }

  return $terms;
}

function get_terms_for_approx_name($vid, $name) {
  $terms = array();

  $sql = 'SELECT tid, vid, name FROM {taxonomy_term_data} WHERE vid = :vid AND name LIKE :name';
  $result = db_query($sql, array(':vid' => $vid, ':name' => '%' . $name . '%'));
  foreach ($result as $r) {
    $terms[$r->tid] = $r->name;
  }

  return $terms;
}

function create_taxonomy_result($terms) {
  $result = '{"totalResultsCount":' . count($terms) . ',"terms":[';

  $count = 0;
  foreach ($terms as $tid => $term) {
    $term_name = $term;
    if (strlen($term_name) > 55) {
      $term_name = substr($term_name, 0, 55) . ' ...';
    }
    $term_s = '{"term":"' . $term_name . '","tid":"' . $tid . '"},';
    $result = $result . $term_s;
    $count++;
  }
  if ($count != 0) {
    $result = substr($result, 0, strlen($result) - 1);
  }
 
  $result = $result . ']}';
  return $result;
}

