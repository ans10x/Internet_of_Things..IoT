<?php 

$mysqli= new mysqli('localhost','ans10x','Aa123456789','smart_method');

if($mysqli->connect_error){
    die('Connect error : '.$mysqli->connect_error);
}


if (isset($_POST['backword'])){
	echo '<p style="color:Blue;text-align:center;">B</p>';
	mysqli_query($mysqli,"INSERT INTO`task2` SET `BW` = 'B'");
}


if (isset($_POST['forword'])){
	echo  '<p style="color:Blue;text-align:center;">F</p>';
	mysqli_query($mysqli,"INSERT INTO`task2` SET `FW` = 'F'");
}

if (isset($_POST['right'])){
	echo  '<p style="color:Blue;text-align:center;">R</p>';
	mysqli_query($mysqli,"INSERT INTO`task2` SET `Ri` = 'R'");
}

if (isset($_POST['left'])){
	echo  '<p style="color:Blue;text-align:center;">L</p>';
	mysqli_query($mysqli,"INSERT INTO`task2` SET `Le` = 'L'");
}
if (isset($_POST['stop'])){
	echo  '<p style="color:Blue;text-align:center;">S</p>';
	mysqli_query($mysqli,"INSERT INTO`task2` SET `stop` = 'S'");
}



?>


<!DOCTYPE HTML>

<html>
<head></head>

<body style= "background-color:silver";>
<center>
<form>
    <br> <br> <br> <br> <br>
    <br> <br> <br> <br> <br>
    <br> <br> <br> <br> <br>
    
  <input type="button" value="Go back!" onclick="history.back()">
</form>
</center>
</body>



</html>
