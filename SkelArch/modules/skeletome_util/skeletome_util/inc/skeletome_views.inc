<?php

define('__EDIT_PREFIX__', '<td class="views-field views-field-nid" >');
define('__DELETE_PREFIX__', '<td class="views-field views-field-nid-1" >');
define('__NID_2__', '<td class="views-field views-field-nid-2" >');

define('__ROW_START__', '<tr class="');
define('__ROW_END__', '</tr>');
define('__GROUP_ROW_HEAD__', '<td class="views-field views-field-gid" >');
define('__GROUP_ROW_END__', '</td>');

define('__ED_POSTFIX__', '</td>');
define('__CAPTION_PRE__', '<caption>');
define('__CAPTION_POST__', '</caption>');

function create_new_gmview_output($output) {
  $new_output = '';
  $new_output = find_and_replace($output, __EDIT_PREFIX__, 'edit.png', 'edit');
  $new_output = find_and_replace($new_output, __DELETE_PREFIX__, 'delete.png', 'delete');
  return $new_output;
}

function create_new_tableview_output($output, $ul_class) {
  $new_output = '';
  $new_output = find_and_replace($output, __EDIT_PREFIX__, 'edit.png', 'edit');
  $new_output = find_and_replace($new_output, __DELETE_PREFIX__, 'delete.png', 'delete');
  $new_output = my_str_replace($new_output, '<ul>', '<ul id="' . $ul_class . '">');
  return $new_output;
}

function create_new_patientdiag_output($output) {
  $new_output = '';
  $new_output = find_and_replace($output, __EDIT_PREFIX__, 'delete.png', 'delete');
  $new_output = find_and_replace_comment($new_output, __DELETE_PREFIX__);
  return $new_output;
}

function create_new_allgroups_output($output) {
  $new_output = find_and_replace_visibility($output, __EDIT_PREFIX__);
  $new_output = find_and_replace_no_members($new_output, __DELETE_PREFIX__);
  $new_output = find_and_replace_manager($new_output, __NID_2__);
  return $new_output;
}

function create_new_mygroups_output($output) {
  $new_output = find_and_replace_visibility($output, __EDIT_PREFIX__);
  $new_output = find_and_replace_no_members($new_output, __DELETE_PREFIX__);
  $new_output = find_and_replace_manager($new_output, __NID_2__);
  return $new_output;
}

function create_new_patients_output($input) {
  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, __CAPTION_PRE__);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen(__CAPTION_PRE__));
    $tmp = substr($tmp, $idx + strlen(__CAPTION_PRE__));
    $idx2 = strpos($tmp, __CAPTION_POST__);
    $content = trim(substr($tmp, 0, $idx2));

    $new_content = '<div class="block-title"><h2 class="title">' . $content . '</h2></div>';

    $new_output = $new_output . $new_content;
    $tmp = substr($tmp, $idx2 + strlen(__CAPTION_POST__));
    $idx = strpos($tmp, __CAPTION_PRE__);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function create_new_patientsbycase_output($input) {
  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, __ROW_START__);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen(__ROW_START__));
    $tmp = substr($tmp, $idx + strlen(__ROW_START__));
    $idx2 = strpos($tmp, __ROW_END__);
    $to_process = substr($tmp, 0, $idx2);
    $processed_row = process_groups($to_process);
    $new_output = $new_output . $processed_row . __ROW_END__;
    $tmp = substr($tmp, $idx2 + strlen(__ROW_END__));
    $idx = strpos($tmp, __ROW_START__);
  }
  $new_output = $new_output . $tmp;
  return $new_output;
}

function process_groups($to_process) {
  $nid = find_node_nid($to_process);
  $groups_html = get_groups_for_node($nid);
  return single_find_and_replace($to_process, __GROUP_ROW_HEAD__, __GROUP_ROW_END__, $groups_html);
}

function get_groups_for_node($nid) {
  $base_path = url(NULL, array('absolute' => TRUE));
  global $user;
  $user_groups = get_groups_for_entity($user->uid, 'user');
  $node_groups = get_groups_for_entity($nid, 'node');

  $groups_to_format = array();
  if (is_user_owner($nid, $user->uid)) {
    $groups_to_format = $node_groups;
  } else {
    foreach($node_groups as $group) {
      if (in_array($group, $user_groups)) {
	$groups_to_format[] = $group;
      }
    }
  }

  if (count($groups_to_format) != 0) {
    $output = '<ul id="navlist">';
    for($i = 0; $i < count($groups_to_format); $i++) {
      $group = $groups_to_format[$i];
      $label = get_group_label($group);
      $nid = get_nid_for_group($group);
      $output .= '<li><a href="' . $base_path . 'node/' . $nid . '">' . $label . '</a></li>';
    }
    $output .= '</ul>';
  } else {
    $output = '<ul id="navlist"><li><i>Not shared</i></li></ul>';
  }

  return $output;
}

