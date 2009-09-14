/*
 * Copyright 2007-2008 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */
#ifndef __ARCH_ARM_MACH_MX37_CRM_REGS_H__
#define __ARCH_ARM_MACH_MX37_CRM_REGS_H__

#define MXC_CCM_BASE	IO_ADDRESS(CCM_BASE_ADDR)
#define MXC_DPLL1_BASE	IO_ADDRESS(PLL0_BASE_ADDR)
#define MXC_DPLL2_BASE	IO_ADDRESS(PLL1_BASE_ADDR)
#define MXC_DPLL3_BASE	IO_ADDRESS(PLL2_BASE_ADDR)

/* PLL Register Offsets */
#define MXC_PLL_DP_CTL			0x00
#define MXC_PLL_DP_CONFIG		0x04
#define MXC_PLL_DP_OP			0x08
#define MXC_PLL_DP_MFD			0x0C
#define MXC_PLL_DP_MFN			0x10
#define MXC_PLL_DP_MFNMINUS		0x14
#define MXC_PLL_DP_MFNPLUS		0x18
#define MXC_PLL_DP_HFS_OP		0x1C
#define MXC_PLL_DP_HFS_MFD		0x20
#define MXC_PLL_DP_HFS_MFN		0x24
#define MXC_PLL_DP_MFN_TOGC		0x28
#define MXC_PLL_DP_DESTAT		0x2c

/* PLL Register Bit definitions */
#define MXC_PLL_DP_CTL_MUL_CTRL		0x2000
#define MXC_PLL_DP_CTL_DPDCK0_2_EN	0x1000
#define MXC_PLL_DP_CTL_DPDCK0_2_OFFSET	12
#define MXC_PLL_DP_CTL_ADE		0x800
#define MXC_PLL_DP_CTL_REF_CLK_DIV	0x400
#define MXC_PLL_DP_CTL_REF_CLK_SEL_MASK	(3 << 8)
#define MXC_PLL_DP_CTL_REF_CLK_SEL_OFFSET	8
#define MXC_PLL_DP_CTL_HFSM		0x80
#define MXC_PLL_DP_CTL_PRE		0x40
#define MXC_PLL_DP_CTL_UPEN		0x20
#define MXC_PLL_DP_CTL_RST		0x10
#define MXC_PLL_DP_CTL_RCP		0x8
#define MXC_PLL_DP_CTL_PLM		0x4
#define MXC_PLL_DP_CTL_BRM0		0x2
#define MXC_PLL_DP_CTL_LRF		0x1

#define MXC_PLL_DP_CONFIG_BIST		0x8
#define MXC_PLL_DP_CONFIG_SJC_CE	0x4
#define MXC_PLL_DP_CONFIG_AREN		0x2
#define MXC_PLL_DP_CONFIG_LDREQ		0x1

#define MXC_PLL_DP_OP_MFI_OFFSET	4
#define MXC_PLL_DP_OP_MFI_MASK		(0xF << 4)
#define MXC_PLL_DP_OP_PDF_OFFSET	0
#define MXC_PLL_DP_OP_PDF_MASK		0xF

#define MXC_PLL_DP_MFD_OFFSET		0
#define MXC_PLL_DP_MFD_MASK		0x07FFFFFF

#define MXC_PLL_DP_MFN_OFFSET		0x0
#define MXC_PLL_DP_MFN_MASK		0x07FFFFFF

#define MXC_PLL_DP_MFN_TOGC_TOG_DIS	(1 << 17)
#define MXC_PLL_DP_MFN_TOGC_TOG_EN	(1 << 16)
#define MXC_PLL_DP_MFN_TOGC_CNT_OFFSET	0x0
#define MXC_PLL_DP_MFN_TOGC_CNT_MASK	0xFFFF

#define MXC_PLL_DP_DESTAT_TOG_SEL	(1 << 31)
#define MXC_PLL_DP_DESTAT_MFN		0x07FFFFFF

