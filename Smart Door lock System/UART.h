/*
 * UART.h
 *
 *  Created on: 11 Oct 2022
 *      Author: marwa
 */

#ifndef UART_H_
#define UART_H_
#include "comman_macros.h"
#include "std_types.h"

/*************************************************************************************************************
                                                Definitions
 *************************************************************************************************************/

#define UART_BAUDRATE   9600

#define BAUD        (((F_CPU / (UART_BAUDRATE * 8UL))) - 1)



/***********************************************************************************************************************
                                                   Types
 ***********************************************************************************************************************/
typedef enum
{
	bit5_mod,bit6_mod,bit7_mod,bit8_mod,reserved1,reserved2,reserved3,bit9_mod
}UART_mod;
typedef enum
{
      Asynmod,Synmod
}UART_asyorsyn;

typedef enum
{
	praity_disabled,resrved,parity_even,parity_odd
}UART_parityMode;

typedef enum
{
	stop_1bit,stop_2bit
}UART_stopBit;




typedef struct
{
	UART_mod mod;
	UART_asyorsyn modop;
	UART_parityMode parity;
	UART_stopBit stopbit;

}UART_config;



/**********************************************************************************************************************
                                                  Prototypes
 **********************************************************************************************************************/
/*
 *
 */

void UART_init(UART_config *str);
/*
 *
 */
void UART_sendByte(uint8 data);
/*
 *
 */
uint8 UART_recieveByte();
/*
 *
 */

void UART_sendString(uint8 *str);
/*
 *
 */
void UART_recieveString(uint8 *str);



#endif /* UART_H_ */
