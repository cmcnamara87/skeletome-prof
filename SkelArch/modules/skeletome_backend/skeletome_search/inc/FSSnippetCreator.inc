<?php
// $Id: FSSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class FSSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $snippet = '';
    if (array_key_exists('und', $this->node->body)) {
      $body = strip_tags($this->node->body['und'][0]['value']);
      if (strlen($body) > 150) {
	$body = substr($body, 0, 150) . ' ...';
      }
      $snippet .= $body;
    }

    return $snippet;
  }
}