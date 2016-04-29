<?php
/**
 * @copyright 2009-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Person $this->person
 */
use Application\Models\Person;
use Blossom\Classes\Url;

$return_url = Url::current_url();
$h = $this->template->getHelper('buttonLink');

$username = $this->person->getUsername();
if (!$username && Person::isAllowed('users')) {
	$username = $h->buttonLink(
		self::generateUri('users.update', ['id'=>$this->person->getId()])."?return_url=$return_url",
		$this->translate('user_add'),
		'add'
	);
}

$editButton = '';
if (Person::isAllowed('people', 'edit')) {
    $editButton = $h->buttonLink(
        self::generateUri('people.update', ['id'=>$this->person->getId()])."?return_url=$return_url",
        $this->translate('edit'),
        'edit'
    );
}
$name = self::escape($this->person->getFullname());
echo "
<section>
    <header>
        <h1>$name</h1>
        <div class=\"tools\">$editButton</div>
    </header>
    
	<table>
		<tr><th>{$this->_('email')}</th>
			<td>{$this->person->getEmail()}</td>
		</tr>
		<tr><th>{$this->_('username')}</th>
			<td>$username</td>
		</tr>
	</table>
</section>
";
