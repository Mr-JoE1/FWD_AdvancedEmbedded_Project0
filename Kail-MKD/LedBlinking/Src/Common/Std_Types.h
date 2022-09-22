/****************************************************************************************************//**
 * @file     Std_Types.h 
 *
 * @brief    Header file for common used macros and def data types  
 *
 * @date     06/09/2022
 *
 * @author   Mohamed Maher
 *      
 *
 *******************************************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

#define NULL_PTR         ((void *)0)
#define NULL					  0

/*****************************************
 * Includes
 ****************************************/

#include <stdint.h>
#include <math.h>

/*****************************************
 * Global Function Macros
 ****************************************/

// Macro Function to easly get desired address
// X: Base address, Y: reg offset enum
#define GetReg(X,Y)				(*((volatile uint32_t*)(((uint32_t)X)+((uint32_t)Y))))
// used to get pin postion in GPIO port 
#define Log(X)	                (int)log2(X)

typedef enum{
	E_NOT_OK,
	E_OK
}Std_ReturnType;


typedef enum{
	FALSE,
	TRUE
}ConditionReturn;

typedef enum{
	DISABLE,
	ENABLE
}boolean;

#endif
