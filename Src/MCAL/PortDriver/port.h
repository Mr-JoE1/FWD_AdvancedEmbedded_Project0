/****************************************************************************************************//**
 * @file     port.h
 *
 * @brief    header file for tivaC gpio peripheral driver 
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/


#ifndef PORT_H
#define PORT_H


/*****************************************
 * Includes
 ****************************************/

#include "Std_Types.h"
#include "tm4c123gh9pm_HW.h"

/*****************************************
 * Global constant Macros
 ****************************************/


// value to unlock writing to GPIO_CR register 
// UNLOCK_KEY must be writen to GPIO_LCK reg before commmiting 
#define UNLOCK_KEY				0x4C4F434B
#define HIGH					0xFF
#define LOW						0x00
#define I2C_F					0x03
#define UART_F					0x02

/*****************************************
 * Global Function Macros
 ****************************************/


/*****************************************
 * Global Data Structs
 ****************************************/
typedef volatile uint32_t Port_IdType; 

//TM4C123 GPIO port has 8 pins at most

typedef enum Port_PinType{
	PIN0				= 0x001,
	PIN1				= 0x002,
	PIN2				= 0x004,
	PIN3				= 0x008,
	PIN4				= 0x010,
	PIN5				= 0x020,
	PIN6				= 0x040,
	PIN7				= 0x080,
} Port_PinType;

//port pin mode enum 
typedef enum Port_PinModeType{
	DIGITAL,
	ANALOG ,
} Port_PinModeType;


// port pin direction enum 
typedef enum Port_PinDirType{
	INPUT		 		= 0x00,
	OUTPUT		 		= 0xFF,
	PERIPHERAL,
} Port_PinDirType;

// enum for internal port pin config modes 
typedef enum Port_PinInternalCFGType{
	CFG_DEFAULT,
	CFG_PULLUP,
	CFG_PULLDOWN,
	CFG_OPENDRAIN
} Port_PinInternalCFGType; 


typedef enum PORT_PinCurrentType{
	CURRENT_NA,
	CURRENT_2m,
	CURRENT_4m,
	CURRENT_8m

}  PORT_PinCurrentType;

typedef enum Port_PinInterruptType{
	INT_DISABLE,
	INT_RISING,
	INT_FALLING,
	INT_BOTH,
} Port_PinInterruptType;



typedef struct {
	Port_IdType 				portId; 
	Port_PinType				pinId; 
	Port_PinModeType 			pinMode; 
	Port_PinDirType				pinDir; 
	Port_PinInternalCFGType 	pinInternalCfg; 
	PORT_PinCurrentType			pinCurrent; 
	Port_PinInterruptType		pinInterrupt; 

} Port_ConfigType;


/*****************************************
 * Global Fucntions 
 ****************************************/
static void Port_ClkGating(Port_IdType  portAddress);

void  Port_Init(const Port_ConfigType* ConfigPtr );

#endif