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
#include "pins.h"

// Hardcoded for SDHC1
const pin_t SDHC_CMD_PIN     = { PORTA, 20 };
const pin_t SDHC_WP_PIN      = { PORTB, 16 };
const pin_t SDHC_CK_PIN      = { PORTA, 21 };
const pin_t SDHC_DAT_PINS[4] = {
    { PORTB, 18 },
    { PORTB, 19 },
    { PORTB, 20 },
    { PORTB, 21 }
};

void sdhc_setup() {
    GCLK->GENCTRL[6].reg = GCLK_GENCTRL_DIV(10) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_DPLL0;
    while(GCLK->SYNCBUSY.bit.GENCTRL6);

    GCLK->PCHCTRL[SDHC1_GCLK_ID     ].reg = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN;
    GCLK->PCHCTRL[SDHC1_GCLK_ID_SLOW].reg = GCLK_PCHCTRL_GEN_GCLK6 | GCLK_PCHCTRL_CHEN;

    set_pin_dir(&SDHC_CK_PIN, GPIO_DIRECTION_OUT);
    set_pin_level(&SDHC_CK_PIN, 0);
    set_pin_pull_mode(&SDHC_CK_PIN, GPIO_PULL_OFF);
    set_pin_pmux(&SDHC_CK_PIN, GPIO_PMUX_I);
    
    set_pin_dir(&SDHC_CMD_PIN, GPIO_DIRECTION_OUT);
    set_pin_level(&SDHC_CMD_PIN, 0);
    set_pin_pull_mode(&SDHC_CMD_PIN, GPIO_PULL_OFF);
    set_pin_pmux(&SDHC_CMD_PIN, GPIO_PMUX_I);

    for(int i = 0; i < 4; i++) {
        set_pin_dir(&SDHC_DAT_PINS[i], GPIO_DIRECTION_OUT);
        set_pin_level(&SDHC_DAT_PINS[i], 0);
        set_pin_pull_mode(&SDHC_DAT_PINS[i], GPIO_PULL_OFF);
        set_pin_pmux(&SDHC_DAT_PINS[i], GPIO_PMUX_I);
    }
}

void set_pin_pmux(const pin_t* pin, enum gpio_pmux mux) {
    uint8_t pmux_id = pin->pin_no >> 1;
    if(pin->pin_no & 1) {
        PORT->Group[pin->type].PMUX[pmux_id].bit.PMUXO = mux;
    } else {
        PORT->Group[pin->type].PMUX[pmux_id].bit.PMUXE = mux;
    }
    PORT->Group[pin->type].PINCFG[pin->pin_no].reg = PORT_PINCFG_PMUXEN;
}

void set_pin_dir(const pin_t* pin, enum gpio_direction direction) {
    PortGroup* grp = &(PORT->Group[pin->type]);
    
    switch(direction) {
    case GPIO_DIRECTION_OFF:
        grp->DIRCLR.reg = (1 << pin->pin_no);
        grp->PINCFG[pin->pin_no].bit.INEN = 0;
        break;
    case GPIO_DIRECTION_IN:
        grp->DIRCLR.reg = (1 << pin->pin_no);
        grp->PINCFG[pin->pin_no].bit.INEN = 1;
        break;
    case GPIO_DIRECTION_OUT:
        grp->DIRSET.reg = (1 << pin->pin_no);
        grp->PINCFG[pin->pin_no].bit.INEN = 0;
        break;
    }
}

void set_pin_pull_mode(const pin_t* pin, enum gpio_pull_mode pull_mode) {
    PortGroup* grp = &(PORT->Group[pin->type]);

    switch(pull_mode) {
    case GPIO_PULL_OFF:
        grp->PINCFG[pin->pin_no].bit.PULLEN = 0;
        break;
    case GPIO_PULL_UP:
        grp->DIRCLR.reg = (1 << pin->pin_no);
        grp->PINCFG[pin->pin_no].bit.PULLEN = 1;
        grp->OUTSET.reg = (1 << pin->pin_no);
        break;
    case GPIO_PULL_DOWN:
        grp->DIRCLR.reg = (1 << pin->pin_no);
        grp->PINCFG[pin->pin_no].bit.PULLEN = 1;
        grp->OUTCLR.reg = (1 << pin->pin_no);
        break;
    }
}

void set_pin_level(const pin_t* pin, uint8_t level) {
    if(level)
        PORT->Group[pin->type].OUTSET.reg = (1 << pin->pin_no);
    else
        PORT->Group[pin->type].OUTCLR.reg = (1 << pin->pin_no);
}

void toggle_pin_level(const pin_t* pin) {
    PORT->Group[pin->type].OUTTGL.reg = (1 << pin->pin_no);
}