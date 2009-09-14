/*
 * Copyright 2004-2008 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *	otg_{get,set}_transceiver() are from arm/plat-omap/usb.c.
 *	which is Copyright (C) 2004 Texas Instruments, Inc.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

/*!
 *@defgroup USB ARC OTG USB Driver
 */

/*!
 * @file usb_common.c
 *
 * @brief platform related part of usb driver.
 * @ingroup USB
 */

/*!
 *Include files
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <linux/usb/otg.h>
#include <linux/usb/fsl_xcvr.h>
#include <linux/regulator/regulator.h>
#include <asm/arch/arc_otg.h>
#include <asm/mach-types.h>

#define MXC_NUMBER_USB_TRANSCEIVER 6
struct fsl_xcvr_ops *g_xc_ops[MXC_NUMBER_USB_TRANSCEIVER] = { NULL };

static struct clk *usb_clk;
static struct clk *usb_ahb_clk;

extern int gpio_usbotg_hs_active(void);
extern int gpio_usbotg_hs_inactive(void);
/*
 * make sure USB_CLK is running at 60 MHz +/- 1000 Hz
 */
static int fsl_check_usbclk(void)
{
	unsigned long freq;

	usb_ahb_clk = clk_get(NULL, "usb_ahb_clk");
	if (clk_enable(usb_ahb_clk)) {
		printk(KERN_ERR "clk_enable(usb_ahb_clk) failed\n");
		return -EINVAL;
	}
	clk_put(usb_ahb_clk);

	usb_clk = clk_get(NULL, "usb_clk");
	freq = clk_get_rate(usb_clk);
	clk_put(usb_clk);
	if ((freq < 59999000) || (freq > 60001000)) {
		printk(KERN_ERR "USB_CLK=%lu, should be 60MHz\n", freq);
		return -1;
	}

	return 0;
}

void fsl_usb_xcvr_register(struct fsl_xcvr_ops *xcvr_ops)
{
	int i;

	pr_debug("%s\n", __func__);
	for (i = 0; i < MXC_NUMBER_USB_TRANSCEIVER; i++) {
		if (g_xc_ops[i] == NULL) {
			g_xc_ops[i] = xcvr_ops;
			return;
		}
	}

	pr_debug("Failed %s\n", __func__);
}
EXPORT_SYMBOL(fsl_usb_xcvr_register);

void fsl_usb_xcvr_unregister(struct fsl_xcvr_ops *xcvr_ops)
{
	int i;

	pr_debug("%s\n", __func__);
	for (i = 0; i < MXC_NUMBER_USB_TRANSCEIVER; i++) {
		if (g_xc_ops[i] == xcvr_ops) {
			g_xc_ops[i] = NULL;
			return;
		}
	}

	pr_debug("Failed %s\n", __func__);
}
EXPORT_SYMBOL(fsl_usb_xcvr_unregister);

static struct fsl_xcvr_ops *fsl_usb_get_xcvr(char *name)
{
	int i;

	pr_debug("%s\n", __func__);
	if (name == NULL) {
		printk(KERN_ERR "get_xcvr(): No tranceiver name\n");
		return NULL;
	}

	for (i = 0; i < MXC_NUMBER_USB_TRANSCEIVER; i++) {
		if (strcmp(g_xc_ops[i]->name, name) == 0) {
			return g_xc_ops[i];
		}
	}
	pr_debug("Failed %s\n", __func__);
	return NULL;
}

/* The dmamask must be set for EHCI to work */
static u64 ehci_dmamask = ~(u32) 0;

/*!
 * Register an instance of a USB host platform device.
 *
 * @param	res:	resource pointer
 * @param       n_res:	number of resources
 * @param       config: config pointer
 *
 * @return      newly-registered platform_device
 *
 * The USB controller supports 3 host interfaces, and the
 * kernel can be configured to support some number of them.
 * Each supported host interface is registered as an instance
 * of the "fsl-ehci" device.  Call this function multiple times
 * to register each host interface.
 */
static int instance_id = 0;
struct platform_device *host_pdev_register(struct resource *res, int n_res,
					   struct fsl_usb2_platform_data *config)
{
	struct platform_device *pdev;
	int rc;

	pr_debug("register host res=0x%p, size=%d\n", res, n_res);

	pdev = platform_device_register_simple("fsl-ehci",
					       instance_id, res, n_res);
	if (IS_ERR(pdev)) {
		pr_debug("can't register %s Host, %ld\n",
			 config->name, PTR_ERR(pdev));
		return NULL;
	}

	pdev->dev.coherent_dma_mask = 0xffffffff;
	pdev->dev.dma_mask = &ehci_dmamask;

