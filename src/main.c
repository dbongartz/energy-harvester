/* *****************************************************************************
 * EIT-TI Project SS2013
 *
 * Name:        Energy harvester with e-paper display.
 *
 * Description: This project will harvest energy from up to two independent low
 *              voltage / low energy sources using an LTC3109 flyback-converter.
 *              An MSP430FR5739 microcontroller measures the harvested and
 *              stored energy. An EA EPA-20A e-paper display is used to display
 *              measured data live. An serial interface is provided to read out
 *              the logged data.
 *
 * Author(s):   Pamela Bogner,
 *              David Bongartz
 *
 * File:        main.c
 *
 * Date:        15.05.2012
 * Revision:    0.1
 *
 * Notes:       -
 *
 * *****************************************************************************
 */

/* Includes */
#include <msp430.h>

#include <stddef.h>
#include <stdint.h>

#include "portdef.h"
#include "_sys_init.h"
#include "_system.h"
#include "_epa_disp.h"

/* Execute before C runtime initialization, DO NOT USE GLOBAL VARIABLES */
#pragma FUNC_EXT_CALLED(_system_pre_init)
int _system_pre_init(void)
{
	WDTCTL = WDTPW | WDTHOLD; /* Stop watchdog timer */

	/*  Initialize MSP430 General Purpose Input Output Ports
	 *
	 *  The GPIO registers should be set in a specific order:
	 *     PxOUT
	 *     PxSEL or PxSELx
	 *     PxDIR
	 *     PxREN
	 *     PxIES
	 *     PxIFG
	 *     PxIE
	 *
	 *     This will ensure that:
	 *         - IFG doesn't get set by manipulating the pin function, edge
	 *           select, and pull-up/down resistor functionalities (see
	 *           Section 8.2.6 of the MSP430 User's manual)
	 *         - Glitch-free setup (configuring the OUT register _before_
	 *           setting the pin direction)
	 *         - Pull-up/pull-down resistor enable with the correct direction
	 *           (.up. vs. .down.)
	 */

	PAOUT = P_TXD;
	PASEL0 = P_UCAP | P_USOL | P_UTEG | P_ISOL | P_ITEG | P_ILOAD;
	PASEL1 = P_UCAP | P_USOL | P_UTEG | P_ISOL | P_ITEG | P_ILOAD;
	PADIR = P_SPICLK | P_SPIOUT | P_TXD | P_D_C | P_VACCEL;
	PAREN = 0;
	PAIES = 0;
	PAIFG = 0;
	PAIE = 0;

	PBOUT = 0;
	PBSEL0 = 0;
	PBSEL1 = 0;
	PBDIR = P_FREE | P_VDISP | P_VAMPS | 0xFF00;
	PBREN = P_ACC0 | P_ACC1 | P_ACC2;
	PBIES = 0;
	PBIFG = 0;
	PBIE = 0;

	PJOUT = 0;
	PJSEL0 = BIT4 | BIT5; /* XTIN XTOUT */
	PJSEL1 = 0;
	PJDIR = P_LED0 | P_LED1 | P_LED2 | P_LED3;
	PJREN = 0;

	/* Initialize Clock System
	 *
	 * Load 16 MHz calibrated data for DCO
	 * -> MCLK:     8 MHz calib.
	 * -> SMCLK:    1x DCO = 8 MHz
	 * -> ACLK:     32.768 kHz crystal
	 */
	CSCTL0 = CSKEY; /* Unlock clock system */
	CSCTL1 = DCOFSEL_3; /* DCO = 8Mhz */
	CSCTL2 = SELA__XT1CLK | SELS__DCOCLK | SELM__DCOCLK;
	/* ACLK = 32kHz, SMCLK = 1Mhz, MCLK = 1Mhz */
	CSCTL3 = DIVA__1 | DIVS__8 | DIVM__8;
	/* XT1LF on in low power mode, SMCLK off */
	CSCTL4 = XT2OFF | SMCLKOFF;
	/* Check for clock failures */

	//TODO Remove DEBUG thing here:
	CSCTL2 |= SELA__VLOCLK;
	CSCTL4 |= XT1OFF;

	do {
		/* Clear XT2 and XT1 fault flags */
		CSCTL5 &= ~(XT2OFFG + XT1OFFG);
		/* Clear oscillator fault flag */
		SFRIFG1 &= ~OFIFG;
		//__delay_cycles(0xFF); /* Wait for possible fault */
	} while (SFRIFG1 & OFIFG);

	CSCTL0_H = 0xFF; /* Lock clock system */

	return 1; /* return(1) for auto_init(), return(0) for skipping */
}

/* Main */
int main(void)
{
	PJOUT |= P_LED0;

	_epa_spi_init();

	_epa_tests('A');

	while (1) {
		PJOUT ^= P_LED0;
		__delay_cycles(800000);
	}

	return 0;
}
