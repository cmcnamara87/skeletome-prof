<?php
// $Id: PatientSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class PatientSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getGenericSnippet() {
    $base_path = url(NULL, array('absolute' => TRUE));
    $snippet = '';

    if (array_key_exists('und', $this->node->field_patient_identifier)) {
      $identifiers = '';
      foreach($this->node->field_patient_identifier['und'] as $id) {
	$identifiers .= $id['value'] . ', ';
      }
      $snippet .= '<b>Identifiers: </b>' . $identifiers;
      $snippet = substr($snippet, 0, strlen($snippet) - 2);
    }

    if (array_key_exists('und', $this->node->field_patient_customtags)) {
      $snippet .= '<br/>';
      $tags = '';
      foreach($this->node->field_patient_customtags['und'] as $tid) {
	$tag = taxonomy_term_load($tid['tid']);
	$tags .= '<a href="' . $base_path . 'taxonomy/term/' . $tid['tid'] . '">' . $tag->name . '</a>, ';
      }
      $snippet .= '<b>Tags: </b>' . $tags;
      $snippet = substr($snippet, 0, strlen($snippet) - 2);
    }

    return $snippet;
  }

}