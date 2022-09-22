/****************************************************************************************************//**
 * @file     timer.c
 *
 * @brief    source file for tivaC GPT module  
 *
 * @date     10/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/

/*****************************************
 * Includes
 ****************************************/

#include "timer.h"
#include "Timer_Cfg.h"




//Array of function pointers used to store user ISR for GPT
void (*Gpt_NotficationTable[12])(); 

static const Gpt_ConfigType*			globalGptConfig;

static const uint32_t Gpt_BaseAddress[MAX_NUMBER_OF_GPT] = 
		{
			TIMER0,
			TIMER1,
			TIMER2,
			TIMER3,
			TIMER4,
			TIMER5,
			WTIMER0,
			WTIMER1,
			WTIMER2,
			WTIMER3,
			WTIMER4,	
			WTIMER5 
		};


/**********************************************************      
 * \Description     : Enables clock gating for timer
 *                                                                                    
 * \Parameters (in) : base address for GPT_TIMER                
 * \Parameters (out): None 
 * \Scope 		   : Private 
 ***********************************************************/
static void Gpt_ClkGating(uint32_t  gptAdrress){
	/*
	 * Timers sysControl Registers 
	 * RCGCTIMER  >> PAGE 338
	 * PRTIMER 	  >> PAGE 404
	 * RCGCWTIMER >> PAGE 357
	 * PRWTIMER   >> PAGE 423
	 */
	
	switch(gptAdrress){
		case TIMER0:			
			GetReg(SYSCTL, RCGC_TIMER) |= 0x01; 
		//	while(!(GetReg(SYSCTL, PR_TIMER) & 0x01));
			break;
		
		case TIMER1:
			GetReg(SYSCTL, RCGC_TIMER) |= 0x02;
			while(!(GetReg(SYSCTL, PR_TIMER) & 0x02));
			break;
		
		case TIMER2:
			GetReg(SYSCTL, RCGC_TIMER) |= 0x04;
			while(!(GetReg(SYSCTL, PR_TIMER) & 0x04));
			break;
		
		case TIMER3:
			GetReg(SYSCTL, RCGC_TIMER) |= 0x08;
			while(!(GetReg(SYSCTL, PR_TIMER) & 0x08));
			break;
		
		case TIMER4:
			GetReg(SYSCTL, RCGC_TIMER)|= 0x10;
			while(!(GetReg(SYSCTL, PR_TIMER) & 0x10));
			break;
		
		case TIMER5:
			GetReg(SYSCTL, RCGC_TIMER) |= 0x20;
			while(!(GetReg(SYSCTL, PR_TIMER) & 0x20));
			break;
		
		case WTIMER0:			
			GetReg(SYSCTL, RCGC_WTIMER) |= 0x01; 
			//while(!(GetReg(SYSCTL, PR_WTIMER) & 0x01));
			break;
		
		case WTIMER1:
			GetReg(SYSCTL, RCGC_WTIMER) |= 0x02;
			while(!(GetReg(SYSCTL, PR_WTIMER) & 0x02));
			break;
		
		case WTIMER2:
			GetReg(SYSCTL, RCGC_WTIMER) |= 0x04;
			while(!(GetReg(SYSCTL, PR_WTIMER) & 0x04));
			break;
		
		case WTIMER3:
			GetReg(SYSCTL, RCGC_WTIMER) |= 0x08;
			while(!(GetReg(SYSCTL, PR_WTIMER) & 0x08));
			break;
		
		case WTIMER4:
			GetReg(SYSCTL, RCGC_WTIMER)|= 0x10;
			while(!(GetReg(SYSCTL, PR_WTIMER) & 0x10));
			break;
		
		case WTIMER5:
			GetReg(SYSCTL, RCGC_WTIMER) |= 0x20;
			while(!(GetReg(SYSCTL, PR_WTIMER) & 0x20));
			break;
	}
}





