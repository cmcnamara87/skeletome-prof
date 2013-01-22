<?php

function create_new_forum($name) {
  $vid = get_vid_for_forums();

  $new_forum = (object) array (
    'vid'		=> $vid,
    'name'		=> $name,
    'description' 	=> '',
    'parent' 		=> array (
      0 => '0',
    ),
  );

  taxonomy_term_save($new_forum);
  insert_into_forumaccess_table($new_forum->tid, 2);
  insert_into_forumaccess_table($new_forum->tid, 3);
  insert_into_forumaccess_table($new_forum->tid, 4);
  insert_into_forumaccess_table($new_forum->tid, 5);

  return $new_forum->tid;
}

function get_vid_for_forums() {
  $sql = 'SELECT vid FROM {taxonomy_vocabulary} t WHERE t.machine_name = :machine_name';
  $result = db_query($sql, array(':machine_name' => 'forums'));
  foreach ($result as $row) {
    return $row->vid;
  }

  return NULL;
}

function delete_forum($tid) {
  taxonomy_term_delete($tid);
}

function insert_into_forumaccess_table($tid, $rid) {
  db_insert('forum_access')->fields(array(
    'tid'		=> $tid,
    'rid'		=> $rid,
    'grant_view'	=> 1,
    'grant_update'	=> 1,
    'grant_delete'	=> 1,
    'grant_create'	=> 1,
    'priority'		=> 0
  ))->execute();
}

function get_forum_for_group($group_nid) {
  $sql = 'SELECT entity_id FROM {field_data_field_forum_group} f WHERE f.field_forum_group_nid = :group_nid';
  $result = db_query($sql, array(':group_nid' => $group_nid));
  foreach ($result as $row) {
    return $row->entity_id;
  }

  return NULL;
}

function get_group_for_forum($tid) {
  $sql = 'SELECT field_forum_group_nid FROM {field_data_field_forum_group} f WHERE f.entity_id = :entity_id';
  $result = db_query($sql, array(':entity_id' => $tid));
  foreach ($result as $row) {
    return $row->field_forum_group_nid;
  }

  return NULL;
}

function get_forumtopics_for_patient($patient_nid) {
  $results = array();
  $sql = 'SELECT entity_id FROM {field_data_field_forum_patient} f WHERE f.field_forum_patient_nid  = :patient_nid';
  $result = db_query($sql, array(':patient_nid' => $patient_nid));
  foreach ($result as $row) {
    $results[] = $row->entity_id;
  }

  return $results;
}

function get_entity_for_param($table, $field, $param) {
  $results = array();
  $sql = 'SELECT entity_id FROM {' . $table . '} f WHERE f.' . $field . '  = :param';
  $result = db_query($sql, array(':param' => $param));
  foreach ($result as $row) {
    $results[] = $row->entity_id;
  }

  return $results;
}

function get_forumtopics_for_forum($tid) {
  $results = array();
  $sql = 'SELECT nid FROM {forum} f WHERE f.tid = :tid';
  $result = db_query($sql, array(':tid' => $tid));
  foreach ($result as $row) {
    $results[] = $row->nid;
  }

  return $results;
}

function find_forum_with_name($name) {
  $sql = 'SELECT tid FROM {taxonomy_term_data} n WHERE n.name = :name';
  $result = db_query($sql, array(':name' => $name));
  $tids = array();
  foreach ($result as $row) {
    $tids[] = $row->tid;
  }

  if (!empty($tids)) {
    return $tids[0];
  } else {
    return NULL;
  }
}

function get_no_topics_for_forum($tid) {
  $sql = 'SELECT count(nid) as count, tid FROM {forum_index} f WHERE f.tid = :tid';
  $result = db_query($sql, array(':tid' => $tid));

  foreach ($result as $row) {
    return $row->count;
  }

  return 0;
}

function get_no_comments_for_forum($tid) {
  $comment_count = 0;
  $sql = 'SELECT comment_count, tid FROM {forum_index} f WHERE f.tid = :tid';
  $result = db_query($sql, array(':tid' => $tid));

  foreach ($result as $row) {
    $comment_count += $row->comment_count;
  }

  return $comment_count;
}

