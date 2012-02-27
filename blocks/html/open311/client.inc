<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="open311_client">
	<?php
		if (isset($_REQUEST['service_code'])) {
			include APPLICATION_HOME.'/blocks/html/open311/clientRequestForm.inc';
		}
		elseif (isset($_REQUEST['group'])) {
			include APPLICATION_HOME.'/blocks/html/open311/chooseService.inc';
		}
		else {
			include APPLICATION_HOME.'/blocks/html/open311/chooseGroup.inc';
		}
	?>
</div>