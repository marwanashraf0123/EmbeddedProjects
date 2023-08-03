/*
 * main.h
 *
 *  Created on: 27 Oct 2022
 *      Author: marwan ashraf
 */

#ifndef MAIN_H_
#define MAIN_H_

/******************************************************************************************************************
                                                    Includes
 ******************************************************************************************************************/

#include "lcd.h"
#include "Timer1.h"
#include"UART.h"
#include "keypad.h"
/*******************************************************************************************************************
                                                        Definitions
 *******************************************************************************************************************/
/* Bytes are send or received as a command indicating a certain activity is starting or ending*/
#define READY                                               0x01
#define DONE                                                0x02
#define PASSWORD_SEND                                       0x03
#define PASSWORD_MATCH                                      0x04
#define PASSWORD_NOT_MATCHED                                0x05
#define PASSWORD_CONFIRMATION_SEND                          0x06
#define CHANGE_PASSWORD                                     0x07
#define OPEN_DOOR                                           0x08
#define CHECK_PASSWORD                                      0x09
#define WRONG_PASSWORD                                      0xA
#define CHECK_IF_SAVED                                      0xB
#define YES_SAVED                                           0xC
#define NO_SAVED_PASSWORD                                   0xD
#define PASSWORD_ARRAY_SIZE                                 5
#define TIMER_TICKS_15SEC                                   2
#define TIMER_TICKS_15SEC_STOP                              4
#define TIMER_TICKS_15SEC_NEXT_STAGE                        3
#define TIMER_TICKS_1MINUTE                                 12
#define TIMER_TICKS_1MINUTE_STOP                            13
#define GLOBALE_ARRAY_OF_POINTERS_SIZE                      3
#define MAX_WRONG_COUNTER                                   3

/*********************************************************************************************************************
                                                Configurations
 **********************************************************************************************************************/
/* Character to be sent in 8 bit mode
 * Async mode
 * Parity bit disabled
 * Stop bit  = 1
 */
UART_config UART_configuration = {bit8_mod,Asynmod,praity_disabled,stop_1bit};

/*Start counting from 0
 * Compare match  = 39062
 * Prescale value = 1024
 * Compare mode timer1
 */
Timer1_ConfigType TIMER_configuration = {0,39062,F_CPU_1024,Compare};

/**********************************************************************************************************************
                                                   Prototypes
 ***********************************************************************************************************************/
/*   The main functions of the HMI_ECU that has 2 options either
 * 	 to open the door or to change the password and according to
 * 	 the user decision it send the chosen command to the control ECU*/

void MainFunction(void);

/*  Function used to display a wrong entered password on screen also count
 *  the number of times that the user entered a wrong password*/
void WrongPasswordScreen(void);
/* Tells the user that he entered a wrong password in the second time while setting a new password*/
void PasswordDOESNTMATCHScreen(void);
/* Function to Create and Store password in a global array*/
void SetPasswordFirstTime(void);
/* Function to Send password that is stored in the global array*/
void SendPassword(uint8 a_arr[]);
/*  Function to Fill in the password from the user using the keypad interfacing
                and store it in a global array*/
void FillPassword(uint8 a_arr[]);
/*Function to Send commands to the control ECU Using UART*/
void sendCommand(uint8 command);
/*Function to receive commands from the control ECU Using UART*/
uint8 recieveCommand(void);
/*It checks whether the user has already entered a password safely and saved it in
 		   the EEPROM or it's his first time creating a password */
void CheckIfPasswordExists(void);
/*Turns on the buzzer for a minute and shows an alert message on the LCD*/
void ALERTscreen(void);
/*Function to assign the call back function(every interrupt) to of the motor timer (15 seconds)*/
void g_tickCounterMotor(void);
/* Function to display a message for 15 seconds that the door is closing and the door is opening for another 15 seconds*/
void doorIsOpeningCloseingScreen(void);
/*Function activates the alarm*/
void g_tickCounterAlarm(void);





#endif /* MAIN_H_ */
