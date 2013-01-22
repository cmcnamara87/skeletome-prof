(function($) {

  var searchTags = {};
  var terms;

  searchTags.clickTerm = function (context) {
    var tag = $(context);
    tid = terms[tag.text()];
    window.location.href = skeletomeBase + "taxonomy/term/" + tid;
  }
  
  Drupal.behaviors.searchTagsTermClick = {
    attach: function (context, settings) {
      skeletomeBase = Drupal.settings.basePath  || [];
      terms = Drupal.settings.terms || [];
      
      $('span.pt-term-text:not(.patientTagsRemove-processed)', context)
	.addClass('patientTagsRemove-processed')
	.each(function () {
	  $(this).click(function () {
	    searchTags.clickTerm(this);
	  })
	});
    }
  };
  
})(jQuery);