/* Register addresses of CCM*/
#define MXC_CCM_CCR	(MXC_CCM_BASE + 0x00)
#define MXC_CCM_CCDR	(MXC_CCM_BASE + 0x04)
#define MXC_CCM_CSR	(MXC_CCM_BASE + 0x08)
#define MXC_CCM_CCSR	(MXC_CCM_BASE + 0x0C)
#define MXC_CCM_CACRR	(MXC_CCM_BASE + 0x10)
#define MXC_CCM_CBCDR2	(MXC_CCM_BASE + 0x18)
#define MXC_CCM_CBCDR3	(MXC_CCM_BASE + 0x1C)
#define MXC_CCM_CBCDR4	(MXC_CCM_BASE + 0x20)
#define MXC_CCM_CBCDR5	(MXC_CCM_BASE + 0x24)
#define MXC_CCM_CBCDR6	(MXC_CCM_BASE + 0x28)
#define MXC_CCM_CBCDR7	(MXC_CCM_BASE + 0x2C)
#define MXC_CCM_CAMR	(MXC_CCM_BASE + 0x30)
#define MXC_CCM_CSCMR1	(MXC_CCM_BASE + 0x34)
#define MXC_CCM_CSCMR2	(MXC_CCM_BASE + 0x38)
#define MXC_CCM_CSCDR1	(MXC_CCM_BASE + 0x3C)
#define MXC_CCM_CS1CDR	(MXC_CCM_BASE + 0x40)
#define MXC_CCM_CS2CDR	(MXC_CCM_BASE + 0x44)
#define MXC_CCM_CSECDR1	(MXC_CCM_BASE + 0x48)
#define MXC_CCM_CSECDR2	(MXC_CCM_BASE + 0x4C)
#define MXC_CCM_CECDR	(MXC_CCM_BASE + 0x50)
#define MXC_CCM_CDCDR	(MXC_CCM_BASE + 0x54)
#define MXC_CCM_CH1CDR	(MXC_CCM_BASE + 0x58)
#define MXC_CCM_CH2CDR	(MXC_CCM_BASE + 0x5C)
#define MXC_CCM_CSCDR2	(MXC_CCM_BASE + 0x60)
#define MXC_CCM_CR2	(MXC_CCM_BASE + 0x64)
#define MXC_CCM_CDHIPR	(MXC_CCM_BASE + 0x68)
#define MXC_CCM_CDCR	(MXC_CCM_BASE + 0x6C)
#define MXC_CCM_CTOR	(MXC_CCM_BASE + 0x70)
#define MXC_CCM_CLPCR	(MXC_CCM_BASE + 0x74)
#define MXC_CCM_CISR	(MXC_CCM_BASE + 0x78)
#define MXC_CCM_CIMR	(MXC_CCM_BASE + 0x7C)
#define MXC_CCM_CCOSR	(MXC_CCM_BASE + 0x80)
#define MXC_CCM_CGPR	(MXC_CCM_BASE + 0x84)
#define MXC_CCM_CCGR0	(MXC_CCM_BASE + 0x88)
#define MXC_CCM_CCGR1	(MXC_CCM_BASE + 0x8C)
#define MXC_CCM_CCGR2	(MXC_CCM_BASE + 0x90)
#define MXC_CCM_CCGR3	(MXC_CCM_BASE + 0x94)
#define MXC_CCM_CCGR4	(MXC_CCM_BASE + 0x98)
#define MXC_CCM_CCGR5	(MXC_CCM_BASE + 0x9C)
#define MXC_CCM_CMEOR	(MXC_CCM_BASE + 0xA0)

/* Define the bits in register CCR */
#define MXC_CCM_CCR_COSC_EN		(1 << 11)
#define MXC_CCM_CCR_FPM_MULT_MASK	(1 << 10)
#define MXC_CCM_CCR_CAMP_EN		(1 << 9)
#define MXC_CCM_CCR_FPM_EN		(1 << 8)
#define MXC_CCM_CCR_OSCNT_OFFSET	(0)
#define MXC_CCM_CCR_OSCNT_MASK		(0xFF)

/* Define the bits in register CCDR */
#define MXC_CCM_CCDR_IPU_HS_MASK	(0x1 << 17)
#define MXC_CCM_CCDR_EMI_HS_MASK	(0x1 << 16)
#define MXC_CCM_CCDR_LOAD_DIVIDERS	(0x1 << 0)

/* Define the bits in register CSR */
#define MXC_CCM_CSR_COSR_READY		(1 << 4)
#define MXC_CCM_CSR_LVS_VALUE		(1 << 3)
#define MXC_CCM_CSR_CAMP_READY		(1 << 2)
#define MXC_CCM_CSR_FPM_READY		(1 << 1)
#define MXC_CCM_CSR_REF_EN_B		(1 << 0)

/* Define the bits in register CCSR */
#define MXC_CCM_CCSR_LP_APM_SEL		(0x1 << 9)
#define MXC_CCM_CCSR_STEP_SEL_OFFSET	(7)
#define MXC_CCM_CCSR_STEP_SEL_MASK	(0x3 << 7)
#define MXC_CCM_CCSR_PLL2_PODF_OFFSET	(5)
#define MXC_CCM_CCSR_PLL2_PODF_MASK	(0x3 << 5)
#define MXC_CCM_CCSR_PLL3_PODF_OFFSET	(3)
#define MXC_CCM_CCSR_PLL3_PODF_MASK	(0x3 << 3)
#define MXC_CCM_CCSR_PLL1_SW_CLK_SEL	(1 << 2)
#define MXC_CCM_CCSR_PLL2_SW_CLK_SEL	(1 << 1)
#define MXC_CCM_CCSR_PLL3_SW_CLK_SEL	(1 << 0)

/* Define the bits in register CACRR */
#define MXC_CCM_CACRR_ARM_PODF_OFFSET	(0)
#define MXC_CCM_CACRR_ARM_PODF_MASK	(0x7)

/* Define the bits in register CBCDR2 */
#define MXC_CCM_CBCDR2_AHB_PODF_OFFSET		(10)
#define MXC_CCM_CBCDR2_AHB_PODF_MASK		(0x7 << 10)
#define MXC_CCM_CBCDR2_IPG_PODF_OFFSET		(8)
#define MXC_CCM_CBCDR2_IPG_PODF_MASK		(0x3 << 8)
#define MXC_CCM_CBCDR2_PERCLK_PRED1_OFFSET	(6)
#define MXC_CCM_CBCDR2_PERCLK_PRED1_MASK	(0x3 << 6)
#define MXC_CCM_CBCDR2_PERCLK_PRED2_OFFSET	(3)
#define MXC_CCM_CBCDR2_PERCLK_PRED2_MASK	(0x7 << 3)
#define MXC_CCM_CBCDR2_PERCLK_PODF_OFFSET	(0)
#define MXC_CCM_CBCDR2_PERCLK_PODF_MASK		(0x7)