	/*
	 * platform_device_add_data() makes a copy of
	 * the platform_data passed in.  That makes it
	 * impossible to share the same config struct for
	 * all OTG devices (host,gadget,otg).  So, just
	 * set the platorm_data pointer ourselves.
	 */
	rc = platform_device_add_data(pdev, config,
				      sizeof(struct fsl_usb2_platform_data));
	if (rc) {
		platform_device_unregister(pdev);
		return NULL;
	}

	printk(KERN_INFO "usb: %s host (%s) registered\n", config->name,
	       config->transceiver);
	pr_debug("pdev=0x%p  dev=0x%p  resources=0x%p  pdata=0x%p\n",
		 pdev, &pdev->dev, pdev->resource, pdev->dev.platform_data);

	instance_id++;

	return pdev;
}

/* DDD looks like this is needed by Belcarra code */
void fsl_platform_set_vbus_power(struct fsl_usb2_platform_data *pdata, int on)
{
	if (pdata->xcvr_ops && pdata->xcvr_ops->set_vbus_power)
		pdata->xcvr_ops->set_vbus_power(pdata->xcvr_ops, pdata, on);
}
EXPORT_SYMBOL(fsl_platform_set_vbus_power);

/* DDD looks like this is needed by Belcarra code */
void fsl_platform_perform_remote_wakeup(struct fsl_usb2_platform_data *pdata)
{
	if (pdata->xcvr_ops && pdata->xcvr_ops->set_remote_wakeup)
		pdata->xcvr_ops->set_remote_wakeup(
			(u32 *)(pdata->regs + ULPIVW_OFF));
}
EXPORT_SYMBOL(fsl_platform_perform_remote_wakeup);

#if defined(CONFIG_USB_OTG)
static struct otg_transceiver *xceiv;

/**
 * otg_get_transceiver - find the (single) OTG transceiver driver
 *
 * Returns the transceiver driver, after getting a refcount to it; or
 * null if there is no such transceiver.  The caller is responsible for
 * releasing that count.
 */
struct otg_transceiver *otg_get_transceiver(void)
{
	pr_debug("%s xceiv=0x%p\n", __func__, xceiv);
	if (xceiv)
		get_device(xceiv->dev);
	return xceiv;
}
EXPORT_SYMBOL(otg_get_transceiver);

int otg_set_transceiver(struct otg_transceiver *x)
{
	pr_debug("%s xceiv=0x%p  x=0x%p\n", __func__, xceiv, x);
	if (xceiv && x)
		return -EBUSY;
	xceiv = x;
	return 0;
}
EXPORT_SYMBOL(otg_set_transceiver);

static struct resource *otg_resources;

struct resource *otg_get_resources(void)
{
	return otg_resources;
}
EXPORT_SYMBOL(otg_get_resources);

int otg_set_resources(struct resource *resources)
{
	otg_resources = resources;
	return 0;
}
EXPORT_SYMBOL(otg_set_resources);
#endif

static void usbh1_set_serial_xcvr(void)
{
	pr_debug("%s: \n", __func__);
	USBCTRL &= ~(UCTRL_H1SIC_MASK | UCTRL_BPE); /* disable bypass mode */
	USBCTRL |= UCTRL_H1SIC_SU6 |		/* single-ended / unidir. */
		   UCTRL_H1WIE | UCTRL_H1DT |	/* disable H1 TLL */
		   UCTRL_H1PM;			/* power mask */
}

static void usbh2_set_ulpi_xcvr(void)
{
	u32 tmp;

	pr_debug("%s\n", __func__);
	USBCTRL &= ~(UCTRL_H2SIC_MASK | UCTRL_BPE);
	USBCTRL |= UCTRL_H2WIE |	/* wakeup intr enable */
		   UCTRL_H2UIE |	/* ULPI intr enable */
		   UCTRL_H2DT |		/* disable H2 TLL */
		   UCTRL_H2PM;		/* power mask */

	/* must set ULPI phy before turning off clock */
	tmp = UH2_PORTSC1 & ~PORTSC_PTS_MASK;
	tmp |= PORTSC_PTS_ULPI;
	UH2_PORTSC1 = tmp;

	UH2_USBCMD |= UCMD_RESET;	/* reset the controller */

	/* allow controller to reset, and leave time for
	 * the ULPI transceiver to reset too.
	 */
	msleep(100);

	/* Turn off the usbpll for ulpi tranceivers */
	clk_disable(usb_clk);
}

