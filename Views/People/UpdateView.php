<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Views\People;

use Blossom\Classes\Block;
use Blossom\Classes\Template;

class UpdateView extends Template
{
    public function __construct(array $vars)
    {
        parent::__construct('default', 'html', $vars);

        $this->blocks[] = new Block('people/updateForm.inc', [
            'person'     => $this->person,
            'return_url' => $this->return_url
        ]);
    }
}
