<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;

class EndpointTable extends TableGateway
{
    public function __construct() { parent::__construct('endpoints', __namespace__.'\Endpoint'); }
}