/*
 * _epa_disp.c
 *
 *  Created on: 20.06.2013
 *      Author: davidb
 */

#include <msp430.h>
#include "_epa_disp.h"

#include <stdint.h>

#include "portdef.h"
#include "6x8_horizontal_MSB_1.h"

/* Module globals */
#pragma NOINIT(framebuf)
volatile uint8_t framebuf[8][3];


/* Initialize SPI for EA EPA-20A display */
void _epa_spi_init(void)
{
	UCB0CTLW0 |= UCSWRST; /* Reset and hold before changing settings */

	/* SLOW MODE */
	/* rising edge, MSB first, master mode, SPI mode, ACLK*/
	UCB0CTLW0 |= UCCKPL | UCMSB | UCMST | UCSYNC | UCSSEL__ACLK;

	/* FAST MODE */
	/* rising edge, MSB first, master mode, SPI mode, SMCLK*/
	//UCB0CTLW0 |= UCCKPL | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK;
	UCB0BRW = 0x01;
	UCB0IFG &= ~UCTXIFG; /* Clear interrupt flag */

	//TODO Enable interrupts

	PASEL1 |= P_SPICLK | P_SPIOUT;

	UCB0CTLW0 &= ~UCSWRST;

	// enable interrupts
}

void _epa_spi_send(void)
{

}

#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
	//TODO Check if new data and send

	UCB0IE &= ~UCTXIE; /* Clear interrupt flag */
}

void _epa_tests(char c)
{
	uint8_t row;
	char c2;

	unsigned int i;
	uint8_t fg;
	uint8_t bg;

	static const uint8_t lut[16] = { 0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x3f, 0xc0, 0xc3,
			0xcc, 0xcf, 0xf0, 0xf3, 0xfc, 0xff };
	c2 = c + 1;
	fg = WHITE;
	bg = BLACK;

	row = 0;
	do {
		framebuf[row][0] = lut[(font[c][row] >> 4) & 0x0F];
		framebuf[row][1] = lut[(font[c][row] | font[c2][row] >> 6) & 0x0F];
		framebuf[row][2] = lut[(font[c2][row] >> 2) & 0x0F];
	} while (++row < 8);


	row = 0;

	do {
		i = 0;
		do {
			if (fg == INVERT && bg == INVERT) {
				framebuf[i][row] = ~framebuf[i][row];
			} else if (fg != WHITE || bg != BLACK) {
				framebuf[i][row] = (framebuf[i][row] & fg) | ((framebuf[0][row] | bg) & ~fg);
			}
		} while (++i < 2);
	} while (++row < 8);
}


void _epa_init(void);

void _epa_sleep(uint8_t mode);

/* _epa_hline() - Draws a horizontal line
 *
 * Parameters:
 *
 * CAUTION: "x" and "length" has to be a multiply of 4 pixels!
 *
 *      x :             Top left x pixel coordinate of the line (4 px bound)
 *      y :             Top left y pixel coordinate of the line
 *      length :        Length of the line. (4 px bound)
 *      width:          Width of the line
 *      color:          Color of the line (WHITE, GRAY1, GRAY2, BLACK)
 */
void _epa_hline(uint8_t x, uint8_t y, uint8_t length, uint8_t width, uint8_t color);

/* _epa_box() - Fills a box with a color
 *
 * Parameters:
 *
 * CAUTION: "x" and "width" has to be a multiply of 4 pixels!
 *
 *      x :             Top left x pixel coordinate of the box (4 px bound)
 *      y :             Top left y pixel coordinate of the box
 *      width:          Width of the box (4 px bound)
 *      height:         Height of the box
 *      color:          Color of the box (WHITE, GRAY1, GRAY2, BLACK)
 */
void _epa_box(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

/* _epa_puts() - Prints a string
 *
 * Parameters:
 *
 * CAUTION: "x" has to be a multiply of 4 pixels! If "stringlength" isn't a
 * multiply of 2 chars, the last char will be blank.
 *
 *      x :             Top left x pixel coordinate of the string (4 px bound)
 *      y :             Top left y pixel coordinate of the string
 *      fg:             Foreground color of the string
 *      bg:             Background color of the string
 *      str:            String with terminating '\0'
 *
 *      Colors available: (WHITE, GRAY1, GRAY2, BLACK)
 */
void _epa_puts(uint8_t x, uint8_t y, uint8_t fg, uint8_t bg, const char* str);
