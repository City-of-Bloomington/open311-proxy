<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Application\Models\Person;

$links = '';
if (Person::isAllowed('users')) {
    $routes = [
        'clients'   => 'client',
        'endpoints' => 'endpoint',
        'people'    => 'person',
        'users'     => 'user'
    ];
    foreach ($routes as $plural=>$singular) {
        $requiredAction = 'index';
        if (Person::isAllowed($plural, $requiredAction)) {
            $url = self::generateUri("$plural.index");
            $links.= "<a href=\"$url\">{$this->_([$singular, $plural, 2])}</a>";
        }
    }
}

if ($links) {
    echo "
    <nav>
        <div class=\"menuLauncher\">{$this->_('admin')}</div>
        <div class=\"menuLinks closed\">$links</div>
    </nav>
    ";
}
