/*
 * std_macros.h
 *
 * Created: 8/20/2022 01:45:51 AM
 *  Author: Zakaria
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_macros.h"
extern void (*timer0_ovf_isr)(void);
extern void (*timer0_ctc_isr)(void);

void TIMER0_normaMode_init(void);
void TIMER0_CTC_init(uint8_t);


#endif /* TIMER0_H_ */