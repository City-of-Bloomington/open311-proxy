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
echo "
<div class=\"endpointInfo\">
	<h2>$name</h2>
	<table>
		<tr><th>url</th><td>$url</td></tr>
		<tr><th>jurisdiction</th><td>$jurisdiction</td></tr>
		<tr><th>api_key</th><td>$api_key</td></tr>
		<tr><th>latitude</th><td>$latitude</td></tr>
		<tr><th>longitude</th><td>$longitude</td></tr>
	</table>
</div>
";
