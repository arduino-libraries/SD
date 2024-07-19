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

    References:
    [1] Physical Layer Simplified Specification v9.00, Aug 22 2022. 
        Available: https://www.sdcard.org/downloads/pls/
*/

#ifndef SDHC_REGISTERS_H
#define SDHC_REGISTERS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --- Status ---
 */

/* Card CURRENT_STATE [1, Tab. 4-42] */
typedef enum {
    SDHC_STATE_IDLE     = 0x00,
    SDHC_STATE_READY    = 0x01,
    SDHC_STATE_IDENT    = 0x02,
    SDHC_STATE_STBY     = 0x03,
    SDHC_STATE_TRAN     = 0x04,
    SDHC_STATE_DATA     = 0x05,
    SDHC_STATE_RCV      = 0x06,
    SDHC_STATE_PRG      = 0x07,
    SDHC_STATE_DIS      = 0x08,
} sdhc_state_t;

/* Card Status - Short for response R6 [1, Tab. 4-39] */
typedef struct {
    /*!< bit:  0.. 1  Reserved for manufacturer test mode */
    uint8_t :2;
    /*!< bit:      2  Reserved for application specific commands */              
    uint8_t :1;
    /*!< bit:      3  Error in the sequence of the authentication process */	                
    uint8_t AKE_SEQ_ERROR:1;
    /*!< bit:      4  Reserved for SD I/O Card */     
    uint8_t :1;
    /*!< bit:      5  The card will expect ACMD, or an indication that the command has been interpreted as ACMD */             
    uint8_t APP_CMD:1;
    /*!< bit:      6  Extension Functions may set this bit to get host to deal with events */ 
    uint8_t FX_EVENT:1;
    /*!< bit:      7  Reserved */
    uint8_t :1;           
    /*!< bit:      8  Corresponds to buffer empty signaling on the bus */          
    uint8_t READY_FOR_DATA:1;
    /*!< bit:  9..12  The state of the card when receiving the command.
                        If the command execution causes a state change, it will be visible to the host
                        in the response to the next command. */
    sdhc_state_t CURRENT_STATE:4;
    /*!< bit:     13 (19)  A general or unknown error occurred during the operation */
    uint8_t ERROR:1;
    /*!< bit:     14 (22)  Command not legal for the card state */
    uint8_t ILLEGAL_COMMAND:1;
    /*!< bit:     15 (23)  The CRC check of the previous command failed */
    uint8_t COM_CRC_ERROR:1;
} sdhc_card_status_short_t;

