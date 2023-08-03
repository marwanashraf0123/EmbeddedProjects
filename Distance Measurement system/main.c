/*
 * main.c
 *
 *  Created on: 13 Oct 2022
 *      Author: marwan ashraf
 */

#include "lcd.h"
#include "ultrasonic.h"


int main()
{
	uint32 prevdistance;
	uint32 distance ;
	SREG |= (1<<7);

	LCD_init();

	UltraSonic_init();
	distance = UltraSonic_read();
	LCD_displayString("distance = ");



	while(1)
	{
		distance = UltraSonic_read();
		LCD_moveCursor( 0,10);
		LCD_intgerToString(distance);
		LCD_displayString("cm");

	}
}

