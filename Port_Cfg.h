 /******************************************************************************
 *
 * Module	   : Port
 *
 * File Name   : Port_Cfg.h
 *
 * Description : Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller 
 *				Port Driver
 *
 * Author	   : Mohamed Ezzat
 ******************************************************************************/

#ifndef Port_CFG_H
#define Port_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              	(1U)
#define PORT_CFG_SW_MINOR_VERSION              	(0U)
#define PORT_CFG_SW_PATCH_VERSION              	(0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     	(4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     	(0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     	(3U)

/* Switches the Development Error Detection and Notification on or off.
   true: Enabled. false: Disabled.*/
#define PORT_DEV_ERROR_DETECT					(STD_ON)

/* Pre-processor switch to enable or disable the use of the function Port_SetPinDirection().
   TRUE: Enabled - Function Port_SetPinDirection() is available.
   FALSE: Disabled - Function Port_SetPinDirection() is not available. */ 
#define PORT_SET_PIN_DIRECTION_API				(STD_ON)

/* Pre-processor switch to enable or disable the use of the function Port_SetPinMode().
   TRUE: Enabled - Function Port_SetPinMode() is available.
   FALSE: Disabled - Function Port_SetPinMode() is not available. */
#define PORT_SET_PIN_MODE_API					(STD_ON)

/* Pre-processor switch to enable or disable the use of the function Version info API.
   TRUE: Enabled - Function Version info API is available.
   FALSE: Disabled - Function Version info API is not available. */
#define PORT_VERSION_INFO_API					(STD_ON)

/*
   Parameter to indicate if the Direction is changeable on a port pin during runtime.
   True: Port Pin Direction changeable allowed.
   False: Port Pin Direction changeable not permitted.
*/
#define PORT_A_PIN_0_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_1_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_2_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_3_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_4_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_5_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_6_DIR_CHANG         			(STD_OFF)
#define PORT_A_PIN_7_DIR_CHANG         			(STD_OFF)
			
#define PORT_B_PIN_0_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_1_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_2_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_3_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_4_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_5_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_6_DIR_CHANG         			(STD_OFF)
#define PORT_B_PIN_7_DIR_CHANG         			(STD_OFF)
			
#define PORT_C_PIN_0_DIR_CHANG         			(STD_OFF)
#define PORT_C_PIN_1_DIR_CHANG         			(STD_OFF)
#define PORT_C_PIN_2_DIR_CHANG         			(STD_OFF)
#define PORT_C_PIN_3_DIR_CHANG         			(STD_OFF)
#define PORT_C_PIN_4_DIR_CHANG         			(STD_OFF)
#define PORT_C_PIN_5_DIR_CHANG         			(STD_OFF) 
#define PORT_C_PIN_6_DIR_CHANG         			(STD_OFF)
#define PORT_C_PIN_7_DIR_CHANG         			(STD_OFF)
			
#define PORT_D_PIN_0_DIR_CHANG         			(STD_OFF)
#define PORT_D_PIN_1_DIR_CHANG         			(STD_OFF)
#define PORT_D_PIN_2_DIR_CHANG         			(STD_OFF) 
#define PORT_D_PIN_3_DIR_CHANG         			(STD_OFF)
#define PORT_D_PIN_4_DIR_CHANG         			(STD_OFF)
#define PORT_D_PIN_5_DIR_CHANG         			(STD_OFF)
#define PORT_D_PIN_6_DIR_CHANG         			(STD_OFF)
#define PORT_D_PIN_7_DIR_CHANG         			(STD_OFF) 
			
#define PORT_E_PIN_0_DIR_CHANG         			(STD_OFF)
#define PORT_E_PIN_1_DIR_CHANG         			(STD_OFF)
#define PORT_E_PIN_2_DIR_CHANG         			(STD_OFF) 
#define PORT_E_PIN_3_DIR_CHANG         			(STD_OFF)
#define PORT_E_PIN_4_DIR_CHANG         			(STD_OFF)
#define PORT_E_PIN_5_DIR_CHANG         			(STD_OFF)   
			
#define PORT_F_PIN_0_DIR_CHANG         			(STD_OFF)
#define PORT_F_PIN_1_DIR_CHANG         			(STD_OFF)
#define PORT_F_PIN_2_DIR_CHANG         			(STD_OFF) 
#define PORT_F_PIN_3_DIR_CHANG         			(STD_OFF)
#define PORT_F_PIN_4_DIR_CHANG         			(STD_OFF) 

/*
   Parameter to indicate if the mode is changeable on a port pin during runtime.
   True: Port Pin mode changeable allowed.
   False: Port Pin mode changeable not permitted.
*/
#define PORT_A_PIN_0_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_1_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_2_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_3_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_4_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_5_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_6_MODE_CHANG         			(STD_OFF)
#define PORT_A_PIN_7_MODE_CHANG         			(STD_OFF)
					 
#define PORT_B_PIN_0_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_1_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_2_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_3_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_4_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_5_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_6_MODE_CHANG         			(STD_OFF)
#define PORT_B_PIN_7_MODE_CHANG         			(STD_OFF)
					 
#define PORT_C_PIN_0_MODE_CHANG         			(STD_OFF)
#define PORT_C_PIN_1_MODE_CHANG         			(STD_OFF)
#define PORT_C_PIN_2_MODE_CHANG         			(STD_OFF)
#define PORT_C_PIN_3_MODE_CHANG         			(STD_OFF)
#define PORT_C_PIN_4_MODE_CHANG         			(STD_OFF)
#define PORT_C_PIN_5_MODE_CHANG         			(STD_OFF) 
#define PORT_C_PIN_6_MODE_CHANG         			(STD_OFF)
#define PORT_C_PIN_7_MODE_CHANG         			(STD_OFF)
					 
#define PORT_D_PIN_0_MODE_CHANG         			(STD_OFF)
#define PORT_D_PIN_1_MODE_CHANG         			(STD_OFF)
#define PORT_D_PIN_2_MODE_CHANG         			(STD_OFF) 
#define PORT_D_PIN_3_MODE_CHANG         			(STD_OFF)
#define PORT_D_PIN_4_MODE_CHANG         			(STD_OFF)
#define PORT_D_PIN_5_MODE_CHANG         			(STD_OFF)
#define PORT_D_PIN_6_MODE_CHANG         			(STD_OFF)
#define PORT_D_PIN_7_MODE_CHANG         			(STD_OFF) 
					 
#define PORT_E_PIN_0_MODE_CHANG         			(STD_OFF)
#define PORT_E_PIN_1_MODE_CHANG         			(STD_OFF)
#define PORT_E_PIN_2_MODE_CHANG         			(STD_OFF) 
#define PORT_E_PIN_3_MODE_CHANG         			(STD_OFF)
#define PORT_E_PIN_4_MODE_CHANG         			(STD_OFF)
#define PORT_E_PIN_5_MODE_CHANG         			(STD_OFF)   
					 
#define PORT_F_PIN_0_MODE_CHANG         			(STD_OFF)
#define PORT_F_PIN_1_MODE_CHANG         			(STD_OFF)
#define PORT_F_PIN_2_MODE_CHANG         			(STD_OFF) 
#define PORT_F_PIN_3_MODE_CHANG         			(STD_OFF)
#define PORT_F_PIN_4_MODE_CHANG         			(STD_OFF) 


#endif /* Port_CFG_H */
