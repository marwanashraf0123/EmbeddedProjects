/*
 * Timer1.c
 *
 *  Created on: 24 Oct 2022
 *      Author: marwan ashraf
 */

#include "Timer1.h"


/******************************************************************************************************************
                                                 Global Static Variables
 ******************************************************************************************************************/


static volatile void (*g_ptr_Timer1_Callback)(void) = NULL_PTR;



/******************************************************************************************************************
                                                  ISR
 ******************************************************************************************************************/
ISR(TIMER1_OVF_vect)                    //Overflow mode
{
	/* Call the Call Back function in the application after the edge is detected */
	(*g_ptr_Timer1_Callback)();
}


ISR(TIMER1_COMPA_vect)                 //compare mode
{
	/* Call the Call Back function in the application after the edge is detected */
	(*g_ptr_Timer1_Callback)();
}


/***************************************************************************************************************
                                                   Functions
 ***************************************************************************************************************/
/*
 * Function to initialise  timer1
 * Set configuration parameters for timer 1 chose from (normal mode,compare mode)
 * Set configuration parameters prescaler value (1,8,64,1024)
 * Set initial value for the timer1 to start count from it
 * Set compare value if working with compare mode
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	TIMSK = 0;
	OCR1A= 0;


	TCNT1 = (Config_Ptr->initial_value); // Set initial value to the required value


	switch (Config_Ptr->mode)
	{
	case Normal:
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);    //Non PWM mode
		TCCR1B = (Config_Ptr->prescaler); // Set the prescaler value and mode
		TIMSK |= (1<<TOIE1) ; //Enable Interrupt for Normal Mode
		break;
	case Compare:
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);    //Non PWM mode
		TCCR1B = (1<<WGM12)  | (Config_Ptr->prescaler); // Set prescaler value and mode
		OCR1A= (Config_Ptr->compare_value);   // Set the compare value for Timer1 compare mode
		TIMSK |= (1<<OCIE1A) ; // Enable Interrupt for compare match mode
		break;
	}
}
void Timer1_deInit(void)
{
	/*
	 * Put value of 0 on the all of the timer register
	 */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	TIMSK = 0;
	OCR1A= 0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_ptr_Timer1_Callback = a_ptr ;  // assign the adress of the function to global pointer to function
}


