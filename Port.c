/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Ezzat
 ******************************************************************************/

#include "Port.h"
#include "Det.h"
#include "Port_Regs.h"
#include "Common_Macros.h"

/******************************************************************************
 *                      	 GLOBAL VARIABLES                             *
 ******************************************************************************/

STATIC uint8 Port_initStatus = PORT_UNINITIALIZED;
STATIC const Port_ConfigPins* conf = NULL_PTR;
STATIC void Port_PrivGetPinAndPort(uint8 *pin_num,uint8 *port_num,uint8 Pin);

/*******************************************************************************
 *                      	Function Definition                            *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Port_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): conf -> Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initializes the Port Driver module.
 *              - Setup the pins as Digital GPIO pins
 *              - Setup the direction of the GPIO pins
 *              - Setup the internal resistor for i/p pins
 *              - Setup the initial value for pins  
 ************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr){
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(ConfigPtr == NULL_PTR){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_INIT_ID,
				PORT_E_PARAM_CONFIG
		);
	}
	else
#endif
	{
		conf = ConfigPtr->Pins;

		/* Dummy Variable to store the */
		volatile uint8 dummy;

		/* Some variables to store the Pin number and Port number */
		uint8 port_num;
		uint8 pin_num;
                
                                          
                /* Enable the Clock of PORT */
                SYSCTL_REGCGC2_REG |= 0x0000003F;
                dummy = SYSCTL_REGCGC2_REG;

		/* Looping on All pins */
		for(uint8 i =0; i<PORT_NUMBER_OF_PORT_PINS;i++)
		{
			/* Decide the PORT and PIN of pin */
                         Port_PrivGetPinAndPort(&pin_num,&port_num,i);
                         
                         if(port_num == 5){
                           dummy++;
                         }

			/*
			 * Set The Configuration of pin	
			 */
			if( ((port_num == 3) && (pin_num == 7)) || ((port_num == 5) && (pin_num == 0)) ) /* PD7 or PF0 */
			{
				Port_Registers[port_num]->Port_LockReg = 0x4C4F434B;         /* Unlock the GPIOCR register */   
				SET_BIT(Port_Registers[port_num]->Port_CommitReg, pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
			}
			else if( (port_num == 2) && (pin_num <= 3) ) /* PC0 to PC3 */
			{
                          /* Do Nothing ...  this is the JTAG pins so we skip the loop*/
                          continue;
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}
                        



			/* Set the pin operation as Digital */
			CLEAR_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); /* Disable the Analog Functionality */
			SET_BIT(Port_Registers[port_num]->Port_DenReg,pin_num);/* Enable the Digital Functionality */

		       /*
		 	* Set Direction of pin , we firstly clear the crossponding bit
			* and then put the value in the bit.		
			*/
			Port_Registers[port_num]->Port_DirReg[0] &= ~(STD_HIGH<<pin_num);
			Port_Registers[port_num]->Port_DirReg[0] |= ( (Direction) << pin_num);

			/* Disable The internal Pull Up and Pull Down by default and enable them only if the pin is GPIO i/p*/
			CLEAR_BIT(Port_Registers[port_num]->Port_PurReg ,pin_num);  /* Disable the Internal Pull Up */
			CLEAR_BIT(Port_Registers[port_num]->Port_PdrReg[0] ,pin_num);  /* Disable the Internal Pull DOWN */
			
			/*
			 * For Set The Mode of the pin , if it is GPIO pin , then we clear the crossponding
			 * bit in GPIOAFSEL and clear the crossponding PORT MASK CONTROL 4 bits in GPIOPCTL,
			 * else we set the PORT MASK CONTROL 4 bits in GPIOPCTL & set the crossponding
			 * bit in GPIOAFSEL.
			 * Firstly there are some settings which are not commonly configured such as Analog Functionality
			 * which is used only with ADC pins and internal resistor which is used with internal GPIO pins
			 * so i disabled them and if i need them in the required configurations
			 */
			
			/* DIO MODE */
			if((conf[i].pinMode) == PORT_PIN_MODE_DIO)
			{
				/* The associated pin functions as a GPIO and is controlled by the GPIO registers*/
				CLEAR_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); 
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);
                                
                                if(conf[i].direction == PORT_PIN_OUTPUT){
                                  
                                  /* Set the crosponding bit to make it output */
                                  Port_Registers[port_num]->Port_DirReg[0] |= ( PORT_PIN_OUTPUT << pin_num);
                                 /*   
                                  * Set Initial value of pin , we firstly clear the crossponding bit
                                  * and then put the value in the bit.		
                                  */
                                  Port_Registers[port_num]->Port_DataReg &= ~(STD_HIGH<<pin_num);
                                  Port_Registers[port_num]->Port_DataReg |= ( (conf[i].pinInitialValue) << pin_num);
  
                                }

				/* Check if the pin is i/p to configure the internal resistor */
				if( (conf[i].direction) == PORT_PIN_INPUT )
				{
                                        /* CLEAR the crosponding bit to make it intput */
                                        Port_Registers[port_num]->Port_DirReg[0] &= ~(STD_HIGH<<pin_num);
                                        
					if( (conf[i].resistor) == PULL_UP )
					{
						SET_BIT(Port_Registers[port_num]->Port_PurReg ,pin_num);  /* Enable the Internal Pull Up */
					}

					else if( (conf[i].resistor) == PULL_DOWN )
					{
						SET_BIT(Port_Registers[port_num]->Port_PdrReg[0] ,pin_num);  /* Enable the Internal Pull Down */
					}

					else
					{
						/* Do Nothing */
					}
				}
			}

			/* UART MODE */
			else if((conf[i].pinMode) == PORT_PIN_MODE_UART)
			{
				/* The associated pin functions as a UART and is controlled by the UART registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 

				/* In case of UART1 we put 2 in the crossponding 4-bits , else we put 1*/
				if(conf[i].pinId == PORT_C_PIN_4 || conf[i].pinId == PORT_C_PIN_5)
				{
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4)+1);     /* Set the 2nd bit in the required 4-bits */
				}
				else
				{
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,pin_num * 4);     /* Set the first bit in the required 4-bits */

				}
			}

			/* USB Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_USB)
			{
				/* The associated pin functions as a USB and is controlled by the USB registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 

				/* Enable The Analog Functionality For PB0 , PB1 , PD4 , PD5 pins*/
				if( conf[i].pinId == PORT_B_PIN_0 || conf[i].pinId == PORT_B_PIN_1){
					SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);  /* Disable the Digital Functionality */
					CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num);  /* Enable the Analog Functionality */
				}
				else if( conf[i].pinId == PORT_D_PIN_4 || conf[i].pinId == PORT_D_PIN_5){
					SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);  /* Disable the Digital Functionality */
					CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num);  /* Enable the Analog Functionality */
				}
				else /* PORTC - PORTD - PORTF */
				{
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4)+3); /* Set the 4th bit in the required 4-bits */
				}
			}

			/* I2C Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_I2C)
			{
				/* The associated pin functions as a I2C and is controlled by the I2C registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,pin_num * 4);     /* Set the first bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1);/* Set the Second bit in the required 4-bits */
			}

			/* SSI Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_SSI)
			{
				/* The associated pin functions as a SSI and is controlled by the SSI registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1);/* Set the Second bit in the required 4-bits */
			}

			/* CAN Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_CAN)
			{
				/* The associated pin functions as a CAN and is controlled by the CAN registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */

				/* In case of PF0 or PF3 , we set the 1st and second bit , else the 4th bit */
				if(conf[i].pinId == PORT_F_PIN_0 || conf[i].pinId == PORT_F_PIN_3 )
				{
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) );/* Set the 1st bit in the required 4-bits */
				}
				else
				{					 
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3);/* Set the 4th bit in the required 4-bits */
				}
			}

			/* PWM Mode -> For PWM M0 ONLY!!!!*/
			else if((conf[i].pinMode) == PORT_PIN_MODE_PWM)
			{
				/* The associated pin functions as a PWM and is controlled by the PWM registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
			}

			/* QEI Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_QEI)
			{
				/* The associated pin functions as a QEI and is controlled by the QEI registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +2 );/* Set the 3rd bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
			}

			/* GPT Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_GPT)
			{
				/* The associated pin functions as a GPT and is controlled by the GPT registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +2 );/* Set the 3rd bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) );   /* Set the 1st bit in the required 4-bits */
			}

			/* NMI Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_NMI)
			{
				/* The associated pin functions as a NMI and is controlled by the NMI registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
			}

			/* Analog Compare Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_ANALOG_COMP)
			{
				/* The associated pin functions as a Analog Compare and is controlled by the Analog Compare registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */

				/* In case of PF0 or PF1 , we set the 1st and 4th bit , else enable analog compare */
				if(conf[i].pinId == PORT_F_PIN_0 || conf[i].pinId == PORT_F_PIN_1)
				{
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
					SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) );   /* Set the 1st bit in the required 4-bits */
				}
				else
				{
					/* Set the pin operation as Analog */
					SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); /* Enable the Analog Functionality */
					CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num); /* Disable the Digital Functionality */
				}
			}

			/* CORE Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_CORE)
			{
				/* The associated pin functions as a CORE and is controlled by the CORE registers*/
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +2 );/* Set the 3rd bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
			}

			/* ADC Mode */
			else if((conf[i].pinMode) == PORT_PIN_MODE_ADC)
			{
				/* Set the pin operation as Analog */
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); /* Enable the Analog Functionality */
				CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num); /* Disable the Digital Functionality */
				CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */

			}  
		}
	}
}

