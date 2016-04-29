<?php
/**
 * @copyright 2011-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Client $this->client
 * @param SimpleXMLElement $this->service
 */
use Application\Models\Endpoint;

$endpoint = $this->client->getEndpoint();
$service_code = "{$this->service->service_code}";
$service_name = self::escape($this->service->service_name);
$service_description = self::escape($this->service->description);

foreach (Endpoint::$optionalOpen311Fields as $field) {
	$$field = !empty($_POST[$field]) ? self::escape($_POST[$field]) : '';
}
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

	<form method="post" action="<?= $embed_uri; ?>" enctype="multipart/form-data">
		<fieldset><legend>Location</legend>
			<div>
				<span id="location"><?= $address_string; ?></span>
				<button id="openMapButton" class="chooseLocation">Choose Location</button>
			</div>
			<div id="map_overlay"></div>
			<input name="address_string" id="address_string" type="hidden" value="<?= $address_string; ?>" />
			<input name="lat" id="lat" type="hidden" value="<?= $lat; ?>" />
			<input name="long" id="long" type="hidden" value="<?= $long; ?>" />
		</fieldset>

		<fieldset><legend>Contact Info</legend>
			<table>
				<tr><td><label for="first_name">First Name</label></td>
					<td><input name="first_name" id="first_name" value="<?= $first_name; ?>" type="text" /></td>
				</tr>
				<tr><td><label for="last_name">Last Name</label></td>
					<td><input name="last_name" id="last_name" value="<?= $last_name; ?>" type="text" /></td>
				</tr>
				<tr><td><label for="phone">Phone</label></td>
					<td><input name="phone" id="phone" value="<?= $phone; ?>" type="text" /></td>
				</tr>
				<tr><td><label for="email">Email</label></td>
					<td><input name="email" id="email" value="<?= $email; ?>" type="text" /></td>
				</tr>
			</table>
		</fieldset>

		<fieldset><legend>Report Details</legend>
			<ul><li><label for="description">Description</label>
					<div><textarea name="description" id="description"><?= $description; ?></textarea></div>
				</li>
			<?php
				$service = $endpoint->getServiceDefinition($service_code);
				if ($service && $service->attributes) {
					foreach ($service->attributes->attribute as $attribute) {
						$code = self::escape($attribute->code);
						$description = self::escape($attribute->description);
						$datatype = "{$attribute->datatype}";

						$inputHTML = '';
						switch ($datatype) {
							case 'singlevaluelist':
								echo "
								<li><label for=\"$code\">$description</label>
									<div><select name=\"attribute[$code]\" id=\"$code\"><option></option>
								";
										foreach ($attribute->values->value as $value) {
											$selected = (!empty($_POST['attribute'][$code])
														&& $_POST['attribute'][$code] == $value->key)
												? 'selected="selected"'
												: '';
											$k = self::escape($value->key);
											$n = self::escape($value->name);
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
										$checked = (isset($_POST['attribute'][$code])
													&& is_array($_POST['attribute'][$code])
													&& in_array($value->key, $_POST['attribute'][$code]))
											? 'checked="checked"'
											: '';
										$k = self::escape($value->key);
										$n = self::escape($value->name);
										echo "
										<li><label>
												<input name=\"attribute[{$code}][]\" type=\"checkbox\" value=\"$k\" $checked />
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
								$n = !empty($_POST['attribute'][$code])
									? self::escape($_POST['attribute'][$code])
									: '';
								echo "
								<li><label for=\"$code\">$description</label>
									<div><textarea name=\"attribute[$code]\" id=\"$code\">$n</textarea></div>
								</li>
								";
								break;

							default:
								$n = !empty($_POST['attribute'][$code])
									? self::escape($_POST['attribute'][$code])
									: '';
								echo "
								<li><label for=\"$code\">$description</label>
									<div><input name=\"attribute[$code]\" id=\"$code\" value=\"$n\" /></div>
								</li>
								";
						}
					}
				}
			?>
			</ul>
		</fieldset>

		<fieldset><legend>Media</legend>
			<p>Upload a photo</p>
			<input type="file" name="media" />
		</fieldset>

		<fieldset>
			<input name="client" type="hidden" value="<?= $this->client->getId(); ?>" />
			<input name="service_code" type="hidden" value="<?= $service_code; ?>" />

			<button type="submit" class="submit">Submit</button>
		</fieldset>
	</form>
</section>
<script type="text/javascript">
<?php
	$lat  = $endpoint->getLatitude()  ? $endpoint->getLatitude()  : DEFAULT_LATITUDE;
	$long = $endpoint->getLongitude() ? $endpoint->getLongitude() : DEFAULT_LONGITUDE;
	echo "
	var DEFAULT_LATITUDE  = $lat,
		DEFAULT_LONGITUDE = $long,
		BASE_URL = '".BASE_URL."';
	";
?>
</script>
<?php
	$this->template->addToAsset('scripts', YUI.'/yui/yui-min.js');
	$this->template->addToAsset('scripts', 'https://maps.googleapis.com/maps/api/js?sensor=true');
	$this->template->addToAsset('scripts', BASE_URL.'/js/map_picker.js');
?>