/* Define the bits in register CBCDR3 */
#define MXC_CCM_CBCDR3_AXI_A_PODF_OFFSET	(0)
#define MXC_CCM_CBCDR3_AXI_A_PODF_MASK		(0x7)

/* Define the bits in register CBCDR4 */
#define MXC_CCM_CBCDR4_AXI_B_PODF_OFFSET	(0)
#define MXC_CCM_CBCDR4_AXI_B_PODF_MASK		(0x7)

/* Define the bits in register CBCDR5 */
#define MXC_CCM_CBCDR5_AXI_C_PODF_OFFSET	(0)
#define MXC_CCM_CBCDR5_AXI_C_PODF_MASK		(0x7)

/* Define the bits in register CBCDR6 */
#define MXC_CCM_CBCDR6_EMI_PODF_OFFSET		(0)
#define MXC_CCM_CBCDR6_EMI_PODF_MASK		(0x7)
#define MXC_CCM_CBCDR6_EMI_CLK_SEL		(0x1 << 3)
#define MXC_CCM_CBCDR6_PERIPH_CLK_SEL		(0x1 << 4)

/* Define the bits in register CBCDR7 */
#define MXC_CCM_CBCDR7_IPG_INT_MEM_PODF_OFFSET	(3)
#define MXC_CCM_CBCDR7_IPG_INIT_MEM_PODF_MASK	(0x3 << 3)
#define MXC_CCM_CBCDR7_NFC_PODF_OFFSET		(0)
#define MXC_CCM_CBCDR7_NFC_PODF_MASK		(0x7)

/* Define the bits in register CAMR */
#define MXC_CCM_CAMR_PERIPH_CLK_SEL_OFFSET	(12)
#define MXC_CCM_CAMR_PERIPH_CLK_SEL_MASK	(0x3 << 12)
#define MXC_CCM_CAMR_DDR_CLK_SEL_OFFSET		(10)
#define MXC_CCM_CAMR_DDR_CLK_SEL_MASK		(0x3 << 10)
#define MXC_CCM_CAMR_ARM_AXI_CLK_SEL_OFFSET	(8)
#define MXC_CCM_CAMR_ARM_AXI_CLK_SEL_MASK	(0x3 << 8)
#define MXC_CCM_CAMR_VPU_CLK_SEL_OFFSET		(6)
#define MXC_CCM_CAMR_VPU_CLK_SEL_MASK		(0x3 << 6)
#define MXC_CCM_CAMR_VPU_AXI_CLK_SEL_OFFSET	(4)
#define MXC_CCM_CAMR_VPU_AXI_CLK_SEL_MASK	(0x3 << 4)
#define MXC_CCM_CAMR_IPU_HSP_CLK_SEL_OFFSET	(2)
#define MXC_CCM_CAMR_IPU_HSP_CLK_SEL_MASK	(0x3 << 2)

/* Define the bits in register CSCMR1 */
#define MXC_CCM_CSCMR1_SSI_EXT2_CLK_SEL_OFFSET		(30)
#define MXC_CCM_CSCMR1_SSI_EXT2_CLK_SEL_MASK		(0x3 << 30)
#define MXC_CCM_CSCMR1_SSI_EXT1_CLK_SEL_OFFSET		(28)
#define MXC_CCM_CSCMR1_SSI_EXT1_CLK_SEL_MASK		(0x3 << 28)
#define MXC_CCM_CSCMR1_DI_CLK_SEL			(0x1 << 27)
#define MXC_CCM_CSCMR1_USB_PHY_CLK_SEL_OFFSET		(26)
#define MXC_CCM_CSCMR1_USB_PHY_CLK_SEL			(0x1 << 26)
#define MXC_CCM_CSCMR1_UART_CLK_SEL_OFFSET		(24)
#define MXC_CCM_CSCMR1_UART_CLK_SEL_MASK		(0x3 << 24)
#define MXC_CCM_CSCMR1_USBOH2_CLK_SEL_OFFSET		(22)
#define MXC_CCM_CSCMR1_USBOH2_CLK_SEL_MASK		(0x3 << 22)
#define MXC_CCM_CSCMR1_ESDHC1_MSHC1_CLK_SEL_OFFSET 	(20)
#define MXC_CCM_CSCMR1_ESDHC1_MSHC1_CLK_SEL_MASK 	(0x3 << 20)
#define MXC_CCM_CSCMR1_ESDHC3_CLK_SEL			(0x1 << 19)
#define MXC_CCM_CSCMR1_PERCLK_IPG_CLK_SEL		(0x1 << 18)
#define MXC_CCM_CSCMR1_ESDHC2_MSHC2_CLK_SEL_OFFSET	(16)
#define MXC_CCM_CSCMR1_ESDHC2_MSHC2_CLK_SEL_MASK	(0x3 << 16)
#define MXC_CCM_CSCMR1_SSI1_CLK_SEL_OFFSET		(14)
#define MXC_CCM_CSCMR1_SSI1_CLK_SEL_MASK		(0x3 << 14)
#define MXC_CCM_CSCMR1_SSI2_CLK_SEL_OFFSET		(12)
#define MXC_CCM_CSCMR1_SSI2_CLK_SEL_MASK		(0x3 << 12)
#define MXC_CCM_CSCMR1_SSI_APM_CLK_SEL			(0x1 << 9)
#define MXC_CCM_CSCMR1_SPDIF_CLK_SEL			(0x1 << 8)
#define MXC_CCM_CSCMR1_TVE_CLK_SEL			(0x1 << 7)
#define MXC_CCM_CSCMR1_TVE_EXT_CLK_SEL			(0x1 << 6)
#define MXC_CCM_CSCMR1_CSPI_CLK_SEL_OFFSET		(4)
#define MXC_CCM_CSCMR1_CSPI_CLK_SEL_MASK		(0x3 << 4)
#define MXC_CCM_CSCMR1_PERCLK_LP_APM_CLK_SEL		(0x1 << 2)
#define MXC_CCM_CSCMR1_SSI_EXT2_COM_CLK_SEL		(0x1 << 1)
#define MXC_CCM_CSCMR1_SSI_EXT1_COM_CLK_SEL		(0x1)

