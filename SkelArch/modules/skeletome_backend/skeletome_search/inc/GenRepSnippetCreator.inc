<?php
// $Id: GenRepSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class GenRepSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $snippet = '';
    $date_html = date_format_date(new DateObject($this->node->field_genrep_date['und'][0]['value']), 'custom', 'd/m/Y');
    $snippet .= '<b>Date: </b>' . $date_html;

    if (array_key_exists('und', $this->node->field_genrep_refno)) {
      $identifiers = '';
      foreach($this->node->field_genrep_refno['und'] as $id) {
	$identifiers .= $id['value'] . ', ';
      }
      $snippet .= '<br/>';
      $snippet .= '<b>Reference no.: </b>' . $identifiers;
      $snippet = substr($snippet, 0, strlen($snippet) - 2);
    }

    if (array_key_exists('und', $this->node->field_genrep_gm)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Number of gene mutations: </b>' . count($this->node->field_genrep_gm['und']);
    }

    return $snippet;
  }
}