function is_currentuser_forum_moderator($forum_nid) {
  global $user;
  $results = array();
  $sql = 'SELECT nid FROM {acl_node} as acln JOIN {acl_user} as aclu on acln.acl_id=aclu.acl_id WHERE aclu.uid = :uid';
  $result = db_query($sql, array(':uid' => $user->uid));

  foreach ($result as $row) {
    $results[] = $row->nid;
  }

  if (in_array($forum_nid, $results)) {
    return TRUE;
  }

  return FALSE;
}

function forum_has_patient($nid) {
  $count = 0;
  $sql = 'SELECT count(field_forum_patient_nid) as patient_count FROM {field_data_field_forum_patient } f WHERE f.entity_id = :nid AND f.entity_type = :ettype AND f.bundle = :bundle';
  $result = db_query($sql, array(':nid' => $nid, ':ettype' => 'node', ':bundle' => 'forum'));
  foreach ($result as $row) {
    $count = $row->patient_count;
  }

  return $count != 0;
}

function get_forumsummary($forum_nid, $patient_nid) {
  $candidates = array();
  $sql = 'SELECT entity_id FROM {field_data_field_forumsummary_patient} f WHERE f.field_forumsummary_patient_nid = :nid';
  $result = db_query($sql, array(':nid' => $patient_nid));
  foreach ($result as $row) {
    $candidates[] = $row->entity_id;
  }

  $candidates2 = array();
  $sql = 'SELECT entity_id FROM {field_data_field_forumsummary_forum } f WHERE f.field_forumsummary_forum_nid = :nid';
  $result = db_query($sql, array(':nid' => $forum_nid));
  foreach ($result as $row) {
    $candidates2[] = $row->entity_id;
  }

  $intersect = array_intersect($candidates, $candidates2);
  if (!empty($intersect)) {
    foreach ($intersect as $id => $val) {
      return $val;
    }
  }

  return NULL;
}

function get_forumsummary_for_patient($patient_nid) {
  $candidates = array();
  $sql = 'SELECT entity_id FROM {field_data_field_forumsummary_patient} f WHERE f.field_forumsummary_patient_nid = :nid';
  $result = db_query($sql, array(':nid' => $patient_nid));
  foreach ($result as $row) {
    $candidates[] = $row->entity_id;
  }

  return $candidates;
}


