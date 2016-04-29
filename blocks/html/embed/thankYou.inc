<?php
/**
 * @copyright 2012-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Endpoint $this->endpoint
 * @param SimpleXMLElement $this->request
 */
?>
<section class="thankYou">
	<h1><?= self::escape($this->endpoint->getName()); ?></h1>
	<p>Thank you for the report.</p>
	<?php
		if (!empty($_REQUEST['client'])) {
			echo "
			<p>Do you want to
				<a href=\"".BASE_URI."/embed?client=$_REQUEST[client]\">file another report?</a>
			</p>
			";
		}
	?>
</section>
