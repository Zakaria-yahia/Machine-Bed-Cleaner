/*
 * Stepper.h
 *
 * Created: 22/12/2022 12:14:24 ص
 *  Author: Electronica Care
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#include "std_macros.h"

void Stepper_init(void);
void Stepper_Run(uint8_t direction,char motor);

#endif /* STEPPER_H_ */