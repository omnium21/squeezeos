/*
 *  Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */
#include <linux/init.h>
#include <asm/dma.h>
#include <asm/arch/hardware.h>

#include <linux/device.h>
#include "serial.h"

#define MXC_MMC_BUFFER_ACCESS     0x38
#define MXC_SSI_TX0_REG           0x0
#define MXC_SSI_TX1_REG           0x4
#define MXC_SSI_RX0_REG           0x8
#define MXC_SSI_RX1_REG           0xC
#define MXC_FIRI_TXFIFO           0x14
#define MXC_SDHC_MMC_WML          16
#define MXC_SDHC_SD_WML           64
#define MXC_SSI_TXFIFO_WML        0x4
#define MXC_SSI_RXFIFO_WML        0x6
#define MXC_FIRI_WML              16

typedef struct mxc_sdma_info_entry_s {
	mxc_dma_device_t device;
	mxc_sdma_channel_params_t *chnl_info;
} mxc_sdma_info_entry_t;

static mxc_sdma_channel_params_t mxc_sdma_uart1_rx_params = {
	.chnl_params = {
			.watermark_level = UART1_UFCR_RXTL,
			.per_address = UART1_BASE_ADDR,
			.peripheral_type = UART,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_UART1_RX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART1_RX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart1_tx_params = {
	.chnl_params = {
			.watermark_level = UART1_UFCR_TXTL,
			.per_address = UART1_BASE_ADDR + MXC_UARTUTXD,
			.peripheral_type = UART,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_UART1_TX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART1_TX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart2_rx_params = {
	.chnl_params = {
			.watermark_level = UART2_UFCR_RXTL,
			.per_address = UART2_BASE_ADDR,
			.peripheral_type = UART,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_UART2_RX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART2_RX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart2_tx_params = {
	.chnl_params = {
			.watermark_level = UART2_UFCR_TXTL,
			.per_address = UART2_BASE_ADDR + MXC_UARTUTXD,
			.peripheral_type = UART,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_UART2_TX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART2_TX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart3_rx_params = {
	.chnl_params = {
			.watermark_level = UART3_UFCR_RXTL,
			.per_address = UART3_BASE_ADDR,
			.peripheral_type = UART_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_UART3_RX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART3_RX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart3_tx_params = {
	.chnl_params = {
			.watermark_level = UART3_UFCR_TXTL,
			.per_address = UART3_BASE_ADDR + MXC_UARTUTXD,
			.peripheral_type = UART_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_UART3_TX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART3_TX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart4_rx_params = {
	.chnl_params = {
			.watermark_level = UART4_UFCR_RXTL,
			.per_address = UART4_BASE_ADDR,
			.peripheral_type = UART,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_UART4_RX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART4_RX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_uart4_tx_params = {
	.chnl_params = {
			.watermark_level = UART4_UFCR_TXTL,
			.per_address = UART4_BASE_ADDR + MXC_UARTUTXD,
			.peripheral_type = UART,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_UART4_TX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_UART4_TX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_mmc1_width1_params = {
	.chnl_params = {
			.watermark_level = MXC_SDHC_MMC_WML,
			.per_address =
			MMC_SDHC1_BASE_ADDR + MXC_MMC_BUFFER_ACCESS,
			.peripheral_type = MMC,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SDHC1,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_MMC1,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_mmc1_width4_params = {
	.chnl_params = {
			.watermark_level = MXC_SDHC_SD_WML,
			.per_address =
			MMC_SDHC1_BASE_ADDR + MXC_MMC_BUFFER_ACCESS,
			.peripheral_type = MMC,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SDHC1,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_MMC1,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_mmc2_width1_params = {
	.chnl_params = {
			.watermark_level = MXC_SDHC_MMC_WML,
			.per_address =
			MMC_SDHC2_BASE_ADDR + MXC_MMC_BUFFER_ACCESS,
			.peripheral_type = MMC,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SDHC2,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_MMC2,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_mmc2_width4_params = {
	.chnl_params = {
			.watermark_level = MXC_SDHC_SD_WML,
			.per_address =
			MMC_SDHC2_BASE_ADDR + MXC_MMC_BUFFER_ACCESS,
			.peripheral_type = MMC,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SDHC2,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_MMC2,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_8bit_rx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_RX0_REG,
			.peripheral_type = SSI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI1_RX1,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_8bit_tx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_TX0_REG,
			.peripheral_type = SSI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI1_TX1,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_16bit_rx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_RX0_REG,
			.peripheral_type = SSI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI1_RX1,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_16bit_tx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_TX0_REG,
			.peripheral_type = SSI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI1_TX1,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_24bit_rx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_RX0_REG,
			.peripheral_type = SSI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI1_RX1,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_24bit_tx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_TX0_REG,
			.peripheral_type = SSI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI1_TX1,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_8bit_rx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_RX1_REG,
			.peripheral_type = SSI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI1_RX2,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_8bit_tx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_TX1_REG,
			.peripheral_type = SSI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI1_TX2,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_16bit_rx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_RX1_REG,
			.peripheral_type = SSI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI1_RX2,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_16bit_tx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_TX1_REG,
			.peripheral_type = SSI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI1_TX2,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_24bit_rx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_RX1_REG,
			.peripheral_type = SSI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI1_RX2,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi1_24bit_tx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI1_BASE_ADDR + MXC_SSI_TX1_REG,
			.peripheral_type = SSI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI1_TX2,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI1_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_8bit_rx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_RX0_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI2_RX1,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_8bit_tx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_TX0_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI2_TX1,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_16bit_rx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_RX0_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI2_RX1,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_16bit_tx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_TX0_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI2_TX1,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_24bit_rx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_RX0_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI2_RX1,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_24bit_tx0_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_TX0_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI2_TX1,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_8bit_rx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_RX1_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI2_RX2,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_8bit_tx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_TX1_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI2_TX2,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_16bit_rx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_RX1_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI2_RX2,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_16bit_tx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_TX1_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI2_TX2,
			.bd_number = 32,
			.word_size = TRANSFER_16BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_24bit_rx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_RXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_RX1_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_SSI2_RX2,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_RX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_ssi2_24bit_tx1_params = {
	.chnl_params = {
			.watermark_level = MXC_SSI_TXFIFO_WML,
			.per_address = SSI2_BASE_ADDR + MXC_SSI_TX1_REG,
			.peripheral_type = SSI_SP,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_SSI2_TX2,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_SSI2_TX,
	.chnl_priority = 2,
};

static mxc_sdma_channel_params_t mxc_sdma_fir_rx_params = {
	.chnl_params = {
			.watermark_level = MXC_FIRI_WML,
			.per_address = FIRI_BASE_ADDR,
			.peripheral_type = FIRI,
			.transfer_type = per_2_emi,
			.event_id = DMA_REQ_FIRI_RX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_FIR_RX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_fir_tx_params = {
	.chnl_params = {
			.watermark_level = MXC_FIRI_WML,
			.per_address = FIRI_BASE_ADDR + MXC_FIRI_TXFIFO,
			.peripheral_type = FIRI,
			.transfer_type = emi_2_per,
			.event_id = DMA_REQ_FIRI_TX,
			.bd_number = 32,
			.word_size = TRANSFER_8BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_FIR_TX,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_memory_params = {
	.chnl_params = {
			.peripheral_type = MEMORY,
			.transfer_type = emi_2_emi,
			.bd_number = 32,
			.word_size = TRANSFER_32BIT,
			},
	.channel_num = MXC_DMA_CHANNEL_MEMORY,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_packet_data0_rd_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = dsp_2_emi,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_PACKET_DATA0_RD,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_packet_data0_wr_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = emi_2_dsp,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_PACKET_DATA0_WR,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_packet_data1_rd_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = dsp_2_emi,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_PACKET_DATA1_RD,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_packet_data1_wr_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = emi_2_dsp,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_PACKET_DATA1_WR,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_log0_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = dsp_2_emi,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_LOG0_CHNL,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_log1_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = dsp_2_emi,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_LOG1_CHNL,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_log2_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = dsp_2_emi,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_LOG2_CHNL,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_channel_params_t mxc_sdma_dsp_log3_params = {
	.chnl_params = {
			.peripheral_type = DSP,
			.transfer_type = dsp_2_emi,
			.bd_number = 32,
			},
	.channel_num = MXC_DMA_CHANNEL_DSP_LOG3_CHNL,
	.chnl_priority = MXC_SDMA_DEFAULT_PRIORITY,
};

static mxc_sdma_info_entry_t mxc_sdma_active_dma_info[] = {
	{MXC_DMA_UART1_RX, &mxc_sdma_uart1_rx_params},
	{MXC_DMA_UART1_TX, &mxc_sdma_uart1_tx_params},
	{MXC_DMA_UART2_RX, &mxc_sdma_uart2_rx_params},
	{MXC_DMA_UART2_TX, &mxc_sdma_uart2_tx_params},
	{MXC_DMA_UART3_RX, &mxc_sdma_uart3_rx_params},
	{MXC_DMA_UART3_TX, &mxc_sdma_uart3_tx_params},
	{MXC_DMA_UART4_RX, &mxc_sdma_uart4_rx_params},
	{MXC_DMA_UART4_TX, &mxc_sdma_uart4_tx_params},
	{MXC_DMA_MMC1_WIDTH_1, &mxc_sdma_mmc1_width1_params},
	{MXC_DMA_MMC1_WIDTH_4, &mxc_sdma_mmc1_width4_params},
	{MXC_DMA_MMC2_WIDTH_1, &mxc_sdma_mmc2_width1_params},
	{MXC_DMA_MMC2_WIDTH_4, &mxc_sdma_mmc2_width4_params},
	{MXC_DMA_SSI1_8BIT_RX0, &mxc_sdma_ssi1_8bit_rx0_params},
	{MXC_DMA_SSI1_8BIT_TX0, &mxc_sdma_ssi1_8bit_tx0_params},
	{MXC_DMA_SSI1_16BIT_RX0, &mxc_sdma_ssi1_16bit_rx0_params},
	{MXC_DMA_SSI1_16BIT_TX0, &mxc_sdma_ssi1_16bit_tx0_params},
	{MXC_DMA_SSI1_24BIT_RX0, &mxc_sdma_ssi1_24bit_rx0_params},
	{MXC_DMA_SSI1_24BIT_TX0, &mxc_sdma_ssi1_24bit_tx0_params},
	{MXC_DMA_SSI1_8BIT_RX1, &mxc_sdma_ssi1_8bit_rx1_params},
	{MXC_DMA_SSI1_8BIT_TX1, &mxc_sdma_ssi1_8bit_tx1_params},
	{MXC_DMA_SSI1_16BIT_RX1, &mxc_sdma_ssi1_16bit_rx1_params},
	{MXC_DMA_SSI1_16BIT_TX1, &mxc_sdma_ssi1_16bit_tx1_params},
	{MXC_DMA_SSI1_24BIT_RX1, &mxc_sdma_ssi1_24bit_rx1_params},
	{MXC_DMA_SSI1_24BIT_TX1, &mxc_sdma_ssi1_24bit_tx1_params},
	{MXC_DMA_SSI2_8BIT_RX0, &mxc_sdma_ssi2_8bit_rx0_params},
	{MXC_DMA_SSI2_8BIT_TX0, &mxc_sdma_ssi2_8bit_tx0_params},
	{MXC_DMA_SSI2_16BIT_RX0, &mxc_sdma_ssi2_16bit_rx0_params},
	{MXC_DMA_SSI2_16BIT_TX0, &mxc_sdma_ssi2_16bit_tx0_params},
	{MXC_DMA_SSI2_24BIT_RX0, &mxc_sdma_ssi2_24bit_rx0_params},
	{MXC_DMA_SSI2_24BIT_TX0, &mxc_sdma_ssi2_24bit_tx0_params},
	{MXC_DMA_SSI2_8BIT_RX1, &mxc_sdma_ssi2_8bit_rx1_params},
	{MXC_DMA_SSI2_8BIT_TX1, &mxc_sdma_ssi2_8bit_tx1_params},
	{MXC_DMA_SSI2_16BIT_RX1, &mxc_sdma_ssi2_16bit_rx1_params},
	{MXC_DMA_SSI2_16BIT_TX1, &mxc_sdma_ssi2_16bit_tx1_params},
	{MXC_DMA_SSI2_24BIT_RX1, &mxc_sdma_ssi2_24bit_rx1_params},
	{MXC_DMA_SSI2_24BIT_TX1, &mxc_sdma_ssi2_24bit_tx1_params},
	{MXC_DMA_FIR_RX, &mxc_sdma_fir_rx_params},
	{MXC_DMA_FIR_TX, &mxc_sdma_fir_tx_params},
	{MXC_DMA_MEMORY, &mxc_sdma_memory_params},
	{MXC_DMA_DSP_PACKET_DATA0_RD, &mxc_sdma_dsp_packet_data0_rd_params},
	{MXC_DMA_DSP_PACKET_DATA0_WR, &mxc_sdma_dsp_packet_data0_wr_params},
	{MXC_DMA_DSP_PACKET_DATA1_RD, &mxc_sdma_dsp_packet_data1_rd_params},
	{MXC_DMA_DSP_PACKET_DATA1_WR, &mxc_sdma_dsp_packet_data1_wr_params},
	{MXC_DMA_DSP_LOG0_CHNL, &mxc_sdma_dsp_log0_params},
	{MXC_DMA_DSP_LOG1_CHNL, &mxc_sdma_dsp_log1_params},
	{MXC_DMA_DSP_LOG2_CHNL, &mxc_sdma_dsp_log2_params},
	{MXC_DMA_DSP_LOG3_CHNL, &mxc_sdma_dsp_log3_params},
};

static int mxc_sdma_info_entrys =
    sizeof(mxc_sdma_active_dma_info) / sizeof(mxc_sdma_active_dma_info[0]);

/*!
 * This functions Returns the SDMA paramaters associated for a module
 *
 * @param channel_id the ID of the module requesting DMA
 * @return returns the sdma parameters structure for the device
 */
mxc_sdma_channel_params_t *mxc_sdma_get_channel_params(mxc_dma_device_t
						       channel_id)
{
	mxc_sdma_info_entry_t *p = mxc_sdma_active_dma_info;
	int i;

	for (i = 0; i < mxc_sdma_info_entrys; i++, p++) {
		if (p->device == channel_id) {
			return p->chnl_info;
		}
	}
	return NULL;
}

/*!
 * This functions marks the SDMA channels that are statically allocated
 *
 * @param chnl the channel array used to store channel information
 */
void mxc_get_static_channels(mxc_dma_channel_t * chnl)
{
	/* Make static allocated channels unavailable to dynamic selection */
	chnl[MXC_DMA_CHANNEL_DSP_PACKET_DATA0_RD].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_PACKET_DATA0_WR].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_PACKET_DATA1_RD].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_PACKET_DATA1_WR].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_LOG0_CHNL].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_LOG1_CHNL].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_LOG2_CHNL].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_DSP_LOG3_CHNL].dynamic = 0;
	chnl[MXC_DMA_CHANNEL_GEM].dynamic = 0;
}

EXPORT_SYMBOL(mxc_sdma_get_channel_params);
EXPORT_SYMBOL(mxc_get_static_channels);
