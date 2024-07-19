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
#ifndef PINS_H
#define PINS_H

#include <WVariant.h>

enum gpio_pmux { 
    GPIO_PMUX_A, 
    GPIO_PMUX_B,
    GPIO_PMUX_C,
    GPIO_PMUX_D,
    GPIO_PMUX_E,
    GPIO_PMUX_F,
    GPIO_PMUX_G,
    GPIO_PMUX_H,
    GPIO_PMUX_I,
    GPIO_PMUX_J,
    GPIO_PMUX_K,
    GPIO_PMUX_L,
    GPIO_PMUX_M,
    GPIO_PMUX_N
};

enum gpio_direction { 
    GPIO_DIRECTION_OFF, 
    GPIO_DIRECTION_IN, 
    GPIO_DIRECTION_OUT };

enum gpio_pull_mode { 
    GPIO_PULL_OFF, 
    GPIO_PULL_UP, 
    GPIO_PULL_DOWN };

typedef struct {
    EPortType type;
    uint32_t pin_no;
} pin_t;

void sdhc_setup();

void set_pin_pmux(const pin_t* pin, enum gpio_pmux mux);

void set_pin_dir(const pin_t* pin, enum gpio_direction direction);

void set_pin_pull_mode(const pin_t* pin, enum gpio_pull_mode pull_mode);

void set_pin_level(const pin_t* pin, uint8_t level);

void toggle_pin_level(const pin_t* pin);

#endif // PINS_H