/* Define the bits in register CSCMR2 */
#define MXC_CCM_CSCMR2_SPDIF1_COM			(1 << 5)
#define MXC_CCM_CSCMR2_SPDIF0_COM			(1 << 4)
#define MXC_CCM_CSCMR2_SPDIF1_CLK_SEL_OFFSET		(2)
#define MXC_CCM_CSCMR2_SPDIF1_CLK_SEL_MASK		(0x3 << 2)
#define MXC_CCM_CSCMR2_SPDIF0_CLK_SEL_OFFSET		(0)
#define MXC_CCM_CSCMR2_SPDIF0_CLK_SEL_MASK		(0x3)

/* Define the bits in register CSCDR1 */
#define MXC_CCM_CSCDR1_ESDHC2_MSHC2_CLK_PRED_OFFSET	(22)
#define MXC_CCM_CSCDR1_ESDHC2_MSHC2_CLK_PRED_MASK	(0x7 << 22)
#define MXC_CCM_CSCDR1_ESDHC2_MSHC2_CLK_PODF_OFFSET	(19)
#define MXC_CCM_CSCDR1_ESDHC2_MSHC2_CLK_PODF_MASK	(0x7 << 19)
#define MXC_CCM_CSCDR1_ESDHC1_MSHC1_CLK_PRED_OFFSET	(16)
#define MXC_CCM_CSCDR1_ESDHC1_MSHC1_CLK_PRED_MASK	(0x7 << 16)
#define MXC_CCM_CSCDR1_PGC_CLK_PODF_OFFSET		(14)
#define MXC_CCM_CSCDR1_PGC_CLK_PODF_MASK		(0x3 << 14)
#define MXC_CCM_CSCDR1_ESDHC1_MSHC1_CLK_PODF_OFFSET	(11)
#define MXC_CCM_CSCDR1_ESDHC1_MSHC1_CLK_PODF_MASK	(0x7 << 11)
#define MXC_CCM_CSCDR1_USBOH2_CLK_PRED_OFFSET		(8)
#define MXC_CCM_CSCDR1_USBOH2_CLK_PRED_MASK		(0x7 << 8)
#define MXC_CCM_CSCDR1_USBOH2_CLK_PODF_OFFSET		(6)
#define MXC_CCM_CSCDR1_USBOH2_CLK_PODF_MASK		(0x3 << 6)
#define MXC_CCM_CSCDR1_UART_CLK_PRED_OFFSET		(3)
#define MXC_CCM_CSCDR1_UART_CLK_PRED_MASK		(0x7 << 3)
#define MXC_CCM_CSCDR1_UART_CLK_PODF_OFFSET		(0)
#define MXC_CCM_CSCDR1_UART_CLK_PODF_MASK		(0x7)

/* Define the bits in register CS1CDR and CS2CDR */
#define MXC_CCM_CS1CDR_SSI1_CLK_PRED_OFFSET		(6)
#define MXC_CCM_CS1CDR_SSI1_CLK_PRED_MASK		(0x7 << 6)
#define MXC_CCM_CS1CDR_SSI1_CLK_PODF_OFFSET		(0)
#define MXC_CCM_CS1CDR_SSI1_CLK_PODF_MASK		(0x3F)

#define MXC_CCM_CS2CDR_SSI2_CLK_PRED_OFFSET		(6)
#define MXC_CCM_CS2CDR_SSI2_CLK_PRED_MASK		(0x7 << 6)
#define MXC_CCM_CS2CDR_SSI2_CLK_PODF_OFFSET		(0)
#define MXC_CCM_CS2CDR_SSI2_CLK_PODF_MASK		(0x3F)

