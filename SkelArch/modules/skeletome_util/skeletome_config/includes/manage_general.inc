<?php

define('_MODULE_NODE_', 'node');
define('_MODULE_COMMENT_', 'comment');
define('_MODULE_USER_', 'user');
define('_MODULE_MEDIA_', 'media');
define('_MODULE_SEARCH_', 'search');
define('_MODULE_FILTER_', 'filter');
define('_MODULE_FORUM_', 'forum');
define('_MODULE_OG_', 'og');

define('_FIELD_SKELETOME_TAGS_', 'field_skeletome_tags');

function perform_gm_action($action) {
  if ($action === '0') {
    create_user_roles();
  }
  if ($action === '1') {
    set_auth_ac();
    set_forumadmin_ac();
    set_admin_ac();
    set_administrator_ac();
  }
  if ($action === '2') {
    add_missing_fields();
  }
  if ($action === '3') {
    create_patient_views();
  }
}

function create_user_roles() {
  insert_into_actualroles_table(4, 'forumadmin', 2);
  insert_into_actualroles_table(5, 'admin', 3);
}

function create_patient_views() {
  $my_patients_views = array('my_patients_by_group:view_block:Group', 'my_patients_by_case:view_block:Case');
  $all_patients_views = array('all_patients_by_group:view_block:Group', 'all_patients_by_case:view_block:Case');

  create_viewpage('All patients', 'patients', $all_patients_views);
  create_viewpage('My patients', 'mypatients', $my_patients_views);
}

function create_viewpage($title, $url_alias, $views) {
  global $user;

  $viewpage_node = new stdClass();
  $viewpage_node->type = 'view_page';
  $viewpage_node->language = 'und';
  $viewpage_node->uid = $user->uid;

  $viewpage_node->title = $title;
  $viewpage_node->field_viewpage_url['und'][0]['value'] = $url_alias;
  $viewpage_node->field_viewpage_url['und'][0]['safe_value'] = $url_alias;

  $viewpage_node->field_viewpage_currentview['und'][0]['value'] = $views[0];
  $viewpage_node->field_viewpage_currentview['und'][0]['safe_value'] = $views[0];

  $count = 0;
  foreach ($views as $view) {
    $viewpage_node->field_viewpage_viewdetails['und'][$count]['value'] = $view;
    $viewpage_node->field_viewpage_viewdetails['und'][$count]['safe_value'] = $view;
    $count++;
  }

  node_save($viewpage_node);
}


function add_missing_fields() {
  $types_array = array('clinical_summary', 'patient', 'xray_description');
  $field_instance = field_info_instance('node', _FIELD_SKELETOME_TAGS_, 'x_ray');
  foreach ($types_array as $type) {
    $field_instance['bundle'] = $type;
    field_create_instance($field_instance);
  }

  create_forumtopic_fields();
  create_forum_fields();
}

function create_forumtopic_fields() {
  $t = get_t();

  $field_description = array (
    'field_forum_attachment' => array(
      'field_name'	=> 'field_forum_attachment',
      'label'		=> $t('Attachment'),
      'cardinality'	=> -1,
      'type'		=> 'file',
      'settings'	=> array(
	'display_field' => '1',
	'uri_scheme' => 'private'
      )
    ),
    'field_forum_patient' => array(
      'field_name'	=> 'field_forum_patient',
      'label'		=> $t('Patient'),
      'cardinality'	=> 1,
      'type'		=> 'node_reference',
      'settings'	=> array(
	'referenceable_types' => array(
	  'patient' => 'patient'
	)
      )
    ),
    'field_forum_patientprovenance' => array(
      'field_name'	=> 'field_forum_patientprovenance',
      'label'		=> $t('Patient provenance'),
      'cardinality'	=> 1,
      'type'		=> 'node_reference',
      'settings'	=> array(
	'referenceable_types' => array(
	  'patient' => 'patient'
	)
      )
    ),
    'field_forum_useraudience' => array(
      'field_name'	=> 'field_forum_useraudience',
      'label'		=> $t('User audience'),
      'cardinality'	=> -1,
      'type'		=> 'user_reference',
      'settings'	=> array(
	'referenceable_roles' => 
	  array (
	    2 => '2',
	    4 => 0,
	    5 => 0,
	    3 => 0,
	  ),
	'referenceable_status' => 
	  array (
	    1 => '1',
	    0 => 0,
	  )
      )
    ),
  );

  $field_instance_desc = array(
    'field_forum_attachment' => array(
      'field_name' => 'field_forum_attachment',
      'label'       => $t('Attachment'),
      'cardinality' => -1,
      'widget'      => array(
        'type'    => 'file_generic',
      ),
      'display' => array(
	'default' => array(
	  'type'  => 'hidden',
	  'label' => 'hidden',
	),
        'full' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
      ),
      'settings' => array(
        'file_extensions' => 'txt, pdf, doc, docx, jpg, png, gif',
        'file_directory' => 'forum/attachments'
      )
    ),
    'field_forum_patient' => array(
      'field_name'	=> 'field_forum_patient',
      'label'		=> $t('Patient'),
      'cardinality'	=> 1,
      'widget'		=> array(
        'type'    => 'node_reference_autocomplete',
      ),
      'display' => array(
	'default' => array(
	  'type'  => 'hidden',
	  'label' => 'hidden',
	),
        'full' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
      ),
    ),
    'field_forum_patientprovenance' => array(
      'field_name'	=> 'field_forum_patientprovenance',
      'label'		=> $t('Patient provenance'),
      'cardinality'	=> 1,
      'widget'		=> array(
        'type'    => 'node_reference_autocomplete',
      ),
      'display' => array(
	'default' => array(
	  'type'  => 'hidden',
	  'label' => 'hidden',
	),
        'full' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
      ),
    ),
    'field_forum_useraudience' => array(
      'field_name'	=> 'field_forum_useraudience',
      'label'		=> $t('User audience'),
      'cardinality'	=> -1,
      'widget'		=> array(
        'type'    => 'user_reference_autocomplete',
      ),
      'display' => array(
	'default' => array(
	  'type'  => 'hidden',
	  'label' => 'hidden',
	),
        'full' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
      ),
    ),
  );

  foreach ($field_description as $field) {
    field_create_field($field);
  }

  foreach ($field_instance_desc as $instance) {
    $instance['entity_type'] = 'node';
    $instance['bundle'] = 'forum';
    field_create_instance($instance);
  }
}

