
/*
*------------------------------------------------------------------------------
* main.c
*
* main application specific module.
*
* (C)2008 Sam's Logic.
*
* The copyright notice above does not evidence any
* actual or intended publication of such source code.
*
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* File				: main.c
* Created by		: Sam
* Last changed by	: Sam
* Last changed		: 07/07/2009
*------------------------------------------------------------------------------
*
* Revision 0.0 07/07/2009 Sam
* Initial revision
*
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------
*/

#include "board.h"
#include "timer.h"	// Timer related functions
#include "uart.h"
#include "communication.h"
#include "heartBeat.h"
#include "app.h"
#include "ECAN.h"

/*
*------------------------------------------------------------------------------
* Private Defines
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Processor config bits
*------------------------------------------------------------------------------
*/
/*
#pragma config OSC     = INTIO67
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOREN    = ON
#pragma config BORV     = 3
#pragma config WDT      = OFF
#pragma config WDTPS    = 512	//32768
#pragma config MODE 	= MC
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
//#pragma config PBADEN   = OFF
#pragma config STVREN   = ON
#pragma config LVP      = OFF
//#pragma config ICPRT  = OFF       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = ON
#pragma config CP2      = ON
#pragma config CP3      = ON
#pragma config CPB      = ON
#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
#pragma config WRT2     = OFF
//#pragma config WRT3   = OFF
#pragma config WRTB     = OFF//N       // Boot Block Write Protection
#pragma config WRTC     = OFF
#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
#pragma config EBTR2    = OFF
#pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF

*/

#pragma config RETEN 		= OFF
//#pragma config INTOSCSEL 	= HIGH
#pragma config XINST 		= OFF
#pragma config FOSC 		= INTIO2
#pragma config PLLCFG 		= ON
#pragma config FCMEN 		= OFF
#pragma config IESO 		= OFF
#pragma config PWRTEN 		= OFF
#pragma config BOREN 		= OFF
#pragma config WDTEN 		= OFF
#pragma config CANMX 		= PORTB
#pragma config MSSPMSK 		= MSK7
#pragma config MCLRE 		= ON
#pragma config STVREN 		= ON
#pragma config CP0 			= OFF
#pragma config CP1 			= OFF
#pragma config CP2 			= OFF
#pragma config CP3 			= OFF


extern UINT32 TimerUpdate_count;
extern UINT16 keypadUpdate_count;


/*
*------------------------------------------------------------------------------
* Private Macros
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Data Types
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Variables
*------------------------------------------------------------------------------
*/
void EnableInterrupts(void);
/*
*------------------------------------------------------------------------------
* Private Variables (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Constants
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Constants (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Function Prototypes (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Functions
*------------------------------------------------------------------------------
*/


/*
*------------------------------------------------------------------------------
* void main(void)

* Summary	: Application specifc main routine. Initializes all port and
*			: pheriperal and put the main task into an infinite loop.
*
* Input		: None
*
* Output	: None
*
*------------------------------------------------------------------------------
*/

#define MMD_REFRESH_PERIOD	(65535 - 16000)
#define TICK_PERIOD	(65535 - 16000)


	UINT8 line[10] ="123456 "; 

void main(void)
{
	UINT8 i,j;
	BOOL ledStrip_On = 0;

	UINT8 count = 0;

	BRD_init();
	HB_init();


	//COM_init(CMD_SOP,CMD_EOP,RESP_SOP,RESP_EOP,APP_comCallBack);
	
	//APP_init();

	TMR0_init(TICK_PERIOD,0);	//initialize timer0

	UART1_init( 19200 );
//	UART2_init( 19200 );

    // Initialize CAN module
    InitECAN();

	EnableInterrupts();

	while(1)
	{

		if(  heartBeatCount >= 500 )
		{
			HB_task();
			heartBeatCount = 0;
		}
    
		if( appUpdateCount >= 10 )
		{
			APP_task(  );
			appUpdateCount = 0;
		}

		//ClrWdt();	
	}
}

/*
*  End of main.c
*/