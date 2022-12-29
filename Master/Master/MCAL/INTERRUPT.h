/*
 * INTERRUPT.h
 *
 * Created: 20/12/2022 07:19:18 م
 *  Author: Electronica Care
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "std_macros.h"

void INTERUPT_INPUT_CAPTURE_init(void);

extern void (*Interrupt_isr)(void);



#endif /* INTERRUPT_H_ */