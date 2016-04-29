<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Controllers;

use Application\Models\Client;
use Application\Models\ClientTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class ClientsController extends Controller
{
    public function index()
    {
        $table = new ClientTable();
        $clients = $table->find();
        return new \Application\Views\Clients\ListView(['clients' => $clients]);
    }

    public function update()
    {
        $client = !empty($_REQUEST['id'])
            ? $this->loadClient($_REQUEST['id'])
            : new Client();

        if (isset($_POST['name'])) {
            try {
                $client->handleUpdate($_POST);
                $client->save();
                header('Location: '.self::generateUrl('clients.index'));
                exit();
            }
            catch (\Exception $e) { $_SESSION['errorMessages'][] = $e; }
        }
        return new \Application\Views\Clients\UpdateView(['client'=>$client]);
    }

    public function delete()
    {
        $client = $this->loadClient($_REQUEST['id']);
        try {
            $client->delete();
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
        }
        header('Location: '.self::generateUrl('clients.index'));
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
			header('Location: '.self::generateUrl('clients.index'));
			exit();
		}
	}
}