<?php

define('_GROUP_AUDIENCE_', 'group_audience');
define('_GROUP_CONTENT_VISIBILITY_', 'group_content_access');

define('_GROUP_GROUP_', 'group_group');
define('_GROUP_ACCESS_', 'group_access');
define('_GROUP_ROLES_', 'og_roles_permissions');
define('_GROUP_REGISTER_', 'group_register');

define('_OG_FIELD_ACCESS_', 'og_field_access');
define('_OG_', 'og');

function perform_gcm_action($action) {
  if ($action === '0') {
    set_group_contenttypes();
  }
  if ($action === '1') {
    add_ac_restrictions();
  }
}

function set_group_contenttypes() {
  $types_array = array('clinical_summary', 'contact_information', 'diagnosis', 'forum', 'gene_mutation', 'genetic_report', 'patient', 'news_item', 'x_ray', 'media_gallery', 'xray_description', 'consent_item', 'reference_letter');

  foreach ($types_array as $type) {
    og_create_field(_GROUP_AUDIENCE_, 'node', $type);
    og_create_field(_GROUP_CONTENT_VISIBILITY_, 'node', $type);
  }

  og_create_field(_GROUP_GROUP_, 'node', 'skeletome_group');
  og_create_field(_GROUP_ACCESS_, 'node', 'skeletome_group');
  og_create_field(_GROUP_ROLES_, 'node', 'skeletome_group');
  og_create_field(_GROUP_REGISTER_, 'node', 'skeletome_group');
}

