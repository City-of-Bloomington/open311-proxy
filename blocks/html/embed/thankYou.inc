<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoint $this->endpoint
 * @param SimpleXMLElement $this->request
 */
?>
<div class="thankYou">
	<h2><?php echo View::escape($this->endpoint->getName()); ?></h2>
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
</div>
