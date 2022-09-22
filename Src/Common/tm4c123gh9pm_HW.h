
/****************************************************************************************************//**
 * @file     tm4c123gh9pm_HW.h
 *
 * @brief    TM4C123GH6PM Device header with memory mapping for MCU peripherals
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/

#ifndef  TM4C123GH6PM_HW_H
#define  TM4C123GH6PM_HW_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************
 * Includes
 ****************************************/

#include <stdint.h>
#include <math.h>

/******************************************************************
*   GPT Registers
 ******************************************************************/
typedef enum GPTRegOffset{
	GPT_CFG							=0x000,
	GPT_TAMR						=0x004,
	GPT_TBMR                        =0x008,
	GPT_CTL                         =0x00C,
	GPT_IMR                         =0x018,
	GPT_RIS                         =0x01C,
	GPT_ICR                         =0x024, 
	GPT_TAILR                       =0x028,
	GPT_TAPR						=0x038,
	GPT_TAV                         =0x050
										  
} GPTRegOffset;       


// GPT Module Base Addresses 
#define TIMER0                      0x40030000
#define TIMER1                      0x40031000
#define TIMER2                      0x40032000
#define TIMER3                      0x40033000
#define TIMER4                      0x40034000
#define TIMER5                      0x40035000

#define WTIMER0                     0x40036000
#define WTIMER1                     0x40037000
#define WTIMER2                     0x4004C000
#define WTIMER3                     0x4004D000
#define WTIMER4                     0x4004E000
#define WTIMER5                     0x4004F000
/******************************************************************
 *  SysTick Timer  Registers
 ******************************************************************/
#define NVIC_ST_CTRL_R       		*((volatile uint32_t*)0xE000E010)
#define NVIC_ST_RELOAD_R      		*((volatile uint32_t*)0xE000E014)
#define NVIC_ST_CURRENT_R       	*((volatile uint32_t*)0xE000E018)
	 

/******************************************************************
 *  SysTick Timer  Registers
 ******************************************************************/
 #define NVIC 					     0xE000E000
typedef enum NVICRegOffset{
	
	EN0						=0x100, 
	EN1						=0x104,
	EN2						=0x108,
	EN3						=0x10C,
	EN4						=0x110

}NVICRegOffset;


/******************************************************************
 *  GPIO Periphelar Registers enum and Defenations 
 ******************************************************************/
 
// enum for all GPIO registers , Datasheet page 660
//-- some regs are ignored 
typedef enum GPIORegOffset{
	
	//data sheet says Data register offset starts from 0x00 
	// although it does not work !!
	// but when making offset for last address before offset 0x400 it works 
	// don't know why for now -- But it works !
	GPIO_DATA						= 0x3FC,        
	GPIO_DIR 						= 0x400,     
	GPIO_IS 						= 0x404,
	GPIO_IBE 						= 0x408,
	GPIO_IEV 						= 0x40C,
	GPIO_IM 						= 0x410,
	GPIO_RIS						= 0x414,
	GPIO_MIS						= 0x418,
	GPIO_ICR						= 0x41C,
	GPIO_AFSEL						= 0x420,
	GPIO_DRV2M						= 0x500,
	GPIO_DRV4M						= 0x504,
	GPIO_DRV8M						= 0x508,
	GPIO_ODR						= 0x50C,
	GPIO_PUR						= 0x510,
	GPIO_PDR						= 0x514,
	GPIO_SLR 						= 0x518,
	GPIO_DEN						= 0x51C,
	GPIO_LCK						= 0x520,
	GPIO_CR							= 0x524,
	GPIO_AMSEL						= 0x528,
	GPIO_PCTL						= 0x52C
} GPIORegOffset;

// GPIO Module base addresses
#define PORTA 					    0x40004000
#define PORTA_AHB 				    0x40058000
#define PORTB 					    0x40005000
#define PORTB_AHB 				    0x40059000
#define PORTC 					    0x40006000
#define PORTC_AHB 				    0x4005A000
#define PORTD 					    0x40007000
#define PORTD_AHB 				    0x4005B000
#define PORTE 					    0x40024000
#define PORTE_AHB 				    0x4005C000
#define PORTF 					    0x40025000
#define PORTF_AHB 				    0x4005D000



#define NVIC_EN0            	((volatile uint32_t*)0xE000E100)	


/******************************************************************
 *  SYSTEM CONTROL  
 ******************************************************************/
 #define SYSCTL 					0x400FE000

typedef enum SysCtlRegOffset{

	//All clock Gating Offset
	RCGC_WD							=0x600,  //watchdog timer
	RCGC_TIMER						=0x604,	 //16-32 GPT TIMER
	RCGC_GPIO						=0x608,
	RCGC_DMA						=0x60C,
	RCGC_ADC						=0x638,
	RCGC_PWM						=0x640,
	RCGC_WTIMER						=0x65C,
	
	
	//ALL CLOCKGATING READY 
	PR_WD							=0xA00,
	PR_TIMER						=0xA04,
	PR_GPIO							=0xA08,
	PR_DMA							=0x60C,
	PR_ADC							=0xA38,
	PR_PWM                          =0xA40,
	PR_WTIMER						=0xA5C

}SysCtlRegOffset;


/******************************************************************
 *  MCU Periphelar memory Mapping -- Base Addresses
 ******************************************************************/

#define WATCHDOG0                   0x40000000UL
#define WATCHDOG1                   0x40001000UL



#define SSI0                        0x40008000UL
#define SSI1                        0x40009000UL
#define SSI2                        0x4000A000UL
#define SSI3                        0x4000B000UL

#define UART0                       0x4000C000UL
#define UART1                       0x4000D000UL
#define UART2                       0x4000E000UL
#define UART3                       0x4000F000UL
#define UART4                       0x40010000UL
#define UART5                       0x40011000UL
#define UART6                       0x40012000UL
#define UART7                       0x40013000UL

#define I2C0                        0x40020000UL
#define I2C1                        0x40021000UL
#define I2C2                        0x40022000UL
#define I2C3                        0x40023000UL

#define PWM0                        0x40028000UL
#define PWM1                        0x40029000UL

#define QEI0                        0x4002C000UL
#define QEI1                        0x4002D000UL





#define ADC0                        0x40038000UL
#define ADC1                        0x40039000UL
#define COMP                        0x4003C000UL
#define CAN0                        0x40040000UL
#define CAN1                        0x40041000UL



#define USB0                        0x40050000UL

#define EEPROM                      0x400AF000UL
#define SYSEXC                      0x400F9000UL
#define HIB                         0x400FC000UL
#define FLASH_CTRL                  0x400FD000UL
#define SYSCTL                      0x400FE000UL
#define UDMA                        0x400FF000UL


#ifdef __cplusplus
}
#endif
 
#endif  /*  TM4C123GH6PM_HW_H*/
