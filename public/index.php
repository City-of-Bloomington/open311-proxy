<?php
/**
 * @copyright 2015-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
use Blossom\Classes\Block;
use Blossom\Classes\Template;

/**
 * Grab a timestamp for calculating process time
 */
$startTime = microtime(1);

include '../bootstrap.inc';

$p = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
$route = $ROUTES->match($p, $_SERVER);
if ($route) {
    if (isset($route->params['controller']) && isset($route->params['action'])) {

        $role = isset($_SESSION['USER']) ? $_SESSION['USER']->getRole() : 'Anonymous';

        if (   $ZEND_ACL->hasResource($route->params['controller'])
            && $ZEND_ACL->isAllowed($role, $route->params['controller'], $route->params['action'])) {

            $controller = 'Application\\Controllers\\'.ucfirst($route->params['controller']).'Controller';
            $action     = $route->params['action'];

            if (!empty($route->params['id'])) {
                    $_GET['id'] = $route->params['id'];
                $_REQUEST['id'] = $route->params['id'];
            }

            $c = new $controller();
            $view = $c->$action();
        }
        else {
            $view = new \Application\Views\ForbiddenView();
        }
    }
}
else {
    $f = $ROUTES->getFailedRoute();
    $view = new \Application\Views\NotFoundView();
}

echo $view->render();

if ($view->outputFormat === 'html') {
    # Calculate the process time
    $endTime = microtime(1);
    $processTime = $endTime - $startTime;
    echo "<!-- Process Time: $processTime -->";
}
