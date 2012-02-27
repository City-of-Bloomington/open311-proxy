<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Endpoint
{
	private $data;

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
				throw new Exception('people/unknownPerson');
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

	//----------------------------------------------------------------
	// Custom Functions
	//----------------------------------------------------------------
	/**
	 * @param array $post
	 */
	public function set($post)
	{
		$fields = array('url','name','jurisdiction','api_key');
		foreach ($fields as $field) {
			if (isset($post)) {
				$set = ucfirst($field);
				$this->$set($post[$field]);
			}
		}
	}
}