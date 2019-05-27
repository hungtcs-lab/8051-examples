#include <stdio.h>
#include <mcs51/8051.h>
#include "sd.h"
#include "delay.h"
#include "serial.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  uint8_t i;
  uint8_t r1;
  SD_Card card;
  SD_CSD_V1 csd_v1;

  serial_init();
  r1 = sd_init(&card);

  switch(r1)
  {
    case 0x00:
    {
      printf("success\n");
      printf("card type is %d\n", card.type);
      r1 = sd_read_csd_v1(&csd_v1);
      printf("r1 is %d\n", r1);

      printf("csd CSD_STRUCTURE: 0x%02X\n", csd_v1.CSD_STRUCTURE);
      printf("csd TAAC: 0x%02X\n", csd_v1.TAAC);
      printf("csd NSAC: 0x%02X\n", csd_v1.NSAC);
      printf("csd TRAN_SPEED: 0x%02X\n", csd_v1.TRAN_SPEED);
      printf("csd CCC: 0x%02X\n", csd_v1.CCC);
      printf("csd READ_BL_LEN: 0x%02X\n", csd_v1.READ_BL_LEN);
      printf("csd READ_BL_PARTIAL: 0x%02X\n", csd_v1.READ_BL_PARTIAL);
      printf("csd WRITE_BLK_MISALIGN: 0x%02X\n", csd_v1.WRITE_BLK_MISALIGN);
      printf("csd READ_BLK_MISALIGN: 0x%02X\n", csd_v1.READ_BLK_MISALIGN);
      printf("csd DSR_IMP: 0x%02X\n", csd_v1.DSR_IMP);
      printf("csd C_SIZE: 0x%02X\n", csd_v1.C_SIZE);
      printf("csd VDD_R_CURR_MIN: 0x%02X\n", csd_v1.VDD_R_CURR_MIN);
      printf("csd VDD_R_CURR_MAX: 0x%02X\n", csd_v1.VDD_R_CURR_MAX);
      printf("csd VDD_W_CURR_MIN: 0x%02X\n", csd_v1.VDD_W_CURR_MIN);
      printf("csd VDD_W_CURR_MAX: 0x%02X\n", csd_v1.VDD_W_CURR_MAX);
      printf("csd C_SIZE_MULT: 0x%02X\n", csd_v1.C_SIZE_MULT);
      printf("csd ERASE_BLK_EN: 0x%02X\n", csd_v1.ERASE_BLK_EN);
      printf("csd SECTOR_SIZE: 0x%02X\n", csd_v1.SECTOR_SIZE);
      printf("csd WP_GRP_SIZE: 0x%02X\n", csd_v1.WP_GRP_SIZE);
      printf("csd WP_GRP_ENABLE: 0x%02X\n", csd_v1.WP_GRP_ENABLE);
      printf("csd R2W_FACTOR: 0x%02X\n", csd_v1.R2W_FACTOR);
      printf("csd WRITE_BL_LEN: 0x%02X\n", csd_v1.WRITE_BL_LEN);
      printf("csd WRITE_BL_PARTIAL: 0x%02X\n", csd_v1.WRITE_BL_PARTIAL);
      printf("csd FILE_FORMAT_GRP: 0x%02X\n", csd_v1.FILE_FORMAT_GRP);
      printf("csd COPY: 0x%02X\n", csd_v1.COPY);
      printf("csd PERM_WRITE_PROTECT: 0x%02X\n", csd_v1.PERM_WRITE_PROTECT);
      printf("csd TMP_WRITE_PROTECT: 0x%02X\n", csd_v1.TMP_WRITE_PROTECT);
      printf("csd FILE_FORMAT: 0x%02X\n", csd_v1.FILE_FORMAT);
      printf("csd CRC: 0x%02X\n", csd_v1.CRC);

      printf("\n\n");
      printf("memory capacity: %ld\n", sd_get_memory_capacity(&csd_v1));

      break;
    }
    case 0x01:
    {
      printf("timeout\n");
      break;
    }
    case 99:
    {
      printf("no sd card\n");
      break;
    }
    default:
      break;
  }

  while(1)
  {

  }
}
