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
#include "sdcard_defines.h"
#include "sdcard_commands.h"

#include "../sdhc/sdhc_commands.h"

const uint32_t sdcard_xfer_speed_units[7] = {10, 100, 1000, 10000, 0, 0, 0};
const uint32_t sdcard_xfer_speed_multipliers[16] = {0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80};

bool sdcard_cmd0_go_idle_state(sdcard_t* sdcard) {
    return (sdhc_cmd0_go_idle_state(sdcard->device) == SDHC_E_OK);
}

bool sdcard_cmd2_all_send_cid(sdcard_t* sdcard) {
    if(sdhc_cmd2_all_send_cid(sdcard->device) != SDHC_E_OK)
        return false;

    sdhc_reg_cid_t* cid = &(sdcard->regs.cid);
    sdhc_get_response_120bit(sdcard->device, cid);
    return true;
}

bool sdcard_cmd3_send_relative_addr(sdcard_t* sdcard) {
    if(sdhc_cmd3_send_relative_addr(sdcard->device) != SDHC_E_OK)
        return false;

    sdhc_resp_r6_t* response = (sdhc_resp_r6_t*)sdhc_get_response_ptr(sdcard->device);
    sdcard->rca = response->rca;
    sdcard->current_state = (sdcard_state_t)response->status.CURRENT_STATE;
    return true;
}

bool sdcard_cmd6_switch_func(sdcard_t* sdcard, sdcard_bus_speed_t bus_speed) {
    if(sdcard->bus_speed == bus_speed)
        return false;

    sdhc_access_mode_t access_mode;
    switch(bus_speed) {
        case SDCARD_BUS_SPEED_DEFAULT_SPEED:
            access_mode = SDHC_ACCESS_MODE_DEFAULT_SDR12;
            break;
        case SDCARD_BUS_SPEED_HIGH_SPEED:
            access_mode = SDHC_ACCESS_MODE_HIGHSPEED_SDR25;
            break;
        default:
            return false;
    }
    if(sdhc_cmd6_switch_func(sdcard->device, access_mode) != SDHC_E_OK)
        return false;

    uint8_t buf[SDPROT_SWITCH_FUNC_BLOCKSIZE];
    if(sdhc_read_blocks(sdcard->device, buf, SDPROT_SWITCH_FUNC_BLOCKSIZE, 1) != SDHC_E_OK)
        return false;

    // sdhc_card_status_t* response = (sdhc_card_status_t*)sdhc_get_response_ptr(sdcard->device);
    // if(response->SWITCH_ERROR)
    //     return false;
        
    sdcard->bus_speed = bus_speed;
    switch(bus_speed) {
        case SDCARD_BUS_SPEED_DEFAULT_SPEED:
            sdcard->clock_hz = sdcard->clock_hz >> 1;
            sdhc_set_high_speed(sdcard->device, false);
            break;
        case SDCARD_BUS_SPEED_HIGH_SPEED:
            sdcard->clock_hz = sdcard->clock_hz << 1;
            sdhc_set_high_speed(sdcard->device, true);
            break;
        default:
            return false;
    }
    sdhc_set_clk(sdcard->device, sdcard->clock_hz, SDHC_CLOCK_PROGRAMMABLE);

    return true;
}

bool sdcard_cmd7_select_card(sdcard_t* sdcard) {
    if(sdhc_cmd7_select_card(sdcard->device, sdcard->rca) != SDHC_E_OK)
        return false;

    sdhc_card_status_t* response = (sdhc_card_status_t*)sdhc_get_response_ptr(sdcard->device);
    sdcard->current_state = (sdcard_state_t)response->CURRENT_STATE;
    return true;
}

bool sdcard_cmd7_deselect_card(sdcard_t* sdcard) {
    if(sdhc_cmd7_deselect_card(sdcard->device, sdcard->rca) != SDHC_E_OK)
        return false;

    sdhc_card_status_t* response = (sdhc_card_status_t*)sdhc_get_response_ptr(sdcard->device);
    sdcard->current_state = (sdcard_state_t)response->CURRENT_STATE;
    return true;
}

