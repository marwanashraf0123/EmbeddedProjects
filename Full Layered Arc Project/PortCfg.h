/******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Marwan Ashraf
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
Moduel Versio 1.0.0
*/

#define PORT_CFG_SW_MAJOR_VERSION    (1U)
#define PORT_CFG_SW_MINOR_VERSION    (0U)
#define PORT_CFG_SW_PATCH_VERSION    (0U)
/*
AUTOSAR Version 4.0.3
*/

#define PORT_CFG_AR_RELEASE_MAJOR_VERSION    (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION    (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION    (3U)

/*Pre Compile option for Port_SetPinDirection*/
#define PORT_SET_PIN_DRIECTION_API    (STD_ON)

/* Pre Compile option for Port_GetVersionInfo*/
#define PORT_GET_VERSION_INFO_API      (STD_ON)


/* Pre compile option for Port_SetPinMod*/
#define PORT_SET_PIN_MODE_API           (STD_ON)

/* Pre Compile option for Dev Error*/
#define PORT_DEV_ERROR_DETECT           (STD_ON)

/* Number of configured pins in Tiva c*/
#define PORT_CONFIGURED_PINS              (43U)

/* Ports For tive c*/
#define PORT_PortA                        (0U)
#define PORT_PortB                        (1U)
#define PORT_PortC                        (2U)
#define PORT_PortD                        (3U)
#define PORT_PortE                        (4U)
#define PORT_PortF                        (5U)

/* pins for tiva c */
#define PORT_Pin0                          (0U)
#define PORT_Pin1                          (1U)
#define PORT_Pin2                          (2U)
#define PORT_Pin3                          (3U) 
#define PORT_Pin4                          (4U)
#define PORT_Pin5                          (5U)
#define PORT_Pin6                          (6U)
#define PORT_Pin7                          (7U)

#endif /* PORT_CFG_H */
