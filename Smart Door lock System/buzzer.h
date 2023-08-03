/*
 * buzzer.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Mina Adel Attia
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
#include "comman_macros.h"
#include "gpio.h"
#include <avr\io.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Buzzer Ports and pins */

#define BUZZER_PORT_ID	PORTD_ID
#define BUZZER_PIN_ID	PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*Description:
 *
 * This function is responsible of buzzer initialization. It sets the buzzer pin as
 * an output pin and sets its initial value to zero ie the buzzer is OFF*/
void Buzzer_Init(void);


/*Description:
 *
 * This function turns the buzzer ON*/
void Buzzer_ON(void);
/*Description:
 *
 * This function turns the buzzer OFF*/
void Buzzer_OFF(void);


#endif /* BUZZER_H_ */