static void usbh2_set_serial_xcvr(void)
{
	pr_debug("%s: \n", __func__);

	/* Stop then Reset */
	UH2_USBCMD &= ~UCMD_RUN_STOP;
	while (UH2_USBCMD & UCMD_RUN_STOP) ;

	UH2_USBCMD |= UCMD_RESET;
	while (UH2_USBCMD & UCMD_RESET) ;

	USBCTRL &= ~(UCTRL_H2SIC_MASK);	/* Disable bypass mode */
	USBCTRL &= ~(UCTRL_H2PM);	/* Power Mask */
	USBCTRL &= ~UCTRL_OCPOL;	/* OverCurrent Polarity is Low Active */
	USBCTRL |= UCTRL_H2WIE |	/* Wakeup intr enable */
		UCTRL_H2LOCKD |		/* Host2 Lock Disable */
	    UCTRL_IP_PUE_DOWN |	/* ipp_pue_pulldwn_dpdm */
	    UCTRL_USBTE |	/* USBT is enabled */
	    UCTRL_H2DT;		/* Disable H2 TLL */

	USBCTRL &= ~(UCTRL_PP);
	UH2_PORTSC1 = (UH2_PORTSC1 & (~PORTSC_PTS_MASK)) | PORTSC_PTS_SERIAL;

	if (UH2_HCSPARAMS & HCSPARAMS_PPC)
		UH2_PORTSC1 |= PORTSC_PORT_POWER;

	/* Reset controller before set host mode */
	UH2_USBCMD |= UCMD_RESET;
	while (UH2_USBCMD & UCMD_RESET) ;

	msleep(100);
}

extern void usbh2_get_xcvr_power(struct device *dev);
extern void usbh2_put_xcvr_power(struct device *dev);

int fsl_usb_host_init(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata = pdev->dev.platform_data;
	struct fsl_xcvr_ops *xops;

	pr_debug("%s: pdev=0x%p  pdata=0x%p\n", __func__, pdev, pdata);

	xops = fsl_usb_get_xcvr(pdata->transceiver);
	if (!xops) {
		printk(KERN_ERR "%s transceiver ops missing\n", pdata->name);
		return -EINVAL;
	}
	pdata->xcvr_ops = xops;
	pdata->xcvr_type = xops->xcvr_type;
	pdata->pdev = pdev;

	if (fsl_check_usbclk() != 0)
		return -EINVAL;

	/* set host2 usb phy usb3317 power supply for imx31 3 stack */
	if ((pdata->xcvr_type == PORTSC_PTS_ULPI) && (machine_is_mx31_3ds())) {
		pdata->xcvr_pwr =
		    kmalloc(sizeof(struct fsl_xcvr_power), GFP_KERNEL);
		if (!(pdata->xcvr_pwr))
			return -ENOMEM;

		pdata->xcvr_pwr->usb_pdev = pdev;
		usbh2_get_xcvr_power(&(pdev->dev));
	}

	pr_debug("%s: grab pins\n", __func__);
	if (pdata->gpio_usb_active())
		return -EINVAL;

	if (clk_enable(usb_clk)) {
		printk(KERN_ERR "clk_enable(usb_clk) failed\n");
		return -EINVAL;
	}

	if (xops->init)
		xops->init(xops);

	if (xops->xcvr_type == PORTSC_PTS_SERIAL) {
		if (machine_is_mx35_3ds())
			usbh2_set_serial_xcvr();
		else
			usbh1_set_serial_xcvr();
	} else if (xops->xcvr_type == PORTSC_PTS_ULPI) {
		usbh2_set_ulpi_xcvr();
	}

	pr_debug("%s: %s success\n", __func__, pdata->name);
	return 0;
}
EXPORT_SYMBOL(fsl_usb_host_init);

void fsl_usb_host_uninit(struct fsl_usb2_platform_data *pdata)
{
	pr_debug("%s\n", __func__);

	if (pdata->xcvr_ops && pdata->xcvr_ops->uninit)
		pdata->xcvr_ops->uninit(pdata->xcvr_ops);

	pdata->regs = NULL;

	pdata->gpio_usb_inactive();
	if (pdata->xcvr_type == PORTSC_PTS_SERIAL)
		clk_disable(usb_clk);
	else if ((pdata->xcvr_type == PORTSC_PTS_ULPI)
		 && (machine_is_mx31_3ds())) {
		usbh2_put_xcvr_power(&(pdata->xcvr_pwr->usb_pdev->dev));
		kfree(pdata->xcvr_pwr);
	}
}
EXPORT_SYMBOL(fsl_usb_host_uninit);

static void otg_set_serial_xcvr(void)
{
	pr_debug("%s\n", __func__);
}

