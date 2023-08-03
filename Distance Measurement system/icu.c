/*
 * icu.c
 *
 *  Created on: 7 Oct 2022
 *      Author: marwan ashraf
 */
#include <avr/io.h>
#include "comman_macros.h"
#include "icu.h"
#include <avr/interrupt.h>

/*******************************************************************************************************************
 *                           Global Variables
 *************************************************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/******************************************************************************************************************
                                                       Functions
 ******************************************************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{

		(*g_callBackPtr)();
	}
}

/*
 * Initialise the Icu to certain clock and working edge (rising,falling)
 * Enable ICU
 * Enable Interrupt for ICU
 * Initialise Timer1
 */
void Icu_Init(const Icu_Config *a_str)
{
	/*
	 * Intialise PD6 as an input for the ICU
	 */
	DDRD &=~(1<<PD6);
	/*
	 * Timer1 is set to normal mode
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	/*
	 * Set the clock (prescaler) for the timer
	 */
	TCCR1B = (TCCR1B & 0xF8) | (a_str ->clock);
	/*
	 * Set the detection edge for the icu
	 */
	TCCR1B = (TCCR1B & 0xBF) | ((a_str ->edge)<<6);
	/*
	 * Start counting from  0
	 */
	TCNT1 = 0;
	ICR1 = 0 ;
	/*
	 * Enable interrupt for ICU
	 */
	SET_BIT(TIMSK,TICIE1);
}
/*
 * Set the ICU detection edge
 */
void Icu_setEdgeDetectionType(Icu_EdgeType a_edge)
{
	/*
	 * Put the ICES1 bit to the required edge value
	 */
	TCCR1B = (TCCR1B & 0xBF) | ((a_edge)<<6);
}
/*
 * Set address call back function for icu
 */
void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
/*
 * Store the timer count of Timer1 when event occurs in the ICR1 register
 */
uint16 Icu_getInputCaptureValue()
{
	/*
	 * Return the value of the input captured
	 */
	return ICR1;
}
/*
 * Reset the timer to start over
 */
void Icu_ClearTimerValue()
{
	TCNT1 = 0;
}
/*
 * Deintilaise the timer to stop the icu
 */

void Icu_Deinit()
{
	TCNT1 = 0 ;
	ICR1 = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK &=~(1<<TICIE1);
}

