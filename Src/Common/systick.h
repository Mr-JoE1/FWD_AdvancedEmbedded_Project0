/****************************************************************************************************//**
 * @file     systick.h
 *
 * @brief    header file for cortex m4  systick timer 
 *
 * @date     04/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/


#ifndef SYSTICK_H
#define SYSTICK_H


/*****************************************
 * Includes
 ****************************************/
#include <stdint.h>>
#include "tm4c123gh9pm_HW.h"

/************************************
 * User Config global Macros 
 ************************************/
 
 // to increase sysTick overflow time over 1000ms 
 // set this macro to 1
 #define SYSTICK_CLKSRC_SLOW  0
 
 
/*****************************************
 * Global Fucntions 
 ****************************************/

static void SysTick_init(uint32_t ms);
void SysTick_Delay(uint32_t ms ); 

#endif
