<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class EndpointsController extends Controller
{
	public function index()
	{
		$list = new EndpointList();
		$list->find();
		$this->template->blocks[] = new Block(
			'endpoints/list.inc',
			array('endpointList'=>$list)
		);
	}

	public function view()
	{
		$endpoint = $this->loadEndpoint($_GET['endpoint_id']);
		$service = !empty($_REQUEST['service_code'])
			? $endpoint->getService($_REQUEST['service_code'])
			: null;
		if ($service) {
			$this->template->blocks[] = new Block(
				'endpoints/requestForm.inc',
				array('endpoint'=>$endpoint, 'service'=>$service)
			);
		}
		elseif (isset($_REQUEST['group'])) {
			$this->template->blocks[] = new Block('endpoints/chooseService.inc', array('endpoint'=>$endpoint));
		}
		else {
			$this->template->blocks[] = new Block('endpoints/chooseGroup.inc', array('endpoint'=>$endpoint));
		}
	}

	public function update()
	{
		$endpoint = !empty($_REQUEST['endpoint_id'])
			? $this->loadEndpoint($_REQUEST['endpoint_id'])
			: new Endpoint();

		if (isset($_POST['url'])) {
			$endpoint->set($_POST);
			try {
				$endpoint->save();
				header('Location: '.BASE_URL.'/endpoints/view?endpoint_id='.$endpoint->getId());
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}
		$this->template->blocks[] = new Block(
			'endpoints/updateForm.inc',
			array('endpoint'=>$endpoint)
		);
	}

	/**
	 * @return Endpoint
	 */
	private function loadEndpoint($id)
	{
		try {
			return new Endpoint($id);
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
			header('Location: '.BASE_URL.'/endpoints');
			exit();
		}
	}
}