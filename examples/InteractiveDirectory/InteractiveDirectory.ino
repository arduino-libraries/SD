/*
  SD card basic example
  This example shows how to create and delete an SD card directory.

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
String dir;
int ch;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while (1);
  }

  root = SD.open("/"); // create root reference.
  Serial.println("initialization done.");

  printDirectory(root, 0); // print directory and file list
  Serial.println("1.Create Directory"); //ask user to input choice
  Serial.println("2.Delete Directory");
  Serial.println("Enter your choice:");
  //wait for input
  waitip();
  ch = Serial.parseInt();//get choice input

  if (ch == 1)  //for creating directory
  {
    Serial.println("Enter directory name to create:");//ask user for directory name
    waitip();
    dir = Serial.readString();
    dir.trim();

    if (SD.exists(dir)) { //if directory already exists
      Serial.println(dir + " already exists!");

    } else { //if directory not exists create one
      Serial.println(dir + " doesn't exist.");
      Serial.println("Creating directory..");
      SD.mkdir(dir);  // creating directory
       
      if (SD.exists(dir))
      {
        Serial.println(dir + " created!!");

      } else
      {
        Serial.println("Error: " + dir + " not created");
      }
    }
  }
  else if (ch == 2) {  //for deleting directory
    Serial.println("Enter directory name to delete:");//ask user for directory name
    waitip();
    dir = Serial.readString();
    dir.trim();
    if (SD.exists(dir)) { //if directory already exists then delete it.
      SD.rmdir(dir);    //deleting directory.

      if (SD.exists(dir))
      {
        Serial.println("Error: " + dir + " not deleted!!");
      }
      else {
        Serial.println(" " + dir + " deleted!!");

      }
    }
    else   //if directory not exists then show error message.
    {
      Serial.println("Error: " + dir + " not exists!!");
    }
  }
  else // if user enters wrong choice
  {
    Serial.println("Error:wrong choice!!");
  }
}

void loop() {
  // nothing happens after setup finishes.
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
