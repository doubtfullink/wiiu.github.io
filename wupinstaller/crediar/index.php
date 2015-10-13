<?php
	$ug = $_SERVER['HTTP_USER_AGENT'];
	if( !strpos( $ug, "Nintendo WiiU" ) )
		die("Wrong Version, only 5.3.2 is supported.");
	if( !strpos( $ug, "NintendoBrowser" ) )
		die("Wrong Version, only 5.3.2 is supported.");
	if( !strpos( $ug, "3.0.3.12.15" ) )
		die("Wrong Version, only 5.3.2 is supported.");
	echo "<script type=\"text/javascript\">window.location = \"payload.php\";</script>";
?>
