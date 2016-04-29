<?php
/**
 * @copyright 2014-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
use Application\Models\Person;

class PersonTest extends PHPUnit_Framework_TestCase
{
	public function testGetFullName()
	{
		$person = new Person();
		$person->setFirstname('First');
		$person->setLastname('Last');
		$this->assertEquals('First Last', $person->getFullname());
	}

	public function testAuthenticationMethodDefaultsToLocal()
	{
		$person = new Person();
		$person->setFirstname('First');
		$person->setLastname('Last');
		$person->setEmail('test@localhost');
		$person->setUsername('test');
		$person->validate();

		$this->assertEquals('local', $person->getAuthenticationMethod());
	}
}
