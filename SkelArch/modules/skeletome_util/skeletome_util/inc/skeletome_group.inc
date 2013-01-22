<?php

function retrieve_groups() {
  $groups = array();

  $sql = 'SELECT gid FROM {og}';
  $result = db_query($sql, array());
  foreach ($result as $row) {
    $groups[] = $row->gid;
  }

  return $groups;
}

function get_groups_with_exact_name($name) {
  $groups = array();

  $sql = 'SELECT gid FROM {og} o WHERE o.label = :label';
  $result = db_query($sql, array(':label' => $name));
  foreach ($result as $row) {
    $groups[] = $row->gid;
  }

  return $groups;
}

function trasfer_group_membership($origin_node, $dest_node) {
  $dest_node->group_content_access['und'][0]['value'] = $origin_node->group_content_access['und'][0]['value'];
  if (array_key_exists('und', $origin_node->group_audience)) {
    $group_audience = $origin_node->group_audience['und'];
    $count = 0;
    foreach ($group_audience as $ga) {
      $dest_node->group_audience['und'][$count]['gid'] = $ga['gid'];
      $dest_node->group_audience['und'][$count]['state'] = $ga['state'];
      $dest_node->group_audience['und'][$count]['created'] = $ga['created'];
      $count++;
    }
  }
}

function get_visibility_for_group($nid) {
  $sql = 'SELECT entity_id, group_access_value FROM {field_data_group_access} f WHERE f.entity_id = :etid';
  $result = db_query($sql, array(':etid' => $nid));
  foreach ($result as $row) {
    return $row->group_access_value;
  }

  return NULL;
}

function get_public_groups() {
  $groups = array();
  $sql = 'SELECT entity_id, group_access_value FROM {field_data_group_access} f WHERE f.group_access_value = :group_access_value';
  $result = db_query($sql, array(':group_access_value' => '0'));
  foreach ($result as $row) {
    $groups[] = $row->entity_id;
  }

  return $groups;
}

function get_gid_for_group($nid) {
  $sql = 'SELECT gid, etid FROM {og} o WHERE o.etid = :etid';
  $result = db_query($sql, array(':etid' => $nid));
  foreach ($result as $row) {
    return $row->gid;
  }

  return NULL;
}

function get_nid_for_group($gid) {
  $sql = 'SELECT gid, etid FROM {og} o WHERE o.gid = :gid';
  $result = db_query($sql, array(':gid' => $gid));
  foreach ($result as $row) {
    return $row->etid;
  }

  return NULL;
}

function get_nids_for_groups($group_gids) {
  $groups = array();
  foreach ($group_gids as $gid) {
    $groups[] = get_nid_for_group($gid);
  }

  return $groups;
}

function get_no_members_for_group($gid) {
  $sql = 'SELECT count(etid) as no_members, gid, entity_type FROM {og_membership} o WHERE o.gid = :gid AND o.entity_type = :entity_type AND o.state = :state';
  $result = db_query($sql, array(':gid' => $gid, ':entity_type' => 'user', ':state' => '1'));

  foreach ($result as $row) {
    return $row->no_members;
  }
  return 0;
}

function get_groups_for_entity($etid, $ettype) {
  $groups = array();

  $sql = 'SELECT gid FROM {og_membership} ogm WHERE ogm.etid = :etid AND ogm.entity_type = :ettype AND ogm.state = :state';
  $result = db_query($sql, array(':etid' => $etid, ':ettype' => $ettype, ':state' => '1'));
  foreach ($result as $row) {
    $groups[] = $row->gid;
  }

  return $groups;
}

function is_currentuser_status_pending($gid) {
  global $user;

  $state = -1;
  $sql = 'SELECT state FROM {og_membership} ogm WHERE ogm.etid = :etid AND ogm.entity_type = :ettype AND ogm.gid = :gid';
  $result = db_query($sql, array(':etid' => $user->uid, ':ettype' => 'user', ':gid' => $gid));
  foreach ($result as $row) {
    $state = $row->state;
  }

  return $state == 2;
}

