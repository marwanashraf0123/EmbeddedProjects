/*
 * File: Motor source file
 * Name: Marwan Ashraf
 * Oct 31/2022
 * */
#include"motor.h"


/*Description: Initialize the motor*/
void Motor_init(void)
{
	MOTOR_DIRECTION_PORT |=  (1<<MOTOR_PIN_IN1) | (1<<MOTOR_PIN_IN2);
	MOTOR_DATA_PORT &= 0xCF;
}

/* Description: Function to make the motor move on clockwise direction */

void Motor_ON_ClockWise(void)
{
	MOTOR_DATA_PORT = CLEAR_BIT(MOTOR_DATA_PORT , MOTOR_PIN_IN1);
	MOTOR_DATA_PORT = SET_BIT(MOTOR_DATA_PORT , MOTOR_PIN_IN2);

}

/*Description: Function to make the motor move on anti-clockwise direction*/

void Motor_ON_Anti_ClockWise(void)
{
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_PIN_IN2);
	MOTOR_DATA_PORT = SET_BIT (MOTOR_DATA_PORT, MOTOR_PIN_IN1);

}
/*Description: Stop the Motor*/
void Motor_Stop(void)
{
	MOTOR_DATA_PORT = CLEAR_BIT(MOTOR_DATA_PORT , MOTOR_PIN_IN2);
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_PIN_IN1);

}
