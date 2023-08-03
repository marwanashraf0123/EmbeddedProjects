 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Marwan Ashraf
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

#include "Common_Macros.h"
/*Port Vendor  id*/
#define PORT_VENDOR_ID    (1000U)


/*Port Moduel id*/
#define PORT_MODULE_ID    (123U)

/*Port instance id*/
#define PORT_INSTANCE_ID    (0U)



/* SW version 1.0.0*/
#define PORT_SW_MAJOR_VERSION            (1U)
#define PORT_SW_MINOR_VERSION            (0U)
#define PORT_SW_PATCH_VERSION            (0U)

/* Autosar version 4.0.3*/
#define PORT_AR_RELEASE_MAJOR_VERSION             (4U)
#define PORT_AR_RELEASE_MINOR_VERSION             (0U)
#define PORT_AR_RELEASE_PATCH_VERSION             (3U)




/*STD_types  header file*/

#include "Std_Types.h"

/*Check AUTOSAR Version with Port.h*/
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
  
/*Pre compile config header file*/
#include "Port_CFG.h"

/*Check AUTOSAR Version with Port.h*/
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

 /* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

   /*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)
#define ZERO                            (0U)
  
/************************************************************************************************
                                           API Service Id Macros
  **********************************************************************************************/
 
  /*Service ID for port init*/
#define PORT_INIT_SID    (uint8)0x00

/*Service ID for port set pin direction */
#define PORT_SET_PIN_DIR_SID     (uint8)0x01
  
/*Service ID for port Refresh port  direction */
#define PORT_REFRESH_PORT_DIR_SID     (uint8)0x03

/*Service ID for port get versio info */
#define PORT_GET_VERSION_INFO_SID         (uint8)0x04
  
/*Service ID for port get versio info */
#define PORT_SET_PIN_MODE_SID             (uint8)0x05


/************************************************************************************************
                                           API For Det Errors
  **********************************************************************************************/
 /* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                   (uint8)0x0A  
  
  /*API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_DIRECTION_UNCHANGEABLE      (uint8)0x0A
  
  /*Port Pin not configured as changeable */
#define PORT_E_PARAM_CONFIG                (uint8)0x0C
 
  /* API Port_Init service */  
#define PORT_E_PARAM_INVALID_MODE          (uint8)0x0D
  
  /* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE           (uint8)0x0E 

  /*API service called without module initialization */
#define PORT_E_UNINIT                      (uint8)0x0F
 
  /* APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER               (uint8)0x10




/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

  
  /*Data type for the symbolic name of a port pin.*/
  typedef uint8 Port_PinType;
  

/*Possible directions of a port pin*/
 typedef enum
 {
   PORT_PIN_IN,PORT_PIN_OUT
   
 }Port_PinDirectionType;

 /*Different port pin modes*/
 typedef uint8 Port_PinModeType;
  
 /* Description: Port Pin Level value from Port pin list */
 
  typedef enum
  {
    PORT_PIN_LEVEL_LOW,
    PORT_PIN_LEVEL_HIGH
    
  }Port_PinLevelValue;
  
  /* Enum to define the mode of the pin */
  typedef enum
  {
    PORT_PIN_MODE_ADC,
    PORT_PIN_MODE_ALT1,
    PORT_PIN_MODE_ALT2,
    PORT_PIN_MODE_ALT3,
    PORT_PIN_MODE_ALT4,
    PORT_PIN_MODE_ALT6,
    PORT_PIN_MODE_ALT7,
    PORT_PIN_MODE_ALT8,
    PORT_PIN_MODE_ALT9,
    PORT_PIN_MODE_DIO,
    
  }Port_PinInitialMode; 
  
/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;


/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{
    uint8 port_num;                   /*ex..PORT_PortA*/
    Port_PinType pin_num;               /*ex.. PORT_PIN0*/ 
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;                /*PULL_UP*/
    Port_PinLevelValue initial_value;             /*ON-OFF*/
    Port_PinInitialMode  initial_mode;                /*PORT_PIN_MODE_DIO*/
    uint8 pin_dir_changeable;			/* STD_ON,STD_OFF 							*/
    uint8 pin_mode_changeable;                   /* STD_ON,STD_OFF */
}Port_ConfigPin;

/* Array of Port_ConfigPin */
typedef struct
{
	Port_ConfigPin Pin[PORT_CONFIGURED_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Service ID :  0x00
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
               - Intialize The direction
               - Intialize The Mode
               - Intialize The internal resistor
               
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );

/**********************************************************************************
** Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Service ID :  0x01
* Reentrancy: reentrant
* Parameters (in): Pin Port Pin ID Number - Port Pin Direction Number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
***********************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction) ;

/**********************************************************************************
** Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Service ID :  0x02
* Reentrancy: Non Reentrant 
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction
***********************************************************************************/
void Port_RefreshPortDirection(void);

/**********************************************************************************
** Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Service ID :  0x03
* Reentrancy: Non Reentrant 
* Parameters (in): versioninfo Pointer to where to store the version information of this module.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
***********************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)

void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif
/**********************************************************************************
** Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Service ID :  0x04
* Reentrancy:  Reentrant 
* Parameters (in): Pin-->Port Pin ID number  Mode -->New Port Pin mode to be set on port pin.  
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
***********************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)

void Port_SetPinMode( Port_PinType Pin,Port_PinModeType Mode);
#endif
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_PinConfig;

#endif /* PORT_H */
