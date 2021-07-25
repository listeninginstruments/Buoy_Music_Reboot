<?php


//Site IDs
//"WestOkoboji", 721
//"SpiritLake", 2118


function getBuoyData($siteid){

	$alerts = false;

	$ch = curl_init();

	curl_setopt($ch, CURLOPT_URL,"https://wqdatalive.com/public/470/sidebar");
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS, "siteID=$siteid");

	curl_setopt($ch, CURLOPT_FILE, $fp);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

	//curl_exec($ch);

	$curr_results = curl_exec($ch);

	if($curr_data === false)
	{
	    if($alerts) { echo 'Curl error: ' . curl_error($ch); }
	}
	else
	{
	    if($alerts) { echo '<br><br>Curl operation completed without any errors<br><br>'; }
	    //if($alerts) { print_r($curr_results); }
	}

	curl_close($ch);


	$json = json_decode($curr_results);
	$curr_data = $json->data;

	//print_r($curr_data);

	//print_r($curr_data->data);

	//because of the named object being date and time driven
	foreach($json->data as $mydata){
    	$temp_data = $mydata; 
    }    


    // Ardunio seems limited to about 9 values for parsing json.
    //Probably fewer once using eathernet code.


    $reform_json = array();
    for($i=0; $i < count($temp_data); $i++){
    	//echo $temp_data[$i]->name;
    	//array_push($reform_json, array("name" => $temp_data[$i]->name, "val"=>$temp_data[$i]->value) );
    	//array_push($reform_json, array( strval($temp_data[$i]->name) => $temp_data[$i]->value);
    	$name_clean1 = str_replace(". ", " ", $temp_data[$i]->name);
    	$name_clean = str_replace(" ", "_", $name_clean1);
    	$reform_json[$name_clean] = $temp_data[$i]->value;
    }

    //print_r($reform_json);

    $arduino_cleaned = array(
    	//"temp_air" => $reform_json["Air_Temperature"],
    	"tt"=> $reform_json["Temperature_at_surface"],
    	//"temp_mid"=> $reform_json["Temperature_at_36_ft"],
    	"tb"=> $reform_json["Temperature_at_82_ft"],
    	"dost" => $reform_json["DOSat_at_10_ft"],
    	//"dos_mid" => $reform_json["DOSat_at_36_ft"],
    	"dosb" => $reform_json["DOSat_at_82_ft"]
    	);
    //echo "[".$reform_json["Air_Temperature"]."]";
    echo "[";
    echo json_encode($arduino_cleaned);
    echo "]";

    //echo json_encode($reform_json);

    //print_r($ouput);

    //print($reform_json["Wind_Speed"]);

	//$temp_arr = array("data" => $temp_data);
    //$output = json_encode($temp_arr);


	//print_r($output);

    /*
    if($alerts) { print_r($temp_data); }

    $return_val = 0;
    for($i=0; $i < count($temp_data); $i++){
    	//echo $temp_data[$i]->name . "\n";
    	if($temp_data[$i]->name == "Temperature at surface"){
    		$return_val = $temp_data[$i]->value;
    	}
    }
	
	echo $return_val;
	*/


}

if($_GET["id"]){
	getBuoyData($_GET["id"]);
} else {
	getBuoyData(721); //default to West O
}

//getBuoyData("WestOkoboji", 721);
//getBuoyData("SpiritLake", 2118);




?>