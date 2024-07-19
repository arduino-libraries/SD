/* Arduino SdFat Library
   Copyright (C) 2008 by William Greiman

   This file is part of the Arduino SdFat Library

   This Library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the Arduino SdFat Library.  If not, see
   <http://www.gnu.org/licenses/>.
*/
#ifndef SdFatUtil_h
#define SdFatUtil_h
/**
   \file
   Useful utility functions.
*/
#include <Arduino.h>
#define NOINLINE __attribute__((noinline,unused))
#define UNUSEDOK __attribute__((unused))
//------------------------------------------------------------------------------
/** Return the number of bytes currently free in RAM. */
static UNUSEDOK int FreeRam(void) {
  extern int  __bss_end;
  extern int* __brkval;
  int free_memory;
  if (reinterpret_cast<int>(__brkval) == 0) {
    // if no heap use from end of bss section
    free_memory = reinterpret_cast<int>(&free_memory)
                  - reinterpret_cast<int>(&__bss_end);
  } else {
    // use from top of stack to heap
    free_memory = reinterpret_cast<int>(&free_memory)
                  - reinterpret_cast<int>(__brkval);
  }
  return free_memory;
}
#endif  // #define SdFatUtil_h
