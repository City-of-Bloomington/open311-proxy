<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
	$this->layout = 'full-width';
	include __DIR__.'/partials/header.inc';
?>
<body>
	<script type="text/javascript">
	var HOST = {};
	function handleMessage(e) {
		if (e.data === 'height') {
			e.source.postMessage(document.body.scrollHeight,e.origin);
			HOST.source = e.source;
			HOST.origin = e.origin;
		}
	}
	window.addEventListener('message',handleMessage,false);
	</script>
	<div id="panel-container">
		<div id="content-panel">
			<?php
				include FRAMEWORK.'/errorMessages.php';

				echo $this->includeBlocks();
			?>
		</div>
	</div>
	<?php
		include __DIR__.'/partials/footer.inc';
	?>
</body>
</html>
<?php
	include __DIR__.'/partials/garbageCollection.inc';
?>
