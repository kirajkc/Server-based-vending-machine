<?php
class rfid_card{
 public $link='';
 function __construct($tagid,$amount){
  $this->connect();
  $this->storeInDB($tagid,$amount);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'rfid') or die('Cannot select the DB');
 }
 
 function storeInDB($tagid,$amount){
  $query = "insert into rfid_card set tagid='".$tagid."', amount='".$amount."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['tagid'] != '' and  $_GET['amount'] != ''){
 $rfid_card=new rfid_card($_GET['tagid'],$_GET['amount']);
}


?>
