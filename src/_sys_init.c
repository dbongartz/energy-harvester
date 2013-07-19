/*
 * _sys_init.c
 *
 *  Created on: 21.06.2013
 *      Author: davidb
 */

#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>

#include "_sys_init.h"

/* -----------------------------------------------------------------------------
 * Initialize Clock System
 *
 * Load 16 MHz calibrated data for DCO
 * -> MCLK:     8 MHz calib.
 * -> SMCLK:    1x DCO = 8 MHz
 * -> ACLK:     32.768 kHz crystal
 *
 * -----------------------------------------------------------------------------
 */
void _clk_init(void) {
	CSCTL0 = CSKEY;
	CSCTL1 = DCOFSEL_3; /* DCO = 8Mhz */

	CSCTL2 = SELA__XT1CLK | SELS__DCOCLK | SELM__DCOCLK;

	/* ACLK = 32kHz, SMCLK = 1Mhz, MCLK = 1Mhz */
	CSCTL3 = DIVA__1 | DIVS__8 | DIVM__8;

	/* XT1LF on in low power mode, SMCLK off */
	CSCTL4 = XT2OFF | SMCLKOFF;

	/* Check for clock failures */
	do {
		/* Clear XT2 and XT1 fault flags */
		CSCTL5 &= ~(XT2OFF + XT1OFFG);

		 /* Clear oscillator fault flag */
		SFRIFG1 &= ~OFIFG;

		//__delay_cycles(0xFF); /* Wait for possible fault */

	} while (SFRIFG1 & OFIFG);
}

void _mclk_change(uint8_t clock);