/* Card Status [1, Tab. 4-42] */
typedef struct {
    /*!< bit:  0.. 1  Reserved for manufacturer test mode */
    uint8_t :2;
    /*!< bit:      2  Reserved for application specific commands */              
    uint8_t :1;
    /*!< bit:      3  Error in the sequence of the authentication process */	                
    uint8_t AKE_SEQ_ERROR:1;
    /*!< bit:      4  Reserved for SD I/O Card */     
    uint8_t :1;
    /*!< bit:      5  The card will expect ACMD, or an indication that the command has been interpreted as ACMD */             
    uint8_t APP_CMD:1;
    /*!< bit:      6  Extension Functions may set this bit to get host to deal with events */ 
    uint8_t FX_EVENT:1;
    /*!< bit:      7  Reserved */
    uint8_t :1;           
    /*!< bit:      8  Corresponds to buffer empty signaling on the bus */          
    uint8_t READY_FOR_DATA:1;
    /*!< bit:  9..12  The state of the card when receiving the command.
                        If the command execution causes a state change, it will be visible to the host
                        in the response to the next command. */
    sdhc_state_t CURRENT_STATE:4;
    /*!< bit:     13  An erase sequence was cleared before executing because an 
                        out of erase sequence command was received. */
    uint8_t ERASE_RESET:1;
    /*!< bit:     14  The command has been executed without using the internal ECC. */
    uint8_t CARD_ECC_DISABLED:1;
    /*!< bit:     15  Set when only partial address space was erased due to existing 
                        write protected blocks or the temporary write protected or write 
                        protected until power cyckle or permanent write protected card
                        was erased. */
    uint8_t WP_ERASE_SKIP:1;
    /*!< bit:     16  Can be either one of the following errors: 
                        - The read only section of the CSD does not match the card content. 
                        - An attempt to reverse the copy (set as original) or permanent WP
                        (unprotected) bits were made. */
    uint8_t CSD_OVERWRITE:1;
    /*!< bit:     17  Reserved for DEFERRED_RESPONSE (refer to eSD addendum) */
    uint8_t :1;
    /*!< bit:     18  Reserved */
    uint8_t :1;
    /*!< bit:     19  A general or unknown error occurred during the operation */
    uint8_t ERROR:1;
    /*!< bit:     20  Internal card controller error */
    uint8_t CC_ERROR:1;
    /*!< bit:     21  Card internal ECC was applied but failed to correct the data */
    uint8_t CARD_ECC_FAILED:1;
    /*!< bit:     22  Command not legal for the card state */
    uint8_t ILLEGAL_COMMAND:1;
    /*!< bit:     23  The CRC check of the previous command failed */
    uint8_t COM_CRC_ERROR:1;
    /*!< bit:     24  Set when a sequence or password error has been detected in 
                        lock/unlock card command */
    uint8_t LOCK_UNLOCK_FAILED:1;
    /*!< bit:     25  When set, signals that the card is locked by the host */
    uint8_t CARD_IS_LOCKED:1;
    /*!< bit:     26  Set when the host attempts to write to a protected block or to the 
                        temporary write protected card or write protected until power cycle
                        card ot permanent write protected card */
    uint8_t WP_VIOLATION:1;
    /*!< bit:     27  An invalid selection of write-blocks for erase occurred */
    uint8_t ERASE_PARAM:1;
    /*!< bit:     28  An error in the sequence of erase commands occurred */
    uint8_t ERASE_SEQ_ERROR:1;
    /*!< bit:     29  The transferrred block length is not allowed for this card, or the number
                        of transferred bytes does not match the block length. */
    uint8_t BLOCK_LEN_ERROR:1;
    /*!< bit:     30  A misaligned address which did not match the block length was used in
                        the command */
    uint8_t ADDRESS_ERROR:1;
    /*!< bit:     31  The command's argument was out of the allowed range for this card */
    uint8_t OUT_OF_RANGE:1;
} sdhc_card_status_t;

/*
 * --- Command arguments ---
 */

#define SDHC_CMD6_NO_INFLUENCE 0xF

/* Function group 1: Access Mode [1, Tab. 4-11] */
typedef enum {
    SDHC_ACCESS_MODE_DEFAULT_SDR12  = 0x0,
    SDHC_ACCESS_MODE_HIGHSPEED_SDR25  = 0x1,
    SDHC_ACCESS_MODE_SDR50  = 0x2,
    SDHC_ACCESS_MODE_SDR104 = 0x3,
    SDHC_ACCESS_MODE_DDR50  = 0x4,
    SDHC_ACCESS_MODE_NO_INFLUENCE = 0xF
} sdhc_access_mode_t;

/* CMD6 (SWITCH_FUNCTION) command arguments [1, Tab. 4-11] */
typedef union {
    struct {
        sdhc_access_mode_t ACCESS_MODE:4;   /*!< bit:  0.. 3  Group 1: Access mode / Bus speed mode */
        uint8_t            GROUP2:4;        /*!< bit:  4.. 7  Group 2: Unimplemented */
        uint8_t            GROUP3:4;        /*!< bit:  8..11  Group 3: Unimplemented */
        uint8_t            GROUP4:4;        /*!< bit: 12..15  Group 4: Unimplemented */
        uint8_t            GROUP5:4;        /*!< bit: 16..19  Group 5: Unimplemented */
        uint8_t            GROUP6:4;        /*!< bit: 20..23  Group 6: Unimplemented */
    } bit;
    uint32_t reg;
} sdhc_cmd6_args_t;

/* Voltage accepted [1, Tab. 4-18][1, Tab. 4-41] */
typedef enum {
    VOLT_ACCEPT_2V7_3V6 = 0x1, /* 2.7-3.6V */
    VACC_LOWV_RESERVED  = 0x2, /* Reserved for low voltage range */
} sdhc_volt_t;

