#include "port.h"
#include "dio.h"
#include "timer.h"

 /**************************************
 * Simple Demo to test Gpt timer0 to blink a led  
 **************************************/


extern const Port_ConfigType Port_Config[];
extern const Gpt_ConfigType Gpt_Config[]; 



int main(){

	Port_Init(Port_Config);
	Gpt_Init(Gpt_Config); 
	Dio_WriteChannel(Channel_F1, STD_LOW);
	Gpt_Start(GPT_TIMER0, 500) ;

	while(1);


}