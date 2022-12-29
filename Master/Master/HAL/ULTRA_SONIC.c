/*
 * ULTRA_SONIC.c
 *
 * Created: 18/12/2022 10:00:19 م
 *  Author: Electronica Care
 */ 

#include "ULTRA_SONIC.h"

short time1=0,time2=0,time3=0;
/*****************************************************************************
* Function Name: TIMER1_INPUT_CAPTURE_init
* Purpose      :init timer1  (NORMAL MODE, 10bit, 1024 prescaler)
* Parameters   : void
* Return value : void
*****************************************************************************/
void ULTRA_SONIC_init(void){
	
	TCCR1A = 0;
	SETBIT(TCCR1B,CS10);
	SETBIT(TCCR1B,CS11);   //prescaler
	SETBIT(TCCR1B,ICES1);   // rising edge select
	SETBIT(TCCR1B,ICNC1);   // noise canclation
	SETBIT(TIFR,ICF1);     // clean flag
	SETBIT(DDRD,7);
	
	
}
/*



*/
uint8_t ULTRA_SONIC_distance(void){
	SETBIT(TCCR1B,ICES1);
	SETBIT(TIFR,ICF1);
	short distance;
	SETBIT(PORTD,7);
	SETBIT(PORTD,3);
	_delay_us(50);
	CLRBIT(PORTD,7);
	CLRBIT(PORTD,3);
	while (READBIT(TIFR,ICF1) == 0);
	
	time1 = ICR1;
	SETBIT(TIFR,ICF1);
	CLRBIT(TCCR1B,ICES1);
	
	while (READBIT(TIFR,ICF1) == 0);
	
	time2 = ICR1;
	SETBIT(TIFR,ICF1);
	
	TCNT1=0;
	
	
 distance =(((time2-time1) * 34600)*64 / F_CPU*2)/4;
	
	return distance;
}

