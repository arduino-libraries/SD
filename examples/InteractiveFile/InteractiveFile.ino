/*
  SD card basic example
  This example shows how to create and delete an SD card file.

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

File myFile, root;
int ch;
String fname;

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

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  root = SD.open("/"); // create root reference.
  printDirectory(root, 0); // print directory and file list
  Serial.println("1.Create File"); //ask user to input choice
  Serial.println("2.Delete File");
  Serial.println("Enter your choice:");
  //wait for input
  waitip();
  ch = Serial.parseInt();//get choice input


  if (ch == 1)  //for creating file
  {
    Serial.println("Enter file name to create file:");//ask user for file name eg. test.txt
    waitip();
    fname = Serial.readString();
    fname.trim();

    if (SD.exists(fname)) { //if file already exists
      Serial.println(fname + " already exists!");

    } else { //if file not exists create one
      Serial.println(fname + " doesn't exist.");
      Serial.println("Creating file..");
      myFile = SD.open(fname, FILE_WRITE); // creating file
      myFile.close();
      if (SD.exists(fname))
      {
        Serial.println(fname + " created!!");

      } else
      {
        Serial.println("Error: " + fname + " not created");
      }
    }
  }
  else if (ch == 2) {  //for deleting file
    Serial.println("Enter file name to delete:");//ask user for file name
    waitip();
    fname = Serial.readString();
    fname.trim();
    if (SD.exists(fname)) { //if file already exists then delete it.

      SD.remove(fname); // deleting file.

      if (SD.exists(fname))
      {
        Serial.println("Error: " + fname + " not deleted!!");
      }
      else {
        Serial.println(" " + fname + " deleted!!");

      }
    }
    else   //if file not exists then show error message.
    {
      Serial.println("Error: " + fname + " not exists!!");
    }
  }
  else // if user enters wrong choice
  {
    Serial.println("Error:wrong choice!!");
  }
}

void loop() {
  // nothing happens after setup
}

void waitip()// wait for user input
{
  while (Serial.available() == 0)
  {}
}

void printDirectory(File dir, int numTabs) // prints directory list
{
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
