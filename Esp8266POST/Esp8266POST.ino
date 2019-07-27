/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */
//rfied enroll repeat,table rfid remove,remove repeated rfid,more resposive
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

//RFID SETTINGS
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          4        // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN); 
String user;

//WIFI SETTINGS
const char *ssid = "GATESECURITY";  //ENTER YOUR WIFI SETTINGS
const char *password = "sec@F!s@t";//"sec@F!s@t";
IPAddress staticIP(172, 16, 31, 41); //ESP static ip
IPAddress gateway(172, 16, 1, 254);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 0, 0);  //Subnet mask
IPAddress dns(172, 16, 10, 10);  //DNS
const char* deviceName = "Test@RFID";

const char *host = "172.16.26.15";   //Server IP

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);
  pinMode(0, INPUT);
  pinMode(2, INPUT);
  pinMode(15, OUTPUT);

  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  WiFi.begin(ssid, password);
  //WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration
  delay(1000);
  WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway, dns);
  Serial.println("");
   delay(1000);

  
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init(); 
  WiFi.config(staticIP, subnet, gateway, dns);delay(1000);
  Serial.println(WiFi.localIP()); 
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
 // Serial.println(digitalRead(0));Serial.println(digitalRead(2));
  digitalWrite(15,LOW);
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  HTTPClient http; 
   String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    // Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  }
  user=content.substring(1);
  user.toUpperCase();
  Serial.println(user);
  String io;
  int flag=0;
  digitalWrite(15,HIGH);
  delay(600);
  digitalWrite(15,LOW);
  while(flag==0){
    if(digitalRead(0)==LOW){
       io = "OUT";
       flag=1;
       digitalWrite(15,HIGH);
       delay(200);
       digitalWrite(15,LOW);
      }
    else if(digitalRead(2)==LOW){
      io = "IN";
      flag=1;
       digitalWrite(15,HIGH);
       delay(200);
       digitalWrite(15,LOW);
      }
      delay(10);
    }

  //Post Data
String  postData = "api_key=tPmAT5Ab3j7F9&name="+user+"&IO="+io;
  http.begin("http://172.16.26.15/submit.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  http.end();  //Close connection
  delay(100);  //Post Data at every 5 seconds
}
//=======================================================================
