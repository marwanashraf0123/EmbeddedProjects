/*
 * main.h
 *
 *  Created on: 31 Oct 2022
 *      Author: marwa
 */

#ifndef MAIN_H_
#define MAIN_H_

#include"EEPROM.h"
#include"UART.h"
#include "Timer1.h"
#include"Motor.h"
#include"buzzer.h"
#include <util/delay.h>
#include "std_types.h"
#include"comman_macros.h"
#include "I2C.h"
/********************************************************************************************************************
                                                            Definations
 ********************************************************************************************************************/
#define READY                                              0x01
#define DONE                                               0x02
#define PASSWORD_SEND                                      0x03
#define PASSWORD_MATCH                                     0x04
#define PASSWORD_NOT_MATCHED                               0x05
#define PASSWORD_CONFIRMATION_SEND                         0x06
#define CHANGE_PASSWORD                                    0x07
#define OPEN_DOOR                                          0x08
#define CHECK_PASSWORD                                     0x09
#define WRONG_PASSWORD                                      0xA
#define CHECK_IF_SAVED                                      0xB
#define YES_SAVED                                           0xC
#define NO_SAVED_PASSWORD                                   0xD
#define TICKS_15SECS                                        2
#define TICKS_15SECS_REVERSE                                3
#define TIMER_TICKS_15SEC_STOP                              4
#define TIMER_TICKS_1MINUTE                                 12
#define TIMER_TICKS_1MINUTE_STOP                            13
#define MAX_WRONG_COUNTER                                   3
#define PASSWORD_ARRAY_SIZE                                 5
#define DEFUALT_VALUE_OF_EEPROM                             1

/****************************************************************************************************************
                                                           Configrations
 ****************************************************************************************************************/
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


TWI_ConfigType TWI_Config = {0b0000010,BaudRate_2}; //baudrate 96000
/*******************************************************************************************************************
                                                            Global Variables
 *******************************************************************************************************************/
uint8 g_password[5];
uint8 g_passmatch[5];
uint8 savedpass[5];
uint8 g_command;
uint8 g_tick=0;
uint8 g_wrong=0;

/*******************************************************************************************************************
                                                               Prototypes
 *******************************************************************************************************************/
/*Function to Send commands to the control ECU Using UART*/
void sendCommand(uint8 command);
/*Function to receive commands from the control ECU Using UART*/
uint8 recieveCommand(void);
/*Function to recevie password stored in global array*/
void recievePassword(uint8 a_arr[]);
/*Function Stores Password in EEPROM*/
void storePasswordInMemory(void);
/*Function Recevie two password check if they match to store in EEPROM*/
boolean Match_or_NoMatch(uint8 *PASS1,uint8 *PASS2);
/*Function gets the password from EEPROM and store it in array*/
void getSavedPassword(uint8 a_arr[]);
/*Function activates the alarm*/
void g_tickCounterAlarm(void);
/*Function to assign the call back function(every interrupt) to of the motor timer (15 seconds)*/
void g_tickCounterMotor(void);















#endif /* MAIN_H_ */