function single_find_and_replace($input, $start, $end, $content) {
  $output = '';
  $tmp = $input;
  $idx = strpos($tmp, $start);
  $output .= substr($tmp, 0, $idx + strlen($start));
  $output .= $content;

  $tmp = substr($tmp, $idx + strlen($start));;
  $idx = strpos($tmp, $end);
  $output .= substr($tmp, $idx);
  return $output;
}

function find_node_nid($input) {
  $tmp = $input;
  $idx = strpos($tmp, '<a href="/skelarch/node/');
  $tmp = substr($tmp, $idx + strlen('<a href="/skelarch/node/'));
  $idx = strpos($tmp, '"');
  $tmp = substr($tmp, 0, $idx);
  return $tmp;
}

function create_new_mypatientsbycase_results($view_result) {
  $new_view_result = array();

  foreach ($view_result as $row) {
    if (!isset($duplicates[$row->nid])) {
      $new_view_result[] = $row;
      $duplicates[$row->nid] = array(
	$row->og_og_membership_gid => $row->og_og_membership_gid
      );
    }
  }

  return $new_view_result;
}

function create_new_allpatients_results($view_result, $remove_duplicates) {
  $results = create_groupbased_results($view_result, 'nid');
  if ($remove_duplicates) {
    return create_new_mypatientsbycase_results($results);
  } else {
    return $results;
  }
}

function create_new_allgroups_results($view_result) {
  global $user;
  $new_view_result = array();
  $user_groups = get_groups_for_entity($user->uid, 'user');

  foreach ($view_result as $row) {
    $gid = get_gid_for_group($row->nid);
    $visibility = get_visibility_for_group($row->nid);
    if (in_array($gid, $user_groups) || ($visibility === '0')) {
      $new_view_result[] = $row;
    }
  }

  return $new_view_result;
}

function create_new_mygroups_results($view_result) {
  global $user;
  $new_view_result = array();
  $user_groups = get_groups_for_entity($user->uid, 'user');

  foreach ($view_result as $row) {
    $gid = get_gid_for_group($row->nid);
    if (in_array($gid, $user_groups)) {
      $new_view_result[] = $row;
    }
  }

  return $new_view_result;
}

function create_groupbased_results($results, $field) {
  global $user;
  $new_view_result = array();
  $groups = get_groups_for_entity($user->uid, 'user');

  foreach ($results as $row) {
    $owner = get_owner_for_node($row->$field);
    if ($owner === $user->uid) {
      $new_view_result[] = $row;
    } else {
      $node_groups = get_groups_for_entity($row->$field, 'node');
      $intersect = array_intersect($groups, $node_groups);
      if (!empty($intersect)) {
 	$new_view_result[] = $row;
      }
    }
  }

  return $new_view_result;
}

