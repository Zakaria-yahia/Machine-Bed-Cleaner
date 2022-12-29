/*
 * std_macros.h
 *
 * Created: 8/20/2022 01:45:51 AM
 *  Author: Zakaria
 */ 

#include "TIMER0.h"

void (*timer0_ovf_isr)(void);
/*****************************************************************************
* Function Name: TIMER0_normaMode_init
* Purpose      : init timer in normal mode with no prescaler
* Parameters   : void
* Return value : void
*****************************************************************************/
void TIMER0_normaMode_ON(void){
	SETBIT(TCCR0,CS00); 
    SETBIT(TCCR0,CS01);//
	SETBIT(TIMSK,TOIE0); // enable timer ov interrupt
	TCNT0=0;

	

}


void TIMER0_normaMode_OFF(void){
	CLRBIT(TCCR0,CS00);
	CLRBIT(TCCR0,CS01);//
	CLRBIT(TIMSK,TOIE0); // enable timer ov interrupt
	TCNT0=0;

	

}

ISR(TIMER0_OVF_vect){
	timer0_ovf_isr();
}