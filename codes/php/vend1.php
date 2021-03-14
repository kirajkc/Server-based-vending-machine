<?php
class chart_vend1{
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
  $query = "UPDATE  chart_vend1 set tagid='".$tagid."', item='".$item."',quantity='".$quantity."', price='".$price."' where tagid='".$tagid."' ";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['tagid'] != '' and  $_GET['item'] != '' and  $_GET['quantity'] != '' and  $_GET['price'] != ''){
 $chart_vend1=new chart_vend1($_GET['tagid'],$_GET['item'],$_GET['quantity'],$_GET['price']);
}


?>