void Gpt_Init(const Gpt_ConfigType* configPtr){
	
	Gpt_ChannelType 				locChannel; 
	Gpt_Prescaler  					locTickPrescaler;
	Gpt_ChannelMode					locChannelMode; 
	Gpt_Notfication					locGptNotification; 
	
	globalGptConfig 		=configPtr;  
	for (uint8_t i=0; i<GPT_ACTIVATED_CHANNELS_SIZE; i++){
		
		locChannel  		= configPtr[i].channel; 
		locTickPrescaler	= configPtr[i].tickPrescaler;
		locChannelMode  	= configPtr[i].channelMode;
		locGptNotification  = configPtr[i].gptNotification;
		
		// Clock Gating 
		Gpt_ClkGating(Gpt_BaseAddress[locChannel]); 
		
		// diable timer before setting 
		GetReg(Gpt_BaseAddress[locChannel],GPT_CTL ) = 0x00;
		// config timer bit width 
		GetReg(Gpt_BaseAddress[locChannel],GPT_CFG ) = 0x04;

		
		// config timer mode 
		if( locChannelMode == GPT_CH_MODE_CONTINUOUS)
			GetReg(Gpt_BaseAddress[locChannel],GPT_TAMR ) |=0x2;
		else
			GetReg(Gpt_BaseAddress[locChannel],GPT_TAMR ) |=0x1;
		
		// config prescaler 
		GetReg(Gpt_BaseAddress[locChannel],GPT_TAILR ) = 0;
		if(locTickPrescaler !=0) {
			GetReg(Gpt_BaseAddress[locChannel],GPT_TAPR ) = locTickPrescaler - 1; 
		
		}

		// mask timer timeout interrupt
		Gpt_DisableNotification(locChannel) ;
		
		if (locGptNotification != NULL_PTR){
			switch(Gpt_BaseAddress[locChannel]){
				case TIMER0:			
					GetReg(NVIC,EN0) |= (1 << 19); 
					Gpt_NotficationTable[0] = locGptNotification;
					break;
				
				case TIMER1:
					GetReg(NVIC,EN0) |= (1 << 21);
					Gpt_NotficationTable[1] = locGptNotification;
					break;
				
				case TIMER2:
					GetReg(NVIC,EN0) |= (1 << 23);
					Gpt_NotficationTable[2] = locGptNotification;
					break;
				
				case TIMER3:
					GetReg(NVIC,EN1) |= (1 << 4);
					Gpt_NotficationTable[3] = locGptNotification;
					break;
				
				case TIMER4:
					GetReg(NVIC,EN2) |= (1 << 6);
					Gpt_NotficationTable[4] = locGptNotification;
					break;
				
				case TIMER5:
					GetReg(NVIC,EN2) |= (1 << 28);
					Gpt_NotficationTable[5] = locGptNotification;
					break;
				
				case WTIMER0:			
					GetReg(NVIC,EN2) |= (1 << 30);
					Gpt_NotficationTable[6] = locGptNotification;
					break;
				
				case WTIMER1:
					GetReg(NVIC,EN3) |= (1 << 0);
					Gpt_NotficationTable[7] = locGptNotification;
					break;
				
				case WTIMER2:
					GetReg(NVIC,EN3) |= (1 << 2);
					Gpt_NotficationTable[8] = locGptNotification;
					break;
				
				case WTIMER3:
					GetReg(NVIC,EN3) |= (1 << 4);
					Gpt_NotficationTable[9] = locGptNotification;
					break;
				
				case WTIMER4:
					GetReg(NVIC,EN3) |= (1 << 6);
					Gpt_NotficationTable[10] = locGptNotification;
					break;
				
				case WTIMER5:
					GetReg(NVIC,EN3) |= (1 << 8);
					Gpt_NotficationTable[11] = locGptNotification;
					break;
				}
				
		
		
		}
		
				
	}
	


}


void Gpt_DelayMs( Gpt_ChannelType channel, Gpt_ValueType msValue ) {
		GetReg(Gpt_BaseAddress[channel],GPT_TAPR ) = 0; 
		// load timer with counts for 1 ms overflow 
		GetReg(Gpt_BaseAddress[channel],GPT_TAILR ) = 16000-1;
			// clear timer timeout flag 
		GetReg(Gpt_BaseAddress[channel],GPT_ICR ) = 0x01; 
		// enable timer for counting 
		GetReg(Gpt_BaseAddress[channel],GPT_CTL ) = 0x01;
	for ( int i =0; i<msValue; i++){
	
		while ( (GetReg(Gpt_BaseAddress[channel],GPT_RIS ) & 0x1) == 0x00 ) 
			; /* wait for TimerA timeout flag */
	
		 GetReg(Gpt_BaseAddress[channel],GPT_ICR ) = 0x01; 
	} 
	
}

void Gpt_Start(Gpt_ChannelType channel, Gpt_ValueType msValue){
	
	Gpt_Prescaler channelPrescaler = 0 ; 
	Gpt_ValueType counts = 0 ;
	double tickTime =62.5/1000; 
	
	for ( uint8_t i = 0 ; i<GPT_ACTIVATED_CHANNELS_SIZE ; i++ ){
	
		if (globalGptConfig[i].channel == channel){
			
			channelPrescaler = globalGptConfig[i].tickPrescaler; 
			break; 	
		}
	}
	  
	if(channelPrescaler !=0)
		 counts = msValue / ((62.5* channelPrescaler)/1000000); 
	else
		 counts = msValue / (62.5/1000000);
	
	 // config timer counts 
	GetReg(Gpt_BaseAddress[channel],GPT_TAILR ) = (counts -1);

	// clear timer timeout flag 
	GetReg(Gpt_BaseAddress[channel],GPT_ICR ) = 0x01; 
	// enable timer for counting 
	GetReg(Gpt_BaseAddress[channel],GPT_CTL ) = 0x01;
	
	// enable timer interupt
	Gpt_EnableNotification( channel);  


}


void Gpt_Stop(Gpt_ChannelType channel) {
	
	GetReg(Gpt_BaseAddress[channel],GPT_CTL ) = 0x00;
	Gpt_DisableNotification(channel) ;


}

void Gpt_DisableNotification( Gpt_ChannelType channel  ){

		 GetReg(Gpt_BaseAddress[channel],GPT_IMR ) = 0; 

}


void Gpt_EnableNotification( Gpt_ChannelType channel   )  {

	GetReg(Gpt_BaseAddress[channel],GPT_IMR ) = 0x01; 
}


// GPT interrupt handlers 

void TIMER0A_Handler(){ Gpt_NotficationTable[0]();}
void TIMER1A_Handler(){ Gpt_NotficationTable[1]();}
void TIMER2A_Handler(){ Gpt_NotficationTable[2]();}
void TIMER3A_Handler(){ Gpt_NotficationTable[3]();}
void TIMER4A_Handler(){ Gpt_NotficationTable[4]();}
void TIMER5A_Handler(){ Gpt_NotficationTable[5]();}
	
void WTIMER0A_Handler(){ Gpt_NotficationTable[6]();}
void WTIMER1A_Handler(){ Gpt_NotficationTable[7]();}
void WTIMER2A_Handler(){ Gpt_NotficationTable[8]();}
void WTIMER3A_Handler(){ Gpt_NotficationTable[9]();}
void WTIMER4A_Handler(){ Gpt_NotficationTable[10]();}
void WTIMER5A_Handler(){ Gpt_NotficationTable[11]();}	