<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Person extends SystemUser
{
	private $data;

	public static function getAuthenticationMethods()
	{
		return array('local','Employee');
	}

	/**
	 * Populates the object with data
	 *
	 * Passing in an associative array of data will populate this object without
	 * hitting the database.
	 *
	 * Passing in a scalar will load the data from the database.
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 *
	 * @param int|string|array $id (ID, email, username)
	 */
	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$result = $id;
			}
			else {
				$zend_db = Database::getConnection();
				if (ctype_digit($id)) {
					$sql = 'select * from people where id=?';
				}
				elseif (false !== strpos($id,'@')) {
					$sql = 'select * from people where email=?';
				}
				else {
					$sql = 'select * from people where username=?';
				}
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

	/**
	 * Throws an exception if anything's wrong
	 * @throws Exception $e
	 */
	public function validate()
	{
		// Check for required fields here.  Throw an exception if anything is missing.
		if (!$this->getFirstname() || !$this->getEmail()) {
			throw new Exception('missingRequiredFields');
		}

		if ($this->getUsername() && !$this->getAuthenticationMethod()) {
			throw new Exception('people/missingAuthenticationMethod');
		}
	}

	/**
	 * Saves this record back to the database
	 */
	public function save()
	{
		$this->validate();
		$zend_db = Database::getConnection();

		if ($this->getId()) {
			$zend_db->update('people',$this->data,"id={$this->getId()}");
		}
		else {
			$zend_db->insert('people',$this->data);
			$this->data['id'] = $zend_db->lastInsertId('people','id');
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
	public function getId()						{ return $this->getField('id'); }
	public function getFirstname()				{ return $this->getField('firstname'); }
	public function getLastname()				{ return $this->getField('lastname'); }
	public function getEmail()					{ return $this->getField('email'); }
	public function getUsername()				{ return $this->getField('username'); }
	public function getRole()					{ return $this->getField('role'); }
	public function getAuthenticationMethod()	{ return $this->getField('authenticationMethod'); }

	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setFirstname($string)					{ $this->data['firstname'] = trim($string); }
	public function setLastname($string)					{ $this->data['lastname'] = trim($string); }
	public function setEmail($string)						{ $this->data['email'] = trim($string); }
	public function setUsername($string)					{ $this->data['username'] = trim($string); }
	public function setAuthenticationMethod($string=null)	{ $this->data['authenticationMethod'] = trim($string); }

	//----------------------------------------------------------------
	// Custom Functions
	//----------------------------------------------------------------
	/**
	 * Sets a person's role
	 *
	 * Roles must be defined in access_control.inc
	 *
	 * @param string $string
	 */
	public function setRole($string)
	{
		global $ZEND_ACL;

		$roles = $ZEND_ACL->getRoles();
		$string = trim($string);
		if (in_array($string, $roles)) {
			$this->data['role'] = $string;
		}
		else {
			throw new Exception('people/unknownRole');
		}
	}


	/**
	 * Callback function from the SystemUser class
	 *
	 * The SystemUser class will determine where the authentication
	 * should occur.  If the user should be authenticated locally,
	 * this function will be called.
	 *
	 * @param string $password
	 * @return boolean
	 */
	protected function authenticateDatabase($password)
	{
		if ($this->getUsername()) {
			$sha1 = sha1(trim($password));

			$zend_db = Database::getConnection();
			$id = $zend_db->fetchOne(
				'select id from people where username=? and password=?',
				array($this->getUsername(),$sha1)
			);
			return $id ? true : false;
		}
	}

	/**
	 * Encrypts the user-provided password
	 *
	 * @param string $string
	 */
	public function setPassword($string=null)
	{
		$this->data['password'] = sha1(trim($string));
	}

	/**
	 * Callback function from the SystemUser class
	 * The SystemUser will determine where the password should be stored.
	 * If the password is stored locally, it will call this function
	 * Passwords should already be encrypted
	 */
	protected function saveLocalPassword()
	{
		if ($this->getId()) {
			$zend_db = Database::getConnection();
			$zend_db->update(
				'people',
				array('password'=>$this->data['password']),
				"id={$this->getId()}"
			);
		}
	}

	/**
	 * Clears all the user account fields
	 */
	public function deleteUserAccount()
	{
		$this->data['username'] = null;
		$this->data['password'] = null;
		$this->data['authenticationMethod'] = null;
		$this->data['role'] = null;
	}

	/**
	 * @return string
	 */
	public function getFullname()
	{
		return "{$this->getFirstname()} {$this->getLastname()}";
	}

	/**
	 * @return string
	 */
	public function getURL()
	{
		if ($this->getId()) {
			return BASE_URL.'/people/view?person_id='.$this->getId();
		}
	}

	/**
	 * @param array $post
	 */
	public function set($post)
	{
		$fields = array('firstname','lastname','email','username','authenticationMethod','role');
		foreach ($fields as $f) {
			if (isset($post[$f])) {
				$set = 'set'.ucfirst($f);
				$this->$set($post[$f]);
			}
			if (!empty($post['password'])) {
				$this->setPassword($post['password']);
			}
		}

		$method = $this->getAuthenticationMethod();
		if ($this->getUsername() && $method && $method != 'local') {
			$identity = new $method($this->getUsername());
			$this->populateFromExternalIdentity($identity);
		}
	}

	/**
	 * @param ExternalIdentity $identity An object implementing ExternalIdentity
	 */
	public function populateFromExternalIdentity(ExternalIdentity $identity)
	{
		if (!$this->getFirstname() && $identity->getFirstname()) {
			$this->setFirstname($identity->getFirstname());
		}
		if (!$this->getLastname() && $identity->getLastname()) {
			$this->setLastname($identity->getLastname());
		}
		if (!$this->getEmail() && $identity->getEmail()) {
			$this->setEmail($identity->getEmail());
		}
	}
}
