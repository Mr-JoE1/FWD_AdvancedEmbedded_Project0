#include "port.h"
#include "dio.h"
#include "timer.h"
#include "Timer_Cfg.h"
 /**************************************
 * Simple Demo to test Gpt timer0 to blink a led  
 **************************************/

static uint32_t onT =100, offT = 200 ; 
extern const Port_ConfigType Port_Config[];
extern const Gpt_ConfigType Gpt_Config[]; 


void pmwBlink( uint32_t onTime, uint32_t offTime); 


int main(){

	Port_Init(Port_Config);
	Gpt_Init(Gpt_Config); 

	while(1){
		onT  *=2 ; 
		offT *=2; 
	
	 pmwBlink(onT, offT) ; 


	}

}

void pmwBlink( uint32_t onTime, uint32_t offTime){
	Dio_WriteChannel(Channel_F1, STD_HIGH);
	Gpt_DelayMs( GPT_TIMER0, onTime ) ;
	Dio_WriteChannel(Channel_F1, STD_LOW);
	Gpt_DelayMs( GPT_TIMER0, offTime ) ; 
}
