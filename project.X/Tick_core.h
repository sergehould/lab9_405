/* 
 * File:   Tick_core.h
 * Author: sh
 *
 * Created on January 28, 2021
 * Author   Date            Comments
 * SH       28 Jan 2021     v1.0
 * SH       3 Feb 2021      v1.1    Add void delay_ticks(unsigned int tics)  
 * SH       25 March 2021   v2.0    Add function TickDiff() and macro TickDiff2
 */

#ifndef TICK_CORE_H
#define	TICK_CORE_H
//#include "initBoard.h"
#include <stdint.h>


#define     SYS_FREQ            80000000 // Running at 80MHz
#define     TICKS_PER_SECOND    (SYS_FREQ >> 1)   // The core timer increments once for every two ticks of SYSCLK
/* Macro for some reason does not work with signed int32_t stamp type */
/* but works with a function: see TickDiff(()*/
//#define TickDiff2(a)     (TickGet()>=(int64_t)a ? TickGet()-(int64_t)a: 0x100000000 + TickGet()-(int64_t)a)
void delay_us(unsigned int us);
int64_t TickGet(void);
void delay_ticks(unsigned int tics);
void TickCoreReset(void);
int64_t TickDiff(int32_t stamp);

#endif	/* PWM_H */

