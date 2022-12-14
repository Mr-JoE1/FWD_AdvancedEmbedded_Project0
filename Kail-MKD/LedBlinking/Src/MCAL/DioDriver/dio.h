/****************************************************************************************************//**
 * @file     dio.h
 *
 * @brief    header file for tivaC gpio peripheral driver 
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/


#ifndef DIO_H
#define DIO_H


/*****************************************
 * Includes
 ****************************************/

#include "Std_Types.h"
#include "tm4c123gh9pm_HW.h"


/*****************************************
 * GLOBAL CONSTANT MACROS
 ****************************************/

#define CHANNEL_SIZE_IN_PORT                8u
#define NUMBER_OF_GPIO_PORTS				6u

/**********************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************/
 
typedef uint8_t Dio_ChannelType; 
#define Channel_A0			0
#define Channel_A1			1
#define Channel_A2			2
#define Channel_A3			3
#define Channel_A4			4
#define Channel_A5			5
#define Channel_A6			6
#define Channel_A7			7

#define Channel_B0			8
#define Channel_B1			9
#define Channel_B2			10
#define Channel_B3			11
#define Channel_B4			12
#define Channel_B5			13
#define Channel_B6			14
#define Channel_B7			15

#define Channel_C0			16
#define Channel_C1			17
#define Channel_C2			18
#define Channel_C3			19
#define Channel_C4			20
#define Channel_C5			21
#define Channel_C6			22
#define Channel_C7			23

#define Channel_D0			24
#define Channel_D1			25
#define Channel_D2			26
#define Channel_D3			27
#define Channel_D4			28
#define Channel_D5			29
#define Channel_D6			30
#define Channel_D7			31
				
#define Channel_E0			32
#define Channel_E1			33
#define Channel_E2			34
#define Channel_E3			35
#define Channel_E4			36
#define Channel_E5			37
#define Channel_E6			38
#define Channel_E7			39

#define Channel_F0			40
#define Channel_F1			41
#define Channel_F2			42
#define Channel_F3			43
#define Channel_F4			44
#define Channel_F5			45
#define Channel_F6			46
#define Channel_F7			47


typedef enum Dio_PortType{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F
}Dio_PortType;


typedef enum Dio_LevelType{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;

 
typedef uint8_t Dio_PortLevelType;
typedef uint32_t Dio_ChannelGroupMskType;
typedef uint8_t  Dio_ChannelGroupOffsetType;

// Typefef for Function Pointer to user Definned ISR for GPIO interrupts

typedef void (*Dio_UserIntISR)();  


typedef struct{
	Dio_ChannelGroupMskType		   	 channelGroupMsk;	
	Dio_ChannelGroupOffsetType	  channelGroupOffset;	
	Dio_PortType			    				port;	
}Dio_ChannelGroupType;
 
 
 
/*****************************************
 * Global Fucntions 
 ****************************************/
 Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId );
 void Dio_WriteChannel ( Dio_ChannelType ChannelId, Dio_LevelType Level );
 Dio_LevelType Dio_ToggleChannel(Dio_ChannelType ChannelId);
 Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId );
 void Dio_WritePort ( Dio_PortType PortId, Dio_PortLevelType Level );
 void DIO_interruptHandler(Dio_ChannelType ChannelId, Dio_UserIntISR userISR);
 static void DIO_ISR_CallBack(volatile uint32_t portAddress); 

#endif
