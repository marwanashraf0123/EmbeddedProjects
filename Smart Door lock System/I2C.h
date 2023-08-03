/*
 * I2C.h
 *
 *  Created on: 25 Oct 2022
 *      Author: marwan ashraf
 */

#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "comman_macros.h"
#include "std_types.h"

/**********************************************************************************************************************
                                                              Definitions
 **********************************************************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/*********************************************************************************************************************
                                                             Types
 *********************************************************************************************************************/
typedef enum
{
	 BaudRate_0,BaudRate_1,BaudRate_2,BaudRate_3
}TWI_BaudRate;

typedef struct
{
	uint8 address;
	TWI_BaudRate bit_rate;
}TWI_ConfigType;




/*********************************************************************************************************************
                                                            Prototypes
 *********************************************************************************************************************/
/*
 * Enabling The TWI
 * Set the bit rate
 * Set slave adress for the device
 * Set the prescaler for the bit rate TWSR
 */

void TWI_init(const  TWI_ConfigType * Config_Ptr);


/*
 * Function used to send the Start bit to  initiate communication
 *Clear the TWINT flag before sending
 *   wait for the flag  TWINT to be set to indicate the the stop byte has been sent
 */
void TWI_start(void);

/*
 * Function used to send the Stop bit to  initiate communication
 *Clear the TWINT flag before sending
 *Clear wait for the flag  TWINT to be set to indicate the the start byte has been sent
 */
void TWI_stop(void);

/*
 * Store the TWDR in a variable
 * Clear the flag TWINT
 * wait for the flag  TWINT to be set to indicate the the byte has been sent
 */
void TWI_writeByte(uint8 data);

/*
 * Clear flag TWINT
 * Enable the positive ACK bit so after receiving one byte sends ACK indicates that the byte has been received successfuly
 *  wait for the flag  TWINT to be set to indicate the the byte has been received
 *  Return the contact of TWDR
 */
uint8 TWI_readByteWithACK(void);
/*
 * Clear flag TWINT
 *  wait for the flag  TWINT to be set to indicate the the byte has been received
 *  Return the contact of TWDR
 */

uint8 TWI_readByteWithNACK(void);

/*
 * Return the statues of the TWI
 */
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */
