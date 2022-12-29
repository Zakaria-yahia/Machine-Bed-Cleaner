#ifndef __GLCD_H__
#define __GLCD_H__

#include "std_macros.h"

#define GLCD_DATA_PORT      PORTA
#define GLCD_CONTROL_PORT   PORTC

#define GLCD_DATA_PORT_DIR      DDRA
#define GLCD_CONTROL_PORT_DIR   DDRC

#define RS_GR     1
#define EN_GR     0
#define CS1    3
#define CS2    4
#define RST    2

/* Command List

0x3f = Turn on GLCD page
0x0c = Enable GLCD page

*/


void GLCD_Init();

void GLCD_SelectChip(uint8_t selection); // 0x00 of 0x0f or 0xf0 or 0xff

void GLCD_SelectPage(uint8_t selection);//from 0 to 7

void GLCD_GoToXY(uint8_t x , uint8_t y);// x 0-127 , y 0-7

void GLCD_CmdWrite(uint8_t cmd);

void GLCD_DataWrite(uint8_t data);

void GLCD_DisplayChar(uint8_t *ptr_array);

void GLCD_DispalyNum(uint32_t num, uint8_t x , uint8_t y);

void GLCD_Clear(uint8_t x , uint8_t y);
void GLCD_GoToXY_dot(uint8_t x , uint8_t y);
void GLCD_GoToXY_shape(uint8_t x , uint8_t y);
void Draw_Graph(void);

#endif

