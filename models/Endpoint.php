<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Endpoint
{
	private $data;

	private $services; // SimpleXML object from GET Service List response
	private $serviceDefinitions = array(); // Array of SimpleXMLElements with service_code as the key

	public static $optionalOpen311Fields = array(
		'address_string','lat','long',
		'first_name','last_name','phone','email',
		'description'
	);

	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$result = $id;
			}
			else {
				$zend_db = Database::getConnection();
				$sql = 'select * from endpoints where id=?';
				$result = $zend_db->fetchRow($sql,array($id));
			}

			if ($result) {
				$this->data = $result;
			}
			else {
				throw new Exception('endpoints/unknownEndpoint');
			}
		}
		else {
			// This is where the code goes to generate a new, empty instance.
			// Set any default values for properties that need it here
		}
	}

	public function validate()
	{
		if (!$this->getUrl() || !$this->getName()
			|| !$this->getJurisdiction() || !$this->getApi_key()) {
			throw new Exception('missingRequiredFields');
		}
	}

	public function save()
	{
		$this->validate();
		$zend_db = Database::getConnection();

		if ($this->getId()) {
			$zend_db->update('endpoints',$this->data,"id={$this->getId()}");
		}
		else {
			$zend_db->insert('endpoints',$this->data);
			$this->data['id'] = $zend_db->lastInsertId('endpoints','id');
		}
	}

	//----------------------------------------------------------------
	// Generic Getters
	//----------------------------------------------------------------
	public function getField($field)
	{
		if (isset($this->data[$field])) {
			return $this->data[$field];
		}
	}
	public function getId()				{ return $this->getField('id'); }
	public function getUrl()			{ return $this->getField('url'); }
	public function getName()			{ return $this->getField('name'); }
	public function getJurisdiction()	{ return $this->getField('jurisdiction'); }
	public function getApi_key()		{ return $this->getField('api_key'); }
	public function getLatitude()		{ return $this->getField('latitude'); }
	public function getLongitude()		{ return $this->getField('longitude'); }

	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setUrl($string)				{ $this->data['url']			= trim($string); }
	public function setName($string)			{ $this->data['name']			= trim($string); }
	public function setJurisdiction($string)	{ $this->data['jurisdiction']	= trim($string); }
	public function setApi_key($string)			{ $this->data['api_key']		= trim($string); }
	public function setLatitude($float)			{ $this->data['latitude']		= (float)$float; }
	public function setLongitude($float)		{ $this->data['longitude']		= (float)$float; }

	/**
	 * @param array $post
	 */
	public function set($post)
	{
		$fields = array('url','name','jurisdiction','api_key','latitude','longitude');
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
		$groups = array();
		$services = $this->getServiceList();
		if ($services) {
			foreach ($services->service as $service) {
				$group = "{$service->group}";
				if (!in_array($group, $groups)) {
					$groups[] = $group;
				}
			}
		}
		return $groups;
	}

	/**
	 * @return SimpleXMLElement
	 */
	public function getServiceList()
	{
		if (!$this->services) {
			$url = "{$this->getUrl()}/services.xml?jurisdiction_id={$this->getJurisdiction()}&api_key={$this->getApi_key()}";
			$services = $this->queryServer($url);
			if ($services) {
				$this->services = $services;
			}
		}
		return $this->services;
	}

	/**
	 * Returns only the services matching the given group
	 *
	 * @param string $group
	 * @return array An array of SimpleXMLElements
	 */
	public function getGroupServices($group)
	{
		$out = array();
		foreach ($this->services as $service) {
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
	 * @return SimpleXMLElement
	 */
	public function getServiceDefinition($service_code)
	{
		if (!array_key_exists($service_code, $this->serviceDefinitions)) {
			$url = "{$this->getUrl()}/services/$service_code.xml?jurisdiction_id={$this->getJurisdiction()}&api_key={$this->getApi_key()}";
			$definition = $this->queryServer($url);
			if ($definition) {
				$this->serviceDefinitions[$service_code] = $definition;
			}
		}
		return isset($this->serviceDefinitions[$service_code])
			? $this->serviceDefinitions[$service_code]
			: null;
	}

	/**
	 * @param array $post
	 * @param Client $client
	 * @return SimpleXMLElement
	 */
	public function postServiceRequest(array $post, Client $client=null)
	{
		$api_key = $client->getApi_key() ? $client->getApi_key() : $this->getApi_key();
		$request = array(
			'jurisdiction_id'=>$this->getJurisdiction(),
			'api_key'=>$api_key,
			'service_code'=>$_POST['service_code']
		);
		foreach (self::$optionalOpen311Fields as $field) {
			if (!empty($_POST[$field])) {
				$request[$field] = $_POST[$field];
			}
		}
		$service = $this->getServiceDefinition($post['service_code']);
		if ($service && $service->attributes) {
			foreach ($service->attributes->attribute as $attribute) {
				$code = "{$attribute->code}";
				if (isset($_POST[$code])) {
					$request[$code] = $_POST[$code];
				}
			}
		}
		$open311 = curl_init("{$this->getUrl()}/requests.xml");
		curl_setopt_array($open311, array(
			CURLOPT_POST=>true,
			CURLOPT_HEADER=>false,
			CURLOPT_RETURNTRANSFER=>true,
			CURLOPT_POSTFIELDS=>$request,
			CURLOPT_SSL_VERIFYPEER=>false
		));
		$response = curl_exec($open311);
		if (!$response) {
			throw new Exception(curl_error($open311));
		}

		return simplexml_load_string($response);
	}

	public function getRequestId()
	{
	}

	public function getServiceRequests()
	{
	}

	/**
	 * @param SimpleXMLElement|string
	 */
	public function getServiceRequest($service_request_id)
	{
		$service_request_id = (string)$service_request_id;
		return $this->queryServer("{$this->getUrl()}/requests/$service_request_id.xml");
	}

	/**
	 * @param string $url
	 * @return SimpleXMLElement
	 */
	private function queryServer($url)
	{
		$file = file_get_contents($url);
		if ($file) {
			$xml = simplexml_load_string($file);
			if ($xml) {
				return $xml;
			}
			else {
				throw new Exception('endpoints/invalidXML');
			}
		}
		else {
			throw new Exception('endpoints/open311ServerUnReachable');
		}
	}
}