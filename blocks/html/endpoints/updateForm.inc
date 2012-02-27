<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoint $this->endpoint
 */
$fields = array('url','name','jurisdiction','api_key');
foreach ($fields as $field) {
	$get = 'get'.ucfirst($field);
	$$field = View::escape($this->endpoint->$get());
}
$title = $this->endpoint->getId() ? View::escape('Edit '.$this->endpoint->getName()) : 'Add Endpoint';
?>
<div class="updateEndpointForm">
	<h2><?php echo $title; ?></h2>
	<form method="post" action="<?php echo BASE_URI; ?>/endpoints/update">
		<fieldset>
			<input name="endpoint_id" type="hidden" value="<?php echo $this->endpoint->getId(); ?>" />
			<table>
				<tr><td><label for="name">Name</label></td>
					<td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
				</tr>
				<tr><td><label for="url">URL</label></td>
					<td><input name="url" id="url" value="<?php echo $url; ?>" /></td>
				</tr>
				<tr><td><label for="jurisdiction">Jurisdiction</label></td>
					<td><input name="jurisdiction" id="jurisdiction" value="<?php echo $jurisdiction; ?>" /></td>
				</tr>
				<tr><td><label for="api_key">API Key</label></td>
					<td><input name="api_key" id="api_key" value="<?php echo $api_key; ?>" /></td>
				</tr>
			</table>
			<button type="submit" class="submit">Submit</button>
			<a class="cancel button" href="<?php echo BASE_URI; ?>/endpoints">Cancel</a>
		</fieldset>
	</form>
</div>