#include "GLCD.h"


//Decimal Numbers in 3 X 5 Format 
static const char Dec_FontLookup [][5] =
{
    {0x3E, 0x51, 0x49, 0x45, 0x3E},// 0 
    {0x00, 0x42, 0x7F, 0x40, 0x00},// 1 
    {0x42, 0x61, 0x51, 0x49, 0x46},// 2 
    {0x21, 0x41, 0x45, 0x4B, 0x31},// 3 
    {0x18, 0x14, 0x12, 0x7F, 0x10},// 4 
    {0x27, 0x45, 0x45, 0x45, 0x39},// 5 
    {0x3C, 0x4A, 0x49, 0x49, 0x30},// 6 
    {0x01, 0x71, 0x09, 0x05, 0x03},// 7 
    {0x36, 0x49, 0x49, 0x49, 0x36},// 8 
    {0x06, 0x49, 0x49, 0x29, 0x1E},// 9 
};


void GLCD_Init()
{
    GLCD_CONTROL_PORT_DIR = 0xff;
    GLCD_DATA_PORT_DIR    = 0xff;

    GLCD_DATA_PORT = 0xff;
    
    SETBIT(GLCD_CONTROL_PORT,RS_GR);
    SETBIT(GLCD_CONTROL_PORT,EN_GR);
    SETBIT(GLCD_CONTROL_PORT,RST);

    CLRBIT(GLCD_CONTROL_PORT,RST);
    _delay_us(10);
    SETBIT(GLCD_CONTROL_PORT,RST);
    _delay_us(10);

    CLRBIT(GLCD_CONTROL_PORT,RS_GR);
    
    SETBIT(GLCD_CONTROL_PORT,CS1);
    SETBIT(GLCD_CONTROL_PORT,CS2);

    GLCD_CmdWrite(0x3F);
    GLCD_CmdWrite(0xC0);

    CLRBIT(GLCD_CONTROL_PORT,CS1);
    CLRBIT(GLCD_CONTROL_PORT,CS2);

    SETBIT(GLCD_CONTROL_PORT,EN_GR);
    
}

void GLCD_SelectChip(uint8_t selection) // 0x00 or 0x0f or 0xf0 or 0xff
{
    switch (selection)
    {
        case 0x00:
        {
            CLRBIT(GLCD_CONTROL_PORT,CS1);
            CLRBIT(GLCD_CONTROL_PORT,CS2);
        }break;
        case 0xf0:
        {
            SETBIT(GLCD_CONTROL_PORT,CS1);
            CLRBIT(GLCD_CONTROL_PORT,CS2);

        }break;
        case 0x0f:
        { 
            CLRBIT(GLCD_CONTROL_PORT,CS1);
            SETBIT(GLCD_CONTROL_PORT,CS2);

        }break;
        case 0xff:
        { 
            SETBIT(GLCD_CONTROL_PORT,CS1);
            SETBIT(GLCD_CONTROL_PORT,CS2);

        }break;
    }
}

void GLCD_SelectPage(uint8_t selection)//from 0 to 7
{
    switch (selection)
    {
    case 0: GLCD_CmdWrite(0xB8);break;
    case 1: GLCD_CmdWrite(0xB9);break;
    case 2: GLCD_CmdWrite(0xBA);break;
    case 3: GLCD_CmdWrite(0xBB);break;
    case 4: GLCD_CmdWrite(0xBC);break;
    case 5: GLCD_CmdWrite(0xBD);break;
    case 6: GLCD_CmdWrite(0xBE);break;
    case 7: GLCD_CmdWrite(0xBF);break;
    default:
        break;
    }
}

void GLCD_GoToXY(uint8_t x , uint8_t y)// x 0-127 , y 0-7
{
    if( (y < 8) && (y >= 0) && (x < 128) && (x >=0) )
    {
        if(x<64)
        {
            GLCD_SelectChip(0xf0);
            GLCD_SelectPage(y);
            GLCD_CmdWrite( ( x | (1<<6) ) );
        }
        else
        {
            x-=64;
            GLCD_SelectChip(0x0f);
            GLCD_SelectPage(y);
            GLCD_CmdWrite( ( x | (1<<6) ) );
        }
    }
}

void GLCD_CmdWrite(uint8_t cmd)
{
    GLCD_DATA_PORT = cmd;         //Send the command nibble
   
    CLRBIT(GLCD_CONTROL_PORT,RS_GR); // Send LOW pulse on RS pin for selecting command register 
   
    CLRBIT(GLCD_CONTROL_PORT,EN_GR);
    _delay_us(100);
    SETBIT(GLCD_CONTROL_PORT,EN_GR); // Generate a High-to-low pulse on EN pin
   
  
    _delay_us(10);
}

void GLCD_DataWrite(uint8_t data)
{
    GLCD_DATA_PORT = data;         //Send the data on DataBus nibble
    
    SETBIT(GLCD_CONTROL_PORT,RS_GR); // Send HIGH pulse on RS pin for selecting data register 
   
    CLRBIT(GLCD_CONTROL_PORT,EN_GR);
    _delay_us(100);
    SETBIT(GLCD_CONTROL_PORT,EN_GR); // Generate a High-to-low pulse on EN pin
   
    
    _delay_us(10);
}

void GLCD_DisplayChar(uint8_t *ptr_array)
{
    uint8_t i;
    for( i=0 ; i<6 ; i++ ) // 5x7 font, 5 chars + 1 blankspace
    {
        GLCD_DataWrite(ptr_array[i]);
    }  
}




void GLCD_Clear(uint8_t x , uint8_t y)
{
   
   uint8_t real_y=y;
   uint8_t dot=0;
   if( (y < 64) && (y >= 0) && (x < 128) && (x >=0) )
   {
	   y=y/8;
	   dot= real_y - (y*8);
	   if(x<64)
	   {
		   GLCD_SelectChip(0xf0);
		   GLCD_SelectPage(7-y);
		   GLCD_CmdWrite( ( x | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x-1) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x-2) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x+1) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x+2) | (1<<6) ) );
		   GLCD_DataWrite(0);
	   }
	   else
	   {
		   x-=64;
		   GLCD_SelectChip(0x0f);
		   GLCD_SelectPage(7-y);
		   GLCD_CmdWrite( ( x | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x-1) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x-2) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x+1) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   GLCD_CmdWrite( ( (x+2) | (1<<6) ) );
		   GLCD_DataWrite(0);
		   
	   }
   }
   

}



void GLCD_GoToXY_dot(uint8_t x , uint8_t y)// x 0-127 , y 0-64
{
	uint8_t real_y=y;
	uint8_t dot=0;
	if( (y < 64) && (y >= 0) && (x < 128) && (x >=0) )
	{
		y=y/8;
		dot= real_y - (y*8);
		if(x<64)
		{
			GLCD_SelectChip(0xf0);
			GLCD_SelectPage(7-y);
			GLCD_CmdWrite( ( x | (1<<6) ) );
			GLCD_DataWrite(1<<(7-dot));
			
		}
		else
		{
			x-=64;
			GLCD_SelectChip(0x0f);
			GLCD_SelectPage(7-y);
			GLCD_CmdWrite( ( x | (1<<6) ) );
			GLCD_DataWrite(1<<(7-dot));
			
		}
	}

	
}


void GLCD_GoToXY_shape(uint8_t x , uint8_t y)// x 0-127 , y 0-64
{
	
	uint8_t real_y=y;
	uint8_t dot=0;
	if( (y < 64) && (y >= 0) && (x < 128) && (x >=0) )
	{
		y=y/8;
		dot= real_y - (y*8);
		if(x<64)
		{
			GLCD_SelectChip(0xf0);
			GLCD_SelectPage(7-y);
			GLCD_CmdWrite( ( x | (1<<6) ) );
			GLCD_DataWrite(124);
			GLCD_CmdWrite( ( (x-1) | (1<<6) ) );
			GLCD_DataWrite(16);
			GLCD_CmdWrite( ( (x-2) | (1<<6) ) );
			GLCD_DataWrite(16);
			GLCD_CmdWrite( ( (x+1) | (1<<6) ) );
			GLCD_DataWrite(16);
			GLCD_CmdWrite( ( (x+2) | (1<<6) ) );
			GLCD_DataWrite(16);
		}
		else
		{
			x-=64;
			GLCD_SelectChip(0x0f);
			GLCD_SelectPage(7-y);
			GLCD_CmdWrite( ( x | (1<<6) ) );
			GLCD_DataWrite(124);
			GLCD_CmdWrite( ( (x-1) | (1<<6) ) );
			GLCD_DataWrite(16);
			GLCD_CmdWrite( ( (x-2) | (1<<6) ) );
			GLCD_DataWrite(16);
			GLCD_CmdWrite( ( (x+1) | (1<<6) ) );
			GLCD_DataWrite(16);
			GLCD_CmdWrite( ( (x+2) | (1<<6) ) );
			GLCD_DataWrite(16);
			
		}
	}
	
}
void Draw_Graph(void)
{
	
	for (uint8_t i=1;i<128;i++)
	{
		GLCD_GoToXY_dot(i,2);
		
		
	}
	
	GLCD_CmdWrite(0xB8);
	GLCD_CmdWrite(0x40);
	GLCD_DataWrite(0);
	
	
	for (uint8_t i=0;i<8;i++)
	{
		GLCD_GoToXY_dot(1,1);
	
		GLCD_SelectPage(7-i);
		GLCD_DataWrite(0xff);
		
	}
	
	GLCD_GoToXY(125,7);
	GLCD_DataWrite(168);
	GLCD_GoToXY(126,7);
	GLCD_DataWrite(112);
	GLCD_GoToXY(0,0);
	GLCD_DataWrite(4);
	GLCD_GoToXY(1,0);
	GLCD_DataWrite(2);
	GLCD_GoToXY(3,0);
	GLCD_DataWrite(2);
	GLCD_GoToXY(4,0);
	GLCD_DataWrite(4);
	GLCD_GoToXY(1,7);
	GLCD_DataWrite(32);
}