/* Define the bits in register CSECDR1 and CSECDR2 */
#define MXC_CCM_CSECDR1_SSI_EXT1_CLK_PRED_OFFSET	(6)
#define MXC_CCM_CSECDR1_SSI_EXT1_CLK_PRED_MASK		(0x7 << 6)
#define MXC_CCM_CSECDR1_SSI_EXT1_CLK_PODF_OFFSET	(0)
#define MXC_CCM_CSECDR1_SSI_EXT1_CLK_PODF_MASK		(0x3F)

#define MXC_CCM_CSECDR2_SSI_EXT2_CLK_PRED_OFFSET	(6)
#define MXC_CCM_CSECDR2_SSI_EXT2_CLK_PRED_MASK		(0x7 << 6)
#define MXC_CCM_CSECDR2_SSI_EXT2_CLK_PODF_OFFSET	(0)
#define MXC_CCM_CSECDR2_SSI_EXT2_CLK_PODF_MASK		(0x3F)

/* Define the bits in register CDCDR */
#define MXC_CCM_CDCDR_TVE_CLK_PRED_OFFSET		(28)
#define MXC_CCM_CDCDR_TVE_CLK_PRED_MASK			(0x7 << 28)
#define MXC_CCM_CDCDR_SPDIF0_CLK_PRED_OFFSET		(25)
#define MXC_CCM_CDCDR_SPDIF0_CLK_PRED_MASK		(0x7 << 25)
#define MXC_CCM_CDCDR_SPDIF0_CLK_PODF_OFFSET		(19)
#define MXC_CCM_CDCDR_SPDIF0_CLK_PODF_MASK		(0x3F << 19)
#define MXC_CCM_CDCDR_SPDIF1_CLK_PRED_OFFSET		(16)
#define MXC_CCM_CDCDR_SPDIF1_CLK_PRED_MASK		(0x7 << 16)
#define MXC_CCM_CDCDR_SPDIF1_CLK_PODF_OFFSET		(9)
#define MXC_CCM_CDCDR_SPDIF1_CLK_PODF_MASK		(0x3F << 9)
#define MXC_CCM_CDCDR_USB_PHY_PRED_OFFSET		(4)
#define MXC_CCM_CDCDR_USB_PHY_PRED_MASK			(0x7 << 4)
#define MXC_CCM_CDCDR_USB_PHY_PODF_OFFSET		(1)
#define MXC_CCM_CDCDR_USB_PHY_PODF_MASK			(0x7 << 1)

/* Define the bits in register CSCDR2 */
#define MXC_CCM_CSCDR2_CSPI_CLK_PRED_OFFSET		(25)
#define MXC_CCM_CSCDR2_CSPI_CLK_PRED_MASK		(0x7 << 25)
#define MXC_CCM_CSCDR2_CSPI_CLK_PODF_OFFSET		(19)
#define MXC_CCM_CSCDR2_CSPI_CLK_PODF_MASK		(0x3F << 19)

/* Define the bits in register CDHIPR */
#define MXC_CCM_CDHIPR_ARM_PODF_BUSY			(1 << 16)
#define MXC_CCM_CDHIPR_NFC_IPG_INT_MEM_PODF_BUSY	(1 << 4)
#define MXC_CCM_CDHIPR_EMI_PODF_BUSY			(1 << 3)
#define MXC_CCM_CDHIPR_AXI_C_PODF_BUSY			(1 << 2)
#define MXC_CCM_CDHIPR_AXI_B_PODF_BUSY			(1 << 1)
#define MXC_CCM_CDHIPR_AXI_A_PODF_BUSY			(1 << 0)

/* Define the bits in register CDCR */
#define MXC_CCM_CDCR_ARM_FREQ_SHIFT_DIVIDER		(0x1 << 2)
#define MXC_CCM_CDCR_PERIPH_CLK_DVFS_PODF_OFFSET	(0)
#define MXC_CCM_CDCR_PERIPH_CLK_DVFS_PODF_MASK		(0x3)

/* Define the bits in register CLPCR */
#define MXC_CCM_CLPCR_BYPASS_SCC_LPM_HS			(0x1 << 22)
#define MXC_CCM_CLPCR_BYPASS_MAX_LPM_HS			(0x1 << 21)
#define MXC_CCM_CLPCR_BYPASS_SDMA_LPM_HS		(0x1 << 20)
#define MXC_CCM_CLPCR_BYPASS_EMI_LPM_HS			(0x1 << 19)
#define MXC_CCM_CLPCR_BYPASS_IPU_LPM_HS			(0x1 << 18)
#define MXC_CCM_CLPCR_BYPASS_RTIC_LPM_HS		(0x1 << 17)
#define MXC_CCM_CLPCR_BYPASS_RNGC_LPM_HS		(0x1 << 16)
#define MXC_CCM_CLPCR_COSC_PWRDOWN			(0x1 << 11)
#define MXC_CCM_CLPCR_STBY_COUNT_OFFSET			(9)
#define MXC_CCM_CLPCR_STBY_COUNT_MASK			(0x3 << 9)
#define MXC_CCM_CLPCR_VSTBY				(0x1 << 8)
#define MXC_CCM_CLPCR_DIS_REF_OSC			(0x1 << 7)
#define MXC_CCM_CLPCR_SBYOS				(0x1 << 6)
#define MXC_CCM_CLPCR_ARM_CLK_DIS_ON_LPM		(0x1 << 5)
#define MXC_CCM_CLPCR_LPSR_CLK_SEL_OFFSET		(3)
#define MXC_CCM_CLPCR_LPSR_CLK_SEL_MASK			(0x3 << 3)
#define MXC_CCM_CLPCR_LPM_OFFSET			(0)
#define MXC_CCM_CLPCR_LPM_MASK				(0x3)

