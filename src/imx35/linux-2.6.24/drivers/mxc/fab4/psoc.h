/* drivers/mxc/fab4/psoc.h
 *
 * Copyright 2008 Logitech
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

#define PSOC_WAIT_MDELAY 10
#define PSOC_WAIT_MTIMEOUT 10000
#define PSOC_CLOCK_UDELAY 2

#define WAIT_AND_POLL 0x800000

static u32 psoc_init[] = {
	/* init1 */
	0x328000, /* 1100101000000000000000 */
	0x000000, /* 0000000000000000000000 */
	0x000000, /* 0000000000000000000000 */
	0x000000, /* 0000000000000000000000 */
	0x000000, /* 0000000000000000000000 */
	0x000000, /* 0000000000000000000000 */
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x37804f, /* 1101111000000001001111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,

	/* init2 */
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x27d00f, /* 1001111101000000001111 */
	0x378037, /* 1101111000000000110111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,

	/* init3 3.3 V */
	0x37b807, /* 1101111011100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37b047, /* 1101111011000001000111 */
	0x37c28f, /* 1101111100001010001111 */
	0x37cfc7, /* 1101111100111111000111 */
	0x37d187, /* 1101111101000110000111 */
	0x37f897, /* 1101111111100010010111 */
	0x000000, /* 0000000000000000000000 */
	0x37b807, /* 1101111011100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37b047, /* 1101111011000001000111 */
	0x37c307, /* 1101111100001100000111 */
	0x37cf57, /* 1101111100111101010111 */
	0x37d187, /* 1101111101000110000111 */
	0x37b887, /* 1101111011100010000111 */
	0x37f897, /* 1101111111100010010111 */
	0x000000, /* 0000000000000000000000 */
	0x37b807, /* 1101111011100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37b047, /* 1101111011000001000111 */
	0x37c28f, /* 1101111100001010001111 */
	0x37cfcf, /* 1101111100111111001111 */
	0x37d187, /* 1101111101000110000111 */
	0x37f897, /* 1101111111100010010111 */
	0x000000, /* 0000000000000000000000 */
	0x37b807, /* 1101111011100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37b047, /* 1101111011000001000111 */
	0x37c307, /* 1101111100001100000111 */
	0x37cf47, /* 1101111100111101000111 */
	0x37d187, /* 1101111101000110000111 */
	0x37b887, /* 1101111011100010000111 */
	0x37f897, /* 1101111111100010010111 */
	0x000000, /* 0000000000000000000000 */
};

static u32 psoc_id_setup[] = {
	0x37b887, /* 1101111011100010000111 */
	0x370017, /* 1101110000000000010111 */
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x27d007, /* 1001111101000000000111 */
	0x378037, /* 1101111000000000110111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,
};

static u32 psoc_bluk_erase[] = {
	0x27e0af, /* 1001111110000010101111 */
	0x27f2b7, /* 1001111111001010110111 */
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x37802f, /* 1101111000000000101111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,
};

static u32 psoc_checksum_setup[] = {
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x27d207, /* 1001111101001000000111 */
	0x37803f, /* 1101111000000000111111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,
};

static u32 psoc_program[] = {
	0x27e2a7, /* 1001111110001010100111 */
	0x27f2b7, /* 1001111111001010110111 */
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x378017, /* 1101111000000000010111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,
};

static u32 psoc_secure[] = {
	0x27e2a7, /* 1001111110001010100111 */
	0x27f2b7, /* 1001111111001010110111 */
	0x37b807, /* 1101111011100000000111 */
	0x37b007, /* 1101111011000000000111 */
	0x27c1d7, /* 1001111100000111010111 */
	0x27c81f, /* 1001111100100000011111 */
	0x37a807, /* 1101111010100000000111 */
	0x37a01f, /* 1101111010000000011111 */
	0x27dc07, /* 1001111101110000000111 */
	0x37c987, /* 1101111100100110000111 */
	0x37d207, /* 1101111101001000000111 */
	0x378027, /* 1101111000000000100111 */
	0x37c007, /* 1101111100000000000111 */
	0x37f897, /* 1101111111100010010111 */

	WAIT_AND_POLL,
};
