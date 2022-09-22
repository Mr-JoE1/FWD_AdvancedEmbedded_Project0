/****************************************************************************************************//**
 * @file     dio.c
 *
 * @brief    source file for tivaC gpio peripheral driver 
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/
#include "dio.h"







/*****************************************
 * Private VARIABLES
 ****************************************/
 static const uint32_t PortBaseAddr[NUMBER_OF_GPIO_PORTS] =
				// ALL PORT ADDRESS DEFs are in uC header 
				{	PORTA,
					PORTB,
					PORTC,
					PORTD,
					PORTE,
					PORTF
				}; 
				
static const uint8_t PortPin[CHANNEL_SIZE_IN_PORT]=
				{
					0x001,
					0x002,
					0x004,
					0x008,
					0x010,
					0x020,
					0x040,
					0x080
				};				

 
// Function pointer used to store user ISR_Fun 
// crosponding to each GPIO_INT PIN 
				
void (*UserISRtable[6][8])();
				
				
				
/**********************************************************      
* \Description     : reads data reg bit for the passed pin 
*                                                                                    
* \Parameters (in) : ChannelId                   
* \Parameters (out): STD_LOW OR STD_HIGH      
* \UsageExample	   : Dio_ReadChannel(Channel_F0);
***********************************************************/

Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId ){
		
	uint32_t portIndex, pinIndex ; 
	portIndex = ChannelId / CHANNEL_SIZE_IN_PORT; 
	pinIndex  = ChannelId % CHANNEL_SIZE_IN_PORT; 
	
	if((GetReg(PortBaseAddr[portIndex], GPIO_DATA) & PortPin[pinIndex]) == 0)
		return STD_LOW; 
	else 
		
	   return STD_HIGH;

}


/**********************************************************      
* \Description     : SET channel OUTPUT HIGH OR LOW  
*                                                                                    
* \Parameters (in) : ChannelId, Level                  
* \Parameters (out): none     
* \UsageExample	   : Dio_WriteChannel(Channel_F0, STD_HIGH);
***********************************************************/
void Dio_WriteChannel ( Dio_ChannelType ChannelId, Dio_LevelType Level ){
	
	uint32_t portIndex, pinIndex ; 
	portIndex = ChannelId / CHANNEL_SIZE_IN_PORT; 
	pinIndex  = ChannelId % CHANNEL_SIZE_IN_PORT;
	
	if(Level == STD_HIGH)
		GetReg(PortBaseAddr[portIndex], GPIO_DATA)  |=(PortPin[pinIndex]);
	else 
		GetReg(PortBaseAddr[portIndex], GPIO_DATA) 	&= ~ PortPin[pinIndex];

}

/**********************************************************      
* \Description     : toggles channel output state  
*                                                                                    
* \Parameters (in) : ChannelId                  
* \Parameters (out): newLevel     
* \UsageExample	   : Dio_ToggleChannel(Channel_F0);
***********************************************************/

Dio_LevelType Dio_ToggleChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType newLevel ; 
	
	if( Dio_ReadChannel(ChannelId) == STD_LOW){
		
		Dio_WriteChannel(ChannelId,STD_HIGH); 
		newLevel = STD_HIGH; 
	
	}else if (Dio_ReadChannel(ChannelId) == STD_HIGH) {
		
		Dio_WriteChannel(ChannelId,STD_LOW); 
		newLevel = STD_LOW;
	
	}
	return newLevel; 
}

/**********************************************************      
* \Description     : reads full port data reg status   
*                                                                                    
* \Parameters (in) : PortId                  
* \Parameters (out): portlevel      
* \UsageExample	   : Dio_ReadPort(PORT_F);
***********************************************************/

Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId ){
	
	return  GetReg(PortBaseAddr[PortId], GPIO_DATA)  ; 

}

/**********************************************************      
* \Description     : wrtite  full port data reg status   
*                                                                                    
* \Parameters (in) : PortId , Level                 
* \Parameters (out): none      
* \UsageExample	   : Dio_ReadPort(PORT_F, 0b010101111);
***********************************************************/

void Dio_WritePort ( Dio_PortType PortId, Dio_PortLevelType Level ){
	
	GetReg(PortBaseAddr[PortId], GPIO_DATA) &=  Level; 

}
	



