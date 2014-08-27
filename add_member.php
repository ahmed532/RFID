<?php
if (!$link = mysql_connect('localhost', 'root', 'Moody_22')) {
    echo 'Could not connect to mysql';
    exit;
}
if (!mysql_select_db('FablabAuto', $link)) {
    echo 'Could not select database';
    exit;
}

$sql    = 'INSERT INTO member (name, RFID_tag, mobile, job)
           VALUES ("'.(string)$_GET['mem_name'].'", "'.(string)$_GET['mem_tag'].
            '", "'.(string)$_GET['mem_mob'].'", "'.(string)$_GET['mem_job'].'")';
$result = mysql_query($sql, $link);

if (!$result) {
    echo "DB Error, could not query the database\n";
    echo 'MySQL Error: ' . mysql_error();
    exit;
}
echo "Done";

mysql_free_result($result);
?>
