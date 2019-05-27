#ifndef __SD_H__
#define __SD_H__

#include <stdio.h>
#include <stdint.h>
#include "spi.h"
#include "delay.h"
#include "config.h"

// Basic Commands (Class 0 And Class 1)
#define CMD0      0x00  // GO_IDLE_STATE
#define CMD1      0x01
#define CMD2      0x02  // ALL_SEND_CID
#define CMD3      0x03  // SEND_RELATIVE_ADDR
#define CMD4      0x04
#define CMD5      0x05
#define CMD6      0x06
#define CMD7      0x07  // SELECT/DESELECT_CARD
#define CMD8      0x08
#define CMD9      0x09  // SEND_CSD
#define CMD10     0x0A  // SEND_CID
#define CMD11     0x0B  // READ_DAT_UNTIL_STOP
#define CMD12     0x0C  // STOP_TRANSMISSION
#define CMD13     0x0D  // SEND_STATUS
#define CMD14     0x0E
#define CMD15     0x0F  // GO_INACTIVE_STATE

// Block Read Commands (Class 2)
#define CMD16     0x10  // SET_BLOCKLEN
#define CMD17     0x11  // READ_SINGLE_BLOCK
#define CMD18     0x12  // READ_MULTIPLE_BLOCK
#define CMD19     0x13
#define CMD20     0x14
#define CMD21     0x15
#define CMD22     0x16
#define CMD23     0x17

// Block Write Commands (Class 4)
#define CMD24     0x18  // WRITE_BLOCK
#define CMD25     0x19  // WRITE_MULTIPLE_BLOCK
#define CMD26     0x1A  // 不適用
#define CMD27     0x1B  // PROGRAM_CSD

// Write Protection (Class 6)
#define CMD28     0x1C  // SET_WRITE_PROT
#define CMD29     0x1D  // CLR_WRITE_PROT
#define CMD30     0x1E  // SEND_WRITE_PROT
#define CMD31     0x1F

// Erase Commands (Class 5)
#define CMD32     0x20  // ERASE_WR_BLK_START
#define CMD33     0x21  // ERASE_WR_BLK_END
#define CMD34     0x22
#define CMD35     0x23
#define CMD36     0x24
#define CMD37     0x25
#define CMD38     0x26  // ERASE
#define CMD39     0x27
#define CMD40     0x28
#define CMD41     0x29

// Lock Card Commands (Class 7)
// SDA可選命令，目前由 SanDisk SD卡支持。
#define CMD42     0x2A
#define CMD43     0x2B
#define CMD44     0x2C
#define CMD45     0x2D
#define CMD46     0x2E
#define CMD47     0x2F
#define CMD48     0x30
#define CMD49     0x31
#define CMD50     0x32
#define CMD51     0x33
#define CMD52     0x34
#define CMD53     0x35
#define CMD54     0x36

// Application Specific Commands (Class 8)
#define CMD55     0x37  // APP_CMD
#define CMD56     0x38  // GEN_CMD
#define CMD57     0x39
#define CMD58     0x3A
#define CMD59     0x3B
#define CMD60     0x3C
#define CMD61     0x3D
#define CMD62     0x3E
#define CMD63     0x3F

// Application Specific Commands Used/Reserved by SD Card
#define ACMD6     0x06  // SET_BUS_WIDTH
#define ACMD13    0x0D  // SD_STATUS
#define ACMD17    0x11
#define ACMD18    0x12
#define ACMD19    0x13
#define ACMD20    0x14
#define ACMD21    0x15
#define ACMD22    0x16  // SEND_NUM_WR_BLOCKS
#define ACMD23    0x17  // SET_WR_BLK_ERASE_COUNT
#define ACMD24    0x18
#define ACMD25    0x19
#define ACMD26    0x1A
#define ACMD38    0x26
#define ACMD39    0x27
#define ACMD40    0x28
#define ACMD41    0x29  // SD_APP_OP_COND
#define ACMD42    0x2A  // SET_CLR_CARD_DETECT
#define ACMD43    0x2B
#define ACMD44    0x2C
#define ACMD45    0x2D
#define ACMD46    0x2E
#define ACMD47    0x2F
#define ACMD48    0x30
#define ACMD49    0x31
#define ACMD51    0x33  // SEND_SCR

#define SD_TYPE_V1_0  0x00

typedef struct __SD_CARD
{
  uint8_t type;
} SD_Card;

typedef struct __SD_CSD_V1
{
  uint8_t CSD_STRUCTURE;
  uint8_t TAAC;
  uint8_t NSAC;
  uint8_t TRAN_SPEED;
  uint16_t CCC;
  uint8_t READ_BL_LEN;
  uint8_t READ_BL_PARTIAL;
  uint8_t WRITE_BLK_MISALIGN;
  uint8_t READ_BLK_MISALIGN;
  uint8_t DSR_IMP;
  uint16_t C_SIZE;
  uint8_t VDD_R_CURR_MIN;
  uint8_t VDD_R_CURR_MAX;
  uint8_t VDD_W_CURR_MIN;
  uint8_t VDD_W_CURR_MAX;
  uint8_t C_SIZE_MULT;
  uint8_t ERASE_BLK_EN;
  uint8_t SECTOR_SIZE;
  uint8_t WP_GRP_SIZE;
  uint8_t WP_GRP_ENABLE;
  uint8_t R2W_FACTOR;
  uint8_t WRITE_BL_LEN;
  uint8_t WRITE_BL_PARTIAL;
  uint8_t FILE_FORMAT_GRP;
  uint8_t COPY;
  uint8_t PERM_WRITE_PROTECT;
  uint8_t TMP_WRITE_PROTECT;
  uint8_t FILE_FORMAT;
  uint8_t CRC;
} SD_CSD_V1;


uint8_t sd_init(SD_Card * card);
// uint8_t sd_read_cid(uint8_t *cid);
// uint8_t sd_read_csd(uint8_t *csd);

uint8_t sd_read_csd_v1(SD_CSD_V1 *csd);
uint64_t sd_get_memory_capacity(SD_CSD_V1 *csd);


#endif // __SD_H__
