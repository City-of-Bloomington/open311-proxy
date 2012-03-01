<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Client $this->client
 * @param SimpleXMLElement $this->service
 */
$endpoint = $this->client->getEndpoint();
$service_code = "{$this->service->service_code}";
$service_name = View::escape($this->service->service_name);
$service_description = View::escape($this->service->description);

foreach (Endpoint::$optionalOpen311Fields as $field) {
	$$field = !empty($_POST[$field]) ? View::escape($_POST[$field]) : '';
}
?>
<div class="breadcrumbs">
	<ul><li><a href="<?php echo BASE_URI."/embed/view?client={$this->client->getId()}"; ?>">
				All Reports
			</a>
		</li>
		<li><?php echo $service_name; ?></li>
	</ul>
</div>
<div class="clientRequestForm">
	<h2><?php echo $service_name; ?></h2>
	<p class="service_description"><?php echo $service_description; ?></p>

	<form method="post" action="<?php echo BASE_URI; ?>/embed">
		<fieldset><legend>Location</legend>
			<div>
				<span id="location"><?php echo $address_string; ?></span>
				<button id="openMapButton" class="chooseLocation">Choose Location</button>
			</div>
			<div id="map_overlay"></div>
			<input name="address_string" id="address_string" type="hidden" value="<?php echo $address_string; ?>" />
			<input name="lat" id="lat" type="hidden" value="<?php echo $lat; ?>" />
			<input name="long" id="long" type="hidden" value="<?php echo $long; ?>" />
		</fieldset>

		<fieldset><legend>Contact Information</legend>
			<table>
				<tr><td><label for="first_name">First Name</label></td>
					<td><input name="first_name" id="first_name" value="<?php echo $first_name; ?>" /></td>
				</tr>
				<tr><td><label for="last_name">Last Name</label></td>
					<td><input name="last_name" id="last_name" value="<?php echo $last_name; ?>" /></td>
				</tr>
				<tr><td><label for="phone">Phone</label></td>
					<td><input name="phone" id="phone" value="<?php echo $phone; ?>" /></td>
				</tr>
				<tr><td><label for="email">Email</label></td>
					<td><input name="email" id="email" value="<?php echo $email; ?>" /></td>
				</tr>
			</table>
		</fieldset>

		<fieldset><legend>Report Details</legend>
			<ul><li><label for="description">Description</label>
					<div><textarea name="description" id="description"><?php echo $description; ?></textarea></div>
				</li>
			<?php
				$service = $endpoint->getServiceDefinition($service_code);
				if ($service && $service->attributes) {
					foreach ($service->attributes->attribute as $attribute) {
						$code = View::escape($attribute->code);
						$description = View::escape($attribute->description);
						$datatype = "{$attribute->datatype}";

						$inputHTML = '';
						switch ($datatype) {
							case 'singlevaluelist':
								echo "
								<li><label for=\"$code\">$description</label>
									<div><select name=\"$code\" id=\"$code\"><option></option>
								";
										foreach ($attribute->values->value as $value) {
											$selected = (!empty($_POST[$code]) && $_POST[$code]==$value->$key)
												? 'selected="selected"'
												: '';
											$k = View::escape($value->key);
											$n = View::escape($value->name);
											echo "<option value=\"$k\" $selected>$n</option>";
										}
								echo "
										</select>
									</div>
								</li>
								";
								break;

							case 'multivaluelist':
								echo "
								<li><fieldset><legend>$description</legend>
									<ul>
								";
									foreach ($attribute->values->value as $value) {
										$checked = (isset($_POST[$code]) && is_array($_POST[$code]) && in_array($value->key, $_POST[$code]))
											? 'checked="checked"'
											: '';
										$k = View::escape($value->key);
										$n = View::escape($value->name);
										echo "
										<li><label>
												<input name=\"{$code}[]\" type=\"checkbox\" value=\"$k\" $checked />
												$n
											</label>
										</li>
										";
									}
								echo "
									</ul>
									</fieldset>
								</li>
								";
								break;

							case 'text':
								$n = !empty($_POST[$code]) ? View::escape($_POST[$code]) : '';
								echo "
								<li><label for=\"$code\">$description</label>
									<div><textarea name=\"$code\" id=\"$code\">$n</textarea></div>
								</li>
								";
								break;

							default:
								$n = !empty($_POST[$code]) ? View::escape($_POST[$code]) : '';
								echo "
								<li><label for=\"$code\">$description</label>
									<div><input name=\"$code\" id=\"$code\" value=\"$n\" /></div>
								</li>
								";
						}
					}
				}
			?>
			</ul>
		</fieldset>

		<fieldset>
			<input name="client" type="hidden" value="<?php echo $this->client->getId(); ?>" />
			<input name="service_code" type="hidden" value="<?php echo $service_code; ?>" />

			<button type="submit" class="submit">Submit</button>
		</fieldset>
	</form>
</div>
<script type="text/javascript">
<?php
	$lat = $endpoint->getLatitude() ? $endpoint->getLatitude() : DEFAULT_LATITUDE;
	$long = $endpoint->getLongitude() ? $endpoint->getLongitude() : DEFAULT_LONGITUDE;
	echo "
	var DEFAULT_LATITUDE = $lat,
		DEFAULT_LONGITUDE = $long,
		BASE_URL = '".BASE_URL."';
	";
?>
</script>
<?php
	$this->template->addToAsset('scripts',YUI.'/yui/yui-min.js');
	$this->template->addToAsset('scripts','http://maps.googleapis.com/maps/api/js?sensor=true');
	$this->template->addToAsset('scripts',BASE_URL.'/js/map_picker.js');
?>