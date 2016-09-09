<?php
/**
 * @copyright 2011-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Client   $this->client
 * @param stdClass $this->service
 */
use Application\Models\Endpoint;

$endpoint            = $this->client->getEndpoint();
$service_code        = $this->service->service_code;
$service_name        = self::escape($this->service->service_name);
$service_description = self::escape($this->service->description);

$embed_uri = self::generateUri('embed.index');
?>
<nav class="breadcrumbs">
	<ul><li><a href="<?= "$embed_uri?client={$this->client->getId()}"; ?>">
				All Reports
			</a>
		</li>
		<li><?= $service_name; ?></li>
	</ul>
</nav>
<section class="clientRequestForm">
    <header>
        <h1><?= $service_name; ?></h1>
    </header>
	<p class="service_description"><?= $service_description; ?></p>
	<?php
        $isExternal               = false;
        $this->service_definition = $endpoint->getServiceDefinition($service_code);

        if ($this->service_definition && $this->service_definition->attributes) {
            foreach ($this->service_definition->attributes as $attribute) {

                if ($attribute->code === Endpoint::EXTERNAL) {
                    $isExternal = true;
                    echo "<a href=\"{$attribute->description}\">{$attribute->description}</a>";
                }
            }
        }

        if (!$isExternal) {
            $this->_include('embed/partials/requestForm.inc');
        }
	?>
</section>
