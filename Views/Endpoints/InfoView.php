<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Views\Endpoints;

use Blossom\Classes\Block;
use Blossom\Classes\Template;

class InfoView extends Template
{
    public function __construct(array $vars)
    {
        parent::__construct('default', 'html', $vars);

		$this->blocks[] = new Block('endpoints/info.inc', ['endpoint' => $this->endpoint]);
    }
}
