<?php
/**
 * @copyright 2011-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Endpoint $this->endpoint
 */
$this->template->addToAsset('scripts', YUI.'/yui/yui-min.js');
$this->template->addToAsset('scripts', BASE_URI.'/js/groupChooser.js');
?>
<div id="groupChooser" class="cob-open311Client-groupChooser">
	<?php
		foreach ($this->endpoint->getServiceGroups() as $group) {
			if ($group) {
				$_GET['group'] = $group;
				$this->_include('embed/chooseService.inc');
			}
		}
	?>
</div>
