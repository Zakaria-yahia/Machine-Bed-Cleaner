/*
 * INTERRUPT.c
 *
 * Created: 20/12/2022 07:18:57 م
 *  Author: Electronica Care
 */
#include "INTERRUPT.h"

 
void (*Interrupt_isr)(void);
/*****************************************************************************
* Function Name: TIMER1_INPUT_CAPTURE_init
* Purpose      :init timer1  (NORMAL MODE, 10bit, no prescaler)
* Parameters   : void
* Return value : void
*****************************************************************************/
void INTERUPT_INPUT_CAPTURE_init(void){
	
	
	SETBIT(SREG,7); //Enable global int0
	CLRBIT(DDRD,2);
	SETBIT(DDRD,3);
	SETBIT(MCUCR,0);
	//	SETBIT(MCUSR,1);
	SETBIT(GICR,6);
	
	
	
}


ISR(INT0_vect){
	
	Interrupt_isr();
	
}
