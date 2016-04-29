<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Views\People;

use Blossom\Classes\Block;
use Blossom\Classes\Template;

class ListView extends Template
{
    public function __construct(array $vars)
    {
        $format = !empty($_REQUEST['format']) ? $_REQUEST['format'] : 'html';
        parent::__construct('default', $format, $vars);

		$this->blocks[] = new Block('people/list.inc',    ['people'   =>$this->people]);
		$this->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$this->people]);
    }
}
