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
#ifndef SDHC_DEFINES_H
#define SDHC_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SDHC_E_OK = 0,
    SDHC_E_INVALID_DATA = -1,
    SDHC_E_ERR = -2,
    SDHC_E_TIMEOUT = -3,
    SDHC_E_CMDINHC = -4,
    SDHC_E_CMDINHD = -5,
    SDHC_E_EISTR = -6,
    SDHC_E_CLK_MODE_UNSUPPORTED = -7,
    SHDC_E_PVALEN = -8,
} sdhc_err_t;

typedef enum {
    SDHC_CLOCK_DIVIDED,
    SDHC_CLOCK_PROGRAMMABLE,
} sdhc_clock_mode_t;

typedef enum {
    SDHC_BUS_WIDTH_1 = 0x0,
    SDHC_BUS_WIDTH_4 = 0x2,
} sdhc_bus_width_t;

#ifdef __cplusplus
}
#endif

#endif /* SDHC_DEFINES_H */