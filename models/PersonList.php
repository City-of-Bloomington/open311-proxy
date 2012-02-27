<?php
/**
 * A collection class for Person objects
 *
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class PersonList extends ZendDbResultIterator
{
	/**
	 * @param array $fields
	 */
	public function __construct($fields=null)
	{
		parent::__construct();
		if (is_array($fields)) {
			$this->find($fields);
		}
	}

	/**
	 * Populates the collection
	 *
	 * @param array $fields
	 * @param string|array $order Multi-column sort should be given as an array
	 * @param int $limit
	 * @param string|array $groupBy Multi-column group by should be given as an array
	 */
	public function find($fields=null,$order='lastname',$limit=null,$groupBy=null)
	{
		$this->select->from('people');

		if (count($fields)) {
			foreach ($fields as $key=>$value) {
				switch ($key) {
					case 'user_account':
						if ($value) {
							$this->select->where('username is not null');
						}
						else {
							$this->select->where('username is null');
						}
					break;

					default:
						$this->select->where("$key=?",$value);
				}
			}
		}

		$this->select->order($order);
		if ($limit) {
			$this->select->limit($limit);
		}
		if ($groupBy) {
			$this->select->group($groupBy);
		}
		$this->populateList();
	}

	/**
	 * Loads a single Person object for the row returned from ZendDbResultIterator
	 *
	 * @param array $key
	 */
	protected function loadResult($key)
	{
		return new Person($this->result[$key]);
	}
}