/* Define the bits in register CISR */
#define MXC_CCM_CISR_ARM_PODF_LOADED			(0x1 << 25)
#define MXC_CCM_CISR_NFC_IPG_INT_MEM_PODF_LOADED	(0x1 << 21)
#define MXC_CCM_CISR_EMI_PODF_LOADED			(0x1 << 20)
#define MXC_CCM_CISR_AXI_C_PODF_LOADED			(0x1 << 19)
#define MXC_CCM_CISR_AXI_B_PODF_LOADED			(0x1 << 18)
#define MXC_CCM_CISR_AXI_A_PODF_LOADED			(0x1 << 17)
#define MXC_CCM_CISR_DIVIDER_LOADED			(0x1 << 16)
#define MXC_CCM_CISR_COSC_READY				(0x1 << 5)
#define MXC_CCM_CISR_CKIH_READY				(0x1 << 4)
#define MXC_CCM_CISR_FPM_READY				(0x1 << 3)
#define MXC_CCM_CISR_LRF_PLL3				(0x1 << 2)
#define MXC_CCM_CISR_LRF_PLL2				(0x1 << 1)
#define MXC_CCM_CISR_LRF_PLL1				(0x1)

/* Define the bits in register CIMR */
#define MXC_CCM_CIMR_MASK_ARM_PODF_LOADED		(0x1 << 25)
#define MXC_CCM_CIMR_MASK_NFC_IPG_INT_MEM_PODF_LOADED	(0x1 << 21)
#define MXC_CCM_CIMR_MASK_EMI_PODF_LOADED		(0x1 << 20)
#define MXC_CCM_CIMR_MASK_AXI_C_PODF_LOADED		(0x1 << 19)
#define MXC_CCM_CIMR_MASK_AXI_B_PODF_LOADED		(0x1 << 18)
#define MXC_CCM_CIMR_MASK_AXI_A_PODF_LOADED		(0x1 << 17)
#define MXC_CCM_CIMR_MASK_DIVIDER_LOADED		(0x1 << 16)
#define MXC_CCM_CIMR_MASK_COSC_READY			(0x1 << 5)
#define MXC_CCM_CIMR_MASK_CKIH_READY			(0x1 << 4)
#define MXC_CCM_CIMR_MASK_FPM_READY			(0x1 << 3)
#define MXC_CCM_CIMR_MASK_LRF_PLL3			(0x1 << 2)
#define MXC_CCM_CIMR_MASK_LRF_PLL2			(0x1 << 1)
#define MXC_CCM_CIMR_MASK_LRF_PLL1			(0x1)

/* Define the bits in register CCOSR */
#define MXC_CCM_CCOSR_CKO2_EN_OFFSET			(0x1 << 24)
#define MXC_CCM_CCOSR_CKO2_DIV_OFFSET			(21)
#define MXC_CCM_CCOSR_CKO2_DIV_MASK			(0x7 << 21)
#define MXC_CCM_CCOSR_CKO2_SEL_OFFSET			(16)
#define MXC_CCM_CCOSR_CKO2_SEL_MASK			(0x1F << 16)
#define MXC_CCM_CCOSR_CKOL_EN				(0x1 << 7)
#define MXC_CCM_CCOSR_CKOL_DIV_OFFSET			(4)
#define MXC_CCM_CCOSR_CKOL_DIV_MASK			(0x7 << 4)
#define MXC_CCM_CCOSR_CKOL_SEL_OFFSET			(0)
#define MXC_CCM_CCOSR_CKOL_SEL_MASK			(0xF)

/* Define the bits in registers CGPR */
#define MXC_CCM_CGPR_EFUSE_PROG_SUPPLY_GATE		(0x1 << 4)
#define MXC_CCM_CGPR_FPM_SEL				(0x1 << 3)
#define MXC_CCM_CGPR_VL_L2BIST_CLKDIV_OFFSET		(0)
#define MXC_CCM_CGPR_VL_L2BIST_CLKDIV_MASK		(0x7)

/* Define the bits in registers CCGRx */
#define MXC_CCM_CCGR_CG_MASK				0x3

