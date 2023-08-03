/*
 * lcd.c
 * Description : the lcd.c file containing the functions
 *  Created on: 3 Oct 2022
 *      Author: marwan
 */
/*********************************************************************************
                                 Includes
 ********************************************************************************/

#include <util/delay.h>
#include "gpio.h"
#include "std_types.h"
#include "comman_macros.h"
#include "lcd.h"

/*********************************************************************************
                                 Functions
 *********************************************************************************/

/*
 * Sends the command to the LCD
 */

void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE == 4)
/*
 * Bits are sent on two chunks of 4 bits
 */
		GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(command,4));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(command,5));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(command,6));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(command,7));

	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	    _delay_ms(1);

	    GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(command,0));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(command,1));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(command,2));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(command,3));


	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	    _delay_ms(1);



#elif (LCD_DATA_BITS_MODE == 8)

	    GPIO_writePort(LCD_DATA_PORT,command);
	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	    _delay_ms(1);
#endif

}

/*
 * Send the needed character to be printed on LCD
 */
void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE == 4)
/*
 * Bits are sent on two chunks of 4 bits
 */
		GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(character,4));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(character,5));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(character,6));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(character,7));

	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	    _delay_ms(1);

	    GPIO_writePin(LCD_DATA_PORT,LCD_DB4_PIN_ID,GET_BIT(character,0));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB5_PIN_ID,GET_BIT(character,1));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB6_PIN_ID,GET_BIT(character,2));
	    GPIO_writePin(LCD_DATA_PORT,LCD_DB7_PIN_ID,GET_BIT(character,3));


	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	    _delay_ms(1);



#elif (LCD_DATA_BITS_MODE == 8)

	    GPIO_writePort(LCD_DATA_PORT,character);
	    _delay_ms(1);
	    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	    _delay_ms(1);
#endif
}

/*
 * Initialise LCD
 * Set up the mode of the LCD 4 or 8 bits
 * Setup the pin direction as an output using GPIO
 */

void LCD_init()
{
	 GPIO_setupPinDirection(LCD_RS_PORT_ID ,LCD_RS_PIN_ID ,PIN_OUTPUT);
	 GPIO_setupPinDirection(LCD_E_PORT_ID ,LCD_E_PIN_ID ,PIN_OUTPUT);

	 _delay_ms(20);


#if (LCD_DATA_BITS_MODE == 8)
	/*
	 * Two lines LCD 8 bit mode 2x16 and 5*7 dots.
	 */

	 GPIO_setupPortDirection(LCD_DATA_PORT,PORT_OUTPUT);
		 LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);


#elif (LCD_DATA_BITS_MODE == 4)
		 GPIO_setupPinDirection(LCD_DATA_PORT,LCD_DB4_PIN_ID,PIN_OUTPUT);
		 GPIO_setupPinDirection(LCD_DATA_PORT,LCD_DB4_PIN_ID,PIN_OUTPUT);
		 GPIO_setupPinDirection(LCD_DATA_PORT,LCD_DB4_PIN_ID,PIN_OUTPUT);

		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INI1);
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INI2);
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);



#endif
		LCD_sendCommand(LCD_CURSOR_OFF);
		LCD_sendCommand(LCD_CLEAR_COMMAND);
}


/*
 * Displays the desired string using LCD display character
 */
void LCD_displayString(uint8 *str)
{
	uint8 i = 0;
	while (str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}
/*
 * Move the cursor the a place in the LCD so the LCD can start printing from the required position
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;
	switch (row)
	{
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = 0x40 +col;
		break;
	case 2:
		lcd_memory_address = 0x10+col;
		break;
	case 3:
		lcd_memory_address = 0x50 +col ;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | SET_CURSOR_LOCATION);
}


/*
 * Display the required string in a specific row and column
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *str)
{
	LCD_moveCursor( row, col);
	LCD_displayString(str);
}
/*
 * clear the lcd screen
 */
void LCD_clearScreen()
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Print decmiel numbers on the LCD by switching the giving number into ASCII code
 */

void LCD_intgerToString(int num)
{
	uint8 buff[16];  // string to hold ASCII result
	itoa(num,buff,10); // convert the data to ASCII and 10 for decimal the 2 for (0or1) 6 for hex 8 for octal
	LCD_displayString(buff); // display the the converted data
}


