/*
 * _epa_disp.h
 *
 *  Created on: 20.06.2013
 *      Author: davidb
 */
#ifndef EPA_DISP_H_
#define EPA_DISP_H_

#include <stdint.h>
#include "portdef.h"

/* Color defines */
#define WHITE  0xFF
#define GRAY1  0xAA
#define GRAY2  0x55
#define BLACK  0x00
#define INVERT 0x01

/* Globals *

/* Macros */
#define _epa_on() PBOUT |= P_VDISP
#define _epa_off() PBOUT &= !P_VDISP

/* Functions */

//TODO Remove DEBUG thing here:
void _epa_tests(char c);

void _epa_spi_init(void);
void _epa_spi_send(void);

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


/* Interrupts */

#endif /* EPA_DISP_H_ */
