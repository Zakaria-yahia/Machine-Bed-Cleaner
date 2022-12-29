/*
 * Stepper.c
 *
 * Created: 22/12/2022 12:14:08 ص
 *  Author: Electronica Care
 */ 
#include "Stepper.h"
#define period 5
void Stepper_init(void){
	 DDRC=0xff;
	
}

void Stepper_Run(uint8_t direction,char motor){
	switch (motor)
	{
		case 'x':
		{
			if (direction==0)
			{
				SETBIT(PORTC,0);
				SETBIT(PORTC,3);
				_delay_ms(period);
				CLRBIT(PORTC,0);
				SETBIT(PORTC,3);
				_delay_ms(period);
				SETBIT(PORTC,2);
				_delay_ms(period);
				CLRBIT(PORTC,3);
				SETBIT(PORTC,2);
				_delay_ms(period);
				SETBIT(PORTC,1);
				_delay_ms(period);
				CLRBIT(PORTC,2);
				_delay_ms(period);
				SETBIT(PORTC,0);
				_delay_ms(period);
				CLRBIT(PORTC,1);
				_delay_ms(period);
				SETBIT(PORTC,0);
				SETBIT(PORTC,3);
				_delay_ms(period);
			}else{
				SETBIT(PORTC,0);
				SETBIT(PORTC,3);
				_delay_ms(period);
				CLRBIT(PORTC,3);
				SETBIT(PORTC,0);
				_delay_ms(period);
				SETBIT(PORTC,1);
				_delay_ms(period);
				CLRBIT(PORTC,0);
				SETBIT(PORTC,1);
				_delay_ms(period);
				SETBIT(PORTC,2);
				_delay_ms(period);
				CLRBIT(PORTC,1);
				_delay_ms(period);
				SETBIT(PORTC,3);
				_delay_ms(period);
				CLRBIT(PORTC,2);
				_delay_ms(period);
				SETBIT(PORTC,0);
				SETBIT(PORTC,3);
				_delay_ms(period);
			}
		}
		
	case 'y':
		{
			if (direction==0)
			{
				SETBIT(PORTC,4);
				SETBIT(PORTC,7);
				_delay_ms(period);
				CLRBIT(PORTC,4);
				SETBIT(PORTC,7);
				_delay_ms(period);
				SETBIT(PORTC,6);
				_delay_ms(period);
				CLRBIT(PORTC,7);
				SETBIT(PORTC,6);
				_delay_ms(period);
				SETBIT(PORTC,5);
				_delay_ms(period);
				CLRBIT(PORTC,6);
				_delay_ms(period);
				SETBIT(PORTC,4);
				_delay_ms(period);
				CLRBIT(PORTC,5);
				_delay_ms(period);
				SETBIT(PORTC,7);
				SETBIT(PORTC,4);
				_delay_ms(period);
			}else{
				SETBIT(PORTC,4);
				SETBIT(PORTC,7);
				_delay_ms(period);
				CLRBIT(PORTC,7);
				SETBIT(PORTC,4);
				_delay_ms(period);
				SETBIT(PORTC,5);
				_delay_ms(period);
				CLRBIT(PORTC,4);
				SETBIT(PORTC,5);
				_delay_ms(period);
				SETBIT(PORTC,6);
				_delay_ms(5);
				CLRBIT(PORTC,5);
				_delay_ms(period);
				SETBIT(PORTC,7);
				_delay_ms(period);
				CLRBIT(PORTC,6);
				_delay_ms(period);
				SETBIT(PORTC,7);
				SETBIT(PORTC,4);
				_delay_ms(period);
			}
		
		
		}
	}
	
}