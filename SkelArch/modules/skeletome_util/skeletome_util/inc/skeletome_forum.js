(function($) {

  var forumNid;
  var selectedGroups;

  Drupal.behaviors.patientForum = {
    attach: function (context, settings) {
      skeletomeBase = Drupal.settings.basePath  || [];
      forumNid = Drupal.settings.forumNid || [];
      selectedGroups = [];

      $("#available_groups").multiselect({
	header: "Choose groups below",
	click: function(event, ui){
	  if (ui.checked) {
	    selectedGroups.push(ui.value);
	  } else {
	    idx = -1;
	    for ( var i = 0; i < selectedGroups.length; i++ ) {
	      if (selectedGroups[i] === ui.value) {
		idx = i;
		break;
	      }
	    }
	    selectedGroups.splice(idx, 1);
	  }
	},
      });
      
      $("#back_button").button();
      $("#forward_button").button();
      $("#share_wo_button").button();
      $("#share_button").button().click(function() {
	link = skeletomeBase + "skeletome-util/forum/share";
	$.post(link, { forumNid: forumNid, groupNids: selectedGroups}, function(data){
	  window.location.href = skeletomeBase + "node/" + forumNid;
	});
      });
     
    }
  };
  
})(jQuery);
