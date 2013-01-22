(function($) {

  var selectedTags = [];

  Drupal.behaviors.genericTagsAdmin = {
    attach: function (context, settings) {
      skeletomeBase = Drupal.settings.basePath  || [];

      $( "#selectable" ).selectable({
	stop: function() {
	  selectedTags = [];
	  $( ".ui-selected", this ).each(function() {
	    var idx = $( "#selectable li" ).index( this );
	    selectedTags.push($( "#selectable li" )[idx].id);
	  });
	}
      });

      $("#create_tag_button").button().click(function() {
	$("#add_tag_dialog").dialog( "open" ); 
      });

      $("#delete_tag_button").button().click(function() {
	link = skeletomeBase + "skeletome-util/generic-tags/delete";
	var selectList = document.getElementById("selectable");
	
	for (i = 0; i < selectedTags.length; i++) {
	  var child = document.getElementById(selectedTags[i]);
	  $.post(link, { tid: selectedTags[i]}, function(data){
	    selectList.removeChild(child);
	  });	  
	}
	$( "#selectable" ).selectable("refresh");
      });;

      $("#add_tag_dialog").dialog({
	autoOpen: false,
	height: 135,
	width: 500,
	modal: true,
	closeOnEscape:	true,
	resizable: false,
	buttons: {
	  "Add": function() {
	    link = skeletomeBase + "skeletome-util/generic-tags/add";
	    tagText = $("#tag_input").val();
	    $.post(link, { newTag: tagText}, function(data){
	      if (data != "ERROR") {
		var selectList = document.getElementById("selectable");
		var newListItem = document.createElement('li');
		newListItem.className = "ui-widget-content";
		newListItem.id = data;
		newListItem.innerHTML = tagText;
		
		selectList.appendChild(newListItem);
		$( "#selectable" ).selectable("refresh");
	      }
	    });
	    $("#add_tag_dialog").dialog( "close" );
	  },
	  Cancel: function() {
	    $("#tag_input").val('');
	    $("#add_tag_dialog").dialog( "close" );
	  }
	},
	open: function() {
	  $("#identifier_input").focus();
	  $("#add_tag_dialog").keyup(function(e) {
	    if (e.keyCode == $.ui.keyCode.ENTER) {
	      link = skeletomeBase + "skeletome-util/generic-tags/add";
	      tagText = $("#tag_input").val();
	      $.post(link, { newTag: tagText}, function(data){
		if (data != "ERROR") {
		  var selectList = document.getElementById("selectable");
		  var newListItem = document.createElement('li');
		  newListItem.className = "ui-widget-content";
		  newListItem.id = data;
		  newListItem.innerHTML = tagText;
		  
		  selectList.appendChild(newListItem);
		  $( "#selectable" ).selectable("refresh");
		}
	      });

	      $("#add_tag_dialog").dialog( "close" );
	    }
	  });
	},
	close: function() {
	  $("#tag_input").val('');
	  $("#add_tag_dialog").dialog( "close" );
	}
      });
      
      
    }
  };
  
})(jQuery);
