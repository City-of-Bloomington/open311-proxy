<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Endpoint $this->endpoint
 * @param SimpleXMLElement $this->service
 */
$jurisdiction = View::escape($this->endpoint->getJurisdiction());
$api_key = View::escape($this->endpoint->getApi_key());

$service_code = "{$this->service->service_code}";
$service_name = View::escape($this->service->service_name);
$service_description = View::escape($this->service->description);

$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
if (isset($url->parameters['group']))			{ unset($url->parameters['group']); }
if (isset($url->parameters['service_code']))	{ unset($url->parameters['service_code']); }
?>
<div class="breadcrumbs">
	<ul><li><a href="<?php echo $url; ?>">All Reports</a></li>
		<li><?php echo $service_name; ?></li>
	</ul>
</div>
<div class="clientRequestForm">
	<h2><?php echo $service_name; ?></h2>
	<p class="service_description"><?php echo $service_description; ?></p>

	<?php $url->parameters = array(); ?>
	<form method="post" action="<?php echo $url; ?>">
		<fieldset><legend>Contact Information</legend>
			<table>
				<tr><td><label for="first_name">First Name</label></td>
					<td><input name="first_name" id="first_name" /></td>
				</tr>
				<tr><td><label for="last_name">Last Name</label></td>
					<td><input name="last_name" id="last_name" /></td>
				</tr>
				<tr><td><label for="phone">Phone</label></td>
					<td><input name="phone" id="phone" /></td>
				</tr>
				<tr><td><label for="email">Email</label></td>
					<td><input name="email" id="email" /></td>
				</tr>
			</table>
		</fieldset>
		<fieldset><legend>Location</legend>
			<p>If your report involves a specific area or place, please select it using the map.</p>
			<div>
				<span id="location"></span>
				<a id="openMapButton" class="chooseLocation button">Open Map</a>
			</div>
			<div id="map_overlay"></div>
			<input name="address_string" id="address_string" type="hidden" />
			<input name="lat" id="lat" type="hidden" />
			<input name="long" id="long" type="hidden" />
		</fieldset>
		<fieldset><legend>Report Details</legend>
			<input name="jurisdiction_id" type="hidden" value="<?php echo $jurisdiction; ?>" />
			<input name="api_key" type="hidden" value="<?php echo $api_key; ?>" />
			<input name="service_code" type="hidden" value="<?php echo $service_code; ?>" />

			<div>
				<div>
					<label for="description">Description</label>
				</div>
				<textarea name="description" id="description"></textarea>
			</div>
		</fieldset>

		<?php
			$service = $this->endpoint->getServiceDefinition($service_code);
			if ($service && $service->attributes) {
				echo "
				<fieldset><legend>Additional Information</legend>
					<table>
				";
				foreach ($service->attributes->attribute as $attribute) {
					$code = View::escape($attribute->code);
					$description = View::escape($attribute->description);
					$datatype = "{$attribute->datatype}";

					$inputHTML = '';
					switch ($datatype) {
						case 'singlevaluelist':
							$inputHTML = "<select name=\"$code\" id=\"$code\"><option></option>";
							foreach ($attribute->values->value as $value) {
								$k = View::escape($value->key);
								$n = View::escape($value->name);
								$inputHTML.= "<option value=\"$k\">$n</option>";
							}
							$inputHTML.= "</select>";
							break;

						case 'multivaluelist':
							$inputHTML = "<select name=\"{$code}[]\" id=\"$code\" multiple=\"multiple\">";
							foreach ($attribute->values->value as $value) {
								$k = View::escape($value->key);
								$n = View::escape($value->name);
								$inputHTML.= "<option value=\"$k\">$n</option>";
							}
							$inputHTML.= "</select>";
							break;

						case 'text':
							$inputHTML = "<textarea name=\"$code\" id=\"$code\"></textarea>";
							break;

						default:
							$inputHTML = "<input name=\"$code\" id=\"$code\" />";
					}
					echo "
					<tr><td><label for=\"$code\">$description</label></td>
						<td>$inputHTML</td>
					</tr>
					";
				}
				echo "
					</table>
				</fieldset>
				";
			}
		?>
		<fieldset>
			<button type="submit" class="submit">Submit</button>
		</fieldset>
	</form>
</div>
<script type="text/javascript">
	var DEFAULT_LATITUDE = <?php #echo DEFAULT_LATITUDE; ?>,
		DEFAULT_LONGITUDE = <?php #echo DEFAULT_LONGITUDE; ?>,
		BASE_URL = '<?php #echo BASE_URL; ?>';
</script>
<?php
#	$this->template->addToAsset('scripts',YUI.'/yui/yui-min.js');
#	$this->template->addToAsset('scripts','http://maps.googleapis.com/maps/api/js?sensor=true');
#	$this->template->addToAsset('scripts',BASE_URL.'/js/open311/map_picker.js');
?>