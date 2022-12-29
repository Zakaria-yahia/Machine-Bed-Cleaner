/*
 * std_macros.h
 *
 * Created: 8/20/2022 01:45:51 AM
 *  Author: Zakaria
 */ 

#include "TIMER0.h"

void (*timer0_ovf_isr)(void);
void (*timer0_ctc_isr)(void);

/*****************************************************************************
* Function Name: TIMER0_normaMode_init
* Purpose      : init timer in normal mode with no prescaler
* Parameters   : void
* Return value : void
*****************************************************************************/
void TIMER0_normaMode_init(void){
	SETBIT(TCCR0,CS00); // NO PRESCALER

	SETBIT(TCCR0,FOC0);
	
	//SETBIT(TIMSK,TOIE0); // enable timer ov interrupt
	//SETBIT(SREG, 7); // enable global interrupt

}

/*****************************************************************************
* Function Name: TIMER0_CTC_init
* Purpose      : init timer in CTC with no prescaler
* Parameters   : void
* Return value : void
*****************************************************************************/
void TIMER0_CTC_init(uint8_t oc){
	SETBIT(TCCR0,CS00); 
	 
	SETBIT(TCCR0,FOC0);
	SETBIT(TCCR0,WGM01); 
	OCR0 = oc;
	SETBIT(TIMSK,OCIE0); 
	SETBIT(SREG, 7); 
}


/*****************************************************************************
* Function Name: TIMER0_freqGen_init
* Purpose      : init timer to generate freq
* Parameters   : void
* Return value : void
*****************************************************************************/
/*


*/
void TIMER0_freqGen_init(uint8_t oc){
	SETBIT(DDRB, 3); 
	SETBIT(TCCR0,CS00); 
	SETBIT(TCCR0,FOC0);
	SETBIT(TCCR0,WGM01); 
	SETBIT(TCCR0,COM00);
	OCR0 = oc;
}

ISR(TIMER0_OVF_vect){
	timer0_ovf_isr();
}

ISR(TIMER0_COMP_vect){
	timer0_ctc_isr();
}