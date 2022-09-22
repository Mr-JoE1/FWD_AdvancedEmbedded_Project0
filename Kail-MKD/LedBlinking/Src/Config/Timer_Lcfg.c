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

#include "Timer_Cfg.h"
#include "timer.h"
#include "dio.h"


void Timer0_Notfication() ; 

/*
 * Consider that System Tick Time = 62.5nS 
 * So timer with 500 ms int time means:
 * 				counts = (500/62.5)*10^6 with no prescaler
 */


const Gpt_ConfigType Gpt_Config[GPT_ACTIVATED_CHANNELS_SIZE]=
{
	/* Channel     		Prescaler    channelMode    		 gptNotification*/			
	{  GPT_TIMER0     	,250    	,GPT_CH_MODE_CONTINUOUS  ,NULL_PTR }	
};


void Timer0_Notfication(){
    Dio_ToggleChannel(Channel_F1);  
}

