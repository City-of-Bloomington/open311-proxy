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

            <dl><dt><label  for="authenticationMethod"><?= $this->_('authenticationMethod'); ?></label></dt>
                <dd><select name="authenticationMethod" id="authenticationMethod" required="true">
                    <?php
                        foreach (Person::getAuthenticationMethods() as $method) {
                            $selected = $authenticationMethod === $method
                                ? 'selected="selected"'
                                : '';
                            echo "<option $selected>$method</option>";
                        }
                    ?>
                    </select>
                </dd>
            </dl>
            <?php
                $field = $this->template->getHelper('field');
                echo $field->input(['name'=>'username', 'id'=>'username', 'label'=>$this->_('username'), 'value'=>$username, 'required'=>true]);
                echo $field->input(['name'=>'password', 'id'=>'password', 'label'=>$this->_('password'), 'type'=>'password']);
				echo $field->input(['name'=>'email',    'id'=>'email',    'label'=>$this->_('email'   ), 'value'=>$email]);
            ?>
            <dl><dt><label  for="role"><?= $this->_('role'); ?></label></dt>
                <dd><select name="role" id="role" required="true"><option></option>
                    <?php
                        global $ZEND_ACL;
                        foreach (array_reverse($ZEND_ACL->getRoles()) as $role) {
                            $selected = $this->user->getRole()==$role
                                ? 'selected="selected"'
                                : '';
                            echo "<option $selected>$role</option>";
                        }
                    ?>
                    </select>
                </dd>
            </dl>
			<?php
				$helper = $this->template->getHelper('saveAndCancelButtons');
				echo $helper->saveAndCancelButtons(self::generateUri('users.index'));
			?>
		</fieldset>
	</form>
</section>
