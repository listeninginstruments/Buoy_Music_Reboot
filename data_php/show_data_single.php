
<?php

	$dir = dirname(__FILE__) . "/data";
	$files = scandir($dir);

	
	if(  $_GET["num"] == null){
		$reading = 2;
	} else {
		$reading = $_GET["num"];
	}
	
	$content_temp = file_get_contents($dir . "/" . $files[$reading]);
	//$json_temp = json_decode($content_temp, true);
	print_r($content_temp);



	//print_r($files[4]);

	//$test = array();

	//array_push($test, ["name"=>explode(".", $files[4])[0], "data"=>"datadata"]);
	//array_push($test, ["name"=>explode(".", $files[5])[0], "data"=>"datadata"]);
	//array_push($test, ["name"=>explode(".", $files[6])[0], "data"=>"datadata"]);


	//print_r($test);


	/*
	$main = array();

	//skip first two . and ..
	for($i=2; $i<100; $i++){
		$content_temp = file_get_contents($dir . "/" . $files[$i]);
		$json_temp = json_decode($content_temp, true);
		array_push($main, ["name"=>explode(".", $files[$i])[0], "data"=>$json_temp]);
	}
	*/



	//print_r($main);

	/*
	$json_remade = json_encode($main);

	$json_loop_check = json_decode($json_remade);
	
	print_r($json_remade);
	*/


	
	/*
	$file_name = explode(".", $files[4])[0];
	print($file_name);

	$content = file_get_contents($dir . "/" . $files[4]);
	$json_1 = json_decode($content, true);

	print_r($json_1);

	print(" /// /// /// /// /// /// /// /// /// /// /// /// /// ///");
	$json_remade = json_encode($json_1);
	print_r($json_remade);
	*/
	

?>
