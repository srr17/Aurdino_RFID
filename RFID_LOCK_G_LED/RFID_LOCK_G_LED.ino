#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10 //MOSI of RFID 
#define RST_PIN 9 //RST of RFID 
#define LED_G 4 //define green LED pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
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
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "AB 5C 5D 13" ||content.substring(1) == "EA 67 6A 80") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Card Accepted : ");
    Serial.println("Welcome Back ! ");
    Serial.println("SOHAN RANE  ");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    delay(300);
    digitalWrite(LED_G, LOW);
    delay(300);
    digitalWrite(LED_G, HIGH);
    delay(300);
    digitalWrite(LED_G, HIGH);
    delay(300);
    digitalWrite(LED_G, LOW);
    delay(300);
    myServo.write(180);
    delay(3000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
 else   {
    Serial.println(" Access denied : ");
    delay(1000);
  }
} 