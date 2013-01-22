<?php
// $Id: RefLetterSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class RefLetterSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $snippet = '';
    $date_html = date_format_date(new DateObject($this->node->field_referenceletter_date['und'][0]['value']), 'custom', 'd/m/Y');
    $snippet .= '<b>Date: </b>' . $date_html;

    if (array_key_exists('und', $this->node->body)) {
      $body = strip_tags($this->node->body['und'][0]['value']);
      if (strlen($body) > 150) {
	$body = substr($body, 0, 150) . ' ...';
      }
      $snippet .= '<br/>';
      $snippet .= '<b>Observations: </b>' . $body;
    }

    return $snippet;
  }
}