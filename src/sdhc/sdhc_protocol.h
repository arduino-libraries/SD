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
#ifndef SDHC_PROTOCOL_H
#define SDHC_PROTOCOL_H

#include <stdbool.h>

typedef enum {
    SDPROT_RLEN_NONE,       /* No response */
    SDPROT_RLEN_48,         /* 48-bit response */
    SDPROT_RLEN_48_BUSY,    /* 48-bit response with busy line */
    SDPROT_RLEN_136,        /* 136-bit response */
} sdprot_rlen_t;

/* Struct representing a SD response type */
typedef struct {
    sdprot_rlen_t       len;
    bool                check_crc;
    bool                check_index;
} sdprot_rtype_t;

#define SDPROT_R0       ((sdprot_rtype_t){ SDPROT_RLEN_NONE,    false, false })
#define SDPROT_R1       ((sdprot_rtype_t){ SDPROT_RLEN_48,      true,  true  })
#define SDPROT_R1B      ((sdprot_rtype_t){ SDPROT_RLEN_48_BUSY, true,  true  })
#define SDPROT_R2       ((sdprot_rtype_t){ SDPROT_RLEN_136,     true,  false })
#define SDPROT_R3       ((sdprot_rtype_t){ SDPROT_RLEN_48,      false, false })
#define SDPROT_R6       ((sdprot_rtype_t){ SDPROT_RLEN_48,      true,  true  })
#define SDPROT_R7       ((sdprot_rtype_t){ SDPROT_RLEN_48,      true,  true  })

typedef enum {
    SDPROT_XFERMODE_NONE,
    SDPROT_XFERMODE_READ_SINGLE,
    SDPROT_XFERMODE_READ_MULTI,
    SDPROT_XFERMODE_WRITE_SINGLE,
    SDPROT_XFERMODE_WRITE_MULTI,
} sdprot_xfermode_t;

typedef struct {
    uint8_t             index;          /* Index of SD command */
    sdprot_rtype_t      response_type;  /* Response type of SD command */
    sdprot_xfermode_t   transfer_mode;  /* Transfer mode (write/read, single/multi-block)*/
} sdprot_cmd_t;

/* Block size for response to CMD6 (512 bytes) */
#define SDPROT_SWITCH_FUNC_BLOCKSIZE        64

/** CMD0: Resets all cards to idle state */
#define SDPROT_CMD0_GO_IDLE_STATE           ((sdprot_cmd_t){  0, SDPROT_R0  })
/** CMD2: Asks any card to send the CID numbers on the CMD line (any card that is connected to the host will respond). */
#define SDPROT_CMD2_ALL_SEND_CID            ((sdprot_cmd_t){  2, SDPROT_R2  })
/** CMD3: Ask the card to publish a new relative address (RCA). */
#define SDPROT_CMD3_SEND_RELATIVE_ADDR      ((sdprot_cmd_t){  3, SDPROT_R6  })
/** CMD6: Checks switchable function (mode 0) and switch card function (mode 1). */
#define SDPROT_CMD6_SWITCH_FUNC             ((sdprot_cmd_t){  6, SDPROT_R1, SDPROT_XFERMODE_READ_SINGLE  })
/** CMD7: Command toggles a card between the stand-by and transfer states or between the programming and disconnect states. */
#define SDPROT_CMD7_SELECT_CARD             ((sdprot_cmd_t){  7, SDPROT_R1B  })
/** CMD7: Command toggles a card between the stand-by and transfer states or between the programming and disconnect states. */
#define SDPROT_CMD7_DESELECT_CARD           ((sdprot_cmd_t){  7, SDPROT_R1 })
/** CMD8: Sends SD Memory Card interface condition, which includes the host supply voltage information and asks the card whether card supports voltage. */
#define SDPROT_CMD8_SEND_IF_COND            ((sdprot_cmd_t){  8, SDPROT_R7  })
/** CMD9: Addressed card sends its card-specific data (CSD) on the CMD line. */
#define SDPROT_CMD9_SEND_CSD                ((sdprot_cmd_t){  9, SDPROT_R2  })
/** CMD13: Addressed card sends its status register. */
#define SDPROT_CMD13_SEND_STATUS            ((sdprot_cmd_t){ 13, SDPROT_R1  })
/** CMD16: (Standard Capacity SD only) This commands sets the block length (in bytes) for read/write/lock commands. Default block length is fixed to 512 Bytes. */
#define SDPROT_CMD16_SET_BLOCKLEN           ((sdprot_cmd_t){ 16, SDPROT_R1  })
/** CMD17: Reads a single block. */
#define SDPROT_CMD17_READ_SINGLE_BLOCK      ((sdprot_cmd_t){ 17, SDPROT_R1, SDPROT_XFERMODE_READ_SINGLE  })
/** CMD18: Reads multiple blocks. */
#define SDPROT_CMD18_READ_MULTIPLE_BLOCK    ((sdprot_cmd_t){ 18, SDPROT_R1, SDPROT_XFERMODE_READ_MULTI   })
/** CMD24: Writes a single block. */
#define SDPROT_CMD24_WRITE_BLOCK            ((sdprot_cmd_t){ 24, SDPROT_R1, SDPROT_XFERMODE_WRITE_SINGLE })
/** CMD25: Writes multiple blocks. */
#define SDPROT_CMD25_WRITE_MULTIPLE_BLOCK   ((sdprot_cmd_t){ 25, SDPROT_R1, SDPROT_XFERMODE_WRITE_MULTI  })
/** CMD32: Sets the address of the first write block to be erased. */
#define SDPROT_CMD32_ERASE_WR_BLK_START     ((sdprot_cmd_t){ 32, SDPROT_R1  })
/** CMD33: Sets the address of the last write block of the contiguous range to be erased. */
#define SDPROT_CMD33_ERASE_WR_BLK_END       ((sdprot_cmd_t){ 33, SDPROT_R1  })
/** CMD38: Erase blocks in the provided range. */
#define SDPROT_CMD38_ERASE                  ((sdprot_cmd_t){ 38, SDPROT_R1B })
/** CMD55: Indicates to the card that the next command is an application-specific commands rather than a standard command. */
#define SDPROT_CMD55_APP_CMD                ((sdprot_cmd_t){ 55, SDPROT_R1  })
/** ACMD6: Defines the data bus width to be used for data transfer. The allowed data bus widths are given in the SCR register. */
#define SDPROT_ACMD6_SET_BUS_WIDTH          ((sdprot_cmd_t){  6, SDPROT_R1  })
/** ACMD41: Sends host capacity support information (HCS) and asks the accessed card to send its operating condition register (OCR) in the response on the CMD line. */
#define SDPROT_ACMD41_SEND_OP_COND          ((sdprot_cmd_t){ 41, SDPROT_R3  })

#endif /* SDHC_PROTOCOL_H */