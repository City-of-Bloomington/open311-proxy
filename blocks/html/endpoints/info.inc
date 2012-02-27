<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoint $this->endpoint
 */
$url = View::escape($this->endpoint->getUrl());
$name = View::escape($this->endpoint->getName());
$jurisdiction = View::escape($this->endpoint->getJurisdiction());
$api_key = View::escape($this->endpoint->getApi_key());
echo "
<div class=\"endpointInfo\">
	<h2>$name</h2>
	<table>
		<tr><th>url</th><td>$url</td></tr>
		<tr><th>jurisdiction</th><td>$jurisdiction</td></tr>
		<tr><th>api_key</th><td>$api_key</td></tr>
	</table>
</div>
";
