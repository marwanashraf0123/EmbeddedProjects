/*
 * UART.c
 *
 *  Created on: 11 Oct 2022
 *      Author: marwa
 */
#include "UART.h"
#include <avr\io.h>

/****************************************************************************************************************
                                                 Functions
 ****************************************************************************************************************/

void UART_init(UART_config *str)
{
	UCSRA = (1<<U2X); // Use Double speed UART

	/*
	 * Enable the receiver
	 * Enable the transmitter
	 * for bit mode we set UCSZ2 to zero
	 */
	UCSRB = (1<<RXEN) | (1<<TXEN);
	/*
	 *Enable writing on port UCSRC by putting 1 in URSEL
	 *For mode size we set UCSZ0 and UCSZ1;
	 *For mode operation we set UMSEL by 1 or 0
	 *For  number of stop bit we set USBS for 1 stop we put 0 for 2 stops we put 1
	 */
	UCSRC |=  (1<<URSEL) ;

	UCSRC = (UCSRC & 0xF9 ) | ((str -> mod)<< 1);
	UCSRC = (UCSRC & 0xBF ) | ((str -> modop)<< 6);
	UCSRC = (UCSRC & 0xCF ) | ((str -> parity)<< 4);
	UCSRC = (UCSRC & 0xF7 ) | ((str -> stopbit)<< 3);


	/*
	 *Enable writing on UBRRL by putting 0 on URSEL
	 */
	UBRRL |= (1<<URSEL);

	UBRRH = BAUD >> 8 ;
	UBRRL = BAUD;

}
void UART_sendByte(uint8 data)
{
	/*
	 * when the UDRE register is clear send data
	 */
	while (BIT_IS_CLEAR(UCSRA,UDRE));

	UDR = data;
}
uint8 UART_recieveByte()
{
	/*
	 * RXC is set to 1 when there is data to be send
	 * Return the data when the RXC is set to 1
	 */

	while (BIT_IS_CLEAR(UCSRA,RXC));

	return UDR ;
}

void UART_sendString(uint8 *str)
{
/*
 * take the bytes from string until it reaches null and every time it sends one byte
 */
	uint8 i = 0;

	while (str[i] != '\0' )
	{
		 UART_sendByte(str[i]);
		i++;
	}

}
void UART_recieveString(uint8 *str)
{
	/*
	 * creat array and store every byte as an element of the array
	 */
	uint8 i = 0;
	while (str[i] != '#')
	{
		str[i] = UART_recieveByte();
		i++;
	}
	str[i] = '\0';
}






