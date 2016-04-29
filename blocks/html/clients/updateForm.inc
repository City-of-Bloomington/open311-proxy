<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Client $this->client
 */
use Application\Models\EndpointTable;

$fields = ['id', 'url', 'name', 'api_key', 'endpoint_id'];
foreach ($fields as $f) {
    $get = 'get'.ucfirst($f);
    $$f = self::escape($this->client->$get());
}

$title = $id ? $this->_('client_edit') : $this->_('client_add');
?>
<section>
    <header>
        <h1><?= $title; ?></h1>
    </header>

    <form method="post" action="<?= self::generateUri('clients.update'); ?>">
        <fieldset><legend><?= $this->_('client_info'); ?></legend>
            <input name="id" type="hidden" value="<?= $id; ?>" />
            <?php
                $field = $this->template->getHelper('field');
                echo $field->input(['name'=>'name',    'id'=>'name',    'label'=>$this->_('name'),    'value'=>$name,    'required'=>true]);
                echo $field->input(['name'=>'url',     'id'=>'url',     'label'=>$this->_('url'),     'value'=>$url,     'required'=>true]);
            ?>
            <dl><dt><label   for="endpoint_id"><?= $this->_('endpoint'); ?></label></dt>
                <dd><select name="endpoint_id" id="endpoint_id">
                    <?php
                        $table = new EndpointTable();
                        $list = $table->find();
                        foreach ($list as $endpoint) {
                            $selected = $endpoint_id === $endpoint->getId()
                                ? 'selected="true"'
                                : '';
                            $en = self::escape($endpoint->getName());
                            echo "<option value=\"{$endpoint->getId()}\" $selected>$en</option>";
                        }
                    ?>
                    </select>
                </dd>
            </dl>
            <?php
                echo $field->input(['name'=>'api_key', 'id'=>'api_key', 'label'=>$this->_('api_key'), 'value'=>$api_key]);

                $h = $this->template->getHelper('saveAndCancelButtons');
                echo $h->saveAndCancelButtons(self::generateUri('clients.index'));
            ?>

        </fieldset>
    </form>
</section>