bool sdcard_cmd8_send_if_cond(sdcard_t* sdcard) {
    uint8_t check_pattern = SDCARD_CHECK_PATTERN;
    sdhc_err_t err = sdhc_cmd8_send_if_cond(sdcard->device, check_pattern);

    sdhc_resp_r7_t* response = (sdhc_resp_r7_t*)sdhc_get_response_ptr(sdcard->device);
    if(err) {
        sdcard->version = SDCARD_VER_1_X_SC;
        return true;
    } else if(response->bit.CHECK_PTN == check_pattern && 
            response->bit.V_ACCEPT == VOLT_ACCEPT_2V7_3V6) {
        sdcard->version = SDCARD_VER_2_0_UNKNOWN;
        return true;
    }
    return false;
}

bool sdcard_cmd9_send_csd(sdcard_t* sdcard) {
    if(sdhc_cmd9_send_csd(sdcard->device, sdcard->rca) != SDHC_E_OK)
        return false;

    sdhc_reg_csd_t* csd = &(sdcard->regs.csd);
    sdhc_get_response_120bit(sdcard->device, csd);
    uint32_t blocknr;
    switch(csd->sd_v1.CSD_STRUCTURE) {
        case SDHC_CSD_STRUCTURE_SD_V1:
            blocknr = (csd->sd_v1.C_SIZE + 1)* (1 << (csd->sd_v1.C_SIZE_MULT + 2));
            sdcard->block_len = csd->sd_v1.READ_BL_LEN;
            sdcard->num_blocks = blocknr* (1 << csd->sd_v1.READ_BL_LEN) >> 10;
            break;
        case SDHC_CSD_STRUCTURE_SD_V2:
            sdcard->num_blocks = (csd->sd_v2.C_SIZE + 1) << 10;
            break;
        case SDHC_CSD_STRUCTURE_SD_V3:
        default:
            return false;
            break;
    }

    sdcard->block_len = (1 << csd->sd_v1.READ_BL_LEN);

    uint32_t unit = sdcard_xfer_speed_units[csd->sd_v1.TRAN_SPEED & 0x7];
    uint32_t mul = sdcard_xfer_speed_multipliers[(csd->sd_v1.TRAN_SPEED >> 3) & 0xF];
    sdcard->clock_hz = unit* mul* 1000;
    sdhc_set_clk(sdcard->device, sdcard->clock_hz, SDHC_CLOCK_DIVIDED);
    return true;
}

bool sdcard_cmd13_send_status(sdcard_t* sdcard) {
    if(sdhc_cmd13_send_status(sdcard->device, sdcard->rca) != SDHC_E_OK)
        return false;

    sdhc_card_status_t* status = (sdhc_card_status_t*)sdhc_get_response_ptr(sdcard->device);
    sdcard->current_state = (sdcard_state_t)status->CURRENT_STATE;
    return true;
}

bool sdcard_cmd16_set_blocklen(sdcard_t* sdcard, uint16_t block_len) {
    if(sdhc_cmd16_set_blocklen(sdcard->device, block_len) != SDHC_E_OK)
        return false;
    
    sdcard->block_len = block_len;
    return true;
}

bool sdcard_cmd17_read_single_block(sdcard_t* sdcard, uint32_t address, bool use_dma) {
    if(sdcard->version == SDCARD_VER_1_X_SC) {
        address = address* sdcard->block_len;
    }
    return (sdhc_cmd17_read_single_block(sdcard->device, address, sdcard->block_len, use_dma) == SDHC_E_OK);
}

bool sdcard_cmd18_read_multiple_block(sdcard_t* sdcard, uint32_t address, uint16_t n_blocks, bool use_dma) {
    if(sdcard->version == SDCARD_VER_1_X_SC) {
        address = address* sdcard->block_len;
    }
    return (sdhc_cmd18_read_multiple_block(sdcard->device, address, sdcard->block_len, n_blocks, use_dma) == SDHC_E_OK);
}

