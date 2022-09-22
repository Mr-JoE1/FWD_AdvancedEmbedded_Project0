/****************************************************************************************************//**
 * @file     timer.h
 *
 * @brief    header file for tivaC GPT module  
 *
 * @date     10/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/
#ifndef  TIMER_H
#define  TIMER_H

#ifdef __cplusplus
extern "C" {
#endif



/*****************************************
 * Includes
 ****************************************/

#include "Std_Types.h"
#include "tm4c123gh9pm_HW.h"

/*****************************************
 * Global constant Macros
 ****************************************/
 
 
 
 /*****************************************
 * Global Data Structs
 ****************************************/
 
 typedef enum Gpt_ChannelType{
 
	 GPT_TIMER0,
	 GPT_TIMER1,
	 GPT_TIMER2,
	 GPT_TIMER3,
	 GPT_TIMER4,
	 GPT_TIMER5,
	 GPT_WIDE_TIMER0,
	 GPT_WIDE_TIMER1,
	 GPT_WIDE_TIMER2,
	 GPT_WIDE_TIMER3,
	 GPT_WIDE_TIMER4,
	 GPT_WIDE_TIMER5
 } Gpt_ChannelType; 
 
 
 typedef uint32_t Gpt_ValueType; 
 
 typedef enum GPT_ModeType {
	 GPT_MODE_NORMAL,
	 GPT_MODE_SLEEP
 
 }GPT_ModeType; 
 

typedef uint32_t Gpt_ChannelCounts;
typedef uint32_t Gpt_Prescaler;


typedef void(*Gpt_Notfication)(); 

typedef enum Gpt_ChannelMode
{
	GPT_CH_MODE_CONTINUOUS,
	GPT_CH_MODE_ONESHOT
}Gpt_ChannelMode;
 


typedef struct Gpt_ConfigType{
	Gpt_ChannelType 				channel; 
	Gpt_Prescaler  					tickPrescaler;
	Gpt_ChannelMode					channelMode; 
	Gpt_Notfication					gptNotification; 

}Gpt_ConfigType; 


 /***************************************
 * Global Fucntions 
 ****************************************/
static void Gpt_ClkGating(uint32_t  gptAdrress);
void Gpt_Init(const Gpt_ConfigType* configPtr);
void Gpt_DelayMs( Gpt_ChannelType channel, Gpt_ValueType msValue );
void Gpt_Start(Gpt_ChannelType channel , Gpt_ValueType value);
void Gpt_DisableNotification(Gpt_ChannelType channel);
void Gpt_EnableNotification(Gpt_ChannelType channel);

#endif