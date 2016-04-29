<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class PeopleController extends Controller
{
	public function index()
	{
		$people = new PersonList();
		$people->find();

		$this->template->blocks[] = new Block('people/personList.inc',array('personList'=>$people));
	}

	public function view()
	{
		try {
			$person = new Person($_REQUEST['person_id']);
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}

		$this->template->blocks[] = new Block('people/personInfo.inc',array('person'=>$person));
	}

	public function update()
	{
		$person = isset($_REQUEST['person_id']) ? new Person($_REQUEST['person_id']) : new Person();

		if (isset($_POST['firstname'])) {
			$person->set($_POST);
			try {
				$person->save();
				header('Location: '.BASE_URL.'/people');
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}

		$this->template->blocks[] = new Block('people/updatePersonForm.inc',array('person'=>$person));
	}
}