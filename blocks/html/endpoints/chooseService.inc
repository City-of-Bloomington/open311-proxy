<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoiunt $this->endpoint
 * @param GET group
 */
$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
$url->group = $_GET['group'];
?>
<div class="serviceChooser">
	<h2><a href="<?php echo $url; ?>">
			<?php echo View::escape($_GET['group']); ?>
		</a>
	</h2>
	<ul>
	<?php
		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		$services = $this->endpoint->getServiceList();
		if ($services) {
			foreach ($services as $service) {
				$url->service_code = "{$service->service_code}";
				$service_name = View::escape($service->service_name);
				echo "<li><a href=\"$url\">$service_name</a></li>";
			}
		}
	?>
	</ul>
</div>