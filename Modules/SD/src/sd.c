#include "sd.h"

uint8_t sd_send_command_hold_on(uint8_t command, uint32_t arguments, uint8_t crc)
{
  uint8_t r1;
  uint16_t retry;

  SD_CS = 1;
  spi_transmit(0xFF);
  SD_CS = 0;

  spi_transmit(command | 0x40);
  spi_transmit((uint8_t)(arguments >> 24));
  spi_transmit((uint8_t)(arguments >> 16));
  spi_transmit((uint8_t)(arguments >> 8));
  spi_transmit((uint8_t)arguments);
  // spi_transmit(crc | 0x01);
  spi_transmit(crc);

  retry = 0;
  do
  {
    r1 = spi_transmit(0xFF);
    retry ++;
  } while(r1 == 0xFF && retry < 0xFFF);

  return r1;
}

uint8_t sd_send_command(uint8_t command, uint32_t arguments, uint8_t crc)
{
  uint8_t r1;

  r1 = sd_send_command_hold_on(command, arguments, crc);
  SD_CS = 1;
  spi_transmit(0xFF);

  return r1;
}

uint8_t sd_init(SD_Card * card)
{
  uint8_t i;
  uint8_t r1;
  uint16_t retry;

  SD_CS = 0;

  delay_ms(5);
  for(i=0; i<10; i++)
  {
    spi_transmit(0xFF);
  }

  retry = 0;
  do
  {
    r1 = sd_send_command(CMD0, 0x00, 0x95);
    retry ++;
  } while(r1 != 0x01 && retry < 0xFF);

  r1 = sd_send_command_hold_on(CMD8, 0x1AA, 0x87);

  if(r1 == 0x05)
  {
    card -> type = SD_TYPE_V1_0;

    SD_CS = 1;
    spi_transmit(0xFF);

    do
    {
      r1 = sd_send_command(CMD55, 0x00, 0x00);
      if(r1 != 0x01)
        return r1;
      r1 = sd_send_command(ACMD41, 0x00, 0x00);
      retry++;
    } while(retry < 0xFFF && r1 != 0x00);

    spi_transmit(0xFF);

    // 禁用CRC校验
    r1 = sd_send_command(CMD59, 0x00, 0x95);
    if(r1 != 0x00)
      return r1;
    // 设置Sector Size
    r1 = sd_send_command(CMD16, 512, 0x95);
    if(r1 != 0x00)
      return r1;
  }
  else if(r1 == 0x01)
  {

  }

  return 0;
}

uint8_t sd_read_data(uint8_t *data, uint16_t length)
{
  uint8_t i;
  uint8_t r1;
  uint16_t retry;

  SD_CS = 0;

  retry = 0;
  do
  {
    r1 = spi_transmit(0xFF);
    if(retry++ > 0xFFF)
    {
      SD_CS = 1;
      return 1;
    }
  } while(r1 != 0xFE);

  for(i=0; i<length; i++)
  {
    *(data + i) = spi_transmit(0xFF);
  }

  spi_transmit(0xFF);
  spi_transmit(0xFF);

  SD_CS = 1;
  spi_transmit(0xFF);

  return 0;
}

uint8_t sd_read_cid(uint8_t *cid)
{
  uint8_t r1;
  r1 = sd_send_command_hold_on(CMD10, 0x00, 0xFF);
  if(r1 != 0x00)
  {
    SD_CS = 1;
    spi_transmit(0xFF);
    return r1;
  }
  r1 = sd_read_data(cid, 16);
  SD_CS = 1;
  spi_transmit(0xFF);
  return r1;
}

uint8_t sd_read_csd_v1(SD_CSD_V1 *csd)
{
  uint8_t r1;
  uint8_t data[16];
  r1 = sd_send_command_hold_on(CMD9, 0x00, 0xFF);
  if(r1)
  {
    SD_CS = 1; spi_transmit(0xFF);
    return r1;
  }
  r1 = sd_read_data(data, 16);
  SD_CS = 1; spi_transmit(0xFF);

  csd -> CSD_STRUCTURE = data[0] >> 6;
  csd -> TAAC = data[1];
  csd -> NSAC = data[2];
  csd -> TRAN_SPEED = data[3];
  csd -> CCC = (data[4] << 4) | (data[5] >> 4);
  csd -> READ_BL_LEN = data[5] & 0x0F;
  csd -> READ_BL_PARTIAL = data[6] >> 7;
  csd -> WRITE_BLK_MISALIGN = (data[6] >> 6) & 0x01;
  csd -> READ_BLK_MISALIGN = (data[6] >> 5) & 0x01;
  csd -> DSR_IMP = (data[6] >> 4) & 0x01;
  csd -> C_SIZE = (((uint16_t)(data[6] & 0x03)) << 10) | (((uint16_t)data[7]) << 2) | (data[8] >> 6);
  csd -> VDD_R_CURR_MIN = (data[8] >> 3) & 0x07;
  csd -> VDD_R_CURR_MAX = data[8] & 0x07;
  csd -> VDD_W_CURR_MIN = (data[9] >> 5) & 0x07;
  csd -> VDD_W_CURR_MAX = (data[9] >> 2) & 0x07;
  csd -> C_SIZE_MULT = ((data[9] & 0x03) << 1) | (data[10] >> 7);
  csd -> ERASE_BLK_EN = (data[10] >> 6) & 0x01;
  csd -> SECTOR_SIZE = ((data[10] << 1) & 0x7F) | (data[11] >> 7);
  csd -> WP_GRP_SIZE = data[11] & 0x7F;
  csd -> WP_GRP_ENABLE = data[12] >> 7;
  csd -> R2W_FACTOR = (data[12] >> 2) & 0x07;
  csd -> WRITE_BL_LEN = ((data[12] & 0x03) << 2) | (data[13] >> 6);
  csd -> WRITE_BL_PARTIAL = (data[13] >> 5) & 0x01;
  csd -> FILE_FORMAT_GRP = data[14] >> 7;
  csd -> COPY = (data[14] >> 6) & 0x01;
  csd -> PERM_WRITE_PROTECT = (data[14] >> 5) & 0x01;
  csd -> TMP_WRITE_PROTECT = (data[14] >> 4) & 0x01;
  csd -> FILE_FORMAT = (data[14] >> 2) & 0x03;
  csd -> CRC = data[15] >> 1;

  return r1;
}

uint64_t sd_get_memory_capacity(SD_CSD_V1 *csd)
{
  // uint16_t mult;
  // uint64_t blocknr;
  // uint16_t block_len;

  // mult = 1 << ((csd -> C_SIZE_MULT) + 2);
  // blocknr = (((csd -> C_SIZE) + 1) * mult);
  // printf("blocknr: %ld\n", blocknr);
  // block_len = 1 << csd -> READ_BL_LEN;
  // return blocknr * block_len;

  return ((csd -> C_SIZE + 1) * (1 << (csd -> C_SIZE_MULT + 2))) * (1 << csd -> READ_BL_LEN);
}
