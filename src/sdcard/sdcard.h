/*
   This file is part of the SD-samd5x library.

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

    (C) Copyright 2024 ADLINK Technology Inc.
*/
#ifndef SDCARD_H
#define SDCARD_H

#include <sam.h>
#include <stdbool.h>
#include <stdint.h>
#include "sdcard_defines.h"
#include "sdcard_commands.h"

#ifdef __cplusplus
extern "C" {
#endif

bool sdcard_init(sdcard_t* sdcard, Sdhc* sdhc, bool high_speed);

bool sdcard_read(sdcard_t* sdcard, void* destination, uint32_t address, uint16_t n_blocks, bool use_dma);

bool sdcard_write(sdcard_t* sdcard, const void* source, uint32_t address, uint16_t n_blocks, bool use_dma);

bool sdcard_is_ready(sdcard_t* sdcard);

#ifdef __cplusplus
}
#endif

#endif /* SDCARD_H */