<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Views\Users;

use Blossom\Classes\Block;
use Blossom\Classes\Template;

class ListView extends Template
{
    public function __construct(array $vars)
    {
        parent::__construct('default', 'html', $vars);

		$this->blocks[] = new Block('users/list.inc',     ['users'     => $this->users]);
		$this->blocks[] = new Block('pageNavigation.inc', ['paginator' => $this->users]);
    }
}