function create_forum_fields() {
  $t = get_t();

  $field_description = array (
    'field_forum_group' => array(
      'field_name'	=> 'field_forum_group',
      'label'		=> $t('Group'),
      'cardinality'	=> -1,
      'type'		=> 'node_reference',
      'settings'	=> array(
	'referenceable_types' => array(
	  'skeletome_group' => 'skeletome_group'
	)
      )
    ),
  );

  $field_instance_desc = array(
    'field_forum_group' => array(
      'field_name'	=> 'field_forum_group',
      'label'		=> $t('Group'),
      'cardinality'	=> -1,
      'widget'		=> array(
        'type'    => 'node_reference_autocomplete',
      ),
      'display' => array(
	'default' => array(
	  'type'  => 'hidden',
	  'label' => 'hidden',
	),
        'full' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'hidden',
        ),
      ),
    ),
  );

  foreach ($field_description as $field) {
    field_create_field($field);
  }

  foreach ($field_instance_desc as $instance) {
    $instance['entity_type'] = 'taxonomy_term';
    $instance['bundle'] = 'forums';
    field_create_instance($instance);
  }
}

function set_forumadmin_ac() {
  $forumadmin_node = array(
    'delete any forum content',
    'edit any forum content'
  );

  foreach ($forumadmin_node as $perm) {
    insert_into_roles_table(4, $perm, _MODULE_NODE_);
  }

  $forumadmin_forum = 'administer forums';
  insert_into_roles_table(4, $forumadmin_forum, _MODULE_FORUM_);
}

function set_admin_ac() {
  $admin_user = 'administer users';
  insert_into_roles_table(5, $admin_user, _MODULE_USER_);

  $admin_og = 'administer group';
  insert_into_roles_table(5, $admin_og, _MODULE_OG_);

  $admin_node = array(
    'create news_item content',
    'create skeletome_group content',
    'create vocabulary_type content',
    'delete any forum content',
    'delete any news_item content',
    'delete any skeletome_group content',
    'delete any vocabulary_type content',
    'delete own news_item content',
    'delete own skeletome_group content',
    'delete own vocabulary_type content',
    'edit any forum content',
    'edit any news_item content',
    'edit any skeletome_group content',
    'edit any vocabulary_type content',
    'edit own news_item content',
    'edit own skeletome_group content',
    'edit own vocabulary_type content'
  );

  foreach ($admin_node as $perm) {
    insert_into_roles_table(5, $perm, _MODULE_NODE_);
  }
}

