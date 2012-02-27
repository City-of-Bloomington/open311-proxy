<?php
/**
 * @copyright 2009-2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
$username = $this->person->getUsername();
if (!$username && userIsAllowed('users')) {
	$username = "
	<a class=\"add button\" href=\"".BASE_URL."/users/update?user_id={$this->person->getId()}\">
		Create Account
	</a>
	";
}

$name = View::escape($this->person->getFullname());
echo <<<EOT
<div class="personInfo">
	<h2>$name</h2>
	<table>
		<tr><th>Email</th>
			<td>{$this->person->getEmail()}</td>
		</tr>
		<tr><th>Username</th>
			<td>$username</td>
		</tr>
	</table>
</div>
EOT;
