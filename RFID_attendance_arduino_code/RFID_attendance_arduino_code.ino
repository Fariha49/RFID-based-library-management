#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define buzz            8
#define led             7
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String CardID = "";

void setup() {
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(buzz, LOW); // Ensure the buzzer is off at the beginning
  digitalWrite(led, LOW);  // Ensure the LED is off at the beginning
  Serial.begin(9600);   // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
}

void loop() {
  digitalWrite(led, LOW);

  while (Serial.available() == 0) {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    for (byte i = 0; i < mfrc522.uid.size; i++) {
      CardID += mfrc522.uid.uidByte[i];
    }

    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(buzz, HIGH);
    delay(50);
    digitalWrite(buzz, LOW);
    Serial.println(CardID);
    delay(500);
    CardID = "";
  }

  String command = Serial.readString();
  if (command == "m") {
    digitalWrite(buzz, HIGH);
    digitalWrite(led, HIGH); // Turn on the LED along with the buzzer
    delay(1000);
    digitalWrite(buzz, LOW);
    digitalWrite(led, LOW); // Turn off the LED after the delay
  }
}