/* CMD8 (SEND_IF_COND) command arguments [1, Tab. 4-18] */
typedef union {
    struct {
        uint8_t  CHECK_PTN:8;               /*!< bit:  8..15  Check pattern */
        sdhc_volt_t V_SUPPLIED:4;           /*!< bit: 16..19  Voltage supplied    */
        uint8_t  PCIE_AVAILABLE:1;          /*!< bit:     20  PCIe Availability   */
        uint8_t  PCIE_1V2_SUPPORTED:1;      /*!< bit:     20  PCIe 1.2V Support         */
        uint32_t :18;                       /*!< bit: 21..39  Reserved                  */
    } bit;
    uint32_t reg;
} sdhc_args_cmd8_t;

typedef enum {
    SDHC_ERASE_MODE_NORMAL = 0,
    SDHC_ERASE_MODE_DISCARD = 1,
    SDHC_ERASE_MODE_FULE = 2,
} sdhc_erase_mode_t;

/*
 * --- Reponses ---
 */

/* SD Card response type R6 (Table 4-32)  */
typedef struct {
    sdhc_card_status_short_t status;        /*!< bit:  0..15  Card status bits          */
    uint16_t rca:16;                        /*!< bit: 16..31  Card status bits          */
} sdhc_resp_r6_t;                                                     

/* Card interface condition [1, Tab. 4-40] */
typedef union {
    struct {
        uint8_t  CHECK_PTN:8;               /*!< bit:  8..15  Echo-back of Check pattern */
        sdhc_volt_t V_ACCEPT:4;             /*!< bit: 16..19  Voltage accepted           */
        uint8_t  PCIE_AVAILABLE:1;          /*!< bit:     20  PCIe Availability/Response */
        uint8_t  PCIE_1V2_SUPPORTED:1;      /*!< bit:     20  PCIe 1.2V Support          */
        uint32_t :18;                       /*!< bit: 21..39  Reserved                   */
    } bit;
    uint32_t reg;
} sdhc_resp_r7_t;

/*
 * --- Registers ---
 */

/* VDD Voltage Window [1, Tab. 5-1]*/
typedef struct {
    uint8_t :7;                 /*!< bit:  0.. 6  reserved */
    uint8_t :1;                 /*!< bit:      7  reserved for Low Voltage Range */
    uint8_t :7;                 /*!< bit:  8..14  reserved */
    uint8_t VDD_27_28:1;        /*!< bit:     15  2.7-2.8 */
    uint8_t VDD_28_29:1;        /*!< bit:     16  2.8-2.9 */
    uint8_t VDD_29_30:1;        /*!< bit:     17  2.9-3.0 */
    uint8_t VDD_30_31:1;        /*!< bit:     18  3.0-3.1 */
    uint8_t VDD_31_32:1;        /*!< bit:     19  3.1-3.2 */
    uint8_t VDD_32_33:1;        /*!< bit:     20  3.2-3.3 */
    uint8_t VDD_33_34:1;        /*!< bit:     21  3.3-3.4 */
    uint8_t VDD_34_35:1;        /*!< bit:     22  3.4-3.5 */
    uint8_t VDD_35_36:1;        /*!< bit:     23  3.5-3.6 */
} sdhc_vdd_v_window_t;

/* OCR Register [1, Tab. 5-1] */
typedef union {
    struct {
        sdhc_vdd_v_window_t voltage_window; /*!< bit:  0..23  VDD Voltage Window */
        uint8_t S18A:1;                     /*!< bit:     24  Switching to 1.8V accepted */
        uint8_t :2;                         /*!< bit: 25..26  Reserved */
        uint8_t :1;                         /*!< bit:     27  (unimplemented) Over 2TB support status (SDUC-only) */
        uint8_t :1;                         /*!< bit:     28  Reserved */
        uint8_t :1;                         /*!< bit:     29  (unimplemented) UHS-II card Status */
        uint8_t CCS:1;                      /*!< bit:     30  Card Capacity Status (CCS) */
        uint8_t POWER_UP_BUSY:1;            /*!< bit:     31  Card power up status bit (busy) */
    } bit;
    uint32_t reg;
} sdhc_reg_ocr_t;

