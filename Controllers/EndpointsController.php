<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Controllers;

use Application\Models\Endpoint;
use Application\Models\EndpointTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class EndpointsController extends Controller
{
    public function index()
    {
        $table = new EndpointTable();
        $list  = $table->find();
        return new \Application\Views\Endpoints\ListView(['endpoints'=>$list]);
    }

    public function view()
    {
        $endpoint = $this->loadEndpoint($_GET['id']);
        return new \Application\Views\Endpoints\InfoView(['endpoint'=>$endpoint]);
    }

    public function update()
    {
        $endpoint = !empty($_REQUEST['id'])
            ? $this->loadEndpoint($_REQUEST['id'])
            : new Endpoint();

        if (isset($_POST['name'])) {
            try {
                $endpoint->handleUpdate($_POST);
                $endpoint->save();
                header('Location: '.self::generateUrl('endpoints.index'));
                exit();
            }
            catch (\Exception $e) { $_SESSION['errorMessages'][] = $e; }
        }

        return new \Application\Views\Endpoints\UpdateView(['endpoint'=>$endpoint]);
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
			header('Location: '.self::generateUrl('endpoints.index'));
			exit();
		}
	}
}