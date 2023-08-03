/*
 * Timer1.h
 *
 *  Created on: 24 Oct 2022
 *      Author: marwan ashraf
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr\io.h>
#include "std_types.h"
#include "comman_macros.h"
#include <avr/interrupt.h>
/**************************************************************************************************************
                                                           Definitions
 **************************************************************************************************************/





/***************************************************************************************************************
                                                          Types
 ***************************************************************************************************************/
typedef enum
{
	Normal,Compare
}Timer1_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;
typedef struct
{
	uint16 initial_value;
	uint16 compare_value;      // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
}Timer1_ConfigType;


/*************************************************************************************************************
                                                          Prototypes
 *************************************************************************************************************/
/*
 * Function to initialise  timer1
 * Set configuration parameters for timer 1 chose from (normal mode,compare mode)
 * Set configuration parameters prescaler value (1,8,64,1024)
 * Set initial value for the timer1 to start count from it
 * Set compare value if working with compare mode
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);



/*
 * Function to stop the timer by by putting 0 on the control register
 */
void Timer1_deInit(void);


/*
 * Call back function for timer1
 */
void Timer1_setCallBack(void(*a_ptr)(void));















#endif /* TIMER1_H_ */
