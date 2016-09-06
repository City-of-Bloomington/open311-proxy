<?php
/**
 * @copyright 2015-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
use Application\Models\Person;

$links = '';
$routes = [
    'clients'   => 'client',
    'endpoints' => 'endpoint',
    'people'    => 'person',
    'users'     => 'user'
];
$requiredAction = 'index';

foreach ($routes as $plural=>$singular) {
    $requiredAction = 'index';
    if (Person::isAllowed($plural, $requiredAction)) {
        $url = BASE_URI."/$plural";
        $links[] = ['url'=>$url, 'label'=>$this->_([$singular, $plural, 2])];
    }
}

if ($links) {
    $helper = $this->getHelper('dropdown');
    echo $helper->dropdown($links, $this->_('admin'), 'Administrator_menu');
}
