/****************************************************************************************************//**
 * @file     Port_Lcfg.c
 *
 * @brief    Source file for user configurtion for Linking Time 
 *
 * @date     06/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/

#include "Port_Cfg.h"
#include "port.h"


//TivaC on board leds and switches

// ALL ON PORTF
#define RED_LED 	PIN1
#define BLUE_LED 	PIN2
#define GREEN_LED 	PIN3

#define SW1		 	PIN4
#define SW2 		PIN0


const Port_ConfigType Port_Config[PORT_ACTIVATED_CHANNELS_SIZE]=
{
	/* portId     pinId   	 pinMode     pinDir    pinInternalCfg   PinCurrent		pinInterrupt*/			
	{  PORTF     ,RED_LED 	 ,DIGITAL    ,OUTPUT   ,CFG_DEFAULT     ,CURRENT_8m		,INT_DISABLE}
	
};