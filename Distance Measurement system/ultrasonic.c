/*
 * ultrasonic.c
 *
 *  Created on: 12 Oct 2022
 *      Author: marwan
 */
#include "ultrasonic.h"
#include <util\delay.h>

/***********************************************************************************************
                                           Static Prototypes
 ***********************************************************************************************/
static void edge_processing();
static void UltraSonic_trigger();


/***********************************************************************************************
                                           Global Variable
 ***********************************************************************************************/
static uint16 g_hightime = 0;
static uint8 g_edgecount = 0;
static uint16 g_distance = 0;
/***********************************************************************************************
                                             Function
 **********************************************************************************************/
static void edge_processing()
{
	g_edgecount++;
	if (g_edgecount == 1)
	{
		Icu_ClearTimerValue();           //CLear the timer value when raising edge occurs
		Icu_setEdgeDetectionType(FALLING);         // set the detection edge for the icu to falling
	}
	else if (g_edgecount == 2)
	{
		g_hightime = Icu_getInputCaptureValue();  //Capture the timer count when falling edge occurs

		Icu_setEdgeDetectionType(RISING);         // set detection edge to Rising edge
	}
}
static void UltraSonic_trigger()
{
	/*
	 * trigger the trigger pin
	 * delay 10 us
	 * set the trigger pin back to 0
	 */
	GPIO_writePin(ULTRA_SONIC_TRIGGER_PORT,ULTRA_SONIC_TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRA_SONIC_TRIGGER_PORT,ULTRA_SONIC_TRIGGER_PIN,LOGIC_LOW);
}
void UltraSonic_init()
{
	Icu_Config Icu_con = {F_CPU_8,RISING};//Config the ICU
	/* Set Trigger ping as output.*/
	GPIO_setupPinDirection(ULTRA_SONIC_TRIGGER_PORT,ULTRA_SONIC_TRIGGER_PIN,PIN_OUTPUT);
	Icu_Init(&Icu_con);                    //  Initiate the ICU
	Icu_setCallBack(edge_processing);  // set the call back function for ICU
}

uint16 UltraSonic_read()
{
	/* Clear all variables to start over */
	 g_hightime = 0;
	 g_edgecount = 0;
	 g_distance = 0;
	 /* clear the timer to begin the operation */
	 Icu_ClearTimerValue();
	 /* trigger the trigger pin*/
	 UltraSonic_trigger();
	 /* Wait until the icu measure the hight time */
	 while (g_edgecount != ULTRA_SONIC_NUM_EDGES);


	 /* Calcualte distance */
	 g_distance = g_hightime / 58 ;

	 return g_distance ;
}
