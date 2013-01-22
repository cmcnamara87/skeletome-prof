<?php
// $Id: DiagnosisSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class DiagnosisSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $snippet = '';
    $date_html = date_format_date(new DateObject($this->node->field_diagnosis_date['und'][0]['value']), 'custom', 'd/m/Y');
    $snippet .= '<b>Date: </b>' . $date_html;
    if (array_key_exists('und', $this->node->field_diagnosis_confidence)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Confidence: </b>' . $this->node->field_diagnosis_confidence['und'][0]['rating'] . '%';
    }

    return $snippet;
  }
}