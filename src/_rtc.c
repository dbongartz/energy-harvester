/*
 * _rtc.c
 *
 *  Created on: 21.06.2013
 *      Author: davidb
 */

#include <msp430.h>
#include "_rtc.h"

void _rtc_init()
{
	RTCCTL1 &= !RTCHOLD;
}

void _rtc_set(const struct _time_t * time)
{
	//TODO
}

void _rtc_read(struct _time_t * time)
{
	//TODO
}