function add_ac_restrictions() {
  $member_og = array(
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
    'delete own xray_description content',
    'delete own x_ray content',
    'update own clinical_summary content',
    'update own consent_item content',
    'update own contact_information content',
    'update own diagnosis content',
    'update own forum content',
    'update own genetic_report content',
    'update own gene_mutation content',
    'update own media_gallery content',
    'update own news_item content',
    'update own patient content',
    'update own patient_note content',
    'update own reference_letter content',
    'update own xray_description content',
    'update own x_ray content',
  );

  foreach ($member_og as $perm) {
    insert_into_og_table(2, $perm, _OG_);
  }

  $nonmember_og_field_access = array(
    'view body field',
    'view field_ci_patient field',
    'view field_consentitem_file field',
    'view field_consentitem_patient field',
    'view field_cs_patient field',
    'view field_cs_tags field',
    'view field_cs_uri field',
    'view field_diagnosis_bd field',
    'view field_diagnosis_date field',
    'view field_diagnosis_patient field',
    'view field_entry_date field',
    'view field_forumattachment field',
    'view field_forum_attachment field',
    'view field_forum_patient field',
    'view field_forum_patientprovenance field',
    'view field_forum_useraudience field',
    'view field_gene_mutation_gene field',
    'view field_gene_mutation_genrep field',
    'view field_gene_mutation_uri field',
    'view field_genrep_attachment field',
    'view field_genrep_date field',
    'view field_genrep_gm field',
    'view field_genrep_patient field',
    'view field_genrep_refno field',
    'view field_genrep_uri field',
    'view field_gm_count field',
    'view field_gm_mutatedcontent field',
    'view field_gm_mutation_type field',
    'view field_gm_offset field',
    'view field_gm_originalcontent field',
    'view field_patientnote_biblio field',
    'view field_patientnote_patient field',
    'view field_patient_address field',
    'view field_patient_ci field',
    'view field_patient_clinicalsummary field',
    'view field_patient_consent field',
    'view field_patient_consentfile field',
    'view field_patient_customtags field',
    'view field_patient_diagnosis field',
    'view field_patient_discussiongroups field',
    'view field_patient_dob field',
    'view field_patient_ethnicity field',
    'view field_patient_forum field',
    'view field_patient_gender field',
    'view field_patient_genrep field',
    'view field_patient_identifier field',
    'view field_patient_letter field',
    'view field_patient_name field',
    'view field_patient_note field',
    'view field_patient_publication field',
    'view field_patient_published field',
    'view field_patient_refno field',
    'view field_patient_uri field',
    'view field_patient_xrayreport field',
    'view field_referenceletter_date field',
    'view field_referenceletter_file field',
    'view field_referenceletter_patient field',
    'view field_skeletome_tags field',
    'view field_xray_description field',
    'view field_xray_description_dc field',
    'view field_xray_description_dm field',
    'view field_xray_description_media field',
    'view field_xray_description_tags field',
    'view field_xray_description_xray field',
    'view field_xray_media field',
    'view field_xray_xraycollection field',
    'view field_xray_xraydescription field',
    'view group_access field',
    'view group_audience field',
    'view group_content_access field',
    'view group_group field',
    'view group_register field',
    'view media_gallery_allow_download field',
    'view media_gallery_block_columns field',
    'view media_gallery_block_rows field',
    'view media_gallery_collection field',
    'view media_gallery_columns field',
    'view media_gallery_date field',
    'view media_gallery_description field',
    'view media_gallery_expose_block field',
    'view media_gallery_format field',
    'view media_gallery_image_info_where field',
    'view media_gallery_lightbox_extras field',
    'view media_gallery_media field',
    'view media_gallery_patient field',
    'view media_gallery_rows field',
    'view media_gallery_uri field',
    'view og_roles_permissions field',
    'view taxonomy_forums field',
  );

  foreach ($nonmember_og_field_access as $perm) {
    insert_into_og_table(1, $perm, _OG_FIELD_ACCESS_);
  }

  $member_og_field_access = array(
    'update body field',
    'update field_ci_patient field',
    'update field_consentitem_file field',
    'update field_consentitem_patient field',
    'update field_cs_patient field',
    'update field_cs_tags field',
    'update field_cs_uri field',
    'update field_diagnosis_bd field',
    'update field_diagnosis_date field',
    'update field_diagnosis_patient field',
    'update field_entry_date field',
    'update field_forumattachment field',
    'update field_forum_attachment field',
    'update field_forum_patient field',
    'update field_forum_patientprovenance field',
    'update field_forum_useraudience field',
    'update field_gene_mutation_gene field',
    'update field_gene_mutation_genrep field',
    'update field_gene_mutation_uri field',
    'update field_genrep_attachment field',
    'update field_genrep_date field',
    'update field_genrep_gm field',
    'update field_genrep_patient field',
    'update field_genrep_refno field',
    'update field_genrep_uri field',
    'update field_gm_count field',
    'update field_gm_mutatedcontent field',
    'update field_gm_mutation_type field',
    'update field_gm_offset field',
    'update field_gm_originalcontent field',
    'update field_patientnote_biblio field',
    'update field_patientnote_patient field',
    'update field_patient_address field',
    'update field_patient_ci field',
    'update field_patient_clinicalsummary field',
    'update field_patient_consent field',
    'update field_patient_consentfile field',
    'update field_patient_customtags field',
    'update field_patient_diagnosis field',
    'update field_patient_discussiongroups field',
    'update field_patient_dob field',
    'update field_patient_ethnicity field',
    'update field_patient_forum field',
    'update field_patient_gender field',
    'update field_patient_genrep field',
    'update field_patient_identifier field',
    'update field_patient_letter field',
    'update field_patient_name field',
    'update field_patient_note field',
    'update field_patient_publication field',
    'update field_patient_published field',
    'update field_patient_refno field',
    'update field_patient_uri field',
    'update field_patient_xrayreport field',
    'update field_referenceletter_date field',
    'update field_referenceletter_file field',
    'update field_referenceletter_patient field',
    'update field_skeletome_tags field',
    'update field_xray_description field',
    'update field_xray_description_dc field',
    'update field_xray_description_dm field',
    'update field_xray_description_media field',
    'update field_xray_description_tags field',
    'update field_xray_description_xray field',
    'update field_xray_media field',
    'update field_xray_xraycollection field',
    'update field_xray_xraydescription field',
    'update group_access field',
    'update group_audience field',
    'update group_content_access field',
    'update group_group field',
    'update group_register field',
    'update media_gallery_allow_download field',
    'update media_gallery_block_columns field',
    'update media_gallery_block_rows field',
    'update media_gallery_collection field',
    'update media_gallery_columns field',
    'update media_gallery_date field',
    'update media_gallery_description field',
    'update media_gallery_expose_block field',
    'update media_gallery_format field',
    'update media_gallery_image_info_where field',
    'update media_gallery_lightbox_extras field',
    'update media_gallery_media field',
    'update media_gallery_patient field',
    'update media_gallery_rows field',
    'update media_gallery_uri field',
    'update og_roles_permissions field',
    'update taxonomy_forums field',
    'view body field',
    'view field_ci_patient field',
    'view field_consentitem_file field',
    'view field_consentitem_patient field',
    'view field_cs_patient field',
    'view field_cs_tags field',
    'view field_cs_uri field',
    'view field_diagnosis_bd field',
    'view field_diagnosis_date field',
    'view field_diagnosis_patient field',
    'view field_entry_date field',
    'view field_forumattachment field',
    'view field_forum_attachment field',
    'view field_forum_patient field',
    'view field_forum_patientprovenance field',
    'view field_forum_useraudience field',
    'view field_gene_mutation_gene field',
    'view field_gene_mutation_genrep field',
    'view field_gene_mutation_uri field',
    'view field_genrep_attachment field',
    'view field_genrep_date field',
    'view field_genrep_gm field',
    'view field_genrep_patient field',
    'view field_genrep_refno field',
    'view field_genrep_uri field',
    'view field_gm_count field',
    'view field_gm_mutatedcontent field',
    'view field_gm_mutation_type field',
    'view field_gm_offset field',
    'view field_gm_originalcontent field',
    'view field_patientnote_biblio field',
    'view field_patientnote_patient field',
    'view field_patient_address field',
    'view field_patient_ci field',
    'view field_patient_clinicalsummary field',
    'view field_patient_consent field',
    'view field_patient_consentfile field',
    'view field_patient_customtags field',
    'view field_patient_diagnosis field',
    'view field_patient_discussiongroups field',
    'view field_patient_dob field',
    'view field_patient_ethnicity field',
    'view field_patient_forum field',
    'view field_patient_gender field',
    'view field_patient_genrep field',
    'view field_patient_identifier field',
    'view field_patient_letter field',
    'view field_patient_name field',
    'view field_patient_note field',
    'view field_patient_publication field',
    'view field_patient_published field',
    'view field_patient_refno field',
    'view field_patient_uri field',
    'view field_patient_xrayreport field',
    'view field_referenceletter_date field',
    'view field_referenceletter_file field',
    'view field_referenceletter_patient field',
    'view field_skeletome_tags field',
    'view field_xray_description field',
    'view field_xray_description_dc field',
    'view field_xray_description_dm field',
    'view field_xray_description_media field',
    'view field_xray_description_tags field',
    'view field_xray_description_xray field',
    'view field_xray_media field',
    'view field_xray_xraycollection field',
    'view field_xray_xraydescription field',
    'view group_access field',
    'view group_audience field',
    'view group_content_access field',
    'view group_group field',
    'view group_register field',
    'view media_gallery_allow_download field',
    'view media_gallery_block_columns field',
    'view media_gallery_block_rows field',
    'view media_gallery_collection field',
    'view media_gallery_columns field',
    'view media_gallery_date field',
    'view media_gallery_description field',
    'view media_gallery_expose_block field',
    'view media_gallery_format field',
    'view media_gallery_image_info_where field',
    'view media_gallery_lightbox_extras field',
    'view media_gallery_media field',
    'view media_gallery_patient field',
    'view media_gallery_rows field',
    'view media_gallery_uri field',
    'view og_roles_permissions field',
    'view taxonomy_forums field',
  );

  foreach ($member_og_field_access as $perm) {
    insert_into_og_table(2, $perm, _OG_FIELD_ACCESS_);
  }
}

function insert_into_og_table($rid, $permission, $module) {
  db_insert('og_role_permission')->fields(array(
      'rid'		=> $rid,
      'permission'	=> $permission,
      'module'		=> $module,
  ))->execute();
}