function set_administrator_ac() {
  $administrator_node = array(
    'create news_item content',
    'create skeletome_group content',
    'create vocabulary_type content',
    'delete any clinical_summary content',
    'delete any consent_item content',
    'delete any contact_information content',
    'delete any diagnosis content',
    'delete any forum content',
    'delete any forum_summary content',
    'delete any genetic_report content',
    'delete any gene_mutation content',
    'delete any media_gallery content',
    'delete any news_item content',
    'delete any patient content',
    'delete any patient_note content',
    'delete any reference_letter content',
    'delete any skeletome_group content',
    'delete any vocabulary_type content',
    'delete any xray_description content',
    'delete any x_ray content',
    'delete own clinical_summary content',
    'delete own consent_item content',
    'delete own contact_information content',
    'delete own diagnosis content',
    'delete own forum content',
    'delete own genetic_report content',
    'delete own gene_mutation content',
    'delete own media_gallery content',
    'delete own news_item content',
    'delete own patient content',
    'delete own patient_note content',
    'delete own reference_letter content',
    'delete own skeletome_group content',
    'delete own vocabulary_type content',
    'delete own x_ray content',
    'edit any clinical_summary content',
    'edit any consent_item content',
    'edit any contact_information content',
    'edit any diagnosis content',
    'edit any forum content',
    'edit any forum_summary content',
    'edit any genetic_report content',
    'edit any gene_mutation content',
    'edit any media_gallery content',
    'edit any news_item content',
    'edit any patient content',
    'edit any patient_note content',
    'edit any reference_letter content',
    'edit any skeletome_group content',
    'edit any vocabulary_type content',
    'edit any xray_description content',
    'edit any x_ray content',
    'edit own clinical_summary content',
    'edit own consent_item content',
    'edit own contact_information content',
    'edit own diagnosis content',
    'edit own forum content',
    'edit own genetic_report content',
    'edit own gene_mutation content',
    'edit own media_gallery content',
    'edit own news_item content',
    'edit own patient content',
    'edit own patient_note content',
    'edit own reference_letter content',
    'edit own skeletome_group content',
    'edit own vocabulary_type content',
    'edit own x_ray content',
  );

  foreach ($administrator_node as $perm) {
    insert_into_roles_table(3, $perm, _MODULE_NODE_);
  }

}

function set_auth_ac() {
  $auth_media = array(
    'administer media',
    'edit media',
    'import media',
  );
  foreach ($auth_media as $perm) {
    insert_into_roles_table(2, $perm, _MODULE_MEDIA_);
  }

  $auth_search = array(
    'search content',
    'use advanced search',
  );
  foreach ($auth_search as $perm) {
    insert_into_roles_table(2, $perm, _MODULE_SEARCH_);
  }

  $auth_user = array(
    'access user profiles',
    'change own username',
  );
  foreach ($auth_user as $perm) {
    insert_into_roles_table(2, $perm, _MODULE_USER_);
  }

  $auth_node = array(
    'create clinical_summary content',
    'create consent_item content',
    'create contact_information content',
    'create diagnosis content',
    'create forum content',
    'create forum_summary content',
    'create genetic_report content',
    'create gene_mutation content',
    'create media_gallery content',
    'create patient content',
    'create patient_note content',
    'create reference_letter content',
    'create xray_description content',
    'create x_ray content',
    'delete own clinical_summary content',
    'delete own contact_information content',
    'delete own consent_item content',
    'delete own diagnosis content',
    'delete own forum content',
    'delete own forum_summary content',
    'delete own genetic_report content',
    'delete own gene_mutation content',
    'delete own media_gallery content',
    'delete own patient content',
    'delete own patient_note content',
    'delete own reference_letter content',
    'delete own xray_description content',
    'delete own x_ray content',
    'edit own clinical_summary content',
    'edit own consent_item content',
    'edit own contact_information content',
    'edit own forum content',
    'edit own forum_summary content',
    'edit own genetic_report content',
    'edit own gene_mutation content',
    'edit own media_gallery content',
    'edit own patient content',
    'edit own patient_note content',
    'edit own reference_letter content',
    'edit own xray_description content',
    'edit own x_ray content'
  );
  foreach ($auth_node as $perm) {
    insert_into_roles_table(2, $perm, _MODULE_NODE_);
  }
}

function insert_into_actualroles_table($rid, $name, $weight) {
  db_insert('role')->fields(array(
      'rid'	=> $rid,
      'name'	=> $name,
      'weight'	=> $weight,
  ))->execute();
}

function insert_into_roles_table($rid, $permission, $module) {
  db_insert('role_permission')->fields(array(
      'rid'		=> $rid,
      'permission'	=> $permission,
      'module'		=> $module,
  ))->execute();
}

function get_permissions_for_role($rid) {
  $permissions = array();

  $sql = 'SELECT rid, permission FROM {role_permission} r WHERE r.rid = :rid AND r.module = :module';
//  $sql = 'SELECT rid, permission FROM {role_permission} r WHERE r.rid = :rid AND r.module = :module';
  $result = db_query($sql, array(':rid' => $rid, ':module' => 'node'));
//  $result = db_query($sql, array(':rid' => $rid, ':module' => 'node'));
  foreach ($result as $row) {
    $permissions[] = $row->permission;
  }

  return $permissions;
}