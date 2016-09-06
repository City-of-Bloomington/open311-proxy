<?php
/**
 * @copyright 2011-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Endpoiunt $this->endpoint
 * @param GET group
 */
use Blossom\Classes\Url;

$url = new Url(Url::current_url());
$url->group = $_GET['group'];
?>
<article class="serviceChooser">
    <header>
        <h1><a href="<?= $url; ?>"><?= self::escape($_GET['group']); ?></a></h1>
    </header>
	<ul>
	<?php
		$services = !empty($_GET['group'])
			? $this->endpoint->getGroupServices($_GET['group'])
			: $this->endpoint->getServiceList();

		if ($services) {
            $url = new Url(Url::current_url());

			foreach ($services as $service) {
				$url->service_code = "{$service->service_code}";
				$service_name = self::escape($service->service_name);
				echo "<li><a href=\"$url\">$service_name</a></li>";
			}
		}
	?>
	</ul>
</article>