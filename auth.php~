<?php
# whatever your timezone is:
date_default_timezone_set("Australia/Brisbane");

// THIS IS PART OF THE ARDUINO SWIPE CARD SECURITY SYSTEM WRITTEN BY BUZZ FEB 2011

$today = getdate();

// generate date/time  and key data in convenient format for log
$q = "";
$m = $today[year]; $m .= "-"; $m .= $today[month]; $m .= "-"; $m .= $today[mday];
$q .= $m; $q .= "  ";
$n = $today[hours]; $n .= "-"; $n .= $today[minutes]; $n .= "-"; $n .= $today[seconds];
$q .= $n; $q .= "  " ;
$q .= $_GET['q'];
$q .= "\n" ;

# log the datetime and the key to the event log:
# you may want to put this file somewhere else, like /var/log, to keep it outside the web-server root.
file_put_contents("door_lock_log.txt",$q,FILE_APPEND);

# if you have something else you want to externally trigger every time a door is opened, do it here:
#eg:  getting a photo from a webcam? 
# $i = file_get_contents("http://192.168.xx.xx/-wvhttp-01-/GetOneShot");
# file_put_contents("/home/space/public_html/door/$m-$n.jpg",$i,FILE_APPEND);


# next check the access control list, and see if its permitted or not? 

// pull the latest JSON request from the disk
# you may want to put this file somewhere else, like /var/log, to keep it outside the web-server root.
$users = json_decode(file_get_contents('door_json.txt'));

foreach ( $users as $user ) {
        //$user[0] = key
        //$user[1] = name;
        $keycode = ltrim(rtrim($user[0]));
        $name = ltrim(rtrim($user[1]));
	if ( $_GET['q'] == $keycode ) { 
		echo "access:3\n"; // 3 means permit entry to the first two doors,  01 and 10 ... at least in our system
		exit;
	} 
}
// no key matched, then deny door access! 
echo "access:0\n"; // 0 means DENY all doors entry 

?>
