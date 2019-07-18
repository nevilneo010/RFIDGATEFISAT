<!DOCTYPE html>
<html>
<head><meta http-equiv="refresh" content="2"></head>
<body>
<link rel="stylesheet" type="text/css" href="style.css">
<div class="div">

<?php
$servername="localhost";
$username="root";
$password="1234567890";
$dbname="db1";
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT Name.Name,rfid.Date1,rfid.IO FROM `rfid` INNER JOIN name ON rfid.RFID=name.RFID WHERE id=(SELECT MAX(id) FROM rfid);";
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_Name = $row["Name"];
        $row_value3 = $row["Date1"]; 
        $io = $row["IO"]; 
        $text="";
        if($io=="IN"){
            echo ' 
                <h1> Welcome back ' .$row_Name . '</h1> 
                <h1> ' . substr($row_value3,11). '</h1>
                <p style="font-size: 100px;color:green;">IN</p>';

        }
        else{
            echo ' 
                <h1> See you soon ' .$text.$row_Name . '</h1> 
                <h1> ' . $row_value3 . '</h1> 
                <p style="font-size: 100px;color:RED;">OUT</p>;';

        }
    }
    $result->free(); 
}
$conn->close();
?> 
</div>
</table>
</body>
</html>