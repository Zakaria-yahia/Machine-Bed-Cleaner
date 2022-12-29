/*
 * EXTERNAL_ENTERRUPT.h
 *
 * Created: 21/12/2022 11:12:38 م
 *  Author: Electronica Care
 */ 


#ifndef EXTERNAL_ENTERRUPT_H_
#define EXTERNAL_ENTERRUPT_H_

#include "std_macros.h"
extern void (*EXTERNAL_ENTERRUPT0_isr)(void);
extern void (*EXTERNAL_ENTERRUPT1_isr)(void);

void EXTERNAL_ENTERRUPT_init(void);



#endif /* EXTERNAL_ENTERRUPT_H_ */