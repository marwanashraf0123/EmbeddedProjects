/*
 * gpio.h
 * File Name: gpio.h
 * Description : Header File for GPIO on AVR MCU
 *  Created on: 27 Sept 2022
 *      Author: marwan ashraf
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/************************************Definitions************************/

#define NUMBER_OF_PINS_PER_PORT 8
#define NUMBER_OF_PORTS 4

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

/**************************************************************************/

/******************************Types***************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/**************************************************************************/

/******************************Prototypes*********************************/


/* Set up the direction  to input or output for a specefic pin.*/
void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction);

/*Read from a specific pin it should be LOGIC_HIGH or LOGIC_LOW and return the value*/
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num);

/*Write in a specific pin LOGIC_HIGH or LOGIC_LOW*/
void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value);

/*Set up the direction input or output for a specific Port.*/
void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction);

/*Read from a specific port and return the value */
uint8 GPIO_readPort(uint8 port_num);

/*Write on a specific port*/
void GPIO_writePort(uint8 port_num,uint8 value);



/**************************************************************************/

#endif /* GPIO_H_ */