/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in):  Pin       -> Port Pin ID number 
 *                   Direction -> Port Pin Direction 
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Sets the port pin direction.
 ************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirection Direction){

	boolean error = FALSE;

#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(Port_initStatus == PORT_UNINITIALIZED){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINDIRECTION_ID,
				PORT_E_UNINIT

		);
		error = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
	if(Pin>=PORT_NUMBER_OF_PORT_PINS){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINDIRECTION_ID,
				PORT_E_PARAM_PIN

		);
		error = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
	if(conf[Pin].pinDirectionChangeable == STD_OFF){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINDIRECTION_ID,
				PORT_E_DIRECTION_UNCHANGEABLE

		);
		error = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
#endif
	if( FALSE == error )
	{
		/* Some variables to store the Pin number and Port number */
		uint8 port_num;
		uint8 pin_num;

		/* Decide the PORT and PIN of pin */
		Port_PrivGetPinAndPort(&pin_num,&port_num,Pin);

		/*
		 * Set Direction of pin , we firstly clear the crossponding bit
		 * and then put the value in the bit.		
		 */
		Port_Registers[port_num]->Port_DirReg[0] &= ~(STD_HIGH<<pin_num);
		Port_Registers[port_num]->Port_DirReg[0] |= ( (Direction) << pin_num);

	}
}

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
void Port_RefreshPortDirection(void){

#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(Port_initStatus == PORT_UNINITIALIZED){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_REFRESHPINDIRECTION_ID,
				PORT_E_UNINIT

		);
	}
	else
