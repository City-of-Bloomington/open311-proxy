<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Client
{
	private $data;

	private $endpoint;

	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$result = $id;
			}
			else {
				$zend_db = Database::getConnection();
				$sql = 'select * from clients where id=?';
				$result = $zend_db->fetchRow($sql,array($id));
			}

			if ($result) {
				$this->data = $result;
			}
			else {
				throw new Exception('clients/unknownClient');
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
			$zend_db->update('clients',$this->data,"id={$this->getId()}");
		}
		else {
			$zend_db->insert('clients',$this->data);
			$this->data['id'] = $zend_db->lastInsertId('clients','id');
		}
	}

	public function delete()
	{
		if ($this->getId()) {
			$zend_db = Database::getConnection();
			$zend_db->delete('clients',"id={$this->getId()}");
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
	public function getEndpoint_id()	{ return $this->getField('endpoint_id'); }

	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setUrl($string)		{ $this->data['url']	= trim($string); }
	public function setName($string)	{ $this->data['name']	= trim($string); }

	//----------------------------------------------------------------
	// Custom Functions
	//----------------------------------------------------------------
	/**
	 * @return Endpoint
	 */
	public function getEndpoint()
	{
		if (!$this->endpoint) {
			if ($this->getEndpoint_id()) {
				$this->endpoint = new Endpoint($this->getEndpoint_id());
			}
		}
		return $this->endpoint;
	}

	/**
	 * @param string $id
	 */
	public function setEndpoint_id($id)
	{
		$this->endpoint = new Endpoint($id);
		$this->data['endpoint_id'] = $this->endpoint->getId();
	}

	/**
	 * @param Endpoint $endpoint
	 */
	public function setEndpoint(Endpoint $endpoint)
	{
		$this->data['endpoint_id'] = $endpoint->getId();
		$this->endpoint = $endpoint;
	}

	/**
	 * @param array $post
	 */
	public function set($post)
	{
		$fields = array('name','url','endpoint_id');
		foreach ($fields as $field) {
			if (isset($post[$field])) {
				$set = 'set'.ucfirst($field);
				$this->$set($post[$field]);
			}
		}
	}
}