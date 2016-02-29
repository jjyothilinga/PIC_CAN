//#include "communication.h"
#include "string.h"
#include "app.h"
//#include "uart.h"
#include "typedefs.h"
#include "eep.h"
#include "uart.h"
#include "ECAN.h"

extern unsigned char temp_D0;
extern unsigned char temp_D1;
extern unsigned char temp_D2;
extern unsigned char temp_D3;
extern unsigned char temp_D4;
extern unsigned char temp_D5;
extern unsigned char temp_D6;
extern unsigned char temp_D7;

typedef struct _APP
{
	UINT8 model[MSG_LENGTH];
	UINT8 eepUpdate;

}APP;

#pragma idata APP_DATA
APP app = {{0},0};

#pragma idata


void APP_init(void)
{
	UINT8 i = 0;

	

}

void APP_task(void)
{

	UINT8 uartData = 0;
	UINT8 i = 0;

	if( UART1_hasData() )
	{
		uartData = UART1_read(  );

		if( uartData == '1' )		
			ECAN_Transmit();
			uartData = 0;
	}
			
 	if( ECAN_Receive() )
    {
		UART1_write( temp_D0 );
		UART1_write( temp_D1 );
		UART1_write( temp_D2 );
		UART1_write( temp_D3 );
		UART1_write( temp_D4 );
		UART1_write( temp_D5 );
		UART1_write( temp_D6 );
		UART1_write( temp_D7 );

		UART1_transmit(  );

    }
	


}

UINT8 APP_comCallBack( far UINT8 *rxPacket, far UINT8* txCode,far UINT8** txPacket)
{

	UINT8 i;

	UINT8 rxCode = rxPacket[0];
	UINT8 length = 0;

	switch( rxCode )
	{
		case CMD_SET_MODEL:
		
			*txCode = CMD_SET_MODEL;
			break;

		default:
		break;

	}

	return length;

}


void UART2_testInit(  )
{

}