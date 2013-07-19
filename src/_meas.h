/*
 * _meas.h
 *
 *  Created on: 21.06.2013
 *      Author: davidb
 */

#ifndef MEAS_H_
#define MEAS_H_

#include <stdint.h>

/* Includes */

/* Defines */

/* Globals */
struct _meas_config {
        uint8_t channels;
};

/* Makros */

/* Functions */

void _meas_init(void);

void _meas_conf(const struct _meas_config * config);

void _meas_start();

int _meas_read(); /* Aktueller Messwert */

int _meas_log_read(); /* Beliebiger Messwert */

#endif /* MEAS_H_ */
