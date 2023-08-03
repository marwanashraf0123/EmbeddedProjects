/*
 * main.c
 *
 *  Created on: Oct 30, 2022
 *      Author: Marwan Ashraf
 *      Description: Human Machine Interface main code
 */



#include "main.h"
#include <util/delay.h>

/************************************************************************************************
 *                                GLOBAL VARIABLES                                              *
 ************************************************************************************************/
static volatile uint8 g_flag=0;               /*global flag variable to check on */
static volatile uint8 Stage=0;	 		      /*global variable to determine which stage we're at*/
uint8 g_key;                                  /*global variable to hold the key value */
uint8 g_password[5];                          /*global array to store the password in it */
uint8 command;                                /*global variable to store the commands in it */
uint8 g_wrong=0;                              /*global variable to count wrong password entered times*/
uint8 g_tick=0;                               /*global ticks to count timer interrupts*/

int main(void)
{
	SREG |= (1<<7);       /* Enable I-Bit for Interrupts */
	/*initialize the LCD*/
	LCD_init();
	/*initialize the UART with the configurations inside the main.h*/
	UART_init(&UART_configuration);

	/*Introduction Screen*/
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"DOOR LOCKER SYSTEM");
	LCD_displayStringRowColumn(1,0,"WELCOME");


	CheckIfPasswordExists(); /*Checks whether a password already exists on the EEPROM or not*/



	for(;;)
	{
		if (Stage==0) /*FIRST TIME USING A PROGRAM...NO SET PASSWORD*/
		{
			SetPasswordFirstTime(); /*HELP USER SET PASSWORD FOR THE FIRST TIME*/
		}
		else if(Stage==1) /*A PASSWORD ALREADY EXISTS*/
		{
			MainFunction(); /*ALLOW USER TO EITHER CHANGE THE PASSWORD OR OPEN THE DOOR*/
		}
		else if(Stage==2) /*OPENING THE DOOR STAGE*/
		{
			doorIsOpeningCloseingScreen();
		}
	}
}

void sendCommand(uint8 command)
{

	/* 1. SEND A READY COMMAND TO THE CONTROL_ECU TO SAY THAT HMI_ECI IS READY
	 * 2.WAITING UNTIL THE CONTROL_ECU SEND A READY COMMAND TOO
	 * 3.SENDING A COMMAND FROM THE HMI_ECU
	 * 4. WAITING UNTIL THE CONTROL_ECU SENDS DONE COMMAND
	 */
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};
	UART_sendByte(command);
	while(UART_recieveByte() != DONE){};

}

uint8 recieveCommand(void){

	/*
	 * 1.WAITING UNTIL THE CONTROL_ECU SEND A READY COMMAND
	 * 2. SEND A READY COMMAND TO THE CONTROL_ECU TO SAY THAT HMI_ECI IS READY
	 * 3. RECIEVE A COMMAND FROM THE CONTROL_ECU
	 * 4. SENDING TO THE  CONTROL_ECU  DONE COMMAND
	 * 5. RETURN THE COMMAND SENT FROM THE COTROL_ECU
	 */
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	command=UART_recieveByte();
	UART_sendByte(DONE);
	return command;
}
void CheckIfPasswordExists(void)
{
	sendCommand(CHECK_IF_SAVED);
	switch (recieveCommand())
	{
	case YES_SAVED:
		Stage=1;
		break;
	case NO_SAVED_PASSWORD:
		Stage=0;
		break;
	}
}

void SetPasswordFirstTime(void)
{
	/**SENDING THE PASSWORD FOR THE FIRST TIME**/
	LCD_clearScreen(); /*Clears the screen*/
	LCD_displayStringRowColumn(0,0,"Enter PW"); /*Ask the user to enter the password for the first time*/
	LCD_moveCursor(1,0);/*Moves the cursor to the bottom row to allow the user to enter the password*/
	FillPassword(g_password); /*User enters the password for the first time*/
	sendCommand(PASSWORD_SEND);/*Command sent to tell the Control_ECU that we're sending the password for the first time*/
	SendPassword(g_password); /*Sends the password value to the Control_ECU which stores it in a global array*/
	g_flag=1;

	if(g_flag==1) /**SENDING THE PASSWORD FOR THE SECOND TIME**/
	{
		LCD_clearScreen(); /*Clears the screen*/
		LCD_displayStringRowColumn(0,0,"Re-Enter PW"); /*Ask the user to enter the password for the second time*/
		LCD_moveCursor(1,0);/*Moves the cursor to the bottom row to allow the user to enter the password*/
		FillPassword(g_password); /*User enters the password for the second time*/
		sendCommand(PASSWORD_CONFIRMATION_SEND);/*Command sent to tell the Control_ECU that we're sending the password for the second time*/
		SendPassword(g_password); /*Sends the password value to the Control_ECU which stores it in a second global array and compares the 2 values*/
		g_flag=2;
	}
	if(g_flag==2) /**WAITING FOR THE CONTROL_ECU TO DETERMINE WHETHER THE PASSWORDS MATCH**/
	{
		switch(recieveCommand())
		{
		case PASSWORD_MATCH:
			g_flag=3;
			Stage=1;
			break;

		case PASSWORD_NOT_MATCHED:
			PasswordDOESNTMATCHScreen();
			g_flag=0;
			break;
		}
	}
}

