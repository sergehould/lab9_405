/***********************************************************************************************
*
*
* FileName:  initBoard.c      
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date            Version     Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould      14 Jan. 2021		v1.0.0      Setup for PIC32    
* 
*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "initBoard.h"

 // Configuration Bit settings
// SYSCLK = 80 MHz 
//(8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (HS+PLL)
// WDT OFF, Peripheral Bus is CPU clock÷8
// Other options are default as per datasheet
// see file:C:\Program Files (x86)\Microchip\xc32\v1.40\docs\config_docs\32mx795f512l.html
 

#pragma config FPLLMUL = MUL_20
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_1 
#pragma config POSCMOD = HS, FNOSC = PRIPLL
#pragma config FPBDIV = DIV_2   // PBCLK = SYSCLK/DIV_2
//#pragma config WDTPS =  PS4096 // Post Scaler  32kHz/32/4096  target
#pragma config WDTPS =  PS256 // Post Scaler  32kHz/32/8  simulation
#pragma config FWDTEN =  OFF // enable

/* Sets up the IOs */
void initIO(void)
{
    /* LEDs */
    TRISAbits.TRISA7 = 0;//LED10
    TRISAbits.TRISA5 = 0;    //Led8

    
    TRISDbits.TRISD6 =1; //S3
    TRISDbits.TRISD7 =1;//S6
    TRISDbits.TRISD13 =1;//S4
    TRISAbits.TRISA6 =1; //S5
       
}


/* Initializes the Timer3 and the ISR               */
/*  init timer 3  to 40MHz/(16*10000) = 250Hz or 4mS */
void initT3(void){
    PR3 = 3000;
    /*
        111 = 1:256 prescale value
        110 = 1:64 prescale value
        101 = 1:32 prescale value
        100 = 1:16 prescale value
        011 = 1:8 prescale value
        010 = 1:4 prescale value
        001 = 1:2 prescale value
        000 = 1:1 prescale value
     */
    //T3CONbits.TCKPS = 0b111; // set prescaler 1:256
    //T3CONbits.TCKPS = 0b101; // set prescaler 1:32
    //T3CONbits.TCKPS = 0b100; // set prescaler 1:16
    T3CONbits.TCKPS = 0b000; // set prescaler 1:1
    T3CONbits.TGATE = 0; // not gated input (the default)
    T3CONbits.TCS = 0; // PCBLK input (the default)
    T3CONbits.ON = 1; // turn on Timer1
    //init interrupts
     __builtin_disable_interrupts();   // disable interrupts
    IPC3bits.T3IP=1;
    INTCONbits.MVEC=1;
    IEC0bits.T3IE=1;
   __builtin_enable_interrupts();   // enable interrupts
}
