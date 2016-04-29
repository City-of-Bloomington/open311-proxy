<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param array $this->clients
 */
use Application\Models\Person;
?>
<section>
    <header>
        <h1><?= $this->_(['client', 'clients', count($this->clients)]); ?></h1>
        <div class="tools">
        <?php
            $helper = $this->template->getHelper('buttonLink');
            if (Person::isAllowed('clients', 'add')) {
                echo $helper->buttonLink(
                    self::generateUri('clients.update'),
                    $this->_('client_add'),
                    'add'
                );
            }
        ?>
        </div>
    <header>
    <?php
        $userCanEdit   = Person::isAllowed('clients', 'edit');
        $userCanDelete = Person::isAllowed('clients', 'delete');
        $editButton    = '';
        $deleteButton  = '';

        foreach ($this->clients as $client) {
            $url     = self::escape($client->getUrl());
            $name    = self::escape($client->getName());
            $api_key = self::escape($client->getApi_key());

            $endpoint     = $client->getEndpoint();
            $endpointName = self::escape($endpoint->getName());
            $endpointUri  = self::generateUri('endpoints.view', ['id'=>$endpoint->getId()]);

            if ($userCanEdit) {
                $editButton = $helper->buttonLink(
                    self::generateUri('clients.update', ['id'=>$client->getId()]),
                    $this->_('client_edit'),
                    'edit'
                );
            }
            if ($userCanDelete) {
                $deleteButton = $helper->buttonLink(
                    self::generateUri('clients.delete', ['id'=>$client->getId()]),
                    $this->_('client_delete'),
                    'delete'
                );
            }
            echo "
            <article>
                <h1>$name $editButton $deleteButton</h1>
                <table>
                    <tr><th>{$this->_('url')}</th><td>$url</td></tr>
                    <tr><th>{$this->_('endpoint')}</th>
                        <td><a href=\"$endpointUri\">$endpointName</a></td>
                    </tr>
                    <tr><th>{$this->_('api_key')}</th>
                        <td>$api_key</td>
                    </tr>
                </table>
            </article>
            ";
        }
    ?>
</section>
