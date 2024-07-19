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
#include "sd_block_device.h"

bool _sd_read_blocks(block_device_t* dev, void* destination, uint32_t block_address, uint32_t length) {
    sdcard_t * sdcard = dev->_hw;
    return sdcard_read(sdcard, destination, block_address, length, true);
}

bool _sd_write_blocks(block_device_t* dev, const void* source, uint32_t block_address, uint32_t length) {
    sdcard_t * sdcard = dev->_hw;
    return sdcard_write(sdcard, source, block_address, length, false);
}

bool _sd_is_ready(block_device_t* dev) {
    sdcard_t * sdcard = dev->_hw;
    return sdcard_is_ready(sdcard);
}

block_device_t sd_create_block_device(sdcard_t* sdcard) {
    block_device_t sd_block_device = {
        ._hw = sdcard,
        .block_len = sdcard->block_len,
        .read_blocks = _sd_read_blocks,
        .write_blocks = _sd_write_blocks,
        .is_ready = _sd_is_ready,
    };
    return sd_block_device;
}