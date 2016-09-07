<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Models;

use Blossom\Classes\ActiveRecord;
use Blossom\Classes\Database;
use Blossom\Classes\Url;

class Endpoint extends ActiveRecord
{
	public static $optionalOpen311Fields = [
		'address_string','lat','long',
		'first_name','last_name','phone','email',
		'description'
	];

	protected $tablename = 'endpoints';

	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$this->data = $id;
			}
			else {
                $sql = 'select * from endpoints where id=?';
				$rows = parent::doQuery($sql, [$id]);
                if (count($rows)) {
                    $this->data = $rows[0];
                }
                else {
                    throw new \Exception('endpoints/unknown');
                }
			}
		}
		else {
			// This is where the code goes to generate a new, empty instance.
			// Set any default values for properties that need it here
		}
	}

	public function validate()
	{
		if (!$this->getUrl() || !$this->getName() || !$this->getJurisdiction()) {
			throw new \Exception('missingRequiredFields');
		}
	}

	public function save()   { parent::save();   }

	//----------------------------------------------------------------
	// Generic Getters and Setters
	//----------------------------------------------------------------
	public function getId()           { return parent::get('id');           }
	public function getUrl()          { return parent::get('url');          }
	public function getName()         { return parent::get('name');         }
	public function getJurisdiction() { return parent::get('jurisdiction'); }
	public function getApi_key()      { return parent::get('api_key');      }
	public function getLatitude()     { return parent::get('latitude');     }
	public function getLongitude()    { return parent::get('longitude');    }

	public function setUrl         ($s) { parent::set('url',          $s); }
	public function setName        ($s) { parent::set('name',         $s); }
	public function setJurisdiction($s)	{ parent::set('jurisdiction', $s); }
	public function setApi_key     ($s) { parent::set('api_key',      $s); }
	public function setLatitude    ($f) { parent::set('latitude', (float)$f); }
	public function setLongitude   ($f) { parent::set('longitude',(float)$f); }

	/**
	 * @param array $post
	 */
	public function handleUpdate($post)
	{
		$fields = ['url', 'name', 'jurisdiction', 'latitude', 'longitude'];
		foreach ($fields as $field) {
			if (isset($post)) {
				$set = 'set'.ucfirst($field);
				$this->$set($post[$field]);
			}
		}
	}

	//----------------------------------------------------------------
	// Open311 API Functions
	//----------------------------------------------------------------
	/**
	 * @return array
	 */
	public function getServiceGroups()
	{
		$groups = [];
		$services = $this->getServiceList();
		if ($services) {
			foreach ($services as $service) {
				$group = "{$service->group}";
				if (!in_array($group, $groups)) {
					$groups[] = $group;
				}
			}
		}
		return $groups;
	}

	/**
	 * @return stdClass JSON data for the service list
	 */
	public function getServiceList()
	{
        static $services = null;

		if (!$services) {
			$url  = "{$this->getUrl()}/services.json?jurisdiction_id={$this->getJurisdiction()}&api_key={$this->getApi_key()}";
			$json = $this->queryServer($url);
			if ($json) {
				$services = $json;
			}
		}
		return $services;
	}

	/**
	 * Returns only the services matching the given group
	 *
	 * @param string $group
	 * @return array An array of Service objects
	 */
	public function getGroupServices($group)
	{
		$out = [];
		foreach ($this->getServiceList() as $service) {
			if ((string)$service->group == $group) {
				$out[] = $service;
			}
		}
		return $out;
	}

	/**
	 * Returns a single service entry from GET Service List
	 *
	 * @param string $service_code
	 * @return SimpleXMLElement
	 */
	public function getService($service_code)
	{
		foreach ($this->getServiceList() as $service) {
			if ("{$service->service_code}" == $service_code) {
				return $service;
			}
		}
	}

	/**
	 * Returns the result from GET Service Definition for a single service
	 *
	 * @param string $service_code
	 * @return stdClass
	 */
	public function getServiceDefinition($service_code)
	{
        static $defs = [];

		if (!array_key_exists($service_code, $defs)) {
			$url = "{$this->getUrl()}/services/$service_code.json?jurisdiction_id={$this->getJurisdiction()}&api_key={$this->getApi_key()}";
			$d = $this->queryServer($url);
			if ($d) { $defs[$service_code] = $d; }
		}

		return isset($defs[$service_code])
                   ? $defs[$service_code]
                   : null;
	}

	/**
	 * @param  array    $post
	 * @param  Client   $client
	 * @return stdClass
	 */
	public function postServiceRequest(array $post, Client $client=null)
	{
		$api_key = $client->getApi_key() ? $client->getApi_key() : $this->getApi_key();
		$request = [
			'jurisdiction_id' => $this->getJurisdiction(),
			'api_key'         => $api_key,
			'service_code'    => $_POST['service_code']
		];
		foreach (self::$optionalOpen311Fields as $field) {
			if (!empty($_POST[$field])) {
				$request[$field] = $_POST[$field];
			}
		}
		$service = $this->getServiceDefinition($post['service_code']);
		if ($service && $service->attributes) {
			foreach ($service->attributes->attribute as $attribute) {
				$code = "{$attribute->code}";
				if (isset($_POST['attribute'][$code])) {
					$request['attribute'][$code] = $_POST['attribute'][$code];
				}
			}
		}
		if (!empty($_FILES['media']['name'])) {
            $request['media'] = new \CURLFile($_FILES['media']['tmp_name'], $_FILES['media']['type'], $_FILES['media']['name']);
		}
		$open311 = curl_init("{$this->getUrl()}/requests.json");
		curl_setopt_array($open311, [
			CURLOPT_POST           => true,
			CURLOPT_HEADER         => false,
			CURLOPT_RETURNTRANSFER => true,
			CURLOPT_POSTFIELDS     => $this->flatten_request_array($request),
			CURLOPT_SSL_VERIFYPEER => false
		]);
		$response = curl_exec($open311);
		if (!$response) {
			throw new \Exception(curl_error($open311));
		}
		$json = json_decode($response);
		if (!$json) {
			echo "------Error from Open311 server----------\n";
			echo $response;
			exit();
		}
		else {
			return $json;
		}
	}

	/**
	 * Creates a curl fields array from a POST array
	 *
	 * Curl does not allow multidimensional arrays.
	 * Instead, you must flatten the multidimensional arrays into
	 * simple fieldname strings
	 *
	 * @param array $request
	 * @param string $prefix
	 * @return array
	 */
	private function flatten_request_array(array $request, $prefix=null)
	{
		$out = [];
		foreach ($request as $key=>$value) {
			if (!is_array($value)) {
				if ($prefix) { $out[$prefix."[$key]"] = $value; }
				else         { $out[$key]             = $value; }
			}
			else {
				$out = array_merge(
					$out,
					$this->flatten_request_array($value, $prefix ? $prefix."[$key]" : $key)
				);
			}
		}
		return $out;
	}

	/**
	 * @param string $service_request_id
	 */
	public function getServiceRequest($service_request_id)
	{
		$service_request_id = (string)$service_request_id;
		return $this->queryServer("{$this->getUrl()}/requests/$service_request_id.json");
	}

	/**
	 * @param  string   $url
	 * @return stdClass The JSON data as an object
	 */
	private function queryServer($url)
	{
		$file = Url::get($url);
		if ($file) {
            $json = json_decode($file);
			if ($json) {
				return $json;
			}
			else {
				throw new \Exception('endpoints/invalidJSON');
			}
		}
		else {
			throw new \Exception('endpoints/open311ServerUnReachable');
		}
	}
}