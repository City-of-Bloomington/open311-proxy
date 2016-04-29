<?php
/**
 * @copyright 2009-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param array $this->people
 */
use Application\Models\Person;
use Blossom\Classes\Url;
?>
<section>
    <header>
        <h1><?= $this->translate(['person','people',2]); ?></h1>
        <div class="tools">
        <?php
            $return_url = Url::current_url();
            $helper = $this->template->getHelper('buttonLink');

            if (Person::isAllowed('people', 'add')) {
                echo $helper->buttonLink(
                    self::generateUri('people.update')."?return_url=$return_url",
                    $this->translate('person_add'),
                    'add'
                );
            }
        ?>
        </div>
    </header>

	<table>
		<thead>
			<tr><th><?= $this->_('username'); ?></th>
				<th><?= $this->_('name'); ?></th>
				<th><?= $this->_(['email','emails',1]); ?></th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->people as $person) {
				$name = self::escape($person->getFullname());
				$url = self::generateUri('people.view', ['id'=>$person->getId()]);
				echo "
				<tr><td><a href=\"$url\">{$person->getUsername()}</a></td>
					<td><a href=\"$url\">$name</a></td>
					<td><a href=\"$url\">{$person->getEmail()}</a></td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</section>
