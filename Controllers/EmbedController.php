<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Controllers;

use Application\Models\Client;
use Application\Models\Captcha;
use Blossom\Classes\Controller;

class EmbedController extends Controller
{
    public function index(array $params=null)
    {
		$client = !empty($_REQUEST['client']) ? $this->loadClient($_REQUEST['client']) : null;
		if ($client) {
			$endpoint = $client->getEndpoint();
			$service  = !empty($_REQUEST['service_code'])
				? $endpoint->getService($_REQUEST['service_code'])
				: null;

			// Handle what the user posts
			if ($service && isset($_POST['service_code']) && Captcha::verify()) {
				try {
					$json     = $endpoint->postServiceRequest($_POST, $client);
					$response = $json[0];
					if (!empty($response->service_request_id)) {
						try {
							$request = $endpoint->getServiceRequest($response->service_request_id);
						}
						catch (Exception $e) {
                            $_SESSION['errorMessages'][] = $e;
                        }
					}
				}
				catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
			}

            $view = new \Application\Views\Embed\EmbedView([
                'client'   => $client,
                'service'  => $service,
                'endpoint' => $endpoint
            ]);
            if (isset($response)) { $view->open311Response = $response; }
            if (isset($request )) { $view->service_request = $request;  }
		}
		else {
            $view = new \Application\Views\NotFoundView();
		}
        return $view;
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