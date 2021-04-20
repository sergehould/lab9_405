/***********************************************************************************************
*
*
* FileName:  initBoard.H      
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date            Version     Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould      14 Jan. 2021		v1.0.0      Setup for PIC32    
* 
*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef INITBOARD_H
#define INITBOARD_H
/**
    Section: Includes
*/
#include <stdint.h>
#include <xc.h>

/**
    Section: Macros
*/
//macros definitions
/**
    Section: Function Prototypes
*/
#define     S3  PORTDbits.RD6
#define     S6  PORTDbits.RD7
#define     S5  PORTAbits.RA6
#define     S4  PORTDbits.RD13

void initIO(void);
void initT3(void);
#endif
