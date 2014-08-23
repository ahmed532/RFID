<?php
if (!$link = mysql_connect('localhost', 'root', 'PassWD51')) {
    echo 'Could not connect to mysql';
    exit;
}
if (!mysql_select_db('FablabAuto', $link)) {
    echo 'Could not select database';
    exit;
}

$sql    = 'SELECT m_id FROM member WHERE RFID_tag = "'.(string)$_GET['q'].'"';
$result = mysql_query($sql, $link);

if (!$result) {
    echo "DB Error, could not query the database\n";
    echo 'MySQL Error: ' . mysql_error();
    exit;
}
if(!mysql_num_rows($result)) {
	echo "C\n";
	$sql2    = 'INSERT INTO logins(m_logged, login_time, login_cost) VALUES ("2", now(), "100")';
	$result2 = mysql_query($sql2, $link);

	if (!$result2) {
    	echo "DB Error, could not query the database\n";
    	echo 'MySQL Error: ' . mysql_error();
    	exit;
	}
}
while ($row = mysql_fetch_assoc($result)) {
	$sql2    = 'INSERT INTO logins(m_logged, login_time, login_cost) VALUES ("'.(string)$row['m_id'].'", now(), "100")';
	$result2 = mysql_query($sql2, $link);

	if (!$result2) {
    	echo "DB Error, could not query the database\n";
    	echo 'MySQL Error: ' . mysql_error();
    	exit;
	}
    echo "O\nB";
}

mysql_free_result($result);
?>
