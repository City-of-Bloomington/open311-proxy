<?php
/**
 * @copyright 2011-2017 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Endpoint $this->endpoint
 * @param GET group
 */
use Application\Models\Endpoint;
use Blossom\Classes\Url;

$url = new Url(Url::current_url(APPLICATION_HOST));
$url->group = $_GET['group'];

$title = $_GET['group'] === Endpoint::FEATURED
    ? $this->_(Endpoint::FEATURED)
    : self::escape($_GET['group']);
?>
<article class="serviceChooser">
    <header>
        <h1><a href="<?= $url; ?>"><?= $title; ?></a></h1>
    </header>
	<ul>
	<?php
		$services = !empty($_GET['group'])
			? $this->endpoint->getGroupServices($_GET['group'])
			: $this->endpoint->getServiceList();

		if ($services) {
            $url = new Url(Url::current_url(APPLICATION_HOST));

			foreach ($services as $s) {
				$url->service_code = $s->service_code;
				$service_name      = self::escape($s->service_name);
				echo "<li><a href=\"$url\">$service_name</a></li>";
			}
		}
	?>
	</ul>
</article>