function group_has_patients($gid) {
  $no_nodes = 0;
  $sql = 'SELECT count(entity_id) as no_nodes FROM {field_data_group_audience} f WHERE f.group_audience_gid = :gid AND f.entity_type = :ettype AND f.bundle = :bundle';
  $result = db_query($sql, array(':gid' => $gid, ':ettype' => 'node', ':bundle' => 'patient'));
  foreach ($result as $row) {
    $no_nodes = $row->no_nodes;
  }

  return $no_nodes != 0;
}

function get_group_forum_nodes($gid) {
  $forum_nodes = array();
  $sql = 'SELECT entity_id FROM {field_data_group_audience} f WHERE f.group_audience_gid = :gid AND f.entity_type = :ettype AND f.bundle = :bundle';
  $result = db_query($sql, array(':gid' => $gid, ':ettype' => 'node', ':bundle' => 'forum'));
  foreach ($result as $row) {
    if (forum_has_patient($row->entity_id)) {
      $forum_nodes[] = $row->entity_id;
    }
  }

  return $forum_nodes;
}


function get_group_labels() {
  $grouplabels = array();

  $sql = 'SELECT gid,label FROM {og}';
  $result = db_query($sql, array());
  foreach ($result as $row) {
    $grouplabels[$row->gid] = $row->label;
  }

  return $grouplabels;
}

function get_group_label($gid) {
  $sql = 'SELECT label FROM {og} WHERE og.gid = :gid';
  $result = db_query($sql, array(':gid' => $gid));
  foreach ($result as $row) {
    return $row->label;
  }

  return NULL;
}

function get_available_groups_for_collaboration($node, $property, $idx) {
  global $user;

  $already_shared = array();
  if (array_key_exists('und', $node->$property)) {
    $groups = $node->$property;
    foreach ($groups['und'] as $group) {
      $already_shared[] = $group[$idx];
    }
  }

  $available_groups = array();
  $public_groups = get_public_groups();
  foreach ($public_groups as $group) {
    if ($idx === 'nid') {
      if (!in_array($group, $already_shared)) {
	$gid = get_gid_for_group($group);
	$available_groups[$gid] = $group;
      }
    } else {
      $gid = get_gid_for_group($group);
      if (!in_array($gid, $already_shared)) {
	$available_groups[$gid] = $group;
      }
    }
  }

  $user_groups = get_groups_for_entity($user->uid, 'user');
  foreach ($user_groups as $group) {
    if (!array_key_exists($group, $available_groups)) {
      if ($idx === 'nid') {
	$nid = get_nid_for_group($group);
	if (!in_array($nid, $already_shared)) {
	  $available_groups[$group] = $nid;
	}
      } else {
	if (!in_array($group, $already_shared)) {
	  $nid = get_nid_for_group($group);
	  $available_groups[$group] = $nid;
	}
      }
    }
  }

  return $available_groups;
}

function create_combohtml($group_list, $grouplist_id) {
  global $user;
  $user_groups = get_nids_for_groups(get_groups_for_entity($user->uid, 'user'));
  $user_member_available = array();
  $user_nonmember_available = array();
  foreach ($group_list as $group) {
    if (in_array($group, $user_groups)) {
      $user_member_available[] = $group;
    } else {
      $user_nonmember_available[] = $group;
    }
  }

  $html = '<select id="' . $grouplist_id . '" multiple="multiple">';
  if (!empty($user_member_available)) {
    $html .= '<optgroup label="Your groups">';
    foreach ($user_member_available as $group) {
      $group_node = node_load($group);
      $html .= '<option class="' . $group . '" value="' . $group . '">' . $group_node->title . '</option>';
    }
    $html .= '</optgroup>';
  }

  if (!empty($user_nonmember_available)) {
    $html .= '<optgroup label="Other groups">';
    foreach ($user_nonmember_available as $group) {
      $group_node = node_load($group);
      $html .= '<option class="' . $group . '" value="' . $group . '">' . $group_node->title . '</option>';
    }
    $html .= '</optgroup>';
  }
  
  $html .= '</select>';
  return $html;
}
