<?php
class chart_sold1{
 public $link='';
 function __construct($tagid,$item,$quantity,$price){
  $this->connect();
  $this->storeInDB($tagid,$item,$quantity,$price);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'vending') or die('Cannot select the DB');
 }
 
 function storeInDB($tagid,$item,$quantity,$price){
  $query = "insert into chart_sold1 set tagid='".$tagid."', item='".$item."',quantity='".$quantity."', price='".$price."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['tagid'] != '' and  $_GET['item'] != '' and  $_GET['quantity'] != '' and  $_GET['price'] != ''){
 $chart_sold1=new chart_sold1($_GET['tagid'],$_GET['item'],$_GET['quantity'],$_GET['price']);
}


?>
