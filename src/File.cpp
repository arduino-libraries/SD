/*

 SD - a slightly more friendly wrapper for sdfatlib

 This library aims to expose a subset of SD card functionality
 in the form of a higher level "wrapper" object.

 License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

 (C) Copyright 2010 SparkFun Electronics

 */

#include <SD.h>

/* for debugging file open/close leaks
   uint8_t nfilecount=0;
*/

File::File(const SdFile &f, const char *n)
:Stream()
, _file(f)
, _name()
{
  strncpy(_name, n, 12);
  _name[12] = 0;
  /* for debugging file open/close leaks
     nfilecount++;
     Serial.print("Created \"");
     Serial.print(n);
     Serial.print("\": ");
     Serial.println(nfilecount, DEC);
   */
}

File::File(void)
:Stream()
, _file()
, _name()
{
  _name[0] = 0;
  //Serial.print("Created empty file object");
}

File::~File(void)
{
  close();
  //Serial.print(F("Destructor called for file "));
  //Serial.println(_name);
}

// returns a pointer to the file name
char *File::name(void)
{
  return _name;
}

// a directory is a special type of file
boolean File::isDirectory(void)
{
  return _file.isDir();
}

size_t File::write(uint8_t val)
{
  return write(&val, 1);
}

size_t File::write(const uint8_t * buf, size_t size)
{
  size_t t;

  _file.clearWriteError();
  t = _file.write(buf, size);
  if (_file.getWriteError()) {
    setWriteError();
    return 0;
  }
  return t;
}

int File::peek()
{
  int c = _file.read();
  if (c != -1) {
    _file.seekCur(-1);
  }
  return c;
}

int File::read()
{
  return _file.read();
}

// buffered read for more efficient, high speed reading
int File::read(void *buf, uint16_t nbyte)
{
  return _file.read(buf, nbyte);
}

int File::available()
{
  uint32_t n = size() - position();

  return n > 0X7FFF ? 0X7FFF : n;
}

void File::flush()
{
  _file.sync();
}

boolean File::seek(uint32_t pos)
{
  return _file.seekSet(pos);
}

uint32_t File::position()
{
  return _file.curPosition();
}

uint32_t File::size()
{
  return _file.fileSize();
}

void File::close()
{
  _file.close();
  /* for debugging file open/close leaks
     nfilecount--;
     Serial.print("Deleted ");
     Serial.println(nfilecount, DEC);
   */
}

File::operator  bool()
{
  return _file.isOpen();
}