void otg_set_serial_host(void)
{
	pr_debug("%s\n", __func__);
	/* set USBCTRL for host operation
	 * disable: bypass mode,
	 * set: single-ended/unidir/6 wire, OTG wakeup intr enable,
	 *      power mask
	 */
	USBCTRL &= ~UCTRL_OSIC_MASK;
#if defined(CONFIG_ARCH_MX27) || defined(CONFIG_ARCH_MX3)
	USBCTRL &= ~UCTRL_BPE;
#endif

#if defined(CONFIG_MXC_USB_SB3)
	USBCTRL |= UCTRL_OSIC_SB3 | UCTRL_OWIE | UCTRL_OPM;
#elif defined(CONFIG_MXC_USB_SU6)
	USBCTRL |= UCTRL_OSIC_SU6 | UCTRL_OWIE | UCTRL_OPM;
#elif defined(CONFIG_MXC_USB_DB4)
	USBCTRL |= UCTRL_OSIC_DB4 | UCTRL_OWIE | UCTRL_OPM;
#else
	USBCTRL |= UCTRL_OSIC_DU6 | UCTRL_OWIE | UCTRL_OPM;
#endif

	USB_OTG_MIRROR = OTGM_VBUSVAL | OTGM_ASESVLD;	/* 0xa */
}
EXPORT_SYMBOL(otg_set_serial_host);

void otg_set_serial_peripheral(void)
{
	/* set USBCTRL for device operation
	 * disable: bypass mode
	 * set: differential/unidir/6 wire, OTG wakeup intr enable,
	 *      power mask
	 */
	USBCTRL &= ~UCTRL_OSIC_MASK;
#if defined(CONFIG_ARCH_MX27) || defined(CONFIG_ARCH_MX3)
	USBCTRL &= ~UCTRL_BPE;
#endif

#if defined(CONFIG_MXC_USB_SB3)
	USBCTRL |= UCTRL_OSIC_SB3 | UCTRL_OWIE | UCTRL_OPM;
#elif defined(CONFIG_MXC_USB_SU6)
	USBCTRL |= UCTRL_OSIC_SU6 | UCTRL_OWIE | UCTRL_OPM;
#elif defined(CONFIG_MXC_USB_DB4)
	USBCTRL |= UCTRL_OSIC_DB4 | UCTRL_OWIE | UCTRL_OPM;
#else
	USBCTRL |= UCTRL_OSIC_DU6 | UCTRL_OWIE | UCTRL_OPM;
#endif

	USB_OTG_MIRROR = OTGM_VBUSVAL | OTGM_BSESVLD | OTGM_IDIDG;	/* oxd */
}
EXPORT_SYMBOL(otg_set_serial_peripheral);

static void otg_set_ulpi_xcvr(void)
{
	u32 tmp;

	pr_debug("%s\n", __func__);
	USBCTRL &= ~UCTRL_OSIC_MASK;
#if defined(CONFIG_ARCH_MX27) || defined(CONFIG_ARCH_MX3)
	USBCTRL &= ~UCTRL_BPE;
#endif
	USBCTRL |= UCTRL_OUIE |	/* ULPI intr enable */
	    UCTRL_OWIE |	/* OTG wakeup intr enable */
	    UCTRL_OPM;		/* power mask */

	/* must set ULPI phy before turning off clock */
	tmp = UOG_PORTSC1 & ~PORTSC_PTS_MASK;
	tmp |= PORTSC_PTS_ULPI;
	UOG_PORTSC1 = tmp;

	/* need to reset the controller here so that the ID pin
	 * is correctly detected.
	 */
	UOG_USBCMD |= UCMD_RESET;

	/* allow controller to reset, and leave time for
	 * the ULPI transceiver to reset too.
	 */
	msleep(100);

	/* Turn off the usbpll for ulpi tranceivers */
	clk_disable(usb_clk);
}

int fsl_usb_xcvr_suspend(struct fsl_xcvr_ops *xcvr_ops)
{
	if (!machine_is_mx31_3ds())
		return -ECANCELED;

	if (xcvr_ops->xcvr_type == PORTSC_PTS_ULPI) {
		if (fsl_check_usbclk() != 0)
			return -EINVAL;
		if (gpio_usbotg_hs_active())
			return -EINVAL;
		clk_enable(usb_clk);

		otg_set_ulpi_xcvr();

		if (xcvr_ops->suspend)
			/* suspend transceiver */
			xcvr_ops->suspend(xcvr_ops);

		gpio_usbotg_hs_inactive();
		clk_disable(usb_clk);
	}
	return 0;
}
EXPORT_SYMBOL(fsl_usb_xcvr_suspend);