bool sdcard_cmd24_write_block(sdcard_t* sdcard, uint32_t address, bool use_dma) {
    if(sdcard->version == SDCARD_VER_1_X_SC) {
        address = address* sdcard->block_len;
    }
    return (sdhc_cmd24_write_block(sdcard->device, address, sdcard->block_len, use_dma) == SDHC_E_OK);
}

bool sdcard_cmd25_write_multiple_block(sdcard_t* sdcard, uint32_t address, uint16_t n_blocks, bool use_dma) {
    if(sdcard->version == SDCARD_VER_1_X_SC) {
        address = address* sdcard->block_len;
    }
    return (sdhc_cmd25_write_multiple_block(sdcard->device, address, sdcard->block_len, n_blocks, use_dma) == SDHC_E_OK);
}

bool sdcard_cmd32_erase_wr_blk_start(sdcard_t* sdcard, uint32_t lba) {
    return (sdhc_cmd32_erase_wr_blk_start(sdcard->device, lba) == SDHC_E_OK);
}

bool sdcard_cmd33_erase_wr_blk_end(sdcard_t* sdcard, uint32_t lba) {
    if(lba > sdcard->num_blocks)
        return false;
    return (sdhc_cmd33_erase_wr_blk_end(sdcard->device, lba) == SDHC_E_OK);
}

bool sdcard_cmd38_erase(sdcard_t* sdcard, sdcard_erase_mode_t erase_mode) {
    sdhc_erase_mode_t sdhc_erase_mode;
    switch(erase_mode) {
        default:
        case SDCARD_ERASE_MODE_NORMAL:
            sdhc_erase_mode = SDHC_ERASE_MODE_NORMAL;
            break;
        case SDCARD_ERASE_MODE_DISCARD:
            sdhc_erase_mode = SDHC_ERASE_MODE_DISCARD;
            break;
        case SDCARD_ERASE_MODE_FULE:
            sdhc_erase_mode = SDHC_ERASE_MODE_FULE;
            break;
    }

    return sdhc_cmd38_erase(sdcard->device, sdhc_erase_mode);
}

bool sdcard_acmd6_set_bus_width(sdcard_t* sdcard, sdcard_bus_width_t bus_width) {
    if(bus_width == sdcard->bus_width)
        return true;

    sdhc_bus_width_t sdhc_bus_width;
    switch(bus_width) {
        case SDCARD_BUS_1LANE:
            sdhc_bus_width = SDHC_BUS_WIDTH_1;
            break;
        case SDCARD_BUS_4LANE:
            sdhc_bus_width = SDHC_BUS_WIDTH_4;
            break;
        default:
            return false;
    }

    if(sdhc_cmd55_app_cmd(sdcard->device, sdcard->rca) != SDHC_E_OK)
        return false;

    if(sdhc_acmd6_set_bus_width(sdcard->device, sdhc_bus_width) != SDHC_E_OK)
        return false;

    sdhc_set_bus_width(sdcard->device, sdhc_bus_width);
    sdcard->bus_width = bus_width;

    return true;
}

bool sdcard_acmd41_sd_send_op_cond(sdcard_t* sdcard) {
    sdhc_reg_ocr_t hcs = {
        .bit = {
            .voltage_window = {
                .VDD_27_28 = 1,
                .VDD_28_29 = 1,
                .VDD_29_30 = 1,
                .VDD_30_31 = 1,
                .VDD_31_32 = 1,
                .VDD_32_33 = 1,
            },
            .CCS = 1,
        }
    };

    sdhc_reg_ocr_t* ocr = (sdhc_reg_ocr_t*)sdhc_get_response_ptr(sdcard->device);
    int retry = 2100;
    do {
        if(sdhc_cmd55_app_cmd(sdcard->device, sdcard->rca) != SDHC_E_OK)
            return false;
        
        if(sdhc_acmd41_sd_send_op_cond(sdcard->device, hcs) != SDHC_E_OK)
            return false;

        if(retry-- == 0)
            return false;
    } while(!ocr->bit.POWER_UP_BUSY);

    if(ocr->bit.CCS)
        sdcard->version = SDCARD_VER_2_0_HC;
    else
        sdcard->version = SDCARD_VER_2_0_SC;

    return true;
}