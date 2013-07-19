/*
 * _rtc.h
 *
 *  Created on: 21.06.2013
 *      Author: davidb
 */

#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

/* Variables */
struct _time_t {
	uint16_t year;
	//TODO
};

/* Functions */
void _rtc_init();

void _rtc_set(const struct _time_t * time);

void _rtc_read(struct _time_t * time);


#endif /* RTC_H_ */
