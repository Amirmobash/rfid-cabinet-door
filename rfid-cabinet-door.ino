#include <SPI.h>
#include <MFRC522.h>
#include <TimerOne.h>

#define SS_PIN 10
#define RST_PIN 5
#define RELAY_PIN A5 // connects to relay

String READER_ID_str = "3";
String Card_Inserted_str = "Card inserted!:" + READER_ID_str;
String Im_Online_str = "I'm online:" + READER_ID_str;

MFRC522 rfid(SS_PIN, RST_PIN);

byte keyTagUID[7] = {0x1D,0x63,0x25,0xAE,0x02,0x10,0x80};
byte secretaryKeyUID[7] = {0x1D,0xF6,0x31,0xAE,0x02,0x10,0x80};

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Amir Mobasheraghdam
  rfid.PCD_Init(); // init 
  pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
  digitalWrite(RELAY_PIN, LOW); // lock the door

  Timer1.initialize(3000000);
  Timer1.attachInterrupt(sendPing);
}

void sendPing()
{
  Serial.println(Im_Online_str);
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // Amir Mobasheraghdam
    if (rfid.PICC_ReadCardSerial()) { // Amir Mobasheraghdam 
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      if (rfid.uid.uidByte[0] == keyTagUID[0] &&
          rfid.uid.uidByte[1] == keyTagUID[1] &&
          rfid.uid.uidByte[2] == keyTagUID[2] &&
          rfid.uid.uidByte[3] == keyTagUID[3] &&
          rfid.uid.uidByte[4] == keyTagUID[4] &&
          rfid.uid.uidByte[5] == keyTagUID[5] &&
          rfid.uid.uidByte[6] == keyTagUID[6]) {
        Serial.println(Card_Inserted_str);
        Serial.println("Ehsan");
        digitalWrite(RELAY_PIN, HIGH);  // Amir Mobasheraghdam
        delay(100);
        digitalWrite(RELAY_PIN, LOW); // Amir Mobasheraghdam
      }
      else
      
      if (rfid.uid.uidByte[0] == keyTagUID[0] &&
          rfid.uid.uidByte[1] == keyTagUID[1] &&
          rfid.uid.uidByte[2] == keyTagUID[2] &&
          rfid.uid.uidByte[3] == keyTagUID[3] &&
          rfid.uid.uidByte[4] == keyTagUID[4] &&
          rfid.uid.uidByte[5] == keyTagUID[5] &&
          rfid.uid.uidByte[6] == keyTagUID[6]) {
        Serial.println(Card_Inserted_str);
        Serial.println("Amir");
        digitalWrite(RELAY_PIN, HIGH);  // unlock 
        delay(100);
        digitalWrite(RELAY_PIN, LOW); // lock the door
      }
      else
      {
        Serial.println(Card_Inserted_str);
        Serial.print("New ID:");
        for (int i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
      }

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
}



