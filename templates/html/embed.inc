<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php $this->_include('partials/head.inc'); ?>
<body class="full-width">
	<script type="text/javascript">
	var HOST = {};
	function handleMessage(e) {
		if (e.data === 'height') {
			e.source.postMessage(document.body.scrollHeight,e.origin);
			HOST.source = e.source;
			HOST.origin = e.origin;
		}
	}
	if (window.addEventListener) {
		window.addEventListener('message',handleMessage,false);
	}
	</script>
	<main>
        <div class="panel" id="content-panel">
			<?php
                include BLOSSOM.'/errorMessages.php';

				echo $this->includeBlocks();
			?>
		</div>
	</main>
	<?php $this-> _include('partials/footer.inc'); ?>
</body>
</html>
<?php $this->_include('partials/garbageCollection.inc'); ?>
