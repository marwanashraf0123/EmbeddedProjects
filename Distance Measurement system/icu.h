/*
 * icu.h
 *
 *  Created on: 7 Oct 2022
 *      Author: marwan ashraf
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
#include <avr/io.h>
#include "comman_macros.h"
/***************************************************************************************************************************
                                                  Definitions
 ***************************************************************************************************************************/
/***************************************************************************************************************************
                                                     Types
***************************************************************************************************************************/

/*
 * Specfie the clock of the timer
 */
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

/*
 * Specfie the icu working edge
 */
typedef enum
{
	FALLING,RISING
}Icu_EdgeType;

/*
 * A Struct to be passed to a function for config
 */


typedef struct
{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_Config;

/********************************************************************************************************************************************
                                                           Functions
 ********************************************************************************************************************************************/

/*
 * Initialise the Icu to certain clock and working edge (rising,falling)
 * Enable ICU
 * Enable Interrupt for ICU
 * Initialise Timer1
 */
void Icu_Init(const Icu_Config *str);

/*
 * Set the ICU detection edge
 */
void Icu_setEdgeDetectionType(Icu_EdgeType edge);

/*
 * Set address call back function for icu
 */
void Icu_setCallBack(void(*ptr)(void));

/*
 * Store the timer count of Timer1 when event occurs in the ICR1 register
 */
uint16 Icu_getInputCaptureValue();

/*
 * Reset the timer to start over
 */
void Icu_ClearTimerValue();

/*
 * Deintilaise the timer to stop the icu
 */

void Icu_Deinit();



#endif /* ICU_H_ */
