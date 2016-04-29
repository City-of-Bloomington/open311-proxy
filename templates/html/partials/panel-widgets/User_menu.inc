<nav>
<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Blossom\Classes\View;

if (isset($_SESSION['USER'])) {
    $name = self::escape($_SESSION['USER']->getFullname());
    $url = self::generateUri('login.logout');

    echo "
    <div class=\"menuLauncher\">$name</div>
    <div class=\"menuLinks closed\">
        <a href=\"$url\">{$this->_('logout')}</a>
    </div>
    ";
}
else {
    $return_url = self::escape($_SERVER['REQUEST_URI']);
    $url = self::generateUri('login.index');
    echo "<a href=\"$url?return_url=$return_url\">{$this->_('login')}</a>";
}
?>
</nav>