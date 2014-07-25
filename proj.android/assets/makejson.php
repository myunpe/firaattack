<?php
	$a = array(
		"scene" => array(
		"name" => "data",
		"enemy" => 5
	));
	$content = json_encode($a);
	print_r($content);
	print("\n");
	file_put_contents("data.json", $content);
?>