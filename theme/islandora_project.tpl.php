<?php
/**
 * @file
 * This is the template file for the person object page.
 *
 * Here we build an html page using the variables passed in by
 * the islandora_bioinformatics_base_preprocess_islandora_person
 * function.  Elements such as labels and buttons can be added here
 */

/**
 * 	Written by Quintin Dawson, based off of Islandora_Porcus solution pack
 */

//$islandora_content = $islandora_object['PERSON']->content;
//$path = drupal_get_path('module', 'islandora_bioinformatics_base');

/*echo "<pre>";
print_r($variables['project']);
echo "</pre>";*/
?>

<style>
    .person-info {
        float: left;
        position: relative;
        top: 8px;
        margin-right: 20px;
    }

    .person-pic {
        float: left;
        position: relative;
        top: 8px;
        border: none;
    }

    .person-info table {
        border: none;
    }

    .person-info-label {
        font-weight: bold;
        font-size: 14px;
        width: 180px;
    }

    .person-info-heading {
        font-weight: bold;
        font-size: 14px;
        width: 180px;
        border: none;
        background: none;
        text-decoration:underline;
    }
</style>

<div class="person-info">
    <table>
        <tbody>
        <tr><td><img src="<?php print $variables['img_url'] ?>" width="250"></td></tr>
        </tbody>
    </table>
</div>
<div class="person-info">
    <table>
        <tbody>
        <tr><th class="person-info-heading">Project Information</th></tr>
        <tr><td class="person-info-label">Title:</td><td><?php print $variables['project']['title'] ?></td></tr>
        <tr><td class="person-info-label">Organization:</td><td><?php print $variables['project']['organization'] ?></td></tr>
        <tr><td class="person-info-label">City:</td><td><?php print $variables['project']['address']['city'] ?></td></tr>
        <tr><td class="person-info-label">Street:</td><td><?php print $variables['project']['address']['street'] ?></td></tr>
        <tr><td class="person-info-label">Country:</td><td><?php print $variables['project']['address']['country'] ?></td></tr>
        <tr><td class="person-info-label">Postal Code:</td><td><?php print $variables['project']['address']['postcode'] ?></td></tr>
        <tr><td class="person-info-label">Email Address:</td><td><?php print $variables['project']['email'] ?></td></tr>
        <tr><td class="person-info-label">Phone Number:</td><td><?php print $variables['project']['phone'] ?></td></tr>
        <tr><td class="person-info-label">Start Date:</td><td><?php print $variables['project']['startdate'] ?></td></tr>
        <tr><td class="person-info-label">End Date:</td><td><?php print $variables['project']['enddate'] ?></td></tr>
        </tbody>
    </table>
</div>