/****************************************
= To use a GPIO pin as interrupt you have to deal with many register 
= Let's list them :
	- NVIC_ENIn >> to enable gpio interrupt in nvic table 
	- GPIO_IS   >> to set pin interrupt to levels / edges 
	- GPIO_IBE  >> configures the corresponding pin to detect both rising and falling edges,
	- GPIO_IEV  >> configures the corresponding pin to detect positive edge or positive level
	- GPIO_ICR  >> to clear the interrupt flag or it will keep pending / active
	- GPIO_IM   >> to unmask interrupts
	- GPIO_MIS  >> provides the status of interrupt caused by each pin.
= Pin must be intialized as input before config it as interrupt 

= With help of Function pionter and 2D array , 
  we can asign any ISR function to any GPIO interrupt


= Usage Example:     using tivaC sw1 as an interrupt 
	GPIO_initPin(PORTF, PN0, DIGITAL, INPUT);
	GPIO_initInterrupt(PORTF,PN0,FALLING, SW1_ISR  );

******************************************/

void DIO_interruptHandler(Dio_ChannelType ChannelId, Dio_UserIntISR userISR){
	
	
	uint32_t portIndex, pinIndex ;
	
	portIndex = ChannelId / CHANNEL_SIZE_IN_PORT; 
	pinIndex  = ChannelId % CHANNEL_SIZE_IN_PORT;
	// enable the GPIO interrupt in NVIC and save user ISR_FUNC to ISRtable 
	switch(PortBaseAddr[portIndex]){
		  
		case PORTA:	GetReg(NVIC,EN0) |= (1 << 0)	; UserISRtable[0][Log(PortPin[pinIndex])] = userISR; break;
		case PORTB: GetReg(NVIC,EN0) |= (1 << 1)	; UserISRtable[1][Log(PortPin[pinIndex])] = userISR; break;
		case PORTC:	GetReg(NVIC,EN0) |= (1 << 2)	; UserISRtable[2][Log(PortPin[pinIndex])] = userISR; break;
		case PORTD:	GetReg(NVIC,EN0) |= (1 << 3)	; UserISRtable[3][Log(PortPin[pinIndex])] = userISR; break;
		case PORTE:	GetReg(NVIC,EN0) |= (1 << 4)	; UserISRtable[4][Log(PortPin[pinIndex])] = userISR; break;
		case PORTF: GetReg(NVIC,EN0) |= (1 << 30); UserISRtable[5][Log(PortPin[pinIndex])] = userISR; break;
	
	}
}

/***********************************
 = Using this function to map Port address to port index \
   in our ISR table
 = to clear interrupt flag after handling to avoid pending again 
************************************/
static void DIO_ISR_CallBack(volatile uint32_t portAddress)
	{
	uint8_t portNumber;
	switch(portAddress){
		case PORTA: portNumber = 0; break;
		case PORTB: portNumber = 1; break;
		case PORTC: portNumber = 2; break;
		case PORTD: portNumber = 3; break;
		case PORTE: portNumber = 4; break;
		case PORTF: portNumber = 5; break;
	}
	if(GetReg(portAddress,GPIO_MIS) == PortPin[0]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[0];
		UserISRtable[portNumber][0]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[1]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[1];
		UserISRtable[portNumber][1]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[2]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[2];
		UserISRtable[portNumber][2]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[3]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[3];
		UserISRtable[portNumber][3]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[4]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[4];
		UserISRtable[portNumber][4]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[5]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[5];
		UserISRtable[portNumber][5]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[6]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[6];
		UserISRtable[portNumber][6]();
	}
	else if(GetReg(portAddress,GPIO_MIS) == PortPin[7]){
		GetReg(portAddress,GPIO_ICR) |= PortPin[7];
		UserISRtable[portNumber][7]();
	}
}

/*******************************************
 = following functions map Startup code NVIC handlers name to user defined ISR 
 ******************************************/
void GPIOA_Handler(){
	DIO_ISR_CallBack(PORTA);
}

void GPIOB_Handler(){
	DIO_ISR_CallBack(PORTB);
}

void GPIOC_Handler(){
	DIO_ISR_CallBack(PORTC);
}

void GPIOD_Handler(){
	DIO_ISR_CallBack(PORTD);
}

void GPIOE_Handler(){
	DIO_ISR_CallBack(PORTE);
}

void GPIOF_Handler(){
	DIO_ISR_CallBack(PORTF);
}
//*************************************************/



