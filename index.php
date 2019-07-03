<!DOCTYPE html>
<html><body>
<?php
$servername="localhost";
$username="root";
$password="1234567890";
$dbname="db1";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM rfid";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>Name</td> 
        <td>Value 3</td> 
        <td>In/out</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_Name = $row["RFID"];
        $row_value3 = $row["Date1"]; 
        $io = $row["IO"]; 
      
        echo '<tr> 
                <td>' . $row_Name . '</td> 
                <td>' . $row_value3 . '</td> 
                <td>' . $io . '</td> 

              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>