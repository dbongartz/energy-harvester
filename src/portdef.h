/*
 * portdef.h
 *
 *  Created on: 20.06.2013
 *      Author: davidb
 */

#ifndef PORTDEF_H_
#define PORTDEF_H_

#define P_UCAP    BIT0 /* P1.0 */
#define P_USOL    BIT1 /* P1.1 */
#define P_UTEG    BIT2 /* P1.2 */
#define P_ISOL    BIT3 /* P1.3 */
#define P_ITEG    BIT4 /* P1.4 */
#define P_ILOAD   BIT5 /* P1.5 */
#define P_VAMPS   BIT9 /* P4.1: BIT1 */

#define P_SPIOUT  BIT6 /* P1.6 */
#define P_SPICLK  BIT7 /* P1.7 */
#define P_D_C     BITD /* P2.5: BIT5 */
#define P_BUSY    BITE /* P2.6: BIT6 */
#define P_VDISP   BIT8 /* P4.0: BIT0 */

#define P_VACCEL  BITF /* P2.7: BIT7 */
#define P_ACC0    BIT0 /* P3.0 */
#define P_ACC1    BIT1 /* P3.1 */
#define P_ACC2    BIT2 /* P3.2 */

#define P_PGDOUT  BIT8 /* P2.0: BIT0 */
#define P_PGDSOL  BITB /* P2.3: BIT3 */
#define P_PGDTEG  BITC /* P2.4: BIT4 */

#define P_SWIRQ   BIT4 /* P3.4 */
#define P_SW0     BIT5 /* P3.5 */
#define P_SW1     BIT6 /* P3.6 */
#define P_SW2     BIT7 /* P3.7 */

#define P_FREE    BIT3 /* P3.3 */

#define P_RXD     BIT9 /* P2.1: BIT1 */
#define P_TXD     BITA /* P2.2: BIT2 */

#define P_LED0    BIT0 /* PJ.0 */
#define P_LED1    BIT1 /* PJ.1 */
#define P_LED2    BIT2 /* PJ.2 */
#define P_LED3    BIT3 /* PJ.3 */

#endif /* PORTDEF_H_ */
