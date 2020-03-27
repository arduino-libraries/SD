/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created by Abhijeet Kadam

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

String fname, fileData;
int ch;
File root, myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  root = SD.open("/"); // create root reference.
  printDirectory(root, 0); // print directory and file list

  Serial.println("1.Read File"); //ask user to input choice
  Serial.println("2.Write File");
  Serial.println("Enter your choice:");
  //wait for input
  waitip();
  ch = Serial.parseInt();//get choice input

  //for reading the file
  if (ch == 1) {
    Serial.println("Enter file name to read file data:");//ask user for file name eg. test.txt
    waitip();
    fname = Serial.readString();
    fname.trim();

    if (SD.exists(fname)) {
      //if file already exists

      myFile = SD.open(fname);
      if (myFile) {
        Serial.println(" " + fname);
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      }
    } else {
      //if file not exists show the message
      Serial.println(fname + " doesn't exist.");
    }
  } else if (ch == 2) {
    //writing to the file
    Serial.println("Enter file name :");//ask user for file name
    waitip();
    fname = Serial.readString();
    fname.trim();

    myFile = SD.open(fname, FILE_WRITE);//open the file if file not exists create one

    Serial.println("Enter data to store inside the file :");
    waitip();
    fileData = Serial.readString();
    fileData.trim();
    // if the file opened okay, write to it:
    if (myFile) {
      Serial.print("Writing to " + fname + "...");
      myFile.println(fileData);
      // close the file:
      myFile.close();
      Serial.println("done.");
    }  else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
  } else {
    // if user enters wrong choice
    Serial.println("Error:wrong choice!!");
  }
}

void loop() {
  // nothing happens after setup
}

// wait for user input
void waitip() {
  while (Serial.available() == 0)
  {}
}

// prints directory list
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