#endif
	{
         uint8 pin_num,port_num;
          		/* Looping on All pins */
		for(uint8 i =0; i<PORT_NUMBER_OF_PORT_PINS;i++)
		{
			/* Decide the PORT and PIN of pin */
                         Port_PrivGetPinAndPort(&pin_num,&port_num,i);

			/*
			 * Set The Configuration of pin	
			 */

			/*
			 * Set Direction of pin , we firstly clear the crossponding bit
			 * and then put the value in the bit.		
			 */
			Port_Registers[port_num]->Port_DirReg[0] &= ~(STD_HIGH<<pin_num);
			Port_Registers[port_num]->Port_DirReg[0] |= ( (conf[i].direction) << pin_num);
                }
	}
}

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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo){
	boolean error = FALSE;
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(Port_initStatus == PORT_UNINITIALIZED){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_GETVERSIONINFO_ID,
				PORT_E_UNINIT

		);
		error = TRUE;
	}
	else
	{

	}
	if(versioninfo == NULL_PTR){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_GETVERSIONINFO_ID,
				PORT_E_PARAM_POINTER

		);
		error = TRUE;
	}
	else
	{

	}
#endif

if( FALSE == error )
{
	/* Copy the vendor Id */
	versioninfo->vendorID = (uint16)PORT_VENDOR_ID;

	/* Copy the module Id */
	versioninfo->moduleID = (uint16)PORT_MODULE_ID;

	/* Copy Software Major Version */
	versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;

	/* Copy Software Minor Version */
	versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;

	/* Copy Software Patch Version */
	versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;

}

}
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in):  Pin  -> Port Pin ID number 
 *                   Mode -> Port Pin Mode 
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Sets the port pin mode.
 ************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode){
	boolean error = FALSE;
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(Port_initStatus == PORT_UNINITIALIZED){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINMODE_ID,
				PORT_E_UNINIT

		);
		error = TRUE;
	}
	else
	{


	}
	if(conf[Pin].pinModeChangeable == STD_OFF){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINMODE_ID,
				PORT_E_MODE_UNCHANGEABLE

		);
		error = TRUE;
	}
	else

	{


	}
	if(Pin>=PORT_NUMBER_OF_PORT_PINS){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINMODE_ID,
				PORT_E_PARAM_PIN

		);
		error = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
	if(Mode>=PORT_NUMBER_OF_MODES){
		Det_ReportError(

				PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SETPINMODE_ID,
				PORT_E_PARAM_INVALID_MODE

		);
		error = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
#endif
	if(FALSE == error)
	{
		uint8 port_num = 0xFF,i=Pin,pin_num;
		Port_PrivGetPinAndPort(&pin_num,&port_num,i);
		/*
		 * Set The Configuration of pin	
		 */
		/*
		 * Set Direction of pin , we firstly clear the crossponding bit
		 * and then put the value in the bit.		
		 */
		Port_Registers[port_num]->Port_DirReg[0] &= ~(STD_HIGH<<pin_num);
		Port_Registers[port_num]->Port_DirReg[0] |= ( (conf[Pin].direction) << pin_num);

		/*
		 * Set Initial value of pin , we firstly clear the crossponding bit
		 * and then put the value in the bit.		
		 */
		Port_Registers[port_num]->Port_DataReg &= ~(STD_HIGH<<pin_num);
		Port_Registers[port_num]->Port_DataReg |= ( (conf[Pin].direction) << pin_num);

		/* DIO MODE */
		if((conf[i].pinMode) == PORT_PIN_MODE_DIO)
		{
			/* The associated pin functions as a GPIO and is controlled by the GPIO registers*/
			CLEAR_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); 
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);

			/* Check if the pin is i/p to configure the internal resistor */
			if( (conf[i].direction) == STD_LOW )
			{
				if( (conf[i].resistor) == PULL_UP )
				{
					SET_BIT(Port_Registers[port_num]->Port_PurReg, pin_num);  /* Enable the Internal Pull Up */
				}

				else if( (conf[i].resistor) == PULL_DOWN )
				{
					SET_BIT(Port_Registers[port_num]->Port_PdrReg[0] ,pin_num);  /* Enable the Internal Pull Down */
				}

				else
				{
					/* Do Nothing */
				}
			}
		}

		/* UART MODE */
		else if((conf[i].pinMode) == PORT_PIN_MODE_UART)
		{
			/* The associated pin functions as a UART and is controlled by the UART registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 

			/* In case of UART1 we put 2 in the crossponding 4-bits , else we put 1*/
			if(conf[i].pinId == PORT_C_PIN_4 || conf[i].pinId == PORT_C_PIN_5)
			{
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4)+1);     /* Set the 2nd bit in the required 4-bits */
			}
			else
			{
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,pin_num * 4);     /* Set the first bit in the required 4-bits */

			}
		}

		/* USB Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_USB)
		{
			/* The associated pin functions as a USB and is controlled by the USB registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 

			/* Enable The Analog Functionality For PB0 , PB1 , PD4 , PD5 pins*/
			if( conf[i].pinId == PORT_B_PIN_0 || conf[i].pinId == PORT_B_PIN_1){
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);  /* Disable the Digital Functionality */
				CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num);  /* Enable the Analog Functionality */
			}
			else if( conf[i].pinId == PORT_D_PIN_4 || conf[i].pinId == PORT_D_PIN_5){
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);  /* Disable the Digital Functionality */
				CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num);  /* Enable the Analog Functionality */
			}
			else /* PORTC - PORTD - PORTF */
			{
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4)+3); /* Set the 4th bit in the required 4-bits */
			}
		}

		/* I2C Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_I2C)
		{
			/* The associated pin functions as a I2C and is controlled by the I2C registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,pin_num * 4);     /* Set the first bit in the required 4-bits */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1);/* Set the Second bit in the required 4-bits */
		}

		/* SSI Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_SSI)
		{
			/* The associated pin functions as a SSI and is controlled by the SSI registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */					 
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1);/* Set the Second bit in the required 4-bits */
		}

		/* CAN Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_CAN)
		{
			/* The associated pin functions as a CAN and is controlled by the CAN registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */

			/* In case of PF0 or PF3 , we set the 1st and second bit , else the 4th bit */
			if(conf[i].pinId == PORT_F_PIN_0 || conf[i].pinId == PORT_F_PIN_3 )
			{
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) );/* Set the 1st bit in the required 4-bits */
			}
			else
			{					 
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3);/* Set the 4th bit in the required 4-bits */
			}
		}

		/* PWM Mode -> For PWM M0 ONLY!!!!*/
		else if((conf[i].pinMode) == PORT_PIN_MODE_PWM)
		{
			/* The associated pin functions as a PWM and is controlled by the PWM registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
		}

		/* QEI Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_QEI)
		{
			/* The associated pin functions as a QEI and is controlled by the QEI registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);     /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num); /* Delete the preivous configurations */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +2 );/* Set the 3rd bit in the required 4-bits */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
		}

		/* GPT Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_GPT)
		{
			/* The associated pin functions as a GPT and is controlled by the GPT registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,Pin);  /* Delete the preivous configurations */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +2 );/* Set the 3rd bit in the required 4-bits */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) );   /* Set the 1st bit in the required 4-bits */
		}

		/* NMI Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_NMI)
		{
			/* The associated pin functions as a NMI and is controlled by the NMI registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
		}

		/* Analog Compare Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_ANALOG_COMP)
		{
			/* The associated pin functions as a Analog Compare and is controlled by the Analog Compare registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */

			/* In case of PF0 or PF1 , we set the 1st and 4th bit , else enable analog compare */
			if(conf[i].pinId == PORT_F_PIN_0 || conf[i].pinId == PORT_F_PIN_1)
			{
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
				SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) );   /* Set the 1st bit in the required 4-bits */
			}
			else
			{
				/* Set the pin operation as Analog */
				SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); /* Enable the Analog Functionality */
				CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num); /* Disable the Digital Functionality */
			}
		}

		/* CORE Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_CORE)
		{
			/* The associated pin functions as a CORE and is controlled by the CORE registers*/
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num);      /* Enable The ALternative Function */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +3 );/* Set the 4th bit in the required 4-bits */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +2 );/* Set the 3rd bit in the required 4-bits */
			SET_BIT(Port_Registers[port_num]->Port_PctlReg,(pin_num * 4) +1 );/* Set the 2nd bit in the required 4-bits */
		}

		/* ADC Mode */
		else if((conf[i].pinMode) == PORT_PIN_MODE_ADC)
		{
			/* Set the pin operation as Analog */
			SET_BIT(Port_Registers[port_num]->Port_AmselReg ,pin_num); /* Enable the Analog Functionality */
			CLEAR_BIT(Port_Registers[port_num]->Port_DenReg ,pin_num); /* Disable the Digital Functionality */
			CLEAR_HALF_BYTE(Port_Registers[port_num]->Port_PctlReg,pin_num);  /* Delete the preivous configurations */

		}
	}  

}
#endif

/* Decide the PORT and PIN of pin */
STATIC void Port_PrivGetPinAndPort(uint8 *pin_num, uint8 *port_num,uint8 Pin){

 /* PortA -> PortE*/
  if(Pin < 38){

    *port_num = Pin / 8;
    *pin_num = Pin - ((*port_num) * 8);
  }
  else{
    *pin_num = Pin - 38;
    *port_num = PORT_F;
  }
}
