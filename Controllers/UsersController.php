<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class UsersController extends Controller
{
	public function index()
	{
		$users = new PersonList(array('user_account'=>true));

		$this->template->blocks[] = new Block('users/userList.inc',array('userList'=>$users));
	}

	public function update()
	{
		$person = isset($_REQUEST['user_id']) ? new Person($_REQUEST['user_id']) : new Person();

		if (isset($_POST['username'])) {
			try {
				$person->set($_POST);
				$person->save();
				header('Location: '.BASE_URL.'/users');
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}

		if ($person->getId()) {
			$this->template->blocks[] = new Block('people/personInfo.inc',array('person'=>$person));
		}
		$this->template->blocks[] = new Block('users/updateUserForm.inc',array('user'=>$person));
	}

	public function delete()
	{
		try {
			$person = new Person($_REQUEST['user_id']);
			$person->deleteUserAccount();
			$person->save();
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}
		header('Location: '.BASE_URL.'/users');
		exit();
	}
}