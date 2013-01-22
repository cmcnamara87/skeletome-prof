<?php
// $Id: CISnippetCreator.inc $

//define('__PARAM_APIKEY__', 'apikey');

class CISnippetCreator {

  private $nid;
  private $node;

  function __construct($node_id) {
    $this->nid = $node_id;
    $this->node = node_load($this->nid);
  }

  public function getGenericSnippet() {
    $base_path = url(NULL, array('absolute' => TRUE));
    $snippet = '';

    $name = '';
    if (array_key_exists('und', $this->node->field_patient_firstname)) {
      $name .= $this->node->field_patient_firstname['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_patient_lastname)) {
      if (!empty($name)) {
	$name .= ' ';
      }
      $name .= $this->node->field_patient_lastname['und'][0]['value'];
    }
    if (!empty($name)) {
      $snippet .= '<b>Name: </b>' . $name;
    }

    if (array_key_exists('und', $this->node->field_patient_alias)) {
      if (!empty($name)) {
	$snippet .= '<br/>';
      }
      $snippet .= '<b>Alias: </b>' . $this->node->field_patient_alias['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_patient_ethnicity)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Ethnicity: </b>' . $this->node->field_patient_ethnicity['und'][0]['value'];
    }

    $address = '';
    if (array_key_exists('und', $this->node->field_patient_addressstreet)) {
      $address .= $this->node->field_patient_addressstreet['und'][0]['value'];
    }

    if (array_key_exists('und', $this->node->field_patient_addresscity)) {
      if (!empty($address)) {
	$address .= ', ';
      }
      $address .= $this->node->field_patient_addresscity['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_patient_addressstate)) {
      if (!empty($address)) {
	$address .= ', ';
      }
      $address .= $this->node->field_patient_addressstate['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_patient_addresspostcode)) {
      if (!empty($address)) {
	$address .= ', ';
      }
      $address .= $this->node->field_patient_addresspostcode['und'][0]['value'];
    }
    if (array_key_exists('und', $this->node->field_patient_addresscountry)) {
      if (!empty($address)) {
	$address .= ', ';
      }
      $address .= $this->node->field_patient_addresscountry['und'][0]['value'];
    }
    if (!empty($address)) {
      $snippet .= '<br/>';
      $snippet .= '<b>Address: </b>' . $address;
    }

    return $snippet;
  }

}