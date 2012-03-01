<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class EmbedController extends Controller
{
	public function index()
	{
		$this->template->setFilename('embed');

		$client = !empty($_REQUEST['client']) ? $this->loadClient($_REQUEST['client']) : null;
		if ($client) {
			$endpoint = $client->getEndpoint();
			$service = !empty($_REQUEST['service_code'])
				? $endpoint->getService($_REQUEST['service_code'])
				: null;

			// Handle what the user posts
			if ($service && isset($_POST['service_code'])) {
				try {
					$xml = $endpoint->postServiceRequest($_POST);
					$block = new Block('embed/thankYou.inc',array('endpoint'=>$endpoint));
					if ($xml->request->service_request_id) {
						try {
							$block->request = $endpoint->getServiceRequest($xml->request->service_request_id);
						}
						catch (Exception $e) {
							$_SESSION['errorMessages'][] = $e;
						}
					}
					$this->template->blocks[] = $block;
					return;
				}
				catch (Exception $e) {
					$_SESSION['errorMessages'][] = $e;
				}
			}

			// Display the Forms
			if ($service) {
				$this->template->blocks[] = new Block(
					'embed/requestForm.inc',
					array('client'=>$client, 'service'=>$service)
				);
			}
			elseif (isset($_REQUEST['group'])) {
				$this->template->blocks[] = new Block('embed/chooseService.inc', array('endpoint'=>$endpoint));
			}
			else {
				$this->template->blocks[] = new Block('embed/chooseGroup.inc', array('endpoint'=>$endpoint));
			}
		}
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
		}
	}
}