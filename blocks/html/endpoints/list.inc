<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param EndpointList $this->endpointList
 */
$addButton = userIsAllowed('endpoints','add')
	? "<a class=\"add button\" href=\"".BASE_URI."/endpoints/update\">Add</a>"
	: '';
echo "
<div class=\"endpointList\">
	<h2>Endpoints $addButton</h2>
";
	foreach ($this->endpointList as $endpoint) {
		$fields = array('url','name','jurisdiction','api_key','latitude','longitude');
		foreach ($fields as $field) {
			$get = 'get'.ucfirst($field);
			$$field = View::escape($endpoint->$get());
		}

		$editButton = userIsAllowed('endpoints','update')
			? "<a class=\"edit button\" href=\"".BASE_URI."/endpoints/update?endpoint_id={$endpoint->getId()}\">Edit</a>"
			: '';
		echo "
		<div><h3><a href=\"".BASE_URI."/endpoints/view?endpoint_id={$endpoint->getId()}\">$name</a>
				$editButton
			</h3>
			<table>
				<tr><th>url</th><td>$url</td></tr>
				<tr><th>jurisdiction</th><td>$jurisdiction</td></tr>
				<tr><th>api_key</th><td>$api_key</td></tr>
				<tr><th>latitude</th><td>$latitude</td></tr>
				<tr><th>longitude</th><td>$longitude</td></tr>
			</table>
		</div>
		";
	}
echo "
</div>
";