static void otg_set_utmi_xcvr(void)
{
	u32 tmp;

	/* Stop then Reset */
	UOG_USBCMD &= ~UCMD_RUN_STOP;
	while (UOG_USBCMD & UCMD_RUN_STOP) ;

	UOG_USBCMD |= UCMD_RESET;
	while ((UOG_USBCMD) & (UCMD_RESET)) ;

	USBCTRL &= ~UCTRL_PP;	/* USBOTG_PWR low active */
	USBCTRL &= ~UCTRL_OCPOL;	/* OverCurrent Polarity is Low Active */
	USBCTRL &= ~UCTRL_OPM;	/* OTG Power Mask */
	USBCTRL |= UCTRL_OWIE;	/* OTG Wakeup Intr Enable */
	USBCTRL |= UCTRL_OLOCKD;	/* OTG Lock Disable */

	/* set UTMI xcvr */
	tmp = UOG_PORTSC1 & ~PORTSC_PTS_MASK;
	tmp |= PORTSC_PTS_UTMI;
	UOG_PORTSC1 = tmp;

	/* Enable UTMI interface in PHY control Reg */
	USB_PHY_CTR_FUNC |= USB_UTMI_PHYCTRL_UTMI_ENABLE;

	if (UOG_HCSPARAMS & HCSPARAMS_PPC)
		UOG_PORTSC1 |= PORTSC_PORT_POWER;

	/* need to reset the controller here so that the ID pin
	 * is correctly detected.
	 */
	/* Stop then Reset */
	UOG_USBCMD &= ~UCMD_RUN_STOP;
	while (UOG_USBCMD & UCMD_RUN_STOP) ;

	UOG_USBCMD |= UCMD_RESET;
	while ((UOG_USBCMD) & (UCMD_RESET)) ;

	/* allow controller to reset, and leave time for
	 * the ULPI transceiver to reset too.
	 */
	msleep(100);
}

static int otg_used = 0;

int usbotg_init(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata = pdev->dev.platform_data;
	struct fsl_xcvr_ops *xops;

	pr_debug("%s: pdev=0x%p  pdata=0x%p\n", __func__, pdev, pdata);

	xops = fsl_usb_get_xcvr(pdata->transceiver);
	if (!xops) {
		printk(KERN_ERR "DR transceiver ops missing\n");
		return -EINVAL;
	}
	pdata->xcvr_ops = xops;
	pdata->xcvr_type = xops->xcvr_type;
	pdata->pdev = pdev;

	if (!otg_used) {
		if (fsl_check_usbclk() != 0)
			return -EINVAL;

		pr_debug("%s: grab pins\n", __func__);
		if (pdata->gpio_usb_active())
			return -EINVAL;

		if (clk_enable(usb_clk)) {
			printk(KERN_ERR "clk_enable(usb_clk) failed\n");
			return -EINVAL;
		}

		if (xops->init)
			xops->init(xops);

		if (xops->xcvr_type == PORTSC_PTS_SERIAL) {
			if (pdata->operating_mode == FSL_USB2_DR_HOST) {
				otg_set_serial_host();
				/* need reset */
				UOG_USBCMD |= UCMD_RESET;
				msleep(100);
			} else if (pdata->operating_mode == FSL_USB2_DR_DEVICE)
				otg_set_serial_peripheral();
			otg_set_serial_xcvr();
		} else if (xops->xcvr_type == PORTSC_PTS_ULPI) {
			otg_set_ulpi_xcvr();
		} else if (xops->xcvr_type == PORTSC_PTS_UTMI) {
			otg_set_utmi_xcvr();
		}
	}

	otg_used++;
	pr_debug("%s: success\n", __func__);
	return 0;
}
EXPORT_SYMBOL(usbotg_init);

void usbotg_uninit(struct fsl_usb2_platform_data *pdata)
{
	pr_debug("%s\n", __func__);

	otg_used--;
	if (!otg_used) {
		if (pdata->xcvr_ops && pdata->xcvr_ops->uninit)
			pdata->xcvr_ops->uninit(pdata->xcvr_ops);

		pdata->regs = NULL;

		if (machine_is_mx31_3ds()) {
			if (pdata->xcvr_ops && pdata->xcvr_ops->suspend)
				pdata->xcvr_ops->suspend(pdata->xcvr_ops);
			clk_disable(usb_clk);
		}

		pdata->gpio_usb_inactive();
		if (pdata->xcvr_type == PORTSC_PTS_SERIAL)
			clk_disable(usb_clk);
	}
}
EXPORT_SYMBOL(usbotg_uninit);
