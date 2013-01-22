<?php
// $Id: XRaySnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class XRaySnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $snippet = '';
    if (array_key_exists('und', $this->node->field_xray_description)) {
//      $snippet .= '<br/>';
      $snippet .= '<b>Description: </b>' . strip_tags($this->node->field_xray_description['und'][0]['value']);
    }

    if (array_key_exists('und', $this->node->field_skeletome_tags)) {
      $snippet .= '<br/>';

      $terms = array();
      $snippet .= '<b>HPO terms: </b>';
      foreach($this->node->field_skeletome_tags['und'] as $tid) {
	$tag = taxonomy_term_load($tid['tid']);
	$snippet .= '<span class="pt-term pt-term-remove">';
	$snippet .= '<span class="pt-term-text">' . $tag->name . '</span>'; 
	$snippet .= '</span>';

	$terms[$tag->name] = $tag->tid;
      }
      drupal_add_js(array('terms' => $terms), 'setting');
    }

    return $snippet;
  }
}