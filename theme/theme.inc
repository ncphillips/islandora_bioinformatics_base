<?php

/**
  * @file
  * Theme file for Base solution pack. Includes preprocess functions.
  */

function islandora_bioinformatics_person_preprocess_islandora_bioinformatics_person(array &$variables) {

  echo "<pre>";
    print_r("is this even called?");
  echo "</pre>";
  $islandora_object = $variables['islandora_object'];
  // Thumbnail.
  if (isset($islandora_object['IMG'])) {
    $thumbnail_size_url = url("islandora/object/{$islandora_object->id}/datastream/IMG/view");
    $params = array(
      'title' => $islandora_object->label,
      'path' => $thumbnail_size_url,
    );
    $variables['islandora_thumbnail_img'] = theme('image', $params);
  }

  // get some of the MADS data
  if (isset($islandora_object['MADS'])){

    // namespace needs to be set for children() calls
    $ns = "http://www.loc.gov/mads/v2";

    // get all of the MADS XML 
    $mads_data = $islandora_object['MADS']->content;

    // turn this XML into an object
    $obj = new SimpleXMLElement($mads_data);

    // this is not being done the ideal way. There really should only be one child
    // so essentially it should only loop once
    
    foreach ($obj->children($ns) as $authority){
        $authorityTest = parse_authority($authority);
    }

    foreach ($obj->children($ns) as $affiliation){
        $affiliationTest = parse_authority($affiliation);
    }
    /*foreach ($obj->children($ns) as $dataset){
      $authority = parse_authority($authority);
      $identifier = parse_identifier($identifier);
      $affiliation = parse_affiliation($affiliation);
      $url = parse_url($url);
      $note = prase_note($note);
      
    }*/

    $variables['authority'] = $authorityTest;
    //$variables['identifier'] = $identifier;
    $variables['affiliation'] = $affiliationTest;
    //$variables['url'] = $url;
    //$variables['note'] = $note;
  }
}

function parse_authority($auth_container){
    $authority = array();
    foreach($auth_container as $rank){
     foreach($rank->name->namePart->attributes() as $attribute => $value){
        $given = "given";
	if($attribute==$given){
           $givenName = (String) $value;
        }
	$family = "family";
        if($attribute==$family){
    	   $familyName = $value;
        }
	$date = "date";
	if($attribute == $date){
	   $dateValue = $value;
  	}
      }
      $title="title";
      $titleValue = (string) $rank->titleInfo->title;
      if($givenName){
	$authority[$given] = $givenName;
      }
      if($familyName){
        $authority[$family] = $familyName;
      }
      if($dateValue){
        $authority[$date] = $dateValue;
      }
      if($titleValue){
        $authority[$title] = $titleValue;
      }
    }
    return $authority; 
}

function parse_identifier($iden_container){

}

function parse_affiliation($affi_container){
    $affiliation = array();
    foreach($affi_container as $rank){
        $phone = "phone";
	$phoneNum = (string) $rank->phone;
	$email = "email";
	$emailAdd = (string) $rank->email;
	$organization = "organization";	
	$organizationName = (string) $rank->organization;
	$position = "position";
	$positionName = (string) $rank->position;
	$address = "address";
	$addressName = (string) $rank->address;
    }
    if($phoneNum){
	$alliliation[$phone] = $phoneNum;
    }
    if($emailAdd){
        $alliliation[$email] = $emailAdd;
    }
    if($organizationName){
        $alliliation[$organization] = $organizationName;
    }
    if($positionName){
        $alliliation[$position] = $positionNmae;
    }
    if($addressName){
        $alliliation[$address] = $addressName;
    }
    return $affiliation;
}
