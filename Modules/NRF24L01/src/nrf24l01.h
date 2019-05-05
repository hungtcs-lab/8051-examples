#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "spi.h"
#include "config.h"
#include <stdint.h>
#include <mcs51/8051.h>

#define R_REGISTER        0x00    // 读寄存器。5位存储器映射地址
#define W_REGISTER        0x20    // 写寄存器。5位存储器映射地址，仅可在断电或待机模式下执行
#define R_RX_PAYLOAD      0x61    // 读取RX负载。1-32个字节。读操作将始终从字节0开始。有效载荷将在读取后从FIFO中删除。 用于RX模式
#define W_TX_PAYLOAD      0xA0    // 写入TX负载。1-32字节。写操作始终从字节0开始。用于TX模式
#define FLUSH_TX          0xE1    // 刷新TX FIFO，用于TX模式
#define FLUSH_RX          0xE2    // 刷新RX FIFO，用于RX模式，在传输确认期间不应执行（确认包不会完成）。
#define REUSE_TX_PL       0xE3    // 用于PTX设备。重用最后发送的有效负载。 只要CE为高，就会重复发送数据包。在执行W_TX_PAYLOAD或FLUSH TX之前，TX有效负载重用处于活动状态。 在包传输期间，不得激活或停用TX有效载荷重用
#define NOP               0xFF    // 没有操作。 可能用于读取STATUS寄存器

#define CONFIG            0x00    // 配置寄存器
#define EN_AA             0x01    // 启用“自动确认”功能，禁用此功能以与nRF2401兼容
#define EN_RXADDR         0x02    // 启用RX地址
#define SETUP_AW          0x03    // 地址宽度的设置（所有数据管道通用）
#define SETUP_RETR        0x04    // 自动重传的设置
#define RF_CH             0x05    // 射频频道
#define RF_SETUP          0x06    // 射频设置寄存器
#define STATUS            0x07    // 状态寄存器（与MOSI引脚上施加的SPI指令字并行，STATUS寄存器在MISO引脚上串行移出）
#define OBSERVE_TX        0x08    // 传输观察寄存器
#define CD                0x09    // 载波检测
#define RX_ADDR_P0        0x0A    // 接收地址数据管道0。最大长度为5个字节。
#define RX_ADDR_P1        0x0B    // 接收地址数据管道1。最大长度为5个字节。
#define RX_ADDR_P2        0x0C    // 接收地址数据管道2。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define RX_ADDR_P3        0x0D    // 接收地址数据管道3。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define RX_ADDR_P4        0x0E    // 接收地址数据管道4。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define RX_ADDR_P5        0x0F    // 接收地址数据管道5。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define TX_ADDR           0x10    // 发送地址。仅用于PTX设备。如果这是启用了增强型ShockBurstTM的PTX设备，则将RX_ADDR_P0设置为等于此地址以处理自动确认。
#define RX_PW_P0          0x11    // 数据管道0中的RX有效负载中的字节数（1到32个字节）
#define RX_PW_P1          0x12    // 数据管道1中的RX有效负载中的字节数（1到32个字节）
#define RX_PW_P2          0x13    // 数据管道2中的RX有效负载中的字节数（1到32个字节）
#define RX_PW_P3          0x14    // 数据管道3中的RX有效负载中的字节数（1到32个字节）
#define RX_PW_P4          0x15    // 数据管道4中的RX有效负载中的字节数（1到32个字节）
#define RX_PW_P5          0x16    // 数据管道1中的RX有效负载中的字节数（1到32个字节）
#define FIFO_STATUS       0x17    // FIFO状态寄存器

#define TX_ADDR_WIDTH     5
#define TX_PAYLOAD_WIDTH  32
#define RX_PAYLOAD_WIDTH  32

/**
 * 读取寄存器中的数据
 *
 * @param address   寄存器地址
 * @param data      读取寄存器返回的数据
 * @param length    读取的字节长度
 * @return uint8_t  状态寄存器数据
 */
uint8_t nrf24_read_register(uint8_t address, uint8_t *data, uint8_t length);

/**
 * 对寄存器进行写入
 *
 * @param address   寄存器地址
 * @param data      写入寄存器的数据
 * @param length    写入的字节长度
 * @return uint8_t  状态寄存器数据
 */
uint8_t nrf24_write_register(uint8_t address, uint8_t *data, uint8_t length);

uint8_t nrf24_read_register_byte(uint8_t address, uint8_t *data);
uint8_t nrf24_write_register_byte(uint8_t address, uint8_t data);

uint8_t nrf24_device_check(void);

void nrf24_listen(uint8_t *address);
void nrf24_transmit(uint8_t *address, uint8_t *data);

/**
 * 判断是否接收到数据
 *
 * @return uint8_t
 */
uint8_t nrf24_available(void);
void nrf24_read_received_data(uint8_t *rx_data);

#endif // __NRF24L01_H__
