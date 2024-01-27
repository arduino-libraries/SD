# SD library

The SD library allows for reading from and writing to SD cards, e.g. on the Arduino Ethernet Shield. It is built on [sdfatlib](http://code.google.com/p/sdfatlib/) by William Greiman. The library supports FAT16 and FAT32 file systems on standard SD cards and SDHC cards. It uses short 8.3 names for files. The file names passed to the SD library functions can include paths separated by forward-slashes, /, e.g. "directory/filename.txt". Because the working directory is always the root of the SD card, a name refers to the same file whether or not it includes a leading slash (e.g. "/file.txt" is equivalent to "file.txt"). As of version 1.0, the library supports opening multiple files.

The communication between the microcontroller and the SD card uses [SPI](https://www.arduino.cc/en/Reference/SPI), which takes place on digital pins 11, 12, and 13 (on most Arduino boards) or 50, 51, and 52 (Arduino Mega). Additionally, another pin must be used to select the SD card. This can be the hardware SS pin - pin 10 (on most Arduino boards) or pin 53 (on the Mega) - or another pin specified in the call to SD.begin(). Note that even if you don't use the hardware SS pin, it must be left as an output or the SD library won't work.

To use this library:

```
#include <SPI.h>
#include <SD.h>
```

[Notes on using the Library and various shields](https://www.arduino.cc/en/Reference/SDCardNotes).

## Examples

* [Card Info](https://www.arduino.cc/en/Tutorial/LibraryExamples/CardInfo): Get info about your SD card.
* [Datalogger](https://www.arduino.cc/en/Tutorial/LibraryExamples/Datalogger): Log data from three analog sensors to an SD card.
* [Dump File](https://www.arduino.cc/en/Tutorial/LibraryExamples/DumpFile): Read a file from the SD card.
* [Files](https://www.arduino.cc/en/Tutorial/LibraryExamples/Files): Create and destroy an SD card file.
* [List Files](https://www.arduino.cc/en/Tutorial/LibraryExamples/Listfiles): Print out the files in a directory on a SD card.
* [Read Write](https://www.arduino.cc/en/Tutorial/LibraryExamples/ReadWrite): Read and write data to and from an SD card.
