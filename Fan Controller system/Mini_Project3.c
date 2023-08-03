/*
 ============================================================================
 Name        : Mini_Project3.c
 Author      : Mohamed Tarek
 Description : System control fan speed based on the room temperature
 Date        : 19/06/2017
 ============================================================================
 */

#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include "avr/io.h" /* To use the SREG Register */

typedef enum
{
	FAN_OFF,FAN_ON
}Fan_State;

int main(void)
{
	uint8 temp;

	ADC_ConfigType ADC_Configurations = {INTERNAL_VOLT,F_CPU_8};

	Fan_State Fan1 = FAN_OFF;

	/* Enable interrupts by setting I-bit */
	SREG  |= (1<<7);

	/* Initialize Motor driver */
	DcMotor_Init();

	/* Initialize LCD driver */
	LCD_init();

	/* Initialize ADC driver */
	ADC_init(&ADC_Configurations);

	/* Display this string "Temp =   C" only once on LCD at the second row*/
	LCD_moveCursor(1,4);
	LCD_displayString("Temp =    C");

    while(1)
    {
    	/* Get the temperature value */
    	temp = LM35_getTemperature();

		/* Control the duty cycle of the output PWM signal (Fan Speed) based on the temperature value */
		if(temp >= 120)
		{
			Fan1 = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,100); /* Rotates the motor with 100% from its speed */
		}
		else if(temp >= 90)
		{
			Fan1 = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,75); /* Rotates the motor with 75% from its speed */
		}
		else if(temp >= 60)
		{
			Fan1 = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,50); /* Rotates the motor with 50% from its speed */
		}
		else if(temp >= 30)
		{
			Fan1 = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,25); /* Rotates the motor with 25% from its speed */
		}
		else
		{
			Fan1 = FAN_OFF;
			DcMotor_Rotate(DC_MOTOR_STOP,0); /* Stop the motor */
		}

		/* Display the temperature and FAN state */
		if(Fan1 == FAN_OFF)
		{
			LCD_moveCursor(0,4);
			LCD_displayString("FAN is OFF");
		}
		else
		{
			LCD_moveCursor(0,4);
			LCD_displayString("FAN is ON ");
		}
		
		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,11);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
    }
}
