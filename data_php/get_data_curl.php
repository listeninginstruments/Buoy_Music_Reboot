<?php

//$ch = curl_init("-X POST -F 'siteID=721' ");



function getBuoyData($lakename, $siteid){
	$ch = curl_init();

	curl_setopt($ch, CURLOPT_URL,"https://v2.wqdatalive.com/public/470/sidebar");
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS, "siteID=$siteid");

	curl_setopt($ch, CURLOPT_FILE, $fp);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

	//curl_exec($ch);

	$curr_results = curl_exec($ch);

	if($curr_data === false)
	{
	    echo 'Curl error: ' . curl_error($ch);
	}
	else
	{
	    echo '<br><br>Operation completed without any errors<br><br>';
	}

	curl_close($ch);


	$json = json_decode($curr_results);
	$curr_data = $json->data;

	foreach ($curr_data as $key => $value) {
	   //print "$key\n";
		/*
		there should only ever be one but 
		this is going to change and contain 
		the date / time info 
		*/
		$tempname = $key;
	}

	$explode_time = explode(" ", $tempname);
	$temp_date = strtotime($explode_time[0]);
	$filename_date = date("ymd", $temp_date) . "-" . $explode_time[1];//str_replace(":", "_", $explode_time[1]);

	//print($tempname . " : " . $filename_date);
	//print_r($curr_data);

	$newfile = "/data-2020-$lakename/" . $filename_date . ".json";
	$fp = fopen(dirname(__FILE__) . $newfile , "w");

	if (fwrite($fp, json_encode($curr_data)) === FALSE) {
	    echo "Cannot write to file ($filename)";
	    
	} else {
		echo "<h1>SUCCESS!</h1>Created $newfile ";
	}

	fclose($fp);


}

getBuoyData("WestOkoboji", 721);
getBuoyData("SpiritLake", 2118);




?>