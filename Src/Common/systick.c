/****************************************************************************************************//**
 * @file     systick.c
 *
 * @brief    source file for tivaC Systick Timer  
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/

#include "systick.h"

static void SysTick_init(uint32_t ms){
	/* assuming sysTick clock is internal 16MHZ 
	 * Priodic tick time = 62.5ns 
	 * counts = delsy[ms]/62.5[ns]
	 */
	uint32_t counts =0; 
	 /* (1) disable SysTick during setup */
    NVIC_ST_CTRL_R = 0;            

	/* check user config for timer CLKSRC*/
	if(SYSTICK_CLKSRC_SLOW ==0){
		// 16MHZ internal system clk selected 
		// MAX Delay time is 1050ms 
		counts = ms / (62.5/1000000);
		NVIC_ST_RELOAD_R = counts -1;   /* (2) number of counts to wait */
		NVIC_ST_CURRENT_R = 0;          /* (3) any value written to CURRENT clears */
		NVIC_ST_CTRL_R |= 0x5;          /* (4) enable SysTick with core clock */
		
	} 
	else{
		//  internal system / 4 clk selected -- 4MHZ 
		// MAX Delay time is 1050ms 
		counts = ms / (0.25/1000);
		NVIC_ST_RELOAD_R = counts -1;   
		NVIC_ST_CURRENT_R = 0;          
		NVIC_ST_CTRL_R |= 1; 	
	
	
	
	}
	


}

void SysTick_Delay(uint32_t ms ){
	
		SysTick_init(ms); 
	
	    while((NVIC_ST_CTRL_R&0x00010000)==0) {

        ;                          /* wait for COUNT flag */

		}
		NVIC_ST_CTRL_R = 0;             /* Disabling SysTick Timer */
}