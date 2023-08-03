/*
 * buzzer.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Marwan Ashraf
 */
#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*Description:
 *
 * This function is responsible of buzzer initialization. It sets the buzzer pin as
 * an output pin and sets its initial value to zero ie the buzzer is OFF*/
void Buzzer_Init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}


/*Description:
 *
 * This function turns the buzzer ON*/
void Buzzer_ON(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}
/*Description:
 *
 * This function turns the buzzer OFF*/
void Buzzer_OFF(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}


