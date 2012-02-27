<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class ClientsController extends Controller
{
	public function index()
	{
		$list = new ClientList();
		$list->find();
		$this->template->blocks[] = new Block('clients/list.inc', array('clientList'=>$list));
	}

	public function update()
	{
		$client = !empty($_REQUEST['client_id'])
			? $this->loadClient($_REQUEST['client_id'])
			: new Client();

		if (isset($_POST['name'])) {
			$client->set($_POST);
			try {
				$client->save();
				header('Location: '.BASE_URL.'/clients');
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}
		$this->template->blocks[] = new Block('clients/updateForm.inc', array('client'=>$client));
	}

	public function delete()
	{
		$client = $this->loadClient($_REQUEST['client_id']);
		try {
			$client->delete();
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}
		header('Location: '.BASE_URL.'/clients');
		exit();
	}

	/**
	 * @return Client
	 */
	private function loadClient($id)
	{
		try {
			return new Client($id);
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
			header('Location: '.BASE_URL.'/clients');
			exit();
		}
	}

}