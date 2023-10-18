 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver Registers
 *
 * Author: Mohamed Ezzat
 *
 * Date : 28/9/2023
 ******************************************************************************/

#ifndef PORT_REGS_H
#define PORT_REGS_H

#include "Std_Types.h"

#define PORT_PORTA_BASE_ADDRESS ((Port_RegistersType*)0x400043FC)
#define PORT_PORTB_BASE_ADDRESS ((Port_RegistersType*)0x400053FC)
#define PORT_PORTC_BASE_ADDRESS ((Port_RegistersType*)0x400063FC)
#define PORT_PORTD_BASE_ADDRESS ((Port_RegistersType*)0x400073FC)
#define PORT_PORTE_BASE_ADDRESS ((Port_RegistersType*)0x400243FC)
#define PORT_PORTF_BASE_ADDRESS ((Port_RegistersType*)0x400253FC)

typedef struct{
  uint32 Port_DataReg;
  uint32 Port_DirReg[8];
  uint32 Port_AfselReg[60];
  uint32 Port_PurReg;
  uint32 Port_PdrReg[2];
  uint32 Port_DenReg;
  uint32 Port_LockReg;
  uint32 Port_CommitReg;
  uint32 Port_AmselReg;
  uint32 Port_PctlReg;
}Port_RegistersType;

Port_RegistersType *Port_Registers[]={
  PORT_PORTA_BASE_ADDRESS,
  PORT_PORTB_BASE_ADDRESS,
  PORT_PORTC_BASE_ADDRESS,
  PORT_PORTD_BASE_ADDRESS,
  PORT_PORTE_BASE_ADDRESS,
  PORT_PORTF_BASE_ADDRESS
};


#define SYSCTL_REGCGC2_REG        (*((volatile uint32 *)0x400FE108))

#endif /* PORT_REGS_H */
