<?php
// $Id: ForumSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class ForumSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $snippet = '';
    $snippet .= '<b>Date created: </b>' . date('d/m/Y', $this->node->created);
    $snippet .= '<br/>';
    $snippet .= '<b>Number of comments: </b>' . $this->node->comment_count;
    $snippet .= '<br/>';
    $snippet .= '<b>Last comment added: </b>' . date('d/m/Y', $this->node->last_comment_timestamp);

    if (array_key_exists('und', $this->node->body)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Body: </b>';
      $body = strip_tags($this->node->body['und'][0]['value']);
      if (strlen($body) > 150) {
	$body = substr($body, 0, 150) . ' ...';
      }
      $snippet .= $body;
    }

    return $snippet;
  }
}