/*
 * std_macros.h
 *
 * Created: 8/20/2022 01:45:51 AM
 *  Author: Zakaria
 */ 

 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_macros.h"
extern void (*timer1_ovf_isr)(void);
extern void (*timer1_ctc_isr)(void);

void TIMER1_normaMode_init(void);
void TIMER1_CTC_init(uint8_t);


#endif /* TIMER1_H_ */