/******************************************************************************
 *
 * Module	   : Port
 *
 * File Name   : Port_PBcfg.h
 *
 * Description : Post-Build Configuration Header file for TM4C123GH6PM Microcontroller 
 *				Port Driver
 *
 * Author	   : Mohamed Ezzat
 ******************************************************************************/

#ifndef Port_PBCFG_H
#define Port_PBCFG_H


/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              	(1U)
#define PORT_PBCFG_SW_MINOR_VERSION              	(0U)
#define PORT_PBCFG_SW_PATCH_VERSION              	(0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     	(4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     	(0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     	(3U)

const extern Port_ConfigType port_cfg;
#endif