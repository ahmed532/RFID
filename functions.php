<?php // functions.php
  $dbhost = 'localhost'; // Unlikely to require changing
  $dbname = 'FablabAuto'; // Modify these...
  $dbuser = 'root'; // ...variables according
  $dbpass = 'PassWD51'; // ...to your installation
  $appname = "FablabAuto"; // ...and preference
  mysql_connect($dbhost, $dbuser, $dbpass) or die(mysql_error());
  mysql_select_db($dbname) or die(mysql_error());
  function createTable($name, $query){
    queryMysql("CREATE TABLE IF NOT EXISTS $name($query)");
    echo "Table '$name' created or already exists.<br />";
  }
  function queryMysql($query){
    $result = mysql_query($query) or die(mysql_error());
    return $result;
  }
  function destroySession(){
    $_SESSION=array();
    if (session_id() != "" || isset($_COOKIE[session_name()]))
      setcookie(session_name(), '', time()-2592000, '/');
    session_destroy();
  }
  function sanitizeString($var)
  {
    $var = strip_tags($var);
    $var = htmlentities($var);
    $var = stripslashes($var);
    return mysql_real_escape_string($var);
  }
  function showProfile($user)
  {
    if (file_exists("$user.jpg"))
      echo "<img src='$user.jpg' align='left' />";
    $result = queryMysql("SELECT * FROM profiles WHERE user='$user'");
    if (mysql_num_rows($result)){
      $row = mysql_fetch_row($result);
      echo stripslashes($row[1]) . "<br clear=left /><br/>";
    }
  }
?>