function my_str_replace($input, $needle, $replacement) {
  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $needle);
  while ($idx !== FALSE) {
    $new_output .= substr($tmp, 0, $idx);
    $new_output .= $replacement;
    $tmp = substr($tmp, $idx + strlen($needle));
    $idx = strpos($tmp, $needle);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function find_and_replace_comment($input, $prefix) {
  $base_path = url(NULL, array('absolute' => TRUE));

  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $prefix);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen($prefix));
    $tmp = substr($tmp, $idx + strlen($prefix));
    $idx2 = strpos($tmp, __ED_POSTFIX__);
    $content = trim(substr($tmp, 0, $idx2));

    $comment_text = '<i>(Please click to add a comment)</i>';
    $diag_node = node_load($content);
    if (array_key_exists('und', $diag_node->field_diagnosis_diagcomment)) {
      $diag_comment_node = node_load($diag_node->field_diagnosis_diagcomment['und'][0]['nid']);
      if (array_key_exists('und', $diag_comment_node->body)) {
	if ($diag_comment_node->body['und'][0]['value'] !== '') {
	  $comment_text = $diag_comment_node->body['und'][0]['value'];
	}
      }
    }
    $new_content = '<span class="edit" id="comment_' . $content . '">' . $comment_text . '</span>';
    $new_output = $new_output . $new_content . __ED_POSTFIX__;
    $tmp = substr($tmp, $idx2 + strlen(__ED_POSTFIX__));
    $idx = strpos($tmp, $prefix);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function find_and_replace($input, $prefix, $img, $action) {
  $base_path = url(NULL, array('absolute' => TRUE));

  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $prefix);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen($prefix));
    $tmp = substr($tmp, $idx + strlen($prefix));
    $idx2 = strpos($tmp, __ED_POSTFIX__);
    $content = trim(substr($tmp, 0, $idx2));
    $new_content = '<a id ="' . $action . '_' . $content . '" href="javascript:void(0)""><img src="' . $base_path . $img . '" /></a>';
    $new_output = $new_output . $new_content . __ED_POSTFIX__;
    $tmp = substr($tmp, $idx2 + strlen(__ED_POSTFIX__));
    $idx = strpos($tmp, $prefix);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function find_and_replace_manager($input, $prefix) {
  $base_path = url(NULL, array('absolute' => TRUE));

  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $prefix);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen($prefix));
    $tmp = substr($tmp, $idx + strlen($prefix));
    $idx2 = strpos($tmp, __ED_POSTFIX__);
    $content = trim(substr($tmp, 0, $idx2));

    $owner = get_owner_for_node($content);
    $user = user_load($owner);
    $new_content = '<a href="' . $base_path . 'user/' . $user->uid . '">' . $user->name . '</a>';

    $new_output = $new_output . $new_content . __ED_POSTFIX__;
    $tmp = substr($tmp, $idx2 + strlen(__ED_POSTFIX__));
    $idx = strpos($tmp, $prefix);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function find_and_replace_visibility($input, $prefix) {
  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $prefix);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen($prefix));
    $tmp = substr($tmp, $idx + strlen($prefix));
    $idx2 = strpos($tmp, __ED_POSTFIX__);
    $content = trim(substr($tmp, 0, $idx2));
    $visibility = get_visibility_for_group($content);
    if ($visibility === '0') {
      $new_content = 'Public';
    } else {
      $new_content = 'Private';
    }
    $new_output = $new_output . $new_content . __ED_POSTFIX__;
    $tmp = substr($tmp, $idx2 + strlen(__ED_POSTFIX__));
    $idx = strpos($tmp, $prefix);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function find_and_replace_no_members($input, $prefix) {
  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $prefix);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen($prefix));
    $tmp = substr($tmp, $idx + strlen($prefix));
    $idx2 = strpos($tmp, __ED_POSTFIX__);
    $content = trim(substr($tmp, 0, $idx2));

    $gid = get_gid_for_group($content);
    $count = get_no_members_for_group($gid);
    $new_content = $count;

    $new_output = $new_output . $new_content . __ED_POSTFIX__;
    $tmp = substr($tmp, $idx2 + strlen(__ED_POSTFIX__));
    $idx = strpos($tmp, $prefix);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function find_and_replace_genrep($input, $prefix, $img, $action) {
  $base_path = url(NULL, array('absolute' => TRUE));

  $new_output = '';
  $tmp = $input;
  $idx = strpos($tmp, $prefix);
  while ($idx !== FALSE) {
    $new_output = $new_output . substr($tmp, 0, $idx + strlen($prefix));
    $tmp = substr($tmp, $idx + strlen($prefix));
    $idx2 = strpos($tmp, __ED_POSTFIX__);
    $content = trim(substr($tmp, 0, $idx2));
    $genrep_nid = get_genrep_for_gm($content);
//    $new_content = '<a href="' . $content . '/' . $action . '"><img src="' . $base_path . $img . '" /></a>';
    $new_content = '<a id ="' . $action . '_' . $genrep_nid . '_' . $content . '" href="#""><img src="' . $base_path . $img . '" /></a>';
    $new_output = $new_output . $new_content . __ED_POSTFIX__;
    $tmp = substr($tmp, $idx2 + strlen(__ED_POSTFIX__));
    $idx = strpos($tmp, $prefix);
  }

  $new_output = $new_output . $tmp;
  return $new_output;
}

function get_genrep_for_gm($gm_nid) {
  $sql = 'SELECT entity_id, field_genrep_gm_nid FROM {field_data_field_genrep_gm} f WHERE f.field_genrep_gm_nid = :field_genrep_gm_nid';
  $result = db_query($sql, array(':field_genrep_gm_nid' => $gm_nid));
  foreach ($result as $r) {
    return $r->entity_id;
  }

  return NULL;
}
