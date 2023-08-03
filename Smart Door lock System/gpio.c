/*
 * gpio.c
 *  Description : c file for GPIO
 *  Created on: 27 Sept 2022
 *      Author: marwan ashraf
 */


#include "gpio.h"
#include"comman_macros.h"
#include "avr/io.h"

/**************************************************************************************/

/******************************Functions**********************************************/

void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num, GPIO_PinDirectionType direction)
{
	if ((port_num >= NUMBER_OF_PORTS) || (pin_num >= NUMBER_OF_PINS_PER_PORT))
	{
		// do nothing
	}
	/*set up the pin direction */
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
			if (direction == PIN_OUTPUT)
			{
			SET_BIT(DDRA,pin_num);
			}
			else
			{
			CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:

			if(direction == PIN_OUTPUT)
			{
			SET_BIT(DDRB,pin_num);

			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);

			}
			break;

		case PORTC_ID:

			if (direction == PIN_OUTPUT)
			{
			    SET_BIT(DDRC,pin_num);

			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);

			}
			break;

		case PORTD_ID:

			if(direction == PIN_OUTPUT)
			{
			SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;

		}
	}
}

uint8 GPIO_readPin(uint8 port_num,uint8 pin_num)
{
	uint8 value = LOGIC_LOW;

	if ((port_num >= NUMBER_OF_PORTS) || (pin_num >= NUMBER_OF_PINS_PER_PORT))
	{
		// do nothing
	}
	else
	{
	switch(port_num)
	{
		case PORTA_ID:

			if (BIT_IS_SET(PINA,pin_num))
			{
				value = LOGIC_HIGH;
				break;
			}
			else
			{
				value = LOGIC_LOW;
				break;
			}

		case PORTB_ID:

			if (BIT_IS_SET(PINB,pin_num))
			{
				value = LOGIC_HIGH;
				break;
			}
			else
			{
				value = LOGIC_LOW;
				break;
			}

		case PORTC_ID:

			if (BIT_IS_SET(PINC,pin_num))
			{
				value = LOGIC_HIGH;
				break;
			}
			else
			{
				value =LOGIC_LOW;
				break;
			}

		case PORTD_ID:

			if(BIT_IS_SET(PIND,pin_num))
			{
				value = LOGIC_HIGH;
				break;
			}
			else
			{
				value = LOGIC_LOW;
				break;
			}

	}
	}
	return value;
}
void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value)
{
	if ((port_num >= NUMBER_OF_PORTS) || (pin_num>=NUMBER_OF_PINS_PER_PORT))
	{
		// do nothing
	}
	/*write on specific pin*/
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
		{
			if (value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
				break;
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
				break;
			}
		}
		case PORTB_ID:

			if (value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
				break;
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
				break;
			}

		case PORTC_ID:

			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
				break;
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
				break;
			}

		case PORTD_ID:

			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
				break;
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
				break;
			}

		}
	}
}

void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction)
{
	if (port_num>=NUMBER_OF_PORTS)
	{
		//do nothing
	}
	/*set up the direction of the pins OUTPUT or INPUT*/
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
		{
			DDRA = direction;
			break;
		}
		case PORTB_ID:
		{
			DDRB = direction;
			break;
		}
		case PORTC_ID:
		{
			DDRC = direction;
			break;
		}
		case PORTD_ID:
		{
			DDRD = direction;
			break;
		}
		}
	}
}
void GPIO_writePort(uint8 port_num,uint8 value)
{
	if (port_num>=NUMBER_OF_PORTS)
	{
		//do nothing
	}
	else
	{
		switch (port_num)
		{
		case PORTA_ID:

			PORTA = value;
			break;

		case PORTB_ID:

			PORTB = value;
			break;

		case PORTC_ID:

			PORTC = value;
			break;

		case PORTD_ID:

			PORTD = value;
			break;

		}
	}
}
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;
	if (port_num >= NUMBER_OF_PORTS)
	{
		//do nothing
	}
	switch (port_num)
	{
	case PORTA_ID:

		value = PINA;
		break;

	case PORTB_ID:

		value = PINB;
		break;

	case PORTC_ID:

		value = PINC;
		break;

	case PORTD_ID:

		value = PIND;
		break;

	}
	return value;
}







