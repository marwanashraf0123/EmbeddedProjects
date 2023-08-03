/*
 * EEPROM.h
 *
 *  Created on: 25 Oct 2022
 *      Author: marwan ashraf
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);




#endif /* EEPROM_H_ */
