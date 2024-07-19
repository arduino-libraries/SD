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
#ifndef SDHC_COMMANDS_H
#define SDHC_COMMANDS_H

#include <same.h>
#include <stdint.h>
#include "sdhc.h"

#ifdef __cplusplus
extern "C" {

#endif

static inline sdhc_err_t sdhc_cmd0_go_idle_state(Sdhc* sdhc) {
    return sdhc_cmd(sdhc, SDPROT_CMD0_GO_IDLE_STATE, 0);
}

static inline sdhc_err_t sdhc_cmd2_all_send_cid(Sdhc* sdhc) {
    return sdhc_cmd(sdhc, SDPROT_CMD2_ALL_SEND_CID, 0);
}

static inline sdhc_err_t sdhc_cmd3_send_relative_addr(Sdhc* sdhc) {
    return sdhc_cmd(sdhc, SDPROT_CMD3_SEND_RELATIVE_ADDR, 0);
}

static inline sdhc_err_t sdhc_cmd6_switch_func(Sdhc* sdhc, sdhc_access_mode_t access_mode) {
    sdhc_cmd6_args_t args = { 
        .bit = {
            .ACCESS_MODE = access_mode,
            .GROUP2 = SDHC_CMD6_NO_INFLUENCE,
            .GROUP3 = SDHC_CMD6_NO_INFLUENCE,
            .GROUP4 = SDHC_CMD6_NO_INFLUENCE,
            .GROUP5 = SDHC_CMD6_NO_INFLUENCE,
            .GROUP6 = SDHC_CMD6_NO_INFLUENCE,
        }
    };
    return sdhc_transfer_cmd(sdhc, SDPROT_CMD6_SWITCH_FUNC, args.reg, SDPROT_SWITCH_FUNC_BLOCKSIZE, 1, false);
}

static inline sdhc_err_t sdhc_cmd7_select_card(Sdhc* sdhc, uint16_t rca) {
    return sdhc_cmd(sdhc, SDPROT_CMD7_SELECT_CARD, (uint32_t)(rca) << 16);
}

static inline sdhc_err_t sdhc_cmd7_deselect_card(Sdhc* sdhc, uint16_t rca) {
    return sdhc_cmd(sdhc, SDPROT_CMD7_DESELECT_CARD, (uint32_t)(rca) << 16);
}

static inline sdhc_err_t sdhc_cmd8_send_if_cond(Sdhc* sdhc, uint8_t check_pattern) {
    sdhc_args_cmd8_t arg = {
        .bit = {
            .CHECK_PTN = check_pattern,
            .V_SUPPLIED = VOLT_ACCEPT_2V7_3V6,
        }
    };
    return sdhc_cmd(sdhc, SDPROT_CMD8_SEND_IF_COND, arg.reg);
}

static inline sdhc_err_t sdhc_cmd9_send_csd(Sdhc* sdhc, uint16_t rca) {
    return sdhc_cmd(sdhc, SDPROT_CMD9_SEND_CSD, ((uint32_t)rca) << 16);
}

static inline sdhc_err_t sdhc_cmd13_send_status(Sdhc* sdhc, uint16_t rca) {
    return sdhc_cmd(sdhc, SDPROT_CMD13_SEND_STATUS, ((uint32_t)rca) << 16);
}

static inline sdhc_err_t sdhc_cmd16_set_blocklen(Sdhc* sdhc, uint32_t block_len) {
    return sdhc_cmd(sdhc, SDPROT_CMD16_SET_BLOCKLEN, block_len);
}

static inline sdhc_err_t sdhc_cmd17_read_single_block(Sdhc* sdhc, uint32_t address, uint16_t block_len, uint8_t use_dma) {
    return sdhc_transfer_cmd(sdhc, SDPROT_CMD17_READ_SINGLE_BLOCK, address, block_len, 1, use_dma);
}

static inline sdhc_err_t sdhc_cmd18_read_multiple_block(Sdhc* sdhc, uint32_t address, uint16_t block_len, uint16_t n_blocks, uint8_t use_dma) {
    return sdhc_transfer_cmd(sdhc, SDPROT_CMD18_READ_MULTIPLE_BLOCK, address, block_len, n_blocks, use_dma);
}

static inline sdhc_err_t sdhc_cmd24_write_block(Sdhc* sdhc, uint32_t address, uint16_t block_len, uint8_t use_dma) {
    return sdhc_transfer_cmd(sdhc, SDPROT_CMD24_WRITE_BLOCK, address, block_len, 1, use_dma);
}

static inline sdhc_err_t sdhc_cmd25_write_multiple_block(Sdhc* sdhc, uint32_t address, uint16_t block_len, uint16_t n_blocks, uint8_t use_dma) {
    return sdhc_transfer_cmd(sdhc, SDPROT_CMD25_WRITE_MULTIPLE_BLOCK, address, block_len, n_blocks, use_dma);
}

static inline sdhc_err_t sdhc_cmd32_erase_wr_blk_start(Sdhc* sdhc, uint32_t lba) {
    return sdhc_cmd(sdhc, SDPROT_CMD32_ERASE_WR_BLK_START, lba);
}

static inline sdhc_err_t sdhc_cmd33_erase_wr_blk_end(Sdhc* sdhc, uint32_t lba) {
    return sdhc_cmd(sdhc, SDPROT_CMD33_ERASE_WR_BLK_END, lba);
}

static inline sdhc_err_t sdhc_cmd38_erase(Sdhc* sdhc, sdhc_erase_mode_t erase_mode) {
    return sdhc_cmd(sdhc, SDPROT_CMD38_ERASE, (uint32_t)erase_mode);
}

static inline sdhc_err_t sdhc_cmd55_app_cmd(Sdhc* sdhc, uint16_t rca) {
    return sdhc_cmd(sdhc, SDPROT_CMD55_APP_CMD, (uint32_t)(rca) << 16);
}

static inline sdhc_err_t sdhc_acmd6_set_bus_width(Sdhc* sdhc, sdhc_bus_width_t width) {
    return sdhc_cmd(sdhc, SDPROT_ACMD6_SET_BUS_WIDTH, width);
}

static inline sdhc_err_t sdhc_acmd41_sd_send_op_cond(Sdhc* sdhc, sdhc_reg_ocr_t ocr) {
    return sdhc_cmd(sdhc, SDPROT_ACMD41_SEND_OP_COND, ocr.reg);
}

#ifdef __cplusplus
}
#endif

#endif /* SDHC_COMMANDS_H */