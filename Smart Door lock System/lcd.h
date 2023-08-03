/*
 * lcd.h
 * Description :LCD.h file contains definiteness and prototypes for AVR
 *  Created on: 3 Oct 2022
 *      Author: marwan
 */

#ifndef LCD_H_
#define LCD_H_


#include "comman_macros.h"
#include "std_types.h"
/*****************************************************************************************************
                                        Definitions
******************************************************************************************************/

/* LCD HW Ports and Pins Ids */
#define LCD_DATA_BITS_MODE 8

#if ((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE !=8))

#error "LCD should be 8 bits or 4 bits mode only"

#endif

#define LCD_RS_PORT_ID       PORTD_ID
#define LCD_RS_PIN_ID        PIN4_ID

#define LCD_E_PORT_ID        PORTD_ID
#define LCD_E_PIN_ID         PIN6_ID

#define LCD_DATA_PORT        PORTB_ID

/*if 4 bits mode we need to define the pins one by one */

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/*LCD Command */

#define LCD_CLEAR_COMMAND                   0x01
#define LCD_GO_TO_HOME                      0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE       0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE        0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INI1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INI2   0x32
#define LCD_CURSOR_OFF                      0x0C
#define LCD_CURSOR_ON                       0x0E
#define SET_CURSOR_LOCATION                 0x80
/*************************************************************************************************************
                                         Prototypes
*************************************************************************************************************/

/*Initialze LCD
 * Set up the mode of the LCD 4 or 8 bits
 * Setup the pin direction as an output using GPIO
 */

void LCD_init();

/*
 * Sends the command to the LCD
 */

void LCD_sendCommand(uint8 command);

/*
 * Send the needed character to be printed on LCD
 */
void LCD_displayCharacter(uint8 character);

/*
 * Displays the desired string using LCD display character
 */

void LCD_displayString(uint8 *str);


/*
 * Move the cursor the a place in the LCD so the LCD can start printing from the required position
 */
void LCD_moveCursor(uint8 row,uint8 col);


/*
 * Display the required string in a specific row and column
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *str);

/*
 * Clear the LCD screen
 */
void LCD_clearScreen();

/*
 * Print decmiel numbers on the LCD by switching the giving number into ASCII code
 */
void LCD_intgerToString(int num);





#endif /* LCD_H_ */
