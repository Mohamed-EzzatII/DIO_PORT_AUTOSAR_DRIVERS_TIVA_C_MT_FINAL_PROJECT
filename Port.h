 /******************************************************************************
 *                                                                             *
 * Module: Port                                                                *
 *                                                                             *
 * File Name: Port.h                                                           *
 *                                                                             *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver     *
 *                                                                             *
 * Author: Mohamed Ezzat
 *
 * DONE
 *																			   *
 ******************************************************************************/

#include"Port_Cfg.h"
//#include"Port_PBcfg.c"

#include"Std_Types.h"


#ifndef PORT_H
#define PORT_H



#define PORT_INITIALIZED    (1U)

#define PORT_UNINITIALIZED    (0U)


/* Port Vendor Id */
#define PORT_VENDOR_ID  (1205U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)
/*
 * SW Module Version is 1.0.0
 */
#define PORT_SW_MAJOR_VERSION             (1U)
#define PORT_SW_MINOR_VERSION             (0U)
#define PORT_SW_PATCH_VERSION             (0U)

/*
 * AUTOSAR Version is 4.0.3 compatible
 */
#define PORT_AR_RELEASE_MAJOR_VERSION    (4U)
#define PORT_AR_RELEASE_MINOR_VERSION    (0U)
#define PORT_AR_RELEASE_PATCH_VERSION    (3U)


/* AUTOSAR checking between Std Types and PORT Modules */

#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */

#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

   /* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif   
   


/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Port_Init API Service ID */
#define PORT_INIT_ID                    ((uint8)0x00)

/* Port_SetPinDirection API Service ID */           
#define PORT_SETPINDIRECTION_ID         ((uint8)0x01)

/* Port_RefreshPinDirection API Service ID */       
#define PORT_REFRESHPINDIRECTION_ID     ((uint8)0x02)
	
/* Port_GetVersionInfo API Service ID */            
#define PORT_GETVERSIONINFO_ID          ((uint8)0x03)

/* Port_SetPinMode API Service ID */                
#define PORT_SETPINMODE_ID              ((uint8)0x04)  

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
 
 /* Invalid Port ID request */
#define PORT_E_PARAM_PIN                 ((uint8)0x0A)

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE    ((uint8)0x0B)

/* API Port_Init service called with wrong parameters */
#define PORT_E_PARAM_CONFIG              ((uint8)0x0C)

/* API Port_SetPinMode service called with invalid mode */
#define PORT_E_PARAM_INVALID_MODE        ((uint8)0x0D)

/* API Port_SetPinMode service called, when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE         ((uint8)0x0E)

/* API sevice called without module initialization */
#define PORT_E_UNINIT                    ((uint8)0x0F)

/* APIs called with a NULL Pointer, Error shall be reported */
#define PORT_E_PARAM_POINTER             ((uint8)0x10)

/*******************************************************************************
 *                           MODES - PINS - PORTS ID                           *
 *******************************************************************************/
 
/*Modes' ID*/
#define PORT_PIN_MODE_ADC			(uint8)0
#define PORT_PIN_MODE_DIO			(uint8)1
#define PORT_PIN_MODE_UART			(uint8)2
#define PORT_PIN_MODE_USB			(uint8)3
#define PORT_PIN_MODE_I2C			(uint8)4
#define PORT_PIN_MODE_CAN			(uint8)5
#define PORT_PIN_MODE_PWM			(uint8)6
#define PORT_PIN_MODE_SSI			(uint8)7
#define PORT_PIN_MODE_QEI			(uint8)8
#define PORT_PIN_MODE_GPT			(uint8)9   /* GPT >>> for TxCCP & WTxCCP pins */
#define PORT_PIN_MODE_NMI			(uint8)10
#define PORT_PIN_MODE_ANALOG_COMP	        (uint8)11  /* C0 */
#define PORT_PIN_MODE_CORE			(uint8)12  /*TRD0,TRD!,TRCLK*/ 

/* Port Pin ID number & the data type for the symbolic name of a port pin. */
#define PORT_A_PIN_0    (Port_PinType)0
#define PORT_A_PIN_1    (Port_PinType)1
#define PORT_A_PIN_2    (Port_PinType)2
#define PORT_A_PIN_3    (Port_PinType)3
#define PORT_A_PIN_4    (Port_PinType)4
#define PORT_A_PIN_5    (Port_PinType)5
#define PORT_A_PIN_6    (Port_PinType)6
#define PORT_A_PIN_7    (Port_PinType)7
   
#define PORT_B_PIN_0    (Port_PinType)8
#define PORT_B_PIN_1    (Port_PinType)9
#define PORT_B_PIN_2    (Port_PinType)10 
#define PORT_B_PIN_3    (Port_PinType)11 
#define PORT_B_PIN_4    (Port_PinType)12 
#define PORT_B_PIN_5    (Port_PinType)13 
#define PORT_B_PIN_6    (Port_PinType)14
#define PORT_B_PIN_7    (Port_PinType)15
   
