<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Client extends ActiveRecord
{
	protected $tablename = 'clients';

	protected $endpoint;

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
				if (is_numeric($id)) {
					$sql = 'select * from clients where id=?';
				}
				else {
					$sql = 'select * from clients where name=?';
				}
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
		if (!$this->getUrl() || !$this->getName() || !$this->getEndpoint_id()) {
			throw new Exception('missingRequiredFields');
		}
	}

	public function save()   { parent::save();   }
	public function delete() { parent::delete(); }

	//----------------------------------------------------------------
	// Generic Getters
	//----------------------------------------------------------------
	public function getId()          { return parent::get('id');          }
	public function getUrl()         { return parent::get('url');         }
	public function getName()        { return parent::get('name');        }
	public function getApi_key()     { return parent::get('api_key');     }
	public function getEndpoint_id() { return parent::get('endpoint_id'); }
	public function getEndpoint()    { return parent::getForeignKeyObject('Endpoint', 'endpoint_id'); }

	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setUrl    ($s) { parent::set('url',     $s); }
	public function setName   ($s) { parent::set('name',    $s); }
	public function setApi_key($s) { parent::set('api_key', $s); }
	public function setEndpoint_id($id)    { parent::setForeignKeyField( 'Endpoint', 'endpoint_id', $id); }
	public function setEndpoint(Person $p) { parent::setForeignKeyObject('Endpoint', 'endpoint_id', $p);  }

	/**
	 * @param array $post
	 */
	public function handleUpdate($post)
	{
		$fields = array('name','url','endpoint_id','api_key');
		foreach ($fields as $field) {
			if (isset($post[$field])) {
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
}