void FillPassword(uint8 a_arr[]){
	uint8 counter=0;
	g_key=KEYPAD_getPressedKey();
	while(g_key != '=')
	{
		g_key=KEYPAD_getPressedKey();
		if( ( g_key != '+' && g_key != '-' && g_key != '*' && g_key != '%' && g_key != '=') || (g_key>= 0 && g_key<= 9) )
		{
			if(counter < PASSWORD_ARRAY_SIZE)
			{
				a_arr[counter]=g_key;
				LCD_displayCharacter('*');
				counter++;
			}
		}
		_delay_ms(500);
	}
}

void SendPassword(uint8 a_arr[])
{
	/*
	 * 1. SEND A READY COMMAND TO THE CONTROL_ECU TO SAY THAT HMI_ECI IS READY
	 * 2.WAITING UNTIL THE CONTROL_ECU SEND A READY COMMAND TOO
	 * 3.SENDING THE PASSWORD ENTERED BY THE USER FROM THE GLOBAL ARRAY
	 * 4. WAITING UNTIL THE CONTROL_ECU SENDS DONE COMMAND
	 */
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};

	for(uint8 i=0;i<PASSWORD_ARRAY_SIZE;i++)
	{
		UART_sendByte(a_arr[i]);
	}
	while(UART_recieveByte() != DONE){};
}

void PasswordDOESNTMATCHScreen(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"PW DONT MATCH");
	LCD_displayStringRowColumn(1,0,"TRY AGAIN");
	_delay_ms(2000);

}

void MainFunction(void)
{
	/*
	 * 1. DISPLAY THE MAIN OPTIONS TO THE USER ON THE SCREEN
	 * 2.DEPENDING ON WHICH OPTION HE CHOSE DO IT
	 * 3.CASE'-':
	 *           REQUEST THE OLD PASSOWRD
	 *           FILL IN THE PASSWORD FROM THE USER
	 *           SEND COMMAND TO CONTROL_ECU TO CHECK IF PASSWORD MATCHES WHAT THE USER ENTERED OR NOT
	 *           IF IT MATCHES:
	 *                         GO TO STAGE NUMBER 0 TO CHANGE THE PASSWORD
	 *           IF NOT:
	 *                  DISPLAY PASSWORD WRONG MESSAGE ALSO INCREMENT THE GLOBAL WRONG VARIABLE
	 *   CASE'+':
	 *            REQUEST THE OLD PASSOWRD
	 *            FILL IN THE PASSWORD FROM THE USER
	 *            SEND COMMAND TO CONTROL_ECU TO CHECK IF PASSWORD MATCHES WHAT THE USER ENTERED OR NOT
	 *            IF IT MATCHES:
	 *                          GO TO STAGE NUMBER 2 TO OPEN THE DOOR
	 *            IF NOT:
	 *                   DISPLAY PASSWORD WRONG MESSAGE ALSO INCREMENT THE GLOBAL WRONG VARIABLE
	 */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"(+): OPEN DOOR");
	LCD_displayStringRowColumn(1,0,"(-): CHANGE PW");
	switch(KEYPAD_getPressedKey())
	{
	case '-': /*THE USER DECIDED TO CHANGE THE PASSWORD*/
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"ENTER PW:(5)");
		LCD_moveCursor(1,0);
		_delay_ms(1000);
		FillPassword(g_password);
		sendCommand(CHECK_PASSWORD);
		SendPassword(g_password);
		switch (recieveCommand())
		{
		case PASSWORD_MATCH:
			g_flag=0; /*TO BE ABLE TO RESET THE PASSWORD INSIDE SetPasswordFirstTime() FUNCTION */
			Stage=0; /*GO TO SetPasswordFirstTime() FUNCTION AGAIN*/
			g_wrong=0; /*RESET THE WRONG COUNTER IN CASE THEY ENTERED THE WRONG PASSWORD BEFORE*/
			break;
		case PASSWORD_NOT_MATCHED:
			WrongPasswordScreen(); /*DISPLAY ON LCD WRONG PASSWORD AND INCREMENT WRONG COUNTER*/
			break;
		}
		break;
		case '+': /*THE USER DECIDED TO OPEN THE DOOR*/
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"ENTER PW:(5)");
			LCD_moveCursor(1,0);
			_delay_ms(1000);
			FillPassword(g_password);
			sendCommand(CHECK_PASSWORD);
			SendPassword(g_password);
			switch (recieveCommand()){
			case PASSWORD_MATCH:
				sendCommand(OPEN_DOOR);
				Stage=2; /*ADVANCE TO THE FINAL STAGE WHICH IS OPENING AND CLOSING OF THE GATE*/
				g_wrong=0; /*RESET THE WRONG COUNTER IN CASE THEY ENTERED THE WRONG PASSWORD BEFORE*/
				break;
			case PASSWORD_NOT_MATCHED:
				WrongPasswordScreen(); /*DISPLAY ON LCD WRONG PASSWORD AND INCREMENT WRONG COUNTER*/
				break;
			}
			break;
	}

}

