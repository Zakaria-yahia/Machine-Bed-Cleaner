/*
 * Master.c
 *
 * Created: 20/12/2022 07:14:04 م
 * Author : Electronica Care
 */ 



#include "std_macros.h"
#include "../HAL/GLCD.h"
#include "../HAL/ULTRA_SONIC.h"
#include "../HAL/LCD.h"
#include "../MCAL/INTERRUPT.h"
#include "../MCAL/TIMER0.h"
#include "../MCAL/UART.h"


uint8_t count_ovf;
uint8_t t1,t2,flag,hh;
static void ovf_isr(void);
static void INT_isr(void);

int main(void)
{
	
	Interrupt_isr=INT_isr;
	timer0_ovf_isr = ovf_isr;
	INTERUPT_INPUT_CAPTURE_init();
	GLCD_Init();
	Draw_Graph();
	LCD_init();
	UART_init();
	ULTRA_SONIC_init();
	uint8_t distance_y=0,distance_x=0;
	
	while (1)
	{
		
		LCD_write_command(0x80);
		distance_x= ULTRA_SONIC_distance();
		LCD_write_num(distance_x);
		distance_y=t1;
		LCD_write_command(0xc0);
		LCD_write_num(distance_y);
		
		UART_Transmit(distance_x);
		_delay_ms(1);
		UART_Transmit(distance_y);
		GLCD_GoToXY_shape(distance_x , distance_y);
		_delay_ms(50);
		GLCD_Clear(distance_x , distance_y);
		
		
	}
}




static void INT_isr(void){
	
	static uint8_t count;
	
	count++;
	
	if(count>=1 && READBIT(PIND,2)== 1)
	{
		TIMER0_normaMode_ON();
		count=1;
		flag=1;
		
		
	}else if (count== 2 && flag==1)
	{
		
		t1 = (((TCNT0+(count_ovf*256)) * 34600)* 64/ F_CPU*2)/4;
		flag=0;
		TIMER0_normaMode_OFF();
		count=0;
		count_ovf=0;
	}
	
}


static void ovf_isr(void){
	
	
	
	count_ovf++;
	
	
}
