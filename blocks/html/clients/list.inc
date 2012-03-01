<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ClientList $this->clientList
 */
$addButton = userIsAllowed('clients','add')
	? "<a class=\"add button\" href=\"".BASE_URI."/clients/update\">Add</a>"
	: '';
echo "
<div class=\"clientList\">
	<h2>Clients $addButton</h2>
";
	foreach ($this->clientList as $client) {
		$url = View::escape($client->getUrl());
		$name = View::escape($client->getName());
		$api_key = View::escape($client->getApi_key());

		$endpoint = $client->getEndpoint();
		$endpointName = View::escape($endpoint->getName());

		$editButton = userIsAllowed('clients','update')
			? "<a class=\"edit button\" href=\"".BASE_URI."/clients/update?client_id={$client->getId()}\">Edit</a>"
			: '';
		$deleteButton = userIsAllowed('clients', 'delete')
			? "<a class=\"delete button\" href=\"".BASE_URI."/clients/delete?client_id={$client->getId()}\">Delete</a>"
			: '';
		echo "
		<div><h3>$name $editButton $deleteButton</h3>
			<table>
				<tr><th>url</th><td>$url</td></tr>
				<tr><th>endpoint</th>
					<td><a href=\"".BASE_URI."/endpoints/view?endpoint_id={$endpoint->getId()}\">
							$endpointName
						</a>
					</td>
				</tr>
				<tr><th>api_key</th>
					<td>$api_key</td>
				</tr>
			</table>
		</div>
		";
	}
echo "
</div>
";