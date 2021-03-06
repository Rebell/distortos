/**
 * \file
 * \brief Header with definitions for bit-banding for ARMv7-M
 *
 * \author Copyright (C) 2015-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_ARCHITECTURE_ARM_ARMV6_M_ARMV7_M_INCLUDE_DISTORTOS_ARCHITECTURE_ARMV7_M_BIT_BANDING_H_
#define SOURCE_ARCHITECTURE_ARM_ARMV6_M_ARMV7_M_INCLUDE_DISTORTOS_ARCHITECTURE_ARMV7_M_BIT_BANDING_H_

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)

/*---------------------------------------------------------------------------------------------------------------------+
| global defines
+---------------------------------------------------------------------------------------------------------------------*/

/** beginning of SRAM region which is aliased in bit-band region */
enum { bitbandSramBegin = 0x20000000 };

/** end of SRAM region which is aliased in bit-band region */
enum { bitbandSramEnd = 0x200fffff };

/** start of bit-band alias region of SRAM */
enum { bitbandSramBase = 0x22000000 };

/** beginning of peripheral region which is aliased in bit-band region */
enum { bitbandPeripheralBegin = 0x40000000 };

/** end of peripheral region which is aliased in bit-band region */
enum { bitbandPeripheralEnd = 0x400fffff };

/** start of bit-band alias region of peripherals */
enum { bitbandPeripheralBase = 0x42000000 };

/** address of bit-band alias for SRAM region */
#define BITBAND_SRAM_ADDRESS(address, bit) \
		(bitbandSramBase + (((unsigned long)address) - bitbandSramBegin) * 32 + (bit) * 4)

/** address of bit-band alias for peripheral region */
#define BITBAND_PERIPHERAL_ADDRESS(address, bit) \
		(bitbandPeripheralBase + (((unsigned long)address) - bitbandPeripheralBegin) * 32 + (bit) * 4)

/** address of bit-band alias for any region */
#define BITBAND_ADDRESS(address, bit) \
		((((unsigned long)address) >= bitbandSramBegin) && (((unsigned long)address) <= bitbandSramEnd) ? \
		BITBAND_SRAM_ADDRESS(address, bit) : \
		(((unsigned long)address) >= bitbandPeripheralBegin) && (((unsigned long)address) <= bitbandPeripheralEnd) ? \
		BITBAND_PERIPHERAL_ADDRESS(address, bit) : \
		0 /* fail */ )

/** bit-band alias in SRAM region */
#define BITBAND_SRAM(address, bit)			(*(volatile unsigned long*)BITBAND_SRAM_ADDRESS(address, bit))

/** bit-band alias in peripheral region */
#define BITBAND_PERIPHERAL(address, bit)	(*(volatile unsigned long*)BITBAND_PERIPHERAL_ADDRESS(address, bit))

/** bit-band alias in any region */
#define BITBAND(address, bit)				(*(volatile unsigned long*)BITBAND_ADDRESS(address, bit))

#endif	/* defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) */

#endif	/* SOURCE_ARCHITECTURE_ARM_ARMV6_M_ARMV7_M_INCLUDE_DISTORTOS_ARCHITECTURE_ARMV7_M_BIT_BANDING_H_ */
