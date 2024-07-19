/* Arduino Sd2Card Library
   Copyright (C) 2009 by William Greiman

   This file is part of the Arduino Sd2Card Library

   This Library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the Arduino Sd2Card Library.  If not, see
   <http://www.gnu.org/licenses/>.
*/
#include <Arduino.h>
#include "Sd2Card.h"
#include "gpio/pins.h"
//------------------------------------------------------------------------------
/**
   Determine the size of an SD flash memory card.

   \return The number of 512 byte data blocks in the card
           or zero if an error occurs.
*/
uint32_t Sd2Card::cardSize(void) {
  return sdcard.num_blocks;
}

//------------------------------------------------------------------------------
/** Erase a range of blocks.

   \param[in] firstBlock The address of the first block in the range.
   \param[in] lastBlock The address of the last block in the range.

   \note This function requests the SD card to do a flash erase for a
   range of blocks.  The data on the card after an erase operation is
   either 0 or 1, depends on the card vendor.  The card must support
   single block erase.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t Sd2Card::erase(uint32_t firstBlock, uint32_t lastBlock) {
  return false;
}
//------------------------------------------------------------------------------
/** Determine if card supports single block erase.

   \return The value one, true, is returned if single block erase is supported.
   The value zero, false, is returned if single block erase is not supported.
*/
uint8_t Sd2Card::eraseSingleBlockEnable(void) {
  // sdhc_reg_csd_t reg = (sdhc_reg_csd_t)(sdcard.regs.csd);
  // return reg.sd_v2._ERASE_BLK_EN;
  return false;
}
//------------------------------------------------------------------------------
/**
   Initialize an SD flash memory card.

   \param[in] sckRateID SPI clock rate selector. See setSckRate().
   \param[in] chipSelectPin SD chip select pin number.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.  The reason for failure
   can be determined by calling errorCode() and errorData().
*/
uint8_t Sd2Card::init(bool high_speed) {
  sdhc_setup();
  sdhc = SDHC1;
  sdhc_driver_init(sdhc);
  if(!sdcard_init(&sdcard, sdhc, high_speed)) {
    return false;
  }
  dev = sd_create_block_device(&sdcard);
  return true;
}

uint8_t Sd2Card::init(block_device_t block_dev) {
  dev = block_dev;
  sdcard = *(sdcard_t*)(dev._hw);
  sdhc = sdcard.device;
  return true;
}
//------------------------------------------------------------------------------
/**
   Read a 512 byte block from an SD card device.

   \param[in] block Logical block to be read.
   \param[out] dst Pointer to the location that will receive the data.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t Sd2Card::readBlock(uint32_t block, uint8_t* dst) {
  return dev.read_blocks(&dev, dst, block, 1);
}
//------------------------------------------------------------------------------
/**
   Read part of a 512 byte block from an SD card.

   \param[in] block Logical block to be read.
   \param[in] offset Number of bytes to skip at start of block
   \param[out] dst Pointer to the location that will receive the data.
   \param[in] count Number of bytes to read
   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t Sd2Card::readData(uint32_t block,
                          uint16_t offset, uint16_t count, uint8_t* dst) {
  if (count == 0) {
    return true;
  }
  if ((count + offset) > dev.block_len) {
    return false;
  }
  
  uint8_t tmp_buf[dev.block_len];
  if(!dev.read_blocks(&dev, tmp_buf, block, 1)) {
    return false;
  }
  for(uint16_t i = 0; i < count; i++) {
    dst[i] = tmp_buf[offset+i];
  }
  return true;
}
//------------------------------------------------------------------------------
// wait for card to go not busy
uint8_t Sd2Card::waitNotBusy() {
  while(!dev.is_ready(&dev)) {}
  return true;
}
//------------------------------------------------------------------------------
/**
   Writes a 512 byte block to an SD card.

   \param[in] blockNumber Logical block to be written.
   \param[in] src Pointer to the location of the data to be written.
   \param[in] blocking If the write should be blocking.
   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t Sd2Card::writeBlock(uint32_t blockNumber, const uint8_t* src, uint8_t blocking) {
  if(!blocking) {
    return false;
  }
  #if SD_PROTECT_BLOCK_ZERO
  // don't allow write to first block
  if (blockNumber == 0) {
    //error(SD_CARD_ERROR_WRITE_BLOCK_ZERO);
    return false;
  }
  #endif  // SD_PROTECT_BLOCK_ZERO

  return dev.write_blocks(&dev, src, blockNumber, 1);
}
//------------------------------------------------------------------------------
/** Check if the SD card is busy

  \return The value one, true, is returned when is busy and
   the value zero, false, is returned for when is NOT busy.
*/
uint8_t Sd2Card::isBusy(void) {
  return !dev.is_ready(&dev);
}
