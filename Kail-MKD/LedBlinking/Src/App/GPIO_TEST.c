#include "port.h"
#include "dio.h"
#include "systick.h"
 /**************************************
 * Simple Demo to test GPIO interrupt functions 
 **************************************/


extern const Port_ConfigType Port_Config[];
uint32_t onTime = 0;  


int main(){

	Port_Init(Port_Config);

	// enable GPIO_INT ON PF4 Assign ISR FOR IT 
	//DIO_interruptHandler(Channel_F4, Sw1ISR); 
	
	while(1){
		Dio_WriteChannel(Channel_F1, STD_HIGH);
		//Dio_WriteChannel(Channel_F2, STD_HIGH);
		SysTick_Delay(100);
		
		Dio_WriteChannel(Channel_F1, STD_LOW);
		SysTick_Delay(1000);		
	}
}


