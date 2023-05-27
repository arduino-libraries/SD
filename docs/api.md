# SD library

## SD class

The SD class provides functions for accessing the SD card and manipulating its files and directories.

### `begin()`

Initializes the SD library and card. This begins use of the SPI bus (digital pins 11, 12, and 13 on most Arduino boards; 50, 51, and 52 on the Mega) and the chip select pin, which defaults to the hardware SS pin (pin 10 on most Arduino boards, 53 on the Mega). Note that even if you use a different chip select pin, **the hardware SS pin must be kept as an output or the SD library functions will not work**.

#### Syntax 

```
SD.begin()
SD.begin(cspin)
```

#### Parameters

* `cspin` (optional): the pin connected to the chip select line of the SD card; defaults to the hardware SS line of the SPI bus.

#### Returns

1 on success, 0 on failure.

#### See also

* [exists()](#exists)
* [mkdir()](#mkdir)
* [open()](#open)
* [remove()](#remove)
* [rmdir()](#rmdir)

### `exists()`

Tests whether a file or directory exists on the SD card.

#### Syntax 

```
SD.exists(filename)
```

#### Parameters

* `filename`: the name of the file to test for existence, which can include directories (delimited by forward-slashes, /).

#### Returns

1 if the file or directory exists, 0 if not.

#### See also

* [begin()](#begin)
* [mkdir()](#mkdir)
* [open()](#open)
* [remove()](#remove)
* [rmdir()](#rmdir)

### `exists()`

Tests whether a file or directory exists on the SD card.

#### Syntax 

```
SD.exists(filename)
```

#### Parameters

* `filename`: the name of the file to test for existence, which can include directories (delimited by forward-slashes, /).

#### Returns

1 if the file or directory exists, 0 if not.

#### See also

* [begin()](#begin)
* [mkdir()](#mkdir)
* [open()](#open)
* [remove()](#remove)
* [rmdir()](#rmdir)

### `mkdir()`

Create a directory on the SD card. This will also create any intermediate directories that don't already exists; e.g. `SD.mkdir("a/b/c")` will create a, b, and c.

#### Syntax 

```
SD.mkdir(filename)
```

#### Parameters

* `filename`: the name of the directory to create, with sub-directories separated by forward-slashes, /.

#### Returns

1 if the creating of the directory succeeded, 0 if not.

#### See also

* [begin()](#begin)
* [exists()](#exists)
* [open()](#open)
* [remove()](#remove)
* [rmdir()](#rmdir)

### `open()`

Opens a file on the SD card. If the file is opened for writing, it will be created if it doesn't already exist (but the directory containing it must already exist).

#### Syntax 

```
SD.open(filepath)
SD.open(filepath, mode)
```

#### Parameters

* `filepath`: the name of the file to open, which can include directories (delimited by forward-slashes, /).
* `mode` (optional): the mode in which to open the file. Mode can be `FILE_READ` (open the file for reading, starting at the beginning of the file) or `FILE_WRITE` (open the file for reading and writing, starting at the end of the file).

#### Returns

A File object referring to the opened file; if the file couldn't be opened, this object will evaluate to false in a boolean context, i.e. you can test the return value with "`if (f)`".

#### See also

* [begin()](#begin)
* [exists()](#exists)
* [mkdir()](#mkdir)
* [remove()](#remove)
* [rmdir()](#rmdir)

### `remove()`

Remove a file from the SD card.

#### Syntax 

```
SD.remove(filename)
```

#### Parameters

* `filename`: the name of the file to remove, which can include directories (delimited by forward-slashes, /).

#### Returns

1 if the removal of the file succeeded, 0 if not.

#### See also

* [begin()](#begin)
* [exists()](#exists)
* [mkdir()](#mkdir)
* [open()](#open)
* [rmdir()](#rmdir)

### `rmdir()`

Remove a directory from the SD card. The directory must be empty.

#### Syntax 

```
SD.rmdir(filename)
```

#### Parameters

* `filename`: the name of the directory to remove, with sub-directories separated by forward-slashes, /.

#### Returns

1 if the removal of the directory succeeded, 0 if not (if the directory didn't exist, the return value is unspecified).

#### See also

* [begin()](#begin)
* [exists()](#exists)
* [mkdir()](#mkdir)
* [open()](#open)
* [remove()](#remove)

## File class

The File class allows for reading from and writing to individual files on the SD card.

### `name()`

Returns the file name

#### Syntax 

```
file.name()
```

#### Parameters

None.

#### Returns

The file name.

#### See also

* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `available()`

Check if there are any bytes available for reading from the file. `available()` inherits from the [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) utility class.

#### Syntax 

```
file.available()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).

#### Returns

The number of bytes available as an integer.

#### See also

* [name()](#name)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `close()`

Close the file, and ensure that any data written to it is physically saved to the SD card.

#### Syntax 

```
file.close()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).

#### Returns

None.

#### See also

* [name()](#name)
* [available()](#available)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `flush()`

Ensures that any bytes written to the file are physically saved to the SD card. This is done automatically when the file is closed. `flush()` inherits from the [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) utility class.

#### Syntax 

```
file.flush()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).

#### Returns

None.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `peek()`

Read a byte from the file without advancing to the next one. That is, successive calls to peek() will return the same value, as will the next call to read(). `peek()` inherits from the [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) utility class.

#### Syntax 

```
file.peek()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).

#### Returns

The next byte (or character), or -1 if none is available.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `position()`

Get the current position within the file (i.e. the location to which the next byte will be read from or written to).

#### Syntax 

```
file.position()
file.position(file)
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).

#### Returns

The position within the file (unsigned long).

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `print()`

Print data to the file, which must have been opened for writing. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters '1', '2', '3').

#### Syntax 

```
file.print(data)
file.print(data, BASE)
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
* `data`: the data to print (char, byte, int, long, or string).
* `BASE` (optional): the base in which to print numbers; BIN for binary (base 2), DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns

The number of bytes written, though reading that number is optional.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `println()`

Print data, followed by a carriage return and newline, to the File, which must have been opened for writing. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters '1', '2', '3').

#### Syntax 

```
file.println()
file.println(data)
file.println(data, BASE)
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
* `data`: the data to print (char, byte, int, long, or string).
* `BASE` (optional): the base in which to print numbers; BIN for binary (base 2), DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns

The number of bytes written, though reading that number is optional.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `seek()`

Seek to a new position in the file, which must be between 0 and the size of the file (inclusive).

#### Syntax 

```
file.seek(pos)
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
* `pos`: the position to which to seek (unsigned long).

#### Returns

1 on success, 0 on failure.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `size()`

Get the size of the file.

#### Syntax 

```
file.size()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).

#### Returns

The size of the file in bytes (unsigned long).

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `read()`

Read from the file. read() inherits from the [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) utility class.

#### Syntax 

```
file.read() 
file.read(buf, len)
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
* `buf`: an array of characters or bytes.
* `len`: the number of elements in buf.

#### Returns

When used as `file.read()`:
The next byte (or character), or -1 if none is available. 

When used as `file.read(buf, len)`:
The amount of bytes read, or -1 if an error occurred.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `write()`

Write data to the file.

#### Syntax 

```
file.write(data)
file.write(buf, len)
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
* `data`: the byte, char, or string (char *) to write.
* `buf`: an array of characters or bytes.
* `len`: the number of elements in buf.

#### Returns

The number of bytes written, though reading that number is optional.

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `isDirectory()`

Directories (or folders) are special kinds of files, this function reports if the current file is a directory or not.

#### Syntax 

```
file.isDirectory()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
  
#### Returns

1 if the current file is a directory, 0 if not.

#### Example

```
#include <SD.h>

File root;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);

  SD.begin(10);
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("Done!");
}

void loop() {
  // Nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // No more files
      // Serial.println("**nomorefiles**");
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
      // Files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
  }
}
```

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [openNextFile()](#opennextfile)
* [rewindDirectory()](#rewinddirectory)

### `openNextFile()`

Reports the next file or folder in a directory.

#### Syntax 

```
file.openNextFile()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
  
#### Returns

The next file or folder in the path (char).

#### Example

```
#include <SD.h>

File root;
void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  SD.begin(10);
  root = SD.open("/");
  printDirectory(root, 0);
  delay(2000);

  Serial.println();
  Serial.println("Rewinding, and repeating below:");
  Serial.println();
  delay(2000);

  root.rewindDirectory();
  printDirectory(root, 0);
  root.close();
}

void loop() {
  // Nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      if (numTabs == 0)
        Serial.println("** Done **");
      return;
    }

    for (uint8_t i = 0; i < numTabs; i++)
      Serial.print('\t');

    Serial.print(entry.name());

    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }

    entry.close();
  }
}
```

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [rewindDirectory()](#rewinddirectory)

### `rewindDirectory()`

This function will bring you back to the first file in the directory, used in conjunction with [`openNextFile()`](#opennextfile).

#### Syntax 

```
file.rewindDirectory()
```

#### Parameters

* `file`: an instance of the File class (returned by [SD.open()](#open)).
  
#### Returns

None.

#### Example

```
#include <SD.h>

File root;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  SD.begin(10);
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println();

  Serial.println("PRINT AGAIN");
  Serial.println("-----------");
  root.rewindDirectory();  // Return to the first file in the directory
  printDirectory(root, 0);

  Serial.println("Done!");
}

void loop() {
  // Nothing happens after setup finishes
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No more files
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
      // Files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
  }
}
```

#### See also

* [name()](#name)
* [available()](#available)
* [close()](#close)
* [flush()](#flush)
* [peek()](#peek)
* [position()](#position)
* [print()](#print)
* [println()](#println)
* [seek()](#seek)
* [size()](#size)
* [read()](#read)
* [write()](#write)
* [isDirectory()](#isdirectory)
* [openNextFile()](#opennextfile)
