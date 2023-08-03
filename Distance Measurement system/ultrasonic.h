/*
 * ultrasonic.h
 *
 *  Created on: 12 Oct 2022
 *      Author: marwan
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "icu.h"
#include "gpio.h"

/****************************************************************************************************
                                               Definitions
 ****************************************************************************************************/
#define ULTRA_SONIC_NUM_EDGES               2
#define ULTRA_SONIC_TRIGGER_PORT            PORTB_ID
#define ULTRA_SONIC_TRIGGER_PIN             PIN5_ID
#define ULTRA_SONIC_ECO_PORT                PORTD_ID
#define ULTRA_SONIC_ECOR_PIN                PIN6_ID

/****************************************************************************************************
                                                Prototypes
 ****************************************************************************************************/
/*
 * call back function of the ultrasonic
 * when the eco is triggered start the timer and wait for failing edge
 * the failing edge comes capture the reading of the sensors and clear the timer
 */

void UltraSonic_init();

/* clear the timer value
 * Call the trigger function
 * calculate the distance = high time * 1700
 */
uint16 UltraSonic_read();











#endif /* ULTRASONIC_H_ */
