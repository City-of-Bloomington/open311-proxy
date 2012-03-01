<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoint $this->endpoint
 */
$fields = array('url','name','jurisdiction','api_key','latitude','longitude');
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
			<p>Configure an endpoint you have established a relationship with.
				You must have signed up for at least one api_key from the Open311 server
				at the endpoint.  This will be the default api_key for posting to the endpoint.
			</p>
			<p>
				Additional clients for this endpoint can also have their own api_keys.
			</p>
			<table>
				<tr><td><label for="name" class="required">Name</label></td>
					<td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
				</tr>
				<tr><td><label for="url" class="required">URL</label></td>
					<td><input name="url" id="url" value="<?php echo $url; ?>" /></td>
				</tr>
				<tr><td><label for="jurisdiction" class="required">Jurisdiction</label></td>
					<td><input name="jurisdiction" id="jurisdiction" value="<?php echo $jurisdiction; ?>" /></td>
				</tr>
				<tr><td><label for="api_key" class="required">API Key</label></td>
					<td><input name="api_key" id="api_key" value="<?php echo $api_key; ?>" /></td>
				</tr>
			</table>
		</fieldsset>
		<fieldset>
			<p>You can specify lat/long for the endpoint.  Lat/long will be used
				to center the map on the client request form.
			</p>
			<table>
				<tr><td><label for="latitude">Latitude</label></td>
					<td><input name="latitude" id="latitude" value="<?php echo $latitude; ?>" /></td>
				</tr>
				<tr><td><label for="longitude">Longitude</label></td>
					<td><input name="longitude" id="longitude" value="<?php echo $longitude; ?>" /></td>
				</tr>
			</table>
			<button type="submit" class="submit">Submit</button>
			<a class="cancel" href="<?php echo BASE_URI; ?>/endpoints">Cancel</a>
		</fieldset>
	</form>
</div>