void WrongPasswordScreen(void)
{
	/*
	 *1. DISPLAY A WRONG PASSWORD MESSAGE ON SCREEN
	 *2. INCREMENT THE GLOBAL WRONG VARIABLE
	 *3. SEND COMMAND TO THE CONTROL_ECU THAT THE USER HAS ENTERED A WRONG PASSWORD
	 *4. IF PASSWORD ENTERED IS WRONG 3 TIMES IN A ROW
	 *   IT WILL DISPLAY AN ALARM MESSAGE ON THE SCREEN
	 */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"INCORRECT!");
	g_wrong++;
	sendCommand(WRONG_PASSWORD);
	if(g_wrong == MAX_WRONG_COUNTER)
	{
		ALERTscreen();
	}
	_delay_ms(2000);

}

void g_tickCounterAlarm(void)
{
	g_tick++;
	if(g_tick == TIMER_TICKS_1MINUTE_STOP)
	{
		Timer1_deInit();
		g_tick=0;

	}
}

void g_tickCounterMotor(void)
{
	g_tick++;

	if(g_tick==TIMER_TICKS_15SEC_STOP)
	{
		Timer1_deInit();
		g_tick=0;
	}
}

void ALERTscreen(void)
{
	/*
	 * 1.INITIATE TIMER1 WITH THE GIVEN CONFIGURATIONS
	 * 2.SET THE CALL BACK FUNCTION
	 * 3. WHILE TIMER HASN'T FINISHED COUNTING DISPLAY ALERT MESSAGE AND TURN ON BUZZER
	 * 4. IF TIME REACHED THE REQUIRED COUNTS
	 *    WRONG COUNTER BACK TO ZERO COUNTS ALSO GO BACK TO THE MAIN FUNCTION
	 */
	LCD_clearScreen();
	Timer1_init(&TIMER_configuration); /*INITIALIZE TIMER0*/
	Timer1_setCallBack(g_tickCounterAlarm); /*sets the function which will count 1 Minute*/

	while(g_tick != TIMER_TICKS_1MINUTE)
	{
		LCD_displayStringRowColumn(0,5,"ALERT!!!!");
	}
	if(g_tick==TIMER_TICKS_1MINUTE_STOP)
	{
		g_wrong=0; /*RESETS THE WRONG FLAG*/
		Stage=1; /*RETURN TO MAIN MENU*/
	}
}

void doorIsOpeningCloseingScreen(void)
{
	/*
	 * 1.INITIATE TIMER1 WITH THE GIVEN CONFIGURATIONS
	 * 2.SET THE CALL BACK FUNCTION
	 * 3. WHILE TIMER HASN'T FINISHED COUNTING DISPLAY DOOR IS UNLOCKING AND LOCKING  MESSAGE
	 * 4. IF TIME REACHED THE REQUIRED COUNTS
	 *    WRONG COUNTER BACK TO ZERO COUNTS ALSO GO BACK TO THE MAIN FUNCTION
	 */
	LCD_clearScreen();

	Timer1_init(&TIMER_configuration);
	Timer1_setCallBack(g_tickCounterMotor);
	while(g_tick != TIMER_TICKS_15SEC)
	{
		LCD_displayStringRowColumn(0,0,"DOOR IS UNLOCKING..");
	}

	if(g_tick == TIMER_TICKS_15SEC)
	{
		LCD_clearScreen();
		_delay_ms(2000);
	}

	while(g_tick>= TIMER_TICKS_15SEC && g_tick < TIMER_TICKS_15SEC_STOP)
	{
		if(g_tick == TIMER_TICKS_15SEC_NEXT_STAGE)
		{
			Stage=1;
		}
		LCD_displayStringRowColumn(0,7,"DOOR IS LOCKING..");
	}

}