#define MXC_CCM_CCGR0_CG15_OFFSET			30
#define MXC_CCM_CCGR0_CG14_OFFSET			28
#define MXC_CCM_CCGR0_CG14_MASK				(0x3 << 28)
#define MXC_CCM_CCGR0_CG13_OFFSET			26
#define MXC_CCM_CCGR0_CG13_MASK				(0x3 << 26)
#define MXC_CCM_CCGR0_CG12_OFFSET			24
#define MXC_CCM_CCGR0_CG12_MASK				(0x3 << 24)
#define MXC_CCM_CCGR0_CG11_OFFSET			22
#define MXC_CCM_CCGR0_CG10_OFFSET			20
#define MXC_CCM_CCGR0_CG9_OFFSET			18
#define MXC_CCM_CCGR0_CG8_OFFSET			16
#define MXC_CCM_CCGR0_CG7_OFFSET			14
#define MXC_CCM_CCGR0_CG6_OFFSET			12
#define MXC_CCM_CCGR0_CG5_OFFSET			10
#define MXC_CCM_CCGR0_CG4_OFFSET			8
#define MXC_CCM_CCGR0_CG3_OFFSET			6
#define MXC_CCM_CCGR0_CG2_OFFSET			4
#define MXC_CCM_CCGR0_CG2_MASK				(0x3 << 4)
#define MXC_CCM_CCGR0_CG1_OFFSET			2
#define MXC_CCM_CCGR0_CG1_MASK				(0x3 << 2)
#define MXC_CCM_CCGR0_CG0_OFFSET			0
#define MXC_CCM_CCGR0_CG0_MASK				0x3

#define MXC_CCM_CCGR1_CG15_OFFSET			30
#define MXC_CCM_CCGR1_CG14_OFFSET			28
#define MXC_CCM_CCGR1_CG13_OFFSET			26
#define MXC_CCM_CCGR1_CG12_OFFSET			24
#define MXC_CCM_CCGR1_CG11_OFFSET			22
#define MXC_CCM_CCGR1_CG10_OFFSET			20
#define MXC_CCM_CCGR1_CG9_OFFSET			18
#define MXC_CCM_CCGR1_CG8_OFFSET			16
#define MXC_CCM_CCGR1_CG7_OFFSET			14
#define MXC_CCM_CCGR1_CG6_OFFSET			12
#define MXC_CCM_CCGR1_CG5_OFFSET			10
#define MXC_CCM_CCGR1_CG4_OFFSET			8
#define MXC_CCM_CCGR1_CG3_OFFSET			6
#define MXC_CCM_CCGR1_CG2_OFFSET			4
#define MXC_CCM_CCGR1_CG1_OFFSET			2
#define MXC_CCM_CCGR1_CG0_OFFSET			0

#define MXC_CCM_CCGR2_CG15_OFFSET			30
#define MXC_CCM_CCGR2_CG14_OFFSET			28
#define MXC_CCM_CCGR2_CG13_OFFSET			26
#define MXC_CCM_CCGR2_CG12_OFFSET			24
#define MXC_CCM_CCGR2_CG11_OFFSET			22
#define MXC_CCM_CCGR2_CG10_OFFSET			20
#define MXC_CCM_CCGR2_CG9_OFFSET			18
#define MXC_CCM_CCGR2_CG8_OFFSET			16
#define MXC_CCM_CCGR2_CG7_OFFSET			14
#define MXC_CCM_CCGR2_CG6_OFFSET			12
#define MXC_CCM_CCGR2_CG5_OFFSET			10
#define MXC_CCM_CCGR2_CG4_OFFSET			8
#define MXC_CCM_CCGR2_CG3_OFFSET			6
#define MXC_CCM_CCGR2_CG2_OFFSET			4
#define MXC_CCM_CCGR2_CG1_OFFSET			2
#define MXC_CCM_CCGR2_CG0_OFFSET			0

#define MXC_CCM_CCGR3_CG15_OFFSET			30
#define MXC_CCM_CCGR3_CG14_OFFSET			28
#define MXC_CCM_CCGR3_CG13_OFFSET			26
#define MXC_CCM_CCGR3_CG12_OFFSET			24
#define MXC_CCM_CCGR3_CG11_OFFSET			22
#define MXC_CCM_CCGR3_CG10_OFFSET			20
#define MXC_CCM_CCGR3_CG9_OFFSET			18
#define MXC_CCM_CCGR3_CG8_OFFSET			16
#define MXC_CCM_CCGR3_CG7_OFFSET			14
#define MXC_CCM_CCGR3_CG6_OFFSET			12
#define MXC_CCM_CCGR3_CG5_OFFSET			10
#define MXC_CCM_CCGR3_CG4_OFFSET			8
#define MXC_CCM_CCGR3_CG3_OFFSET			6
#define MXC_CCM_CCGR3_CG2_OFFSET			4
#define MXC_CCM_CCGR3_CG1_OFFSET			2
#define MXC_CCM_CCGR3_CG0_OFFSET			0

#define MXC_CCM_CCGR4_CG15_OFFSET			30
#define MXC_CCM_CCGR4_CG14_OFFSET			28
#define MXC_CCM_CCGR4_CG13_OFFSET			26
#define MXC_CCM_CCGR4_CG12_OFFSET			24
#define MXC_CCM_CCGR4_CG11_OFFSET			22
#define MXC_CCM_CCGR4_CG10_OFFSET			20
#define MXC_CCM_CCGR4_CG9_OFFSET			18
#define MXC_CCM_CCGR4_CG8_OFFSET			16
#define MXC_CCM_CCGR4_CG7_OFFSET			14
#define MXC_CCM_CCGR4_CG6_OFFSET			12
#define MXC_CCM_CCGR4_CG5_OFFSET			10
#define MXC_CCM_CCGR4_CG4_OFFSET			8
#define MXC_CCM_CCGR4_CG3_OFFSET			6
#define MXC_CCM_CCGR4_CG2_OFFSET			4
#define MXC_CCM_CCGR4_CG1_OFFSET			2
#define MXC_CCM_CCGR4_CG0_OFFSET			0

