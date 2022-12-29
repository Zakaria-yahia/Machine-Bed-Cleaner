/*
 * Slave.c
 *
 * Created: 20/12/2022 07:31:57 م
 * Author : Electronica Care
 */ 

#include "std_macros.h"
#include "../HAL/LCD.h"
#include "../MCAL/UART.h"
#include "../MCAL/TIMER0.h"
#include "../MCAL/TIMER1.h"
#include "../MCAL/EXTERNAL_ENTERRUPT.h"
#include "../HAL/Stepper.h"
static void UART_RX_isr(void);
void Stepping_clockwise(uint8_t distance_x, uint8_t distance_y);
void Stepping_Counter_clockwise(uint8_t distance_x, uint8_t distance_y);
static void X_Motor_isr(void);
static void Y_Motor_isr(void);
static void INT0_isr(void);
static void INT1_isr(void);
uint8_t distance_x,distance_y,data;
uint16_t steps_x,steps_y;
uint8_t go_fwd,go_rev;
  uint8_t flag_fwd=0,flag_rev=0;
#define period 5
#define x 'x'
#define y 'y'
#define FWD 0
#define REV 1
int main(void)
{
	 LCD_init();
   UART_isr = UART_RX_isr;
   timer0_ovf_isr=X_Motor_isr;
   timer1_ovf_isr=Y_Motor_isr;
   EXTERNAL_ENTERRUPT0_isr=INT0_isr;
   EXTERNAL_ENTERRUPT1_isr=INT1_isr;
   EXTERNAL_ENTERRUPT_init();
   TIMER0_normaMode_init();
   TIMER1_normaMode_init();
	Stepper_init();
   UART_init();
  
   
   
 
    while (1) 
    {
		
		LCD_write_command(0x80);
		LCD_write_string("X=");
		LCD_write_num(distance_x);
		LCD_write_string("mm");
		LCD_write_string(" Y =");
		LCD_write_num(distance_y);
		LCD_write_string("mm");
		steps_x = (distance_x*10)/4;
		steps_y = (distance_y*10)/4;
		LCD_write_command(0xc0);
		LCD_write_string("X=");
		LCD_write_num(steps_x);
		
		LCD_write_string(" Y=");
		LCD_write_num(steps_y);
		if (go_fwd==1 && (0 == flag_fwd))
		{
				flag_fwd=1;
				SETBIT(TIMSK,TOIE0);
				SETBIT(TIMSK,TOIE2);
			
			
		}
		
		if (go_rev==1 && (0 == flag_rev))
		{
			flag_rev=1;
			SETBIT(TIMSK,TOIE0);
			SETBIT(TIMSK,TOIE2);
			
		}
		
		
		
		
		
    }
}

static void X_Motor_isr(void){
	
	
	
	
	static uint8_t count=0;
	count++;
	if (go_fwd==1 && go_rev==0)
	{
		if (count<=steps_x)
		{
			Stepper_Run(FWD,x);
			}else{
			count=0;
			flag_fwd=0;
			CLRBIT(TIMSK,TOIE0);
			
		}
		if (count>=steps_x)
		{
			go_fwd=0;
			flag_fwd=0;
			count=0;
			CLRBIT(TIMSK,TOIE0);
		}
	}
	 
	if (go_rev==1 && go_fwd==0)
	{
		if (count<=steps_x)
		{
			Stepper_Run(REV,x);
			}else{
			count=0;
			flag_rev=0;
			CLRBIT(TIMSK,TOIE0);
			
		}
		if (count>=steps_x)
		{
			go_rev=0;
			flag_rev=0;
			count=0;
			CLRBIT(TIMSK,TOIE0);
		}
		
	}
	  
	
}


static void Y_Motor_isr(void){
	
	static uint8_t count=0;
	count++;
	if (go_fwd==1 && go_rev==0)
	{
		if (count<=steps_y)
		{
			Stepper_Run(FWD,y);
			}else{
			count=0;
			flag_fwd=0;
			CLRBIT(TIMSK,TOIE2);
		}
		if (count>=steps_y)
		{
			go_fwd=0;
			flag_fwd=0;
			count=0;
			CLRBIT(TIMSK,TOIE2);
		}
		
	}
	
	
	if (go_rev==1 && go_fwd==0)
	{
		if (count<=steps_y)
		{
			Stepper_Run(REV,y);
			}else{
			count=0;
			flag_rev=0;
			CLRBIT(TIMSK,TOIE2);
		}
		if (count>=steps_y)
		{
			go_rev=0;
			flag_rev=0;
			count=0;
			CLRBIT(TIMSK,TOIE2);
		}
		
	}
	
	
}
static void INT0_isr(void){
	if (go_fwd==0 && go_rev==0)
	{
		go_fwd=1;
		
	}
	
}

static void INT1_isr(void){
	if (go_rev==0 && go_fwd ==0)
	{
		go_rev=1;
		
	}

	
}

static void UART_RX_isr(void){
	static uint8_t count=0;
	count++;
	data = UDR;
	if (count==1)
	{
		distance_x=data;
	}else if (count==2)
	{
		distance_y=data;
		count=0;
	}
	
}