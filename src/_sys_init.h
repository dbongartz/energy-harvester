/*
 * _sys_init.h
 *
 *  Created on: 21.06.2013
 *      Author: davidb
 */

#ifndef SYS_INIT_H_
#define SYS_INIT_H_

#include <stdint.h>

void _clk_init(void);

void _mclk_change(uint8_t freq);

#endif /* SYS_INIT_H_ */
