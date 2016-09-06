<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Endpoint $this->endpoint
 */
$fields = ['id', 'url', 'name', 'jurisdiction', 'api_key', 'latitude', 'longitude'];
foreach ($fields as $f) {
    $get = 'get'.ucfirst($f);
    $$f = $this->endpoint->$get();
}

$title = $id ? $this->_('endpoint_edit') : $this->_('endpoint_add');
?>
<section>
    <header><h1><?= $title; ?></h1></header>
    <form method="post" action="<?= self::generateUri('endpoints.update'); ?>">
        <fieldset>
            <p><?= $this->_('endpointInfoHelp', 'messages'); ?></p>
            <input name="id" type="hidden" value="<?= $id; ?>" />
            <?php
                $field = $this->template->getHelper('field');
                foreach (['name', 'url', 'jurisdiction', 'api_key'] as $f) {
                    echo $field->field(['name'=>$f, 'id'=>$f, 'label'=>$this->_($f), 'value'=>$$f, 'required'=>true]);
                }
            ?>
        </fieldset>

        <fieldset>
            <p><?= $this->_('endpointCoordinatesHelp', 'messages'); ?></p>
            <?php
                foreach (['latitude', 'longitude'] as $f) {
                    echo $field->field(['name'=>$f, 'id'=>$f, 'label'=>$this->_($f), 'value'=>$$f]);
                }

                $h = $this->template->getHelper('saveAndCancelButtons');
                echo $h->saveAndCancelButtons(self::generateUri('endpoints.index'));
            ?>
        </fieldset>
    </form>
</section>
