/*
 * UART.h
 *
 * Created: 29/08/2022 08:51:17 م
 *  Author: zakaria yahia
 */ 
#include "std_macros.h"

#ifndef UART_H_
#define UART_H_
void UART_init(void);
void UART_Transmit(uint8_t data);
uint8_t UART_Receive();




#endif /* UART_H_ */