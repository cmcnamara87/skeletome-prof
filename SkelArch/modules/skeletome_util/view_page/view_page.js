(function($) {

  var views;
  var currentView;

  Drupal.behaviors.viewPage = {
    attach: function (context, settings) {
      skeletomeBase = Drupal.settings.basePath  || [];
      views = Drupal.settings.views || [];
      currentView = Drupal.settings.currentView || [];
      
      for (i = 0; i < views.length; i++) {
	$("#" + views[i]).click(function(i) {
	  elem_id = $(i.currentTarget)[0].id;
	  link = skeletomeBase + "node/" + currentView+ "/switch";
	  $.post(link, { view_id: elem_id}, function(data){
	      window.location.href = skeletomeBase + "node/" + currentView;
	    });
	});

      }

    }
  };
  
})(jQuery);
