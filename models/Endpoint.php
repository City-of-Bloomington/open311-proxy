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
		if (!$this->getUrl() || !$this->getName()) {
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

	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setUrl($string)				{ $this->data['url']			= trim($string); }
	public function setName($string)			{ $this->data['name']			= trim($string); }
	public function setJurisdiction($string)	{ $this->data['jurisdiction']	= trim($string); }
	public function setApi_key($string)			{ $this->data['api_key']		= trim($string); }

	/**
	 * @param array $post
	 */
	public function set($post)
	{
		$fields = array('url','name','jurisdiction','api_key');
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
			$file = file_get_contents($url);
			if ($file) {
				$services = simplexml_load_string($file);
				if ($services) {
					$this->services = $services;
				}
			}
		}
		return $this->services;
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
			$file = file_get_contents($url);
			if ($file) {
				$definition = simplexml_load_string($file);
				if ($definition) {
					$this->serviceDefinitions[$service_code] = $definition;
				}
			}
		}
		return isset($this->serviceDefinitions[$service_code])
			? $this->serviceDefinitions[$service_code]
			: null;
	}

	public function postServiceRequest()
	{
	}

	public function getRequestId()
	{
	}

	public function getServiceRequests()
	{
	}

	public function getServiceRequest()
	{
	}
}