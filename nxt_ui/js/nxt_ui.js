 $(document).ready(function(){
 
	$("button").click(function() {
		var val = $(this).text();
		$.get('../nxt_send/nxt_send.cgi?cmd='+$(this).data("action"));
	});
 
 });