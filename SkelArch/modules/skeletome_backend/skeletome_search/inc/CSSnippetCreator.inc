<?php
// $Id: CSSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class CSSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $base_path = url(NULL, array('absolute' => TRUE));
    $snippet = '';

    if (array_key_exists('und', $this->node->field_cs_clinicalsummary)) {
      $body = strip_tags($this->node->field_cs_clinicalsummary['und'][0]['value']);
      if (strlen($body) > 150) {
	$body = substr($body, 0, 150) . ' ...';
      }
      $snippet .= '<b>Clinical summary: </b>' . $body;
    }

    /*
    if (array_key_exists('und', $this->node->field_cs_tags)) {
      $snippet .= '<br/>';

      $terms = array();
      $snippet .= '<b>HPO terms: </b>';
      foreach($this->node->field_cs_tags['und'] as $tid) {
	$tag = taxonomy_term_load($tid['tid']);
	$snippet .= '<span class="pt-term pt-term-remove">';
	$snippet .= '<span class="pt-term-text">' . $tag->name . '</span>'; 
	$snippet .= '</span>';

	$terms[$tag->name] = $tag->tid;
      }
      drupal_add_js(array('terms' => $terms), 'setting');
    }
    */

    return $snippet;
  }

}