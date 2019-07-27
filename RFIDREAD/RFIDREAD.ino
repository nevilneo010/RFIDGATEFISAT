 
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

int flag=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
 // Serial.println("Approximate your card to the reader...");
  //Serial.println();

}
void loop() 
{
while(Serial.available()>0){
  char c=(char)Serial.read();
  if(c=='A')
    flag=1;
  }
  if(flag==1){
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
mfrc522.uid.uidByte[i];
Serial.print("");
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));}
String st=(content.substring(1));
st.toUpperCase();
Serial.print(st);Serial.print("*");

  flag=0;
  }
} 
