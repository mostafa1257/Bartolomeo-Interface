/*
    FreeRTOS V7.1.0 - Copyright (C) 2011 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

#ifndef PORTMACRO_H
#define PORTMACRO_H

#include <msp430.h>
#include <stdint.h>

#if __MSPGCC__ < 20120406
#error FreeRTOS-MSPGCC requires version 20120406 or higher
#elif __MSPGCC__ > 20120406 && __MSPGCC__ < 20120627
#error MSPGCC development releases are buggy, update to 20120627 or higher
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.  
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		int
#define portSTACK_TYPE	unsigned portSHORT
#define portBASE_TYPE	portSHORT
/* Beware: this is only valid for data pointers, not function pointers */
#define portPOINTER_SIZE_TYPE uintptr_t

#if __MSP430X__ & ( __MSP430_CPUX_TARGET_SR20__ | __MSP430_CPUX_TARGET_ISR20__ )
#define portSAVED_REGISTER_TYPE uint20_t
#else /* __MSP430X__ */
#define portSAVED_REGISTER_TYPE portBASE_TYPE
#endif /* __MSP430X__ */

/* Stack sizes are in words, but a major component can be the TCB.
 * Since the size of the TCB depends on the memory model, abstract it.
 * Keep in mind that the memory model also affects the size of return
 * addresses.  Also consider adding space for two TCBs if the task has
 * interrupts enabled, since an interrupt handler will need space for
 * essentially the same information as a TCB, plus whatever its local
 * stack requirements may be. */
#define portTCB_SIZE_WORDS (3+12*sizeof(portSAVED_REGISTER_TYPE)/sizeof(portBASE_TYPE))

/* %u will not print a long int */
#define portLU_PRINTF_SPECIFIER_REQUIRED 1

#ifndef portACLK_FREQUENCY_HZ
/* The tick ISR runs off the ACLK, not the MCLK.  This is normally 32
 * kiHz, but may be another value if the crystal is unavailable and
 * ACLK derives from VLOCLK.  That value is MCU-specific; e.g.  for
 * the MSP430G2553 a reasonable definition is:
 *     ((IFG1 & OFIFG) ? * 12000U : 32768U)
 * As implied by this, the value is not necessarily a constant, though it
 * should remain constant after the platform is configured.
 */
#define portACLK_FREQUENCY_HZ			32768U
#endif /* portACLK_FREQUENCY_HZ */

#if( configUSE_16_BIT_TICKS == 1 )
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif
/*-----------------------------------------------------------*/	

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS()	__disable_interrupt()
#define portENABLE_INTERRUPTS()		__enable_interrupt()
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#define portNO_CRITICAL_SECTION_NESTING		( ( unsigned portSHORT ) 0 )

#define portENTER_CRITICAL()													\
{																				\
extern volatile unsigned portSHORT usCriticalNesting;							\
																				\
	portDISABLE_INTERRUPTS();													\
																				\
	/* Now interrupts are disabled ulCriticalNesting can be accessed */			\
	/* directly.  Increment ulCriticalNesting to keep a count of how many */	\
	/* times portENTER_CRITICAL() has been called. */							\
	usCriticalNesting++;														\
}

#define portEXIT_CRITICAL()														\
{																				\
extern volatile unsigned portSHORT usCriticalNesting;							\
																				\
	if( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )					\
	{																			\
		/* Decrement the nesting count as we are leaving a critical section. */	\
		usCriticalNesting--;													\
																				\
		/* If the nesting level has reached zero then interrupts should be */	\
		/* re-enabled. */														\
		if( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )				\
		{																		\
			portENABLE_INTERRUPTS();											\
		}																		\
	}																			\
}

/*-----------------------------------------------------------*/

/* Task utilities. */
extern void vPortYield( void ) __attribute__ ( ( __naked__ ) );
#define portYIELD()					vPortYield()
void
#if (__MSPGCC__ > 20120406) && !!(__MSP430X__)
 __attribute__ ( ( __c16__ ) )
#endif /* CPUX */
 __attribute__ ( ( __naked__ ) )
vPortYieldFromISR( void );
#define portYIELD_FROM_ISR(x) do {				\
		if (x)	{								\
			vPortYieldFromISR();				\
		}										\
	} while (0)
#define portNOP()					__nop()
/*-----------------------------------------------------------*/

/* Hardwware specifics. */
#define portBYTE_ALIGNMENT			2
#define portSTACK_GROWTH			( -1 )
#define portTICK_RATE_MS			( ( portTickType ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )

/* If we're using the UCS, there are two major chip errata which can
 * cause clock anomalies: UCS7 and UCS10.  We work around them by only
 * running the FLL periodically.  Ensure that we don't re-enable it
 * when leaving a low-power mode or during context switches. */

#if ! defined( portDISABLE_FLL )
#if defined(__MSP430_HAS_UCS__) || defined(__MSP430_HAS_UCS_RF__)
#define portDISABLE_FLL 1
#endif
#endif

#if ! defined( portLPM_bits )
#if portDISABLE_FLL
/* Exclude SCG0 from bits cleared on return, so FLL remains
 * disabled. */
#define portLPM_bits ( LPM4_bits & ~SCG0 )
#else /* portDISABLE_FLL */
#define portLPM_bits LPM4_bits
#endif /* portDISABLE_FLL */
#endif /* portLPM_bits */

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

