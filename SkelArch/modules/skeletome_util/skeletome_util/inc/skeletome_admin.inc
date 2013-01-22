<?php

function manage_gentags_callback() {
  $form_state['build_info']['args'] = array();
  return drupal_build_form('manage_gentags_form', $form_state);
}

function manage_gentags_form($node, &$form_state) {
  $form = array();

  drupal_add_library('system', 'ui.core');
  drupal_add_library('system', 'ui.dialog');
  drupal_add_library('system', 'ui.widget');
  drupal_add_library('system', 'ui.position');
  drupal_add_library('system', 'ui.size');
  drupal_add_library('system', 'ui.autocomplete');
  drupal_add_library('system', 'ui.selectable');

  drupal_add_css(drupal_get_path('module', 'skeletome_util') . '/inc/skeletome_admin.css', array('group' => CSS_DEFAULT));
  drupal_add_js(drupal_get_path('module', 'skeletome_util') .'/inc/skeletome_admin.js', array('group' => JS_DEFAULT));

  $vid = get_vid_for_vocabulary('generic_tags_vocabulary');
  $tags = get_tags_for_vid($vid);

  $list_html = create_list_html($tags);
  $title = '<div class="block-title"><h2 class="title">Current tags</h2></div>';

  $buttons = '<span style="text-align:right;"><a id="create_tag_button" href="javascript:void(0)">Create Tag</a><a id="delete_tag_button" href="javascript:void(0)">Delete</a></span>';

  $add_identifier_dialog = '<div id="add_tag_dialog" title="Create tag"><form>
      <div class="ui-widget"><div style="float:left;"><label for="tag_input">Tag: </label></div><div style="float:right;"><input id="tag_input" /></div></div>
      </form></div>';


  $form['tags'] = array(
    '#markup' =>  $title . $list_html . $add_identifier_dialog,
    '#weight' => 1
  );
  
  return $form;
}

function create_list_html($tags) {
  $html = '';

  $html = $html . '<table id="box-table"><tbody>';
  $html = $html . '<tr><td>';

  $html = $html . '<span class="killer"><a id="create_tag_button" href="javascript:void(0)">Create Tag</a><br/><a id="delete_tag_button" href="javascript:void(0)">Delete</a></span>';


  $html .= '<ol id="selectable">';
  if (count($tags) == 0) {
      $html .= '<li><i>(Currently there are no tags defined.)</i></li>';
  } else {
    foreach ($tags as $tid => $tag) {
      $html .= '<li class="ui-widget-content" id="' . $tid . '">' . $tag . '</li>';
    }
  }
  $html .= '</ol>';

  $html = $html . '</td></tr></tbody></table>';

  return $html;
}

function add_generictag_callback() {
  $newTag = $_POST['newTag'];

  if ($newTag != NULL) {
    if ($newTag !== '') {
      $vid = get_vid_for_vocabulary('generic_tags_vocabulary');
      $new_term = (object) array (
	'vid'	=> $vid,
      );
      $new_term->name = $newTag;
      taxonomy_term_save($new_term);
      echo $new_term->tid;
    } else {
      echo "ERROR";
    }
  } else {
    echo "ERROR";
  }

  exit;
}

function delete_generictag_callback() {
  $tid = $_POST['tid'];
  if ($tid != NULL) {
    if ($tid !== '') {
      taxonomy_term_delete($tid);
    }
  }

  exit;
}

