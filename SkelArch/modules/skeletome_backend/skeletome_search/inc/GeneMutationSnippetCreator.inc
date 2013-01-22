<?php
// $Id: GeneMutationSnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class GeneMutationSnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getSnippet($current_snippet) {
    $base_path = url(NULL, array('absolute' => TRUE));
    $snippet = '';

    $gene_term = taxonomy_term_load($this->node->field_gene_mutation_gene['und'][0]['tid']);
    $snippet .= '<b>Gene: </b><a href="' . $base_path . 'taxonomy/term/' . $gene_term->tid . '">' . $gene_term->name . '</a>';

    if (array_key_exists('und', $this->node->field_gm_mutation_type)) {
      $snippet .= '<br/>';
      $gmt_term = taxonomy_term_load($this->node->field_gm_mutation_type['und'][0]['tid']);
      $snippet .= '<b>Mutation type: </b><a href="' . $base_path . 'taxonomy/term/' . $gmt_term->tid . '">' . $gmt_term->name . '</a>';
    }
    if (array_key_exists('und', $this->node->field_gm_offset)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Offset: </b>' . $this->node->field_gm_offset['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_gm_count)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Count: </b>' . $this->node->field_gm_count['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_gm_originalcontent)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Original content: </b>' . $this->node->field_gm_originalcontent['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_gm_mutatedcontent)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Mutated content: </b>' . $this->node->field_gm_mutatedcontent['und'][0]['value'];
    }

    return $snippet;
  }
}