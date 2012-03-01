"use strict";
YUI().use('node', function(Y) {
	var services = Y.all('#groupChooser .serviceChooser');

	function closeAll() {
		services.each(function (node) {
			if (!node.hasClass('collapsed')) { node.addClass('collapsed'); }
		});
	}

	function toggle(e) {
		e.preventDefault();
		this.get('parentNode').toggleClass('collapsed');
		if (HOST.source) {
			HOST.source.postMessage(document.body.scrollHeight, HOST.origin);
		}
	}

	closeAll();
	Y.delegate('click', toggle, '#groupChooser', '.serviceChooser h3');
});