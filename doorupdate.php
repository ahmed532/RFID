<?php
// this script can be used by the door system for google docs integration  - see buzz.    

// it's called by the google docs spreadsheet whenever the file is exitied, and it should recieve a JSON encoded dump of the first two columns of the spreadsheet in the $_POST['payload'] variable.

# get data and secret
$postdata = stripslashes($_POST['json']); # new way
$secret = $_POST['secret'];

# check secret
if ( $secret != 'somethingsecret' ) {  print "access denied\n"; exit; }

#check we are over https
if ( $_SERVER['HTTPS'] == '' ) { print "access denied\n"; exit ; } 

# uncomment to test google spreadsheet code
//print "$postdata\n";

# cache the latest JSON request onto the disk, for later use by the door access control system ( see logger.php )
file_put_contents('door_json.txt',$postdata);

echo "Space server says: thanks for the update!\n";

# decode users, and itterate over the list, for fun., building a csv file for possible future use
$users = json_decode($postdata);

$csv = '';
$a = 0;
foreach ( $users as $user ) { 
	//$user[0] = key 
	//$user[1] = name;
	$csv .= ltrim(rtrim($user[0]));
	$csv .= ",";
	$csv .= ltrim(rtrim($user[1]));
	$csv .= "\n";

}
# if you need it in some other format, do that here, eg csv? 
#file_put_contents('door_csv.txt',$csv);

?>
