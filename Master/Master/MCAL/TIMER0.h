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
void TIMER0_normaMode_ON(void);
void TIMER0_normaMode_OFF(void);


#endif /* TIMER0_H_ */