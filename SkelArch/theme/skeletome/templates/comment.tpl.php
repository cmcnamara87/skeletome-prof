<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print $picture; ?>

  <div style="margin-left:<?php print $image_width; ?>px;" class="comment-content">


    <div class="comment-text"<?php print $content_attributes; ?>>
      <?php // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
      ?>
    <div class="submitted">
      <?php print t('On'); ?>
      <strong><?php print $created; ?></strong>
    </div>

        <div class="user-signature clearfix">
          <?php print t('By'); ?> <strong><?php print $author; ?></strong>
          <?php if ($signature): ?>
            --
            <?php print $signature; ?>
          <?php endif; ?>
        </div>
    </div>


    <?php print render($content['links']) ?>

    <div class="arrow-border"></div><!--make the triangle using css only-->
    <div class="arrow"></div>
  </div><!--end comment content-->
</div> <!-- end comment -->