/* CID Register (Table 5-2) */
typedef struct __attribute__((__packed__)) {
                                /*!< bit:   0..  7 Reserved */
        uint16_t MDT:12;        /*!< bit:   8.. 19 Manufacturing date */
        uint8_t :4;             /*!< bit:  20.. 23 Reserved */
        uint32_t PSN:32;        /*!< bit:  24.. 55 Product Serial Number */
        uint8_t PRV:8;          /*!< bit:  56.. 63 Product Revision */
        uint8_t PNM[5];         /*!< bit:  64..103 Product Name */
        uint16_t OID;           /*!< bit: 104..119 OEM/Application ID */
        uint8_t MID:8;          /*!< bit: 120..127 Manufacturer ID */
} sdhc_reg_cid_t;

/* CSD_STRUCTURE (Table 5-3) */
typedef enum {
    SDHC_CSD_STRUCTURE_SD_V1 = 0x0,
    SDHC_CSD_STRUCTURE_SD_V2 = 0x1,
    SDHC_CSD_STRUCTURE_SD_V3 = 0x2,
} sdhc_csd_structure_t;

typedef union {
    struct __attribute__((__packed__)) {        /* CSD Version 1.0 (Table 5-4) */
                                                /*!< bit:   0..  7 */
        uint16_t :2;                            /*!< bit:   7..  9 Reserved */
        uint8_t  FILE_FORMAT:2;                 /*!< bit:  10.. 11 File format */
        uint8_t  TMP_WRITE_PROTECT:1;           /*!< bit:       12 Temporary write protection */
        uint8_t  PERM_WRITE_PROTECT:1;          /*!< bit:       13 Permanent write protection */
        uint8_t  COPY:1;                        /*!< bit:       14 Copy flag */
        uint8_t  FILE_FORMAT_GRP:1;             /*!< bit:       15 File format group */
        uint8_t  :5;                            /*!< bit:  16.. 20 Reserved */
        uint8_t  WRITE_BL_PARTIAL:1;            /*!< bit:       21 Partial blocks for write allowed */
        uint8_t  WRITE_BL_LEN:4;                /*!< bit:  22.. 25 Max. write data block length */
        uint8_t  R2W_FACTOR:3;                  /*!< bit:  26.. 28 Write speed factor */
        uint8_t  :2;                            /*!< bit:  29.. 30 Reserved */
        uint8_t  WP_GRP_ENABLE:1;               /*!< bit:       31 Write protect group enable */
        uint8_t  WP_GRP_SIZE:7;                 /*!< bit:  32.. 38 Write protect group size */
        uint8_t  SECTOR_SIZE:7;                 /*!< bit:  39.. 45 Erase sector size*/
        uint8_t  ERASE_BLK_EN:1;                /*!< bit:       46 Erase single block enable */
        uint8_t  C_SIZE_MULT:3;                 /*!< bit   47.. 49 Device size multiplier */
        uint8_t  VDD_W_CURR_MAX:3;              /*!< bit   50.. 52 Max. write current @VDD max */
        uint8_t  VDD_W_CURR_MIN:3;              /*!< bit   53.. 55 Max. write current @VDD min */
        uint8_t  VDD_R_CURR_MAX:3;              /*!< bit   56.. 58 Max. read current @VDD max */
        uint8_t  VDD_R_CURR_MIN:3;              /*!< bit   59.. 61 Max. read current @VDD min */
        uint16_t C_SIZE:12;                     /*!< bit:  62.. 73 Device size */
        uint8_t  :2;                            /*!< bit:  74.. 75 Reserved */
        uint8_t  DSR_IMP:1;                     /*!< bit:       76 DSR Implemented */ 
        uint8_t  READ_BLK_MISALIGN:1;           /*!< bit:       77 Read block misalignment */
        uint8_t  WRITE_BLK_MISALIGN:1;          /*!< bit:       78 Write block misalignment */
        uint8_t  READ_BL_PARTIAL:1;             /*!< bit:       79 (=1) Partial blocks for read allowed */
        uint8_t  READ_BL_LEN:4;                 /*!< bit:  80.. 83 Max. read data block length */
        uint16_t CCC:12;                        /*!< bit:  84.. 95 (=0b01X110110101) Card command classes */
        uint8_t  TRAN_SPEED:8;                  /*!< bit:  96..103 Max. data transfer rate */
        uint8_t  NSAC:8;                        /*!< bit: 104..111 Data read access-time in CLK cycles (NSAC*100) */
        uint8_t  TAAC:8;                        /*!< bit: 112..119 Data read access-time */
        uint8_t  :6;                            /*!< bit: 120..125 Reserved */
        sdhc_csd_structure_t CSD_STRUCTURE:2;   /*!< bit: 126..127 (=0b00) CSD Structure */
    } sd_v1;
    struct __attribute__((__packed__)) {        /* CSD Version 2.0 (Table 5-16) */
                                                /*!< bit:   0..  7 */
        uint16_t :2;                            /*!< bit:   7..  9 Reserved */
        uint8_t  _FILE_FORMAT:2;                /*!< bit:  10.. 11 (0b00) File format */
        uint8_t  TMP_WRITE_PROTECT:1;           /*!< bit:       12 Temporary write protection */
        uint8_t  PERM_WRITE_PROTECT:1;          /*!< bit:       13 Permanent write protection */
        uint8_t  COPY:1;                        /*!< bit:       14 Copy flag */
        uint8_t  _FILE_FORMAT_GRP:1;            /*!< bit:       15 (=0) File format group */
        uint8_t  :5;                            /*!< bit:  16.. 20 Reserved */
        uint8_t  _WRITE_BL_PARTIAL:1;           /*!< bit:       21 (=0) Partial blocks for write allowed */
        uint8_t  _WRITE_BL_LEN:4;               /*!< bit:  22.. 25 (=9) Max. write data block length */
        uint8_t  _R2W_FACTOR:3;                 /*!< bit:  26.. 28 (=0b010) Write speed factor */
        uint8_t  :2;                            /*!< bit:  29.. 30 Reserved */
        uint8_t  _WP_GRP_ENABLE:1;              /*!< bit:       31 (=0) Write protect group enable */
        uint8_t  _WP_GRP_SIZE:7;                /*!< bit:  32.. 38 (=0b0000000) Write protect group size */
        uint8_t  _SECTOR_SIZE:7;                /*!< bit:  39.. 45 (=0x7F) Erase sector size*/
        uint8_t  _ERASE_BLK_EN:1;               /*!< bit:       46 (=1) Erase single block enable */
        uint8_t  :1;                            /*!< bit:       47 Reserved */
        uint32_t C_SIZE:22;                     /*!< bit:  48.. 69 Device size */
        uint8_t  :6;                            /*!< bit:  70.. 75 Reserved */
        uint8_t  DSR_IMP:1;                     /*!< bit:       76 DSR Implemented */ 
        uint8_t  _READ_BLK_MISALIGN:1;          /*!< bit:       77 (=0) Read block misalignment */
        uint8_t  _WRITE_BLK_MISALIGN:1;         /*!< bit:       78 (=0) Write block misalignment */
        uint8_t  _READ_BL_PARTIAL:1;            /*!< bit:       79 (=0) Partial blocks for read allowed */
        uint8_t  _READ_BL_LEN:4;                /*!< bit:  80.. 83 (=9) Max. read data block length */
        uint16_t CCC:12;                        /*!< bit:  84.. 95 (=0b01X110110101) Card command classes */
        uint8_t  _TRAN_SPEED:8;                 /*!< bit:  96..103 (=0x32, 0x5A, 0x0B or 0x2B) Max. data transfer rate */
        uint8_t  _NSAC:8;                       /*!< bit: 104..111 (=0x00) Data read access-time in CLK cycles (NSAC*100) */
        uint8_t  _TAAC:8;                       /*!< bit: 112..119 (=0x0E) Data read access-time */
        uint8_t  :6;                            /*!< bit: 120..125 Reserved */
        sdhc_csd_structure_t CSD_STRUCTURE:2;   /*!< bit: 126..127 (=0b01) CSD Version 2.0 Structure */
    } sd_v2;
} sdhc_reg_csd_t;

#ifdef __cplusplus
}
#endif

#endif /* SDHC_REGISTERS_H */