<?php
/**
 * @copyright 2009-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param PersonList $this->personList
 */
?>
<div class="interfaceBox">
	<h2>People
		<?php
			if (userIsAllowed('people')) {
				echo "<a class=\"add button\" href=\"".BASE_URL."/people/update\">Add a Person</a>";
			}
		?>
	</h2>
	<table>
		<thead>
			<tr><th></th>
				<th>Username</th>
				<th>Name</th>
				<th>Email</th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->personList as $person) {
				$editButton = '';
				if (userIsAllowed('people')) {
					$editButton = "
					<a class=\"edit button\"
						href=\"".BASE_URL."/people/update?person_id={$person->getId()}\">
						Edit
					</a>
					";
				}

				$name = View::escape($person->getFullname());
				echo "
				<tr><td>$editButton</td>
					<td>{$person->getUsername()}</td>
					<td><a href=\"{$person->getURL()}\">$name</a></td>
					<td>{$person->getEmail()}</td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</div>