#define MXC_CCM_CCGR5_CG15_OFFSET			30
#define MXC_CCM_CCGR5_CG14_OFFSET			28
#define MXC_CCM_CCGR5_CG14_MASK				(0x3 << 28)
#define MXC_CCM_CCGR5_CG13_OFFSET			26
#define MXC_CCM_CCGR5_CG13_MASK				(0x3 << 26)
#define MXC_CCM_CCGR5_CG12_OFFSET			24
#define MXC_CCM_CCGR5_CG12_MASK				(0x3 << 24)
#define MXC_CCM_CCGR5_CG11_OFFSET			22
#define MXC_CCM_CCGR5_CG11_MASK				(0x3 << 22)
#define MXC_CCM_CCGR5_CG10_OFFSET			20
#define MXC_CCM_CCGR5_CG9_OFFSET			18
#define MXC_CCM_CCGR5_CG8_OFFSET			16
#define MXC_CCM_CCGR5_CG7_OFFSET			14
#define MXC_CCM_CCGR5_CG6_OFFSET			12
#define MXC_CCM_CCGR5_CG5_OFFSET			10
#define MXC_CCM_CCGR5_CG4_OFFSET			8
#define MXC_CCM_CCGR5_CG3_OFFSET			6
#define MXC_CCM_CCGR5_CG2_OFFSET			4
#define MXC_CCM_CCGR5_CG1_OFFSET			2
#define MXC_CCM_CCGR5_CG0_OFFSET			0

#define MXC_ARM1176_BASE	IO_ADDRESS(ARM1176_BASE_ADDR)
#define MXC_GPC_BASE		IO_ADDRESS(GPC_BASE_ADDR)
#define MXC_DPTC_LP_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x80)
#define MXC_DPTC_GP_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x100)
#define MXC_DVFS_CORE_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x180)
#define MXC_DPTC_PER_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x1C0)
#define MXC_PGC_IPU_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x220)
#define MXC_PGC_VPU_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x240)
#define MXC_SRPGC_EMI_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x280)
#define MXC_SRPGC_ARM_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x2A0)
#define MXC_EMPGC0_ARM_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x2C0)
#define MXC_EMPGC1_ARM_BASE	IO_ADDRESS(GPC_BASE_ADDR + 0x2D0)

/* ARM1176 platform */
#define MXC_ARM1176_PLAT_PVID	(MXC_ARM1176_BASE + 0x0)
#define MXC_ARM1176_PLAT_GPC	(MXC_ARM1176_BASE + 0x4)
#define MXC_ARM1176_PLAT_PIC	(MXC_ARM1176_BASE + 0x8)
#define MXC_ARM1176_PLAT_L2SO	(MXC_ARM1176_BASE + 0xC)
#define MXC_ARM1176_PLAT_EMSO	(MXC_ARM1176_BASE + 0x10)
#define MXC_ARM1176_PLAT_LPC	(MXC_ARM1176_BASE + 0x14)
#define MXC_ARM1176_PLAT_ICGC	(MXC_ARM1176_BASE + 0x18)
#define MXC_ARM1176_PLAT_AMC	(MXC_ARM1176_BASE + 0x1C)

/* GPC */
#define MXC_GPC_CNTR		(MXC_GPC_BASE + 0x0)
#define MXC_GPC_PGR		(MXC_GPC_BASE + 0x4)
#define MXC_GPC_VCR		(MXC_GPC_BASE + 0x8)

/* SRPG */
#define MXC_SRPGC_EMI_SRPGCR	(MXC_SRPGC_EMI_BASE + 0x0)
#define MXC_SRPGC_ARM_SRPGCR	(MXC_SRPGC_ARM_BASE + 0x0)
#define MXC_EMPGC0_ARM_EMPGCR	(MXC_EMPGC0_ARM_BASE + 0x0)
#define MXC_EMPGC1_ARM_EMPGCR	(MXC_EMPGC1_ARM_BASE + 0x0)

#define MXC_PGC_IPU_PGCR	(MXC_PGC_IPU_BASE + 0x0)
#define MXC_PGC_IPU_PGSR	(MXC_PGC_IPU_BASE + 0xC)
#define MXC_PGC_VPU_PGCR	(MXC_PGC_VPU_BASE + 0x0)
#define MXC_PGC_VPU_PGSR	(MXC_PGC_VPU_BASE + 0xC)

#define MXC_ARM1176_PLAT_LPC_DSM	(1 << 16)
#define MXC_ARM1176_PLAT_LPC_DBG_DSM	(1 << 17)

#define MXC_GPC_PGR_ARMPG_OFFSET	8
#define MXC_GPC_PGR_ARMPG_MASK		(3 << 8)

#define MXC_PGCR_PCR			1
#define MXC_SRPGCR_PCR			1
#define MXC_EMPGCR_PCR			1

#define MXC_PGSR_PSR			1

#endif				/* __ARCH_ARM_MACH_MX37_CRM_REGS_H__ */
