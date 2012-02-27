<?php
/**
 * @copyright 2009-2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
$fields = array('firstname','lastname','email');
foreach ($fields as $field) {
	$get = 'get'.ucfirst($field);
	$$field = View::escape($this->person->$get());
}
$title = $this->person->getId() ? View::escape('Edit '.$this->person->getFirstname()) : 'Add Someone';
?>
<div class="updatePersonForm">
	<h2><?php echo $title; ?></h2>
	<form method="post" action="<?php echo BASE_URL; ?>/people/update">
		<fieldset><legend>Person Info</legend>
			<input name="person_id" type="hidden" value="<?php echo $this->person->getId(); ?>" />

			<table>
				<tr><td><label for="firstname" class="required">Firstname</label></td>
					<td><input name="firstname" id="firstname" value="<?php echo $firstname; ?>" /></td>
				</tr>

				<tr><td><label for="lastname" class="required">Lastname</label></td>
					<td><input name="lastname" id="lastname" value="<?php echo $lastname; ?>" /></td>
				</tr>

				<tr><td><label for="email">Email</label></td>
					<td><input name="email" id="email" value="<?php echo $email; ?>" /></td>
				</tr>
			</table>
			<button type="submit" class="submit">Submit</button>
			<button type="button" class="cancel"
				onclick="document.location.href='<?php echo BASE_URL; ?>/people';">
				Cancel
			</button>
		</fieldset>
	</form>
</div>