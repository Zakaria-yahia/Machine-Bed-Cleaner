/*
 * std_macros.h
 *
 * Created: 8/20/2022 01:45:51 AM
 *  Author: Zakaria
 */ 

#include "TIMER1.h"

void (*timer1_ovf_isr)(void);
void (*timer1_ctc_isr)(void);

/*****************************************************************************
* Function Name: TIMER0_normaMode_init
* Purpose      : init timer in normal mode with no prescaler
* Parameters   : void
* Return value : void
*****************************************************************************/
void TIMER1_normaMode_init(void){
	SETBIT(TCCR2,CS20); // NO PRESCALER
	SETBIT(TCCR2,FOC2);
	
	//SETBIT(TIMSK,TOIE2); // enable timer ov interrupt
	SETBIT(SREG, 7); // enable global interrupt

}

/*****************************************************************************
* Function Name: TIMER0_CTC_init
* Purpose      : init timer in CTC with no prescaler
* Parameters   : void
* Return value : void
*****************************************************************************/
void TIMER1_CTC_init(uint8_t oc){
	SETBIT(TCCR2,CS00);

	SETBIT(TCCR2,FOC2);
	SETBIT(TCCR2,WGM21);
	OCR2 = oc;
	//SETBIT(TIMSK,OCIE2);
	//SETBIT(SREG, 7); 
}


/*****************************************************************************
* Function Name: TIMER0_freqGen_init
* Purpose      : init timer to generate freq
* Parameters   : void
* Return value : void
*****************************************************************************/
/*


*/
void TIMER1_freqGen_init(uint8_t oc){
	SETBIT(DDRB, 3); 
	SETBIT(TCCR0,CS00); 
	SETBIT(TCCR0,FOC0);
	SETBIT(TCCR0,WGM01); 
	SETBIT(TCCR0,COM00);
	OCR0 = oc;
}

ISR(TIMER2_OVF_vect){
	timer1_ovf_isr();
}

ISR(TIMER2_COMP_vect){
	timer1_ctc_isr();
}