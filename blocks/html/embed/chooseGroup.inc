<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoint $this->endpoint
 */
$this->template->addToAsset('scripts',YUI.'/yui/yui-min.js');
$this->template->addToAsset('scripts',BASE_URI.'/js/groupChooser.js');
?>
<div id="groupChooser">
	<h2>All Reports</h2>
	<?php
		foreach ($this->endpoint->getServiceGroups() as $group) {
			if ($group) {
				$_GET['group'] = $group;
				include APPLICATION_HOME.'/blocks/html/embed/chooseService.inc';
			}
		}
	?>
</div>