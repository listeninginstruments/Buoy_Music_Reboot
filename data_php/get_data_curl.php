<?php


//$ch = curl_init("-X POST -F 'siteID=721' ");






$ch = curl_init();

curl_setopt($ch, CURLOPT_URL,"https://v2.wqdatalive.com/public/470/sidebar");
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS,
            "siteID=721");

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
    echo 'Operation completed without any errors<br><br>';
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





$fp = fopen(dirname(__FILE__) . "/data/" . $filename_date . ".json", "w");

if (fwrite($fp, json_encode($curr_data)) === FALSE) {
    echo "Cannot write to file ($filename)";
    
} else {
	echo "<h1>SUCCESS!</h1>";
}





fclose($fp);




?>