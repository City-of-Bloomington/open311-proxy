<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param array $this->endpoints
 */
use Application\Models\Person;
?>
<section>
    <header>
        <h1><?= $this->_(['endpoint', 'endpoints', count($this->endpoints)]); ?></h1>
        <div class="tools">
        <?php
            $helper = $this->template->getHelper('buttonLink');
            if (Person::isAllowed('endpoints', 'add')) {
                echo $helper->buttonLink(
                    self::generateUri('endpoints.update'),
                    $this->_('endpoint_add'),
                    'add'
                );
            }
        ?>
        </div>
    </header>
    <?php
        $fields = ['name', 'url', 'jurisdiction', 'api_key', 'latitude', 'longitude'];
        foreach ($this->endpoints as $endpoint) {
            $rows = '';
            foreach ($fields as $f) {
                $get = 'get'.ucfirst($f);
                $$f  = self::escape($endpoint->$get());

                if ($f != 'name') {
                    $rows.= "<tr><th>{$this->_($f)}</th><td>{$$f}</td></tr>";
                }
            }
            $uri = self::generateUri('endpoints.view', ['id'=>$endpoint->getId()]);
            echo "
            <article>
                <header><h1><a href=\"$uri\">$name</a></h1></header>
                <table>
                    $rows
                </table>
            </article>
            ";
        }
    ?>
</section>