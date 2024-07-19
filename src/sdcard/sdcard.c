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
#include "sdcard.h"
#include "../sdhc/sdhc.h"
#include "sdcard_commands.h"

void _sdcard_new(sdcard_t* sdcard, Sdhc* sdhc) {
    sdcard_t c = {
        .device = sdhc,
        .rca = 0,
        .clock_hz = SDCARD_CLK_INIT,
        .block_len = SDCARD_DEFAULT_BLOCK_LEN,
        .num_blocks = 0,
        .bus_speed = SDCARD_BUS_SPEED_DEFAULT_SPEED,
        .bus_width = SDCARD_BUS_1LANE,
        .version = SDCARD_VER_UNKNOWN,
        .current_state = SDCARD_STATE_IDLE,
        .regs = {
            .csd = {},
            .cid = {},
        }
    };
    *sdcard = c;
}

bool sdcard_init(sdcard_t* sdcard, Sdhc* sdhc, bool high_speed) {
    _sdcard_new(sdcard, sdhc);

    sdhc_driver_init(sdhc);

    sdhc_set_bus_width(sdhc, SDHC_BUS_WIDTH_1);
    sdhc_set_high_speed(sdhc, 0);
    sdhc_set_clk(sdhc, SDCARD_CLK_INIT, SDHC_CLOCK_DIVIDED);

    /* Send some clock cycles to initialize */
    volatile uint32_t i;
    for(i = 0; i < 5000; i++) {}

    if(!sdcard_cmd0_go_idle_state(sdcard))
        return false;

    if(!sdcard_cmd8_send_if_cond(sdcard))
        return false;

    if(!sdcard_acmd41_sd_send_op_cond(sdcard))
        return false;

    if(!sdcard_cmd2_all_send_cid(sdcard))
        return false;

    if(!sdcard_cmd3_send_relative_addr(sdcard))
        return false;

    if(!sdcard_cmd9_send_csd(sdcard))
        return false;

    if(!sdcard_cmd7_select_card(sdcard))
        return false;

    if(!sdcard_acmd6_set_bus_width(sdcard, SDCARD_BUS_4LANE))
        return false;
    sdcard->bus_width = SDCARD_BUS_4LANE;

    if(high_speed && sdhc_has_high_speed_support(sdcard->device)) {
        if(sdcard_cmd6_switch_func(sdcard, SDCARD_BUS_SPEED_HIGH_SPEED)) {
            /* Wait for high speed to be switched to */
            for(i = 0; i < 5000; i++) {}
        }
    }

    if(!sdcard_cmd13_send_status(sdcard))
        return false;

    return true;
}

bool sdcard_read(sdcard_t* sdcard, void* destination, uint32_t address, uint16_t n_blocks, bool use_dma) {
    use_dma=true;
    if(use_dma) {
        sdcard->device->SSAR.bit.ADDR = (uint32_t)destination;
    }
    
    bool success;
    if(n_blocks == 1) {
        success = sdcard_cmd17_read_single_block(sdcard, address, use_dma);
    } else {
        success = sdcard_cmd18_read_multiple_block(sdcard, address, n_blocks, use_dma);
    }
    if(!success)
        return false;

    if(use_dma)
        return (sdhc_wait_dma(sdcard->device) == SDHC_E_OK);
    else
        return (sdhc_read_blocks(sdcard->device, destination, sdcard->block_len, n_blocks) == SDHC_E_OK);
}

bool sdcard_write(sdcard_t* sdcard, const void* source, uint32_t address, uint16_t n_blocks, bool use_dma) {
    bool success;
    if(n_blocks == 1) {
        success = sdcard_cmd24_write_block(sdcard, address, use_dma);
    } else {
        success = sdcard_cmd25_write_multiple_block(sdcard, address, n_blocks, use_dma);
    }
    if(!success)
        return false;

    if(use_dma) {
        return (sdhc_wait_dma(sdcard->device) == SDHC_E_OK);
    } else {
        return (sdhc_write_blocks(sdcard->device, source, sdcard->block_len, n_blocks) == SDHC_E_OK);
    }
}

bool sdcard_is_ready(sdcard_t* sdcard) {
    if(!sdcard_cmd13_send_status(sdcard))
        return false;
    sdhc_card_status_t* status = (sdhc_card_status_t*)sdhc_get_response_ptr(sdcard->device);
    return status->READY_FOR_DATA;
}