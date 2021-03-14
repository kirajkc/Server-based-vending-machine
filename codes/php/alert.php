<?php
class chart_alert{
 public $link='';
 function __construct($value){
  $this->connect();
  $this->storeInDB($value);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'vending') or die('Cannot select the DB');
 }
 
 function storeInDB($value){
  $query = "UPDATE  chart_alert set value='".$value."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['value'] != ''){
 $chart_alert=new chart_alert($_GET['value']);
}


?>
