/* drivers/char/jive/jive_wheel.c
 *
 * Copyright 2007 Logitech.
 *	Richard Titmuss <richard_titmuss@logitech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/signal.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/major.h>
#include <linux/string.h>
#include <linux/fcntl.h>
#include <linux/ptrace.h>
#include <linux/ioport.h>
#include <linux/mm.h> 
#include <linux/init.h>
#include <linux/circ_buf.h>
#include <linux/serial.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/init.h>

#include <asm/mach-types.h>
#include <asm/system.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <asm/bitops.h>
#include <asm/delay.h>
#include <asm/hardware.h> 

#include <asm/arch/regs-gpio.h>
#include <asm/arch/regs-timer.h>
#include <asm/arch/map.h>

#include <asm/io.h>

#define PULSES_PER_DETENT 2

#define DEBOUNCE_PERIOD_MS 2
#define PRESS_TIME_MS 4
#define RELEASE_TIME_MS 40

static int pos;

static int lastAB;

static unsigned int state[PRESS_TIME_MS / DEBOUNCE_PERIOD_MS];

static unsigned int count;

static unsigned int index;

static struct input_dev *wheel_dev;

struct timer_list wheel_timer;


static void wheel_scan(unsigned long data)
{		
	int i, AB, ABCD;

	if (++index >= ARRAY_SIZE(state)) {
		index = 0;
	}

	// read A and B
	state[index] = s3c2410_gpio_getpin(S3C2410_GPG4) ? (1 << 0) : 0;
	state[index] |= s3c2410_gpio_getpin(S3C2410_GPG5) ? (1 << 1) : 0;


	/* debounce switches */
	AB = 0xFF;
	for (i = 0; i < ARRAY_SIZE(state); i++) {
		AB &= state[i];
	}


	/* CW rotation:
	 * A B  C D (CD are previous AB state)
	 * 0 1  1 1  => 0x7
	 * 0 0  0 1  => 0x1
	 * 1 0  0 0  => 0x8
	 * 1 1  1 0  => 0xE
	 *
	 * CCW rotation
	 * A B  C D
	 * 1 0  1 1  => 0xB
	 * 0 0  1 0  => 0x2
	 * 0 1  0 0  => 0x4
	 * 1 1  0 1  => 0xD
	 */


	/* wheel state */
	ABCD = (AB << 2) | lastAB;

	switch (ABCD) {
	case 0x1:
	case 0x8:
	case 0x7:
	case 0xE:
		/* CW rotation */
		pos += 1;
		count = 0;
		lastAB = AB;
		//printk(KERN_DEBUG "\tAB %x ABCD %x  1\n", AB, ABCD);
		break;

	case 0xB:
	case 0x4:
	case 0x2:
	case 0xD:
		/* CCW rotation */
		pos -= 1;
		count = 0;
		lastAB = AB;
		//printk(KERN_DEBUG "\tAB %x ABCD %x  -1\n", AB, ABCD);
		break;

	case 0x0:
	case 0x5:
	case 0xA:
	case 0xF:
		/* no change */
		break;

	default:
		/* impossible state */
		printk(KERN_INFO "bad wheel state %x\n", ABCD);
	}


	/* update detent */
	if (pos > PULSES_PER_DETENT) {
		input_report_rel(wheel_dev, REL_WHEEL, 1);
		input_sync(wheel_dev);
		pos = 0;
	}

	if (pos < -PULSES_PER_DETENT) {
		input_report_rel(wheel_dev, REL_WHEEL, -1);
		input_sync(wheel_dev);
		pos = 0;
	}

	if (count++ < (RELEASE_TIME_MS / DEBOUNCE_PERIOD_MS)) {
		/* keep scanning while wheel is rotating */
		mod_timer(&wheel_timer, jiffies + (DEBOUNCE_PERIOD_MS * HZ/1000));
	}
	else {
		/* return the lines to interrupt */
		s3c2410_gpio_cfgpin(S3C2410_GPG4, S3C2410_GPIO_SFN2);
		s3c2410_gpio_cfgpin(S3C2410_GPG5, S3C2410_GPIO_SFN2);
	}

	return;
}

static irqreturn_t wheel_irq(int irq, void *dev_id) 
{
	s3c2410_gpio_cfgpin(S3C2410_GPG4, S3C2410_GPIO_INPUT);
	s3c2410_gpio_cfgpin(S3C2410_GPG5, S3C2410_GPIO_INPUT);

	/* scan wheel */
	mod_timer(&wheel_timer, jiffies); // now

	return IRQ_HANDLED;
}		


#define IRQ_FLAGS IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_SAMPLE_RANDOM

static int __init wheel_init(void)
{
	int i;

	/* For compatibility with the old bootloader allow s3c2413 machines
	 * to work here too. We can't use machine_is_s3c2413() here as that
	 * machine is not configured in the kernel.
	 *
	 * The S3C2413 hack should be removed when the old bootloader has
	 * been phased out.
	 */
	if (!(machine_is_jive() || machine_arch_type == MACH_TYPE_S3C2413))
		return 0;

	// we need to register at least one button and two relative axes 
	// to emulate a mouse
	wheel_dev = input_allocate_device();
	if (wheel_dev == NULL) {
		printk(KERN_ERR "failed to allocate input device\n");
		return -ENOMEM;
	}

	wheel_dev->evbit[0] = BIT(EV_REL);
	wheel_dev->relbit[0] = BIT(REL_WHEEL);
	wheel_dev->name = "Wheel";

	input_register_device(wheel_dev);

	/* Key debounce state */
	index = 0;
	lastAB = 0;
	for (i = 0; i < ARRAY_SIZE(state); i++) {
		state[i] = 0;
	}

	init_timer(&wheel_timer);
	wheel_timer.function = wheel_scan;


        if (request_irq(IRQ_EINT12, wheel_irq, IRQ_FLAGS, "CCW_B", NULL)) {
                 printk(KERN_ERR "Could not allocate CCW_B on IRQ_EINT12 !\n");
                 return -EIO;
	}

        if (request_irq(IRQ_EINT13, wheel_irq, IRQ_FLAGS, "CW_A", NULL)) {
                 printk(KERN_ERR "Could not allocate CW_A on IRQ_EINT13 !\n");
                 return -EIO;
	}

	s3c2410_gpio_irqfilter(S3C2410_GPG4, 1, 0);
	s3c2410_gpio_irqfilter(S3C2410_GPG5, 1, 0);

    	return 0;
}

static void __exit wheel_exit(void) {
	free_irq(IRQ_EINT12, NULL);
	free_irq(IRQ_EINT13, NULL);

	input_unregister_device(wheel_dev);
}

module_init(wheel_init);
module_exit(wheel_exit);


MODULE_DESCRIPTION("Jive wheel driver");
MODULE_AUTHOR("Logitech");
MODULE_LICENSE("GPL");



