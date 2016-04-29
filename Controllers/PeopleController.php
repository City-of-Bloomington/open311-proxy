<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Controllers;

use Application\Models\Person;
use Application\Models\PeopleTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class PeopleController extends Controller
{
    private function loadPerson($id)
    {
        try {
            return new Person($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.self::generateUrl('people.index'));
            exit();
        }
    }
	public function index()
	{
		$table = new PeopleTable();

		$page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
		$people = $table->find(null, null, 20, $page);

		return new \Application\Views\People\ListView(['people'=>$people]);
	}

	public function view()
	{
        $person = $this->loadPerson($_REQUEST['id']);
        return new \Application\Views\People\InfoView(['person'=>$person]);
	}

	public function update()
	{
        $person = !empty($_REQUEST['id'])
            ? $this->loadPerson($_REQUEST['id'])
            : new Person();

        $return_url = !empty($_REQUEST['return_url'])
            ? $_REQUEST['return_url']
            : null;

		if (isset($_POST['firstname'])) {
			$person->handleUpdate($_POST);
			try {
				$person->save();

				if (!$return_url) { $return_url = self::generateUrl('people.view', ['id'=>$person->getId()]); }
				header("Location: $return_url");
				exit();
			}
			catch (\Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}

		return new \Application\Views\People\UpdateView([
            'person'     => $person,
            'return_url' => $return_url
		]);
	}
}
