<?php
/**
 * @copyright 2006-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param User $this->user
 */
use Application\Models\Person;

$fields = ['id', 'authenticationMethod', 'role', 'username', 'email'];
foreach ($fields as $f) {
    $get = 'get'.ucfirst($f);
    $$f = self::escape($this->user->$get());
}

$title = $this->user->getId() ? $this->_('user_edit') : $this->_('user_add');
?>
<section>
    <header>
        <h1><?= $title; ?></h1>
    </header>

	<form method="post" action="<?= self::generateUri('users.update'); ?>">
		<fieldset><legend><?= $this->_('user_info'); ?></legend>
			<input name="id" type="hidden" value="<?= $this->user->getId(); ?>" />
			<?php
                $field = $this->template->getHelper('field');

                $options = [];
                foreach (Person::getAuthenticationMethods() as $method) { $options[] = ['value'=>$method]; }
                echo $field->field([
                    'name'    => 'authenticationMethod',
                    'id'      => 'authenticationMethod',
                    'label'   => $this->_('authenticationMethod'),
                    'value'   => $authenticationMethod,
                    'type'    => 'select',
                    'options' => $options
                ]);

                echo $field->field(['name'=>'username', 'id'=>'username', 'label'=>$this->_('username'), 'value'=>$username, 'required'=>true]);
                echo $field->field(['name'=>'password', 'id'=>'password', 'label'=>$this->_('password'), 'type'=>'password']);
				echo $field->field(['name'=>'email',    'id'=>'email',    'label'=>$this->_('email'   ), 'value'=>$email]);

				$options = [];
                global $ZEND_ACL;
                foreach (array_reverse($ZEND_ACL->getRoles()) as $role) { $options[] = ['value'=>$role]; }
				echo $field->field([
                    'name'    => 'role',
                    'id'      => 'role',
                    'label'   => $this->_('role'),
                    'value'   => $this->user->getRole(),
                    'type'    => 'select',
                    'options' => $options
				]);

				$helper = $this->template->getHelper('saveAndCancelButtons');
				echo $helper->saveAndCancelButtons(self::generateUri('users.index'));
			?>
		</fieldset>
	</form>
</section>