function create_forum_buttons($node, $parent_tid, $parent_name) {
  $html = '';
  $base_path = url(NULL, array('absolute' => TRUE));

  $has_access_rights = FALSE;
  $group_nid = get_group_for_forum($parent_tid);
  $group_node = node_load($group_nid);
  //TODO: Find the real group administrator for OG information - till then assume that the owner of the group node is also the administrator
  //  $group_gid = get_gid_for_group($group_nid);
  //  $group = og_get_group('node', $group_nid);

  if (is_current_user_owner($group_node)) {
    $has_access_rights = TRUE;
  } else {
    //CHECK FORUM MODERATORS
    $has_access_rights = is_currentuser_forum_moderator($node->nid);
  }

  $patient_button_html = '';
  if (array_key_exists('und', $node->field_forum_patient)) {
    if (currentuser_has_access($node->field_forum_patient['und'][0]['nid'])) {
      $patient_button_html .= '<a id="forward_button" href="' . $base_path . 'node/' . $node->field_forum_patient['und'][0]['nid'] . '">To patient overview &gt;&gt;</a>';
    } else {
      $patient_button_html = '<i>(The patient details have not been shared with your group.)</i>';
    }
  } else {
    if (array_key_exists('und', $node->field_forum_patientprovenance)) {
      if (currentuser_has_access($node->field_forum_patientprovenance['und'][0]['nid'])) {
	if (is_current_user_owner(node_load($node->field_forum_patientprovenance['und'][0]['nid']))) {
	  $patient_button_html .= '<a id="forward_button" href="' . $base_path . 'node/' . $node->field_forum_patientprovenance['und'][0]['nid'] . '">To patient overview &gt;&gt;</a>';
	} else {
	  $patient_button_html = '<i>(The patient has been withdrawn from discussion by the case owner.)</i>';
	}
      } else {
	$patient_button_html = '<i>(The patient details have not been shared with your group.)</i>';
      }
    } else {
      $patient_button_html = '<i>(The patient details are missing.)</i>';
    }
  }

  if (currentuser_is_member_of($group_nid)) {
    $buttons = '<div style="text-align:left;"><a id="back_button" href="' . $base_path . 'forum/' . $parent_tid . '">&lt;&lt; To ' . $parent_name . '</a><span style="float:right;">' . $patient_button_html . '</span></div><hr style="border:dashed #CCCCCC; border-width:1px 0 0; height:0;" />';
  } else {
    $buttons = '<div style="text-align:right;">' . $patient_button_html . '</div><hr style="border:dashed #CCCCCC; border-width:1px 0 0; height:0;" />';
  }
  $html .= $buttons;

  if ($has_access_rights) {
    $ac_html = '<div class="block-title"><h2 class="title">Sharing options</h2></div>';

    $available_groups = get_available_groups_for_collaboration($node, 'group_audience', 'gid');
    $available_groups_html = create_combohtml($available_groups, 'available_groups');
    $ac_html .= 'Share this discussion topic with: ' . $available_groups_html . ' <a id="share_button" href="javascript:void(0)">Go</a>';

    if (array_key_exists('und', $node->field_forum_patient)) {
      global $user;
      $owner = get_owner_for_node($node->field_forum_patient['und'][0]['nid']);

      if ($user->uid !== $owner) {
	if (!user_has_access(user_load($owner), $node->nid)) {
	  $ac_html .= '<br />Share this discussion topic with the case owner: ';

	  if (array_key_exists('und', $node->field_forum_useraudience)) {
	    $url = $base_path . 'skeletome-util/forum/disable-caseowner' . $node->nid;
	    $ac_html .= '<a id="share_wo_button" href="' . $url . '">Enable</a>';
	  } else {
	    $url = $base_path . 'skeletome-util/forum/enable-caseowner' . $node->nid . '/' . $node->field_forum_patient['und'][0]['nid'];
	    $ac_html .= '<a id="share_wo_button" href="' . $url . '">Enable</a>';
	  }
	}
      }
    }
    if (array_key_exists('und', $node->group_audience)) {
      $disc_groups = array();
      foreach($node->group_audience['und'] as $group) {
	$g_nid = get_nid_for_group($group['gid']);
	if ($g_nid !== $group_nid) {
	  $disc_groups[$group['gid']] = $g_nid;
	}
      }

      if (!empty($disc_groups)) {
	$ac_html .= '<br/>This discussion topic is currently shared with following groups:';
	$ac_html .= '<ul>';
	foreach($disc_groups as $gid => $g_nid) {
	  $g_node = node_load($g_nid);
	  $url = $base_path . 'skeletome-util/forum/unshare' . $node->nid . '/' . $gid;
	  $ac_html .= '<li><a href="' . $base_path . 'node/' . $g_nid . '">' . $g_node->title . '</a> <a href="' . $url . '"><img src="' . $base_path . 'delete.png" width="1%" /></a></li>';
	}
	$ac_html .= '</ul>';
      }
    }

    $html .= $ac_html . '<hr style="border:dashed #CCCCCC; border-width:1px 0 0; height:0;" />';
  }

  return $html;
}

function share_forum_callback() {
  $now = getdate();
  $groupNids = $_POST['groupNids'];
  $forumNid = $_POST['forumNid'];

  $forum_node = node_load($forumNid);
  $count = 0;
  if (array_key_exists('und', $forum_node->group_audience)) {
    $count = count($forum_node->group_audience['und']);
  }

  foreach($groupNids as $group_nid) {
    $gid = get_gid_for_group($group_nid);
    $forum_node->group_audience['und'][$count]['gid'] = $gid;
    $forum_node->group_audience['und'][$count]['state'] = '1';
    $forum_node->group_audience['und'][$count]['created'] = $now[0];

    $count++;
  }
  
  node_save($forum_node);
  exit;
}

function unshare_forum_callback($forum_nid, $gid) {
  $forum_node = node_load($forum_nid);

  $index = -1;
  for($i = 0; $i < count($forum_node->group_audience['und']); $i++) {
    if ($patient_node->$forum_node['und'][$i]['gid'] === $gid) {
      $index =$i;
    }
  }
  array_splice($forum_node->group_audience['und'], $index, 1);
  node_save($forum_node);
  drupal_goto('node/' . $forum_node->nid);
}

function enableco_forum_callback($forum_nid, $patient_nid) {
  $forum_node = node_load($forum_nid);
  $forum_node->field_forum_useraudience['und'][0]['uid'] = get_owner_for_node($patient_nid);
  node_save($forum_node);
}

function disableco_forum_callback($forum_nid) {
  $forum_node = node_load($forum_nid);
  $forum_node->field_forum_useraudience = array();
  node_save($forum_node);
}
