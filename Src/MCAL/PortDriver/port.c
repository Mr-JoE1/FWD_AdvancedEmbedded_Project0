/****************************************************************************************************//**
 * @file     port.c
 *
 * @brief    source file for tivaC gpio peripheral driver 
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/



#include "port.h"
#include "Port_Cfg.h"




/**********************************************************      
* \Description     : Enables clock gating for passed GPIO
*                                                                                    
* \Parameters (in) : base address for GPIO PORT                     
* \Parameters (out): None 
* \Scope 		   : Private 
***********************************************************/
static void Port_ClkGating(Port_IdType  portAddress){
	
	switch(portAddress){
		case PORTA_AHB:
		case PORTA:
			// page:340 -- same as RCGC2 !!!
			GetReg(SYSCTL, RCGC_GPIO) |= 0x01;
		    // page:406 CHECKING THAT GPIO CLOCK IS ENABLED  
			while(!(GetReg(SYSCTL, PR_GPIO) & 0x01));
			break;
		
		case PORTB_AHB:
		case PORTB:
			GetReg(SYSCTL, RCGC_GPIO) |= 0x02;
			while(!(GetReg(SYSCTL, PR_GPIO) & 0x02));
			break;
		
		case PORTC_AHB:
		case PORTC:
			GetReg(SYSCTL, RCGC_GPIO) |= 0x04;
			while(!(GetReg(SYSCTL, PR_GPIO) & 0x04));
			break;
		
		case PORTD_AHB:
		case PORTD:
			GetReg(SYSCTL, RCGC_GPIO) |= 0x08;
			while(!(GetReg(SYSCTL, PR_GPIO) & 0x08));
			break;
		
		case PORTE_AHB:
		case PORTE:
			GetReg(SYSCTL, RCGC_GPIO)|= 0x10;
			while(!(GetReg(SYSCTL, PR_GPIO) & 0x10));
			break;
		
		case PORTF_AHB:
		case PORTF:
			GetReg(SYSCTL, RCGC_GPIO) |= 0x20;
			while(!(GetReg(SYSCTL, PR_GPIO) & 0x20));
			break;
	}
}

/**********************************************************      
* \Description     : initialize gpio pin mode and direction
*                                                                                    
* \Parameters (in) :const Port_ConfigType* ConfigPtr                     
* \Parameters (out): None      
* \Scope 		   : Public  
***********************************************************/

void Port_Init(const Port_ConfigType* ConfigPtr ){
	
	Port_IdType 				locPortId; 
	Port_PinType				locPinId; 
	Port_PinModeType 			locPinMode; 
	Port_PinDirType				locPinDir; 
	Port_PinInternalCFGType 	locPinInternalCfg; 
	PORT_PinCurrentType			locPinCurrent; 
	Port_PinInterruptType		locPinInterrupt; 
	
	
	
	for(uint8_t i =0 ; i < PORT_ACTIVATED_CHANNELS_SIZE ; i++ )
	{
		locPortId 			= ConfigPtr[i].portId; 
		locPinId  			= ConfigPtr[i].pinId; 
		locPinMode			= ConfigPtr[i].pinMode;
		locPinDir			= ConfigPtr[i].pinDir;
		locPinInternalCfg	= ConfigPtr[i].pinInternalCfg;
		locPinCurrent		= ConfigPtr[i].pinCurrent; 
		locPinInterrupt		= ConfigPtr[i].pinInterrupt;
		
		
		// 1- enable clock gating for the activated port 
		Port_ClkGating(locPortId);
	
		//2- Activate  GPIO Commit REG
		GetReg(locPortId, GPIO_LCK)	  = UNLOCK_KEY;
		GetReg(locPortId, GPIO_CR)   |= locPinId;
	
		//3- Config PinMode
		if(locPinMode == DIGITAL){
			GetReg(locPortId, GPIO_DEN) 	|= locPinId;
			GetReg(locPortId, GPIO_AMSEL)	&= ~(locPinId);
		}else{
			// config it as analog 
			GetReg(locPortId, GPIO_DEN) 	&= ~(locPinId);
			GetReg(locPortId, GPIO_AMSEL)	|= locPinId;
		}
		
		// 4 -Config Pin Direction 
		if(locPinDir == OUTPUT){
			GetReg(locPortId, GPIO_DIR)	 	|= locPinId;
			GetReg(locPortId, GPIO_AFSEL) 	&= ~(locPinId);
			
		}else if(locPinDir == INPUT){
			GetReg(locPortId, GPIO_DIR) 	&= ~(locPinId);
			GetReg(locPortId, GPIO_AFSEL)	&= ~(locPinId);
			
		}else if(locPinDir == PERIPHERAL){
			GetReg(locPortId, GPIO_AFSEL) 	|= (locPinId);
		}
		
		// 5 - Config PIN Internal 
		if( locPinInternalCfg == CFG_PULLUP  ){
			GetReg(locPortId, GPIO_PUR) |= locPinId;

		}else if(locPinInternalCfg == CFG_PULLDOWN){
			GetReg(locPortId, GPIO_PDR) |= locPinId;
		
		}else if(locPinInternalCfg == CFG_OPENDRAIN){
			GetReg(locPortId, GPIO_ODR) |= locPinId;
		
		} 
		
		// 6- Config Pin outpur current
		if( locPinCurrent == CURRENT_2m  ){
			
			GetReg(locPortId, GPIO_DRV2M) |= locPinId;
		}else if( locPinCurrent == CURRENT_4m  ){
			
			GetReg(locPortId, GPIO_DRV4M) |= locPinId;
		}else if( locPinCurrent == CURRENT_8m  ){
			
			GetReg(locPortId, GPIO_DRV8M) |= locPinId;
		}
		
		//7- Config pin Interrupt
		
		if( locPinInterrupt == INT_DISABLE){   
			  // Mask gpio pin EXT_INT and get out of here 
			  GetReg(locPortId, GPIO_IM)   &= ~(locPinId); 
		}
		else{
			
			// FOR ALL interrput events , set detect mode to Edges not levels 
			 GetReg(locPortId, GPIO_IS) &= ~(locPinId);
			
			if( locPinInterrupt == INT_RISING){
				GetReg(locPortId, GPIO_IBE) &= ~(locPinId);
				GetReg(locPortId, GPIO_IEV) |= (locPinId);
				
				
			}else if (locPinInterrupt == INT_FALLING) {
				GetReg(locPortId, GPIO_IBE) &= ~(locPinId);
				GetReg(locPortId, GPIO_IEV) &= ~(locPinId);
				
			
			}else if (locPinInterrupt == INT_BOTH) {
				GetReg(locPortId, GPIO_IBE) |= (locPinId);
			
			}
			// Clear the interrupt flag 
			GetReg(locPortId, GPIO_ICR) |= (locPinId);
			// unmask gpio interrupt bit 
			GetReg(locPortId, GPIO_IM)  |= (locPinId);

	
		}
		
	} // end of for loop
	

} /***************** END OF Port_init Func *********/




