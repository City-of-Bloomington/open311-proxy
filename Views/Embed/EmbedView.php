<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Views\Embed;

use Blossom\Classes\Block;
use Blossom\Classes\Template;

class EmbedView extends Template
{
    public function __construct(array $vars)
    {
        parent::__construct('embed', 'html', $vars);

    }

    public function render()
    {
        if ($this->open311Response) {
            // The user posted something
            $block = new Block('embed/thankYou.inc', ['endpoint' => $this->endpoint]);
            if ($this->service_request) { $block->request = $this->service_request; }
            $this->blocks[] = $block;
        }
        else {
            // Display the Forms
            if ($this->service) {
                $this->blocks[] = new Block(
                    'embed/requestForm.inc',
                    ['client'=>$this->client, 'service'=>$this->service]
                );
            }
            elseif (isset($_REQUEST['group'])) {
                $this->blocks[] = new Block('embed/chooseService.inc', ['endpoint'=>$this->endpoint]);
            }
            else {
                $this->blocks[] = new Block('embed/chooseGroup.inc',   ['endpoint'=>$this->endpoint]);
            }
        }
        return parent::render();
    }
}
