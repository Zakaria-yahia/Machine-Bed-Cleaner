/*
 * UART.c
 *
 * Created: 29/08/2022 08:50:35 م
 *  Author: Zakaria yahia
 */ 

#include "UART.h"

void (*UART_isr)(void);
/*****************************************************************************
* Function Name: UART_init
* Purpose      : initialize UART Protocol
* Parameters   : void
* Return value : void
*****************************************************************************/
void UART_init(void)
{
	UBRRL = 103;
	SETBIT(UCSRB,RXEN);
	SETBIT(UCSRB,TXEN);
	SETBIT(UCSRB,RXCIE);
	SETBIT(SREG,7);
}
/*****************************************************************************
* Function Name: UART_Transmit
* Purpose      : Transmit data in UART Protocol 
* Parameters   : Data will Transmit
* Return value : void
*****************************************************************************/
void UART_Transmit(uint8_t data)
{
	UDR =data;
	while(READBIT(UCSRA,TXC)==0);
	
}

/*****************************************************************************
* Function Name: UART_Transmit
* Purpose      : Receive data in UART Protocol
* Parameters   : void
* Return value : Received Data
*****************************************************************************/
uint8_t UART_Receive()
{
	while(READBIT(UCSRA,RXC)==0);
	return UDR;
}

ISR(USART_RXC_vect){
	
	UART_isr();
	
}