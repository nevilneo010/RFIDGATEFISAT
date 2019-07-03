<?php
$servername="localhost";
$username="root";
$password="1234567890";
$dbname="db1";
$api_key_value = "tPmAT5Ab3j7F9";
$api_key= $name = $value3 = "";
date_default_timezone_set("Asia/Kolkata");
echo '<pre>';
print_r($_POST);
echo '</pre>';
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $name= test_input($_POST["name"]);
        $IO = test_input($_POST["IO"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
       // $sql = "INSERT INTO tes1 VALUES ('" . $name . "', '" . $value3 . "')";
        $sql = "INSERT INTO rfid(RFID,Date1,IO) VALUES ('" . $name . "', '" .date("Y-m-d")." ".date("H:i:s") . "','".$IO."')";

        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
?>

</html>
