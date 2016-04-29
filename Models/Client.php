<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Models;

use Blossom\Classes\ActiveRecord;
use Blossom\Classes\Database;

class Client extends ActiveRecord
{
	protected $tablename = 'clients';

	protected $endpoint;

	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$this->data = $id;
			}
			else {
                $sql = ActiveRecord::isId($id)
                    ? 'select * from clients where id=?'
                    : 'select * from clients where name=?';

				$rows = parent::doQuery($sql, [$id]);
                if (count($rows)) {
                    $this->data = $rows[0];
                }
                else {
                    throw new \Exception('clients/unknown');
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
		if (!$this->getUrl() || !$this->getName() || !$this->getEndpoint_id()) {
			throw new \Exception('missingRequiredFields');
		}
	}

	public function save()   { parent::save();   }
	public function delete() { parent::delete(); }

	//----------------------------------------------------------------
	// Generic Getters and Setters
	//----------------------------------------------------------------
	public function getId()          { return parent::get('id');          }
	public function getUrl()         { return parent::get('url');         }
	public function getName()        { return parent::get('name');        }
	public function getApi_key()     { return parent::get('api_key');     }
	public function getEndpoint_id() { return parent::get('endpoint_id'); }
	public function getEndpoint()    { return parent::getForeignKeyObject(__namespace__.'\Endpoint', 'endpoint_id'); }

	public function setUrl    ($s) { parent::set('url',     $s); }
	public function setName   ($s) { parent::set('name',    $s); }
	public function setApi_key($s) { parent::set('api_key', $s); }
	public function setEndpoint_id($id)    { parent::setForeignKeyField( __namespace__.'\Endpoint', 'endpoint_id', $id); }
	public function setEndpoint(Person $p) { parent::setForeignKeyObject(__namespace__.'\Endpoint', 'endpoint_id', $p);  }

	/**
	 * @param array $post
	 */
	public function handleUpdate($post)
	{
		$fields = ['name', 'url', 'endpoint_id', 'api_key'];
		foreach ($fields as $field) {
			if (isset($post[$field])) {
				$set = 'set'.ucfirst($field);
				$this->$set($post[$field]);
			}
		}
	}
}