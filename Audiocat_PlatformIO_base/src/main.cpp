#include <Arduino.h>
#include <STM32SD.h>

Sd2Card card;
SdFatFs fatFs;

// set RX and TX pins
// HardwareSerial Serial4(PA1, PA0);
File dataFile;

void setup() {
  // put your setup code here, to run once:
  // Serial4.begin(9600);
  Serial.setRx(PA10);
  Serial.setTx(PA9);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Hello there!");

  // Serial.print("Initializing SD card...");
  // SD.setDx(PC8, PC9, PC10, PC11);
  // SD.setCMD(PD2);
  // SD.setCK(PC12); // using PinName
  // // see if the card is present and can be initialized:
  // while (!SD.begin())
  // {
  //   Serial.print("looking for card!");
  //   delay(10);
  // }
  // delay(100);
  // Serial.println("card initialized.");

  // // open the file. note that only one file can be open at a time,
  // // so you have to close this one before opening another.
  // dataFile = SD.open("datalog.txt", FILE_WRITE);
  // // if the file is available, seek to last position
  // if (dataFile) {
  //   dataFile.seek(dataFile.size());
  // }
  // // if the file isn't open, pop up an error:
  // else {
  //   Serial.println("error opening datalog.txt");
  // }


  pinMode(PC7, OUTPUT);
  // pinMode(PG4, OUTPUT);

  card.setDx(PC8, SD_DETECT_NONE, SD_DETECT_NONE, SD_DETECT_NONE);
  card.setCMD(PD2);
  card.setCK(PC12);
  
  while(!card.init()) {
    // Serial4.println("initialization failed. Is a card inserted?");
    delay(10);
  }

  // while (!fatFs.init()) {
  //   Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
  //   delay(10);
  // }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World!");
  digitalWrite(PC7, HIGH); // sets the digital pin 13 on
  // digitalWrite(PG4, HIGH);
  delay(1000);
  // String dataString = "";
  // int sensor = analogRead(A1);
  // dataString += String(sensor);            // waits for a second
  // Serial4.println(dataString);
  digitalWrite(PC7, LOW);  // sets the digital pin 13 off
  // digitalWrite(PG4, LOW);
  delay(1000);            // waits for a second
}
