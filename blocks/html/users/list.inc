<?php
/**
 * @copyright 2007-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param array $this->users
 */
use Application\Models\Person;
?>
<section>
    <header>
        <h1><?= $this->_(['user','users',2]); ?></h1>
        <div class="tools">
        <?php
            $helper = $this->template->getHelper('buttonLink');
            if (Person::isAllowed('users')) {
                echo $helper->buttonLink(self::generateUri('users.update'), $this->_('user_add'), 'add');
            }
        ?>
        </div>
    </header>

	<table>
		<thead>
			<tr><th></th>
				<th><?= $this->_('username'); ?></th>
				<th><?= $this->_('name'); ?></th>
				<th><?= $this->_('authenticationMethod'); ?></th>
				<th><?= $this->_('role'); ?></th>
				<th></th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->users as $user) {
				$editButton = '';
				$deleteButton = '';
				if (Person::isAllowed('users')) {
					$editButton = $helper->buttonLink(
                        self::generateUri('users.update', ['id'=>$user->getId()]),
						$this->_('user_edit'),
						'edit'
					);
					$deleteButton = $helper->buttonLink(
                        self::generateUri('users.delete', ['id'=>$user->getId()]),
						$this->_('user_delete'),
						'delete'
					);
				}

				$name = self::escape($user->getFullname());
				echo "
				<tr><td>$editButton</td>
					<td>{$user->getUsername()}</td>
					<td>$name</td>
					<td>{$user->getAuthenticationMethod()}</td>
					<td>{$user->getRole()}</td>
					<td>$deleteButton</td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</section>
