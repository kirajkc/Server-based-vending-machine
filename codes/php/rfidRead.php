<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "vending";
// REPLACE with Database user
$username = "root";
// REPLACE with Database user password
$password = "";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM `chart_rfid`" WHERE tagid = $tagid ;
$result=mysqli_query($conn,$sql);


if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
	   echo "@"; 
	 echo  $row["tagid"];
	  echo "@"; 
	 echo  $row["amount"];
  }
} else {
  echo "0 results";
}


$conn->close();
?> 
