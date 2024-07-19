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
#ifndef Sd2Card_h
#define Sd2Card_h
/**
   \file
   Sd2Card class
*/
#include "sd_block_device.h"
#include "sdiocard/sdcard.h"
#include "sdhc/sdhc.h"
#include "SdInfo.h"

/** Protect block zero from write if nonzero */
#define SD_PROTECT_BLOCK_ZERO 1

/**
   \class Sd2Card
   \brief Raw access to SD and SDHC flash memory cards.
*/
class Sd2Card {
  public:
    /** Construct an instance of Sd2Card. */
    Sd2Card(void) {}
    uint32_t cardSize(void);
    uint8_t erase(uint32_t firstBlock, uint32_t lastBlock);
    uint8_t eraseSingleBlockEnable(void);
    // /**
    //    \return error code for last error. See Sd2Card.h for a list of error codes.
    // */
    // uint8_t errorCode(void) const {
    //   return errorCode_;
    // }
    // /** \return error data for last error. */
    // uint8_t errorData(void) const {
    //   return status_;
    // }
    /**
       Initialize an SD flash memory card with default clock rate and chip
       select pin.  See sd2Card::init(uint8_t sckRateID, uint8_t chipSelectPin).
    */
    uint8_t init(bool high_speed);
    uint8_t init(block_device_t block_dev);
    
    uint8_t readBlock(uint32_t block, uint8_t* dst);
    uint8_t readData(uint32_t block,
                     uint16_t offset, uint16_t count, uint8_t* dst);

    uint8_t waitNotBusy();
    /**
       Read a cards CID register. The CID contains card identification
       information such as Manufacturer ID, Product name, Product serial
       number and Manufacturing date. */
    uint8_t readCID(sdhc_reg_cid_t* cid) {
      *cid = sdcard.regs.cid;
      return true;
    }
    /**
       Read a cards CSD register. The CSD contains Card-Specific Data that
       provides information regarding access to the card's contents. */
    uint8_t readCSD(sdhc_reg_csd_t* csd) {
      *csd = sdcard.regs.csd;
      return 1;
    }
    /** Return the card type: SD V1, SD V2 or SDHC */
    uint8_t writeBlock(uint32_t blockNumber, const uint8_t* src, uint8_t blocking = 1);
    uint8_t isBusy(void);
  private:
    Sdhc * sdhc;
    sdcard_t sdcard;
    block_device_t dev;
};
#endif  // Sd2Card_h
