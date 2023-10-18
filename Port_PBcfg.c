 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Ezzat
 ******************************************************************************/
#include "Port.h"
const Port_ConfigType port_cfg = {	

	   /******************************************************************************************
	    *******************************************PORT A***************************************** 
	    ******************************************************************************************/
	
         PORT_A_PIN_0,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_0_DIR_CHANG,PORT_A_PIN_0_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_1,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_1_DIR_CHANG,PORT_A_PIN_1_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_2,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_2_DIR_CHANG,PORT_A_PIN_2_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_3,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_3_DIR_CHANG,PORT_A_PIN_3_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_4,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_4_DIR_CHANG,PORT_A_PIN_4_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_5,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_5_DIR_CHANG,PORT_A_PIN_5_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_6,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_6_DIR_CHANG,PORT_A_PIN_6_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_A_PIN_7,PORT_PIN_INPUT,STD_LOW,PORT_A_PIN_7_DIR_CHANG,PORT_A_PIN_7_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,

	   /******************************************************************************************
	    *******************************************PORT B***************************************** 
	    ******************************************************************************************/

         PORT_B_PIN_0,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_0_DIR_CHANG,PORT_B_PIN_0_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_1,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_1_DIR_CHANG,PORT_B_PIN_1_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_2,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_2_DIR_CHANG,PORT_B_PIN_2_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_3,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_3_DIR_CHANG,PORT_B_PIN_3_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_4,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_4_DIR_CHANG,PORT_B_PIN_4_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_5,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_5_DIR_CHANG,PORT_B_PIN_5_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_6,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_6_DIR_CHANG,PORT_B_PIN_6_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_B_PIN_7,PORT_PIN_INPUT,STD_LOW,PORT_B_PIN_7_DIR_CHANG,PORT_B_PIN_7_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,

	   /******************************************************************************************
	    *******************************************PORT C***************************************** 
	    ******************************************************************************************/

	 PORT_C_PIN_0,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_0_DIR_CHANG,PORT_C_PIN_0_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_1,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_1_DIR_CHANG,PORT_C_PIN_1_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_2,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_2_DIR_CHANG,PORT_C_PIN_2_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_3,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_3_DIR_CHANG,PORT_C_PIN_3_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_4,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_4_DIR_CHANG,PORT_C_PIN_4_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_5,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_5_DIR_CHANG,PORT_C_PIN_5_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_6,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_6_DIR_CHANG,PORT_C_PIN_6_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_C_PIN_7,PORT_PIN_INPUT,STD_LOW,PORT_C_PIN_7_DIR_CHANG,PORT_C_PIN_7_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,

	   /******************************************************************************************
	    *******************************************PORT D***************************************** 
	    ******************************************************************************************/

         PORT_D_PIN_0,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_0_DIR_CHANG,PORT_D_PIN_0_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_1,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_1_DIR_CHANG,PORT_D_PIN_1_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_2,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_2_DIR_CHANG,PORT_D_PIN_2_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_3,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_3_DIR_CHANG,PORT_D_PIN_3_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_4,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_4_DIR_CHANG,PORT_D_PIN_4_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_5,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_5_DIR_CHANG,PORT_D_PIN_5_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_6,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_6_DIR_CHANG,PORT_D_PIN_6_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_D_PIN_7,PORT_PIN_INPUT,STD_LOW,PORT_D_PIN_7_DIR_CHANG,PORT_D_PIN_7_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,

	   /******************************************************************************************
	    *******************************************PORT E***************************************** 
	    ******************************************************************************************/

         PORT_E_PIN_0,PORT_PIN_INPUT,STD_LOW,PORT_E_PIN_0_DIR_CHANG,PORT_E_PIN_0_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_E_PIN_1,PORT_PIN_INPUT,STD_LOW,PORT_E_PIN_1_DIR_CHANG,PORT_E_PIN_1_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_E_PIN_2,PORT_PIN_INPUT,STD_LOW,PORT_E_PIN_2_DIR_CHANG,PORT_E_PIN_2_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_E_PIN_3,PORT_PIN_INPUT,STD_LOW,PORT_E_PIN_3_DIR_CHANG,PORT_E_PIN_3_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_E_PIN_4,PORT_PIN_INPUT,STD_LOW,PORT_E_PIN_4_DIR_CHANG,PORT_E_PIN_4_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_E_PIN_5,PORT_PIN_INPUT,STD_LOW,PORT_E_PIN_5_DIR_CHANG,PORT_E_PIN_5_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,

	   /******************************************************************************************
	    *******************************************PORT F***************************************** 
	    ******************************************************************************************/

         PORT_F_PIN_0,PORT_PIN_OUTPUT,STD_LOW,PORT_F_PIN_0_DIR_CHANG, PORT_F_PIN_0_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_F_PIN_1,PORT_PIN_OUTPUT,STD_LOW,PORT_F_PIN_1_DIR_CHANG,PORT_F_PIN_1_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,             
         PORT_F_PIN_2,PORT_PIN_OUTPUT,STD_LOW,PORT_F_PIN_2_DIR_CHANG, PORT_F_PIN_2_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_F_PIN_3,PORT_PIN_INPUT,STD_LOW,PORT_F_PIN_3_DIR_CHANG, PORT_F_PIN_3_MODE_CHANG,DISABLED,PORT_PIN_MODE_DIO,
         PORT_F_PIN_4,PORT_PIN_INPUT,STD_LOW,PORT_F_PIN_4_DIR_CHANG, PORT_F_PIN_4_MODE_CHANG,PULL_UP,PORT_PIN_MODE_DIO,
};		 