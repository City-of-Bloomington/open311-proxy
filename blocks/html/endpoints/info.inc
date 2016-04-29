<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Endpoint $this->endpoint
 */
use Application\Models\Person;

$fields = array('url','name','jurisdiction','api_key','latitude','longitude');
$rows = '';
foreach ($fields as $field) {
	$get = 'get'.ucfirst($field);
	$$field = self::escape($this->endpoint->$get());

	if ($field != 'name') {
        $rows.= "<tr><th>{$this->_($field)}</th><td>{$$field}</td></tr>";
	}
}
?>
<section>
    <header>
        <h1><?= $name; ?></h1>
        <div class="tools">
        <?php
            if (Person::isAllowed('endpoints', 'edit')) {
                $helper = $this->template->getHelper('buttonLink');
                echo $helper->buttonLink(
                    self::generateUri('endpoints.update', ['id'=>$this->endpoint->getId()]),
                    $this->_('endpoint_edit'),
                    'edit'
                );
            }
        ?>
        </div>
    </header>
	<table>
        <?= $rows; ?>
	</table>
</section>