#define PORT_C_PIN_0    (Port_PinType)16
#define PORT_C_PIN_1    (Port_PinType)17 
#define PORT_C_PIN_2    (Port_PinType)18
#define PORT_C_PIN_3    (Port_PinType)19
#define PORT_C_PIN_4    (Port_PinType)20
#define PORT_C_PIN_5    (Port_PinType)21
#define PORT_C_PIN_6    (Port_PinType)22 
#define PORT_C_PIN_7    (Port_PinType)23
   
#define PORT_D_PIN_0    (Port_PinType)24
#define PORT_D_PIN_1    (Port_PinType)25   
#define PORT_D_PIN_2    (Port_PinType)26   
#define PORT_D_PIN_3    (Port_PinType)27   
#define PORT_D_PIN_4    (Port_PinType)28   
#define PORT_D_PIN_5    (Port_PinType)29   
#define PORT_D_PIN_6    (Port_PinType)30   
#define PORT_D_PIN_7    (Port_PinType)31
   
#define PORT_E_PIN_0    (Port_PinType)32
#define PORT_E_PIN_1    (Port_PinType)33
#define PORT_E_PIN_2    (Port_PinType)34
#define PORT_E_PIN_3    (Port_PinType)35
#define PORT_E_PIN_4    (Port_PinType)36
#define PORT_E_PIN_5    (Port_PinType)37
   
#define PORT_F_PIN_0    (Port_PinType)38
#define PORT_F_PIN_1    (Port_PinType)39
#define PORT_F_PIN_2    (Port_PinType)40
#define PORT_F_PIN_3    (Port_PinType)41
#define PORT_F_PIN_4    (Port_PinType)42 

/*PORT INDEXS*/  
#define PORT_A     (0U)
#define PORT_B     (1U)
#define PORT_C     (2U)
#define PORT_D     (3U)
#define PORT_E     (4U)
#define PORT_F     (5U) 
   
/*PIN INDEXS*/    
#define PORT_PIN0 				(uint8)0
#define PORT_PIN1 				(uint8)1
#define PORT_PIN2 				(uint8)2
#define PORT_PIN3 				(uint8)3
#define PORT_PIN4 				(uint8)4
#define PORT_PIN5 				(uint8)5
#define PORT_PIN6 				(uint8)6
#define PORT_PIN7 				(uint8)7   

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
 
#define PORT_NUMBER_OF_PORT_PINS  ((uint8)(43))
#define PORT_NUMBER_OF_MODES      ((uint8)(13))

/* 
   Different port pin modes 
   The type Port_PinModeType shall be used with the function call
   Port_SetPinMode
 */
typedef uint8 Port_PinModeType;

/* Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Possible directions of a port pin */
typedef enum{

	PORT_PIN_INPUT = STD_LOW,
	PORT_PIN_OUTPUT = STD_HIGH

} Port_PinDirection;

/* Possible types of internal resistor */
typedef enum{

	DISABLED,
	PULL_UP,
	PULL_DOWN,

} Port_InternalResistorType;

/* Type of the external data structure containing the initialization 
   data for this module with the following parameters : -
   
   A - Pin mode (e.g. DIO, ADC, SPI …) : this port pin configuration is mandatory
	   unless the port pin is configured for DIO.
   
   B - Pin direction (input, output) : this port pin configuration is mandatory when the
       port pin is to be used for DIO.
   
   C - Pin level init value (see PORT055) : this port pin configuration is mandatory
	   when the port pin is used for DIO.
   
   D - Pin direction changeable during runtime (STD_ON/STD_OFF) : this port pin
	   configuration is MCU dependent.
   
   E - Pin mode changeable during runtime (STD_ON/STD_OFF) : configuration is
	   MCU dependent.
   
   F - Activation of internal pull-ups.
   
   G - Id of pin that is to be configured.
*/
typedef struct{
	
	Port_PinType pinId;
	Port_PinDirection direction;
	uint8 pinInitialValue;
	uint8 pinDirectionChangeable;
	uint8 pinModeChangeable;
	Port_InternalResistorType resistor;
	Port_PinModeType pinMode;
	
} Port_ConfigPins;


/* The array of struct which will carry the configuration of each pin */
typedef struct
{
	Port_ConfigPins Pins[PORT_NUMBER_OF_PORT_PINS ]; 
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): ConfigPtr -> Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initializes the Port Driver module.
*              - Setup the pins as Digital GPIO pins
*              - Setup the direction of the GPIO pins
*              - Setup the internal resistor for i/p pins
*              - Setup the initial value for pins  
************************************************************************************/
void Port_Init(
const Port_ConfigType* ConfigPtr
);

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in):  Pin       -> Port Pin ID number 
                    Direction -> Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

void Port_SetPinDirection( 
Port_PinType Pin, 
Port_PinDirection Direction
);

#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in):  None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(
void
);

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in):  None 
* Parameters (inout): None
* Parameters (out): versioninfo -> Pointer to where to store the version 
*					information of this module
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_GetVersionInfo(
Std_VersionInfoType* versioninfo
);
#endif

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in):  Pin  -> Port Pin ID number 
                    Mode -> Port Pin Mode 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinMode(
Port_PinType Pin,
Port_PinModeType Mode
);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
const extern Port_ConfigType port_cfg;
#endif /* PORT_H */