/***********************************************************************************************
 *
 * Combined LCD and UART Drivers for PIC32.
 *
 ***********************************************************************************************
 * FileName:  cons.c      
 *
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date               v        Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould		3 Feb 2021          Modified version for this lab only. See fprintf2() below
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __CONS_H_
#define __CONS_H_

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

//Migration to MPLAB® Harmony from Legacy Peripheral Libraries -- All the Peripheral Library (PLIB) 
//functions, usually included by plib.h, will be removed from future releases of MPLAB XC32 C/C++ Compiler.
//        Please refer to the MPLAB Harmony Libraries for new projects. For legacy support, these 
//        PLIB Libraries will be available for download from:
//        http://www.microchip.com/pic32_peripheral_lib. 
//        NOTE: The peripheral library header files now contain a #warning message: 
//                "The PLIB functions and macros in this file will be removed from the "
//                "MPLAB XC32 C/C++ Compiler in future releases". To suppress this warning, 
//                define the preprocessor macro _SUPPRESS_PLIB_WARNING before #include'ing a 
//                plib header file. You can define this symbol in your MPLAB X project settings 
//                or you can use a #define _SUPPRESS_PLIB_WARNING 1 in your code before the 
//                #include directive.
//#include "pmp.h"
//#define _SUPPRESS_PLIB_WARNING
//#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
//#include <plib.h>
//#include "peripheral/pmp.h"

//#include "../common/pmp.h"

enum my_fp {
 C_UART1,
 C_UART2,
 C_LCD
};

//#define     __UART1  0
//#define     __UART2  1
//#define     __LCD    2
#define 	SLOW	// for slow LCD
//#define 	FAST	// for fast LCD

#ifdef		SLOW		// for slow LCD, delays modified for the profiling part of the function Generator 
						// lab using Explorer 16 at fcy = 16MHz
// Define a fast instruction execution time in terms of loop time
// typically > 43us
#define	LCD_F_INSTR		1700 //1.04 mS measured, Explorer 16 at fcy = 16MHz

// Define a slow instruction execution time in terms of loop time
// typically > 1.35ms
#define	LCD_S_INSTR		2000//1.22mS measured, Explorer 16 at fcy = 16MHz

// Define the startup time for the LCD in terms of loop time
// typically > 30ms
#define	LCD_STARTUP		14000   //14000  
#endif

#ifdef		FAST		// for fast LCD, delays optimized for Explorer 16 at fcy 16MHz

// Define a fast instruction execution time in terms of loop time
// typically > 43us
#define	LCD_F_INSTR		70  //42uS measured, Explorer 16 at fcy = 16MHz

// Define a slow instruction execution time in terms of loop time
// typically > 1.35ms
#define	LCD_S_INSTR		150//76 uS measured, Explorer 16 at fcy = 16MHz    

// Define the startup time for the LCD in terms of loop time
// typically > 30ms
#define	LCD_STARTUP		2000
#endif


void LCDInit(void);

/** UART2 Driver Hardware Flags

  @Summary
    Specifies the status of the hardware receive or transmit

  @Description
    This type specifies the status of the hardware receive or transmit.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/
//typedef enum
//{
//    /* Indicates that Receive buffer has data, at least one more character can be read */
//    UART2_RX_DATA_AVAILABLE
//        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,
//    
//    /* Indicates that Receive buffer has overflowed */
//    UART2_RX_OVERRUN_ERROR
//        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,
//
//    /* Indicates that Framing error has been detected for the current character */
//    UART2_FRAMING_ERROR
//        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,
//
//    /* Indicates that Parity error has been detected for the current character */
//    UART2_PARITY_ERROR
//        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,
//
//    /* Indicates that Receiver is Idle */
//    UART2_RECEIVER_IDLE
//        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,
//
//    /* Indicates that the last transmission has completed */
//    UART2_TX_COMPLETE
//        /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,
//
//    /* Indicates that Transmit buffer is full */
//    UART2_TX_FULL
//        /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/
//
//}UART2_STATUS;

void UART2_Initialize(void);
void initUart2( void);
void initUart1( void);
void initUart2_wInt( void);
int putc2(char c);
int putc2_noHard(char c);
char getc2( void);
void puts2( char *str );
void outUint8(unsigned char u8_x);
void putI8(unsigned char u8_x);
/**
  Section: Macro Declarations
*/

#define UART2_DataReady  (U2STAbits.URXDA == 1)

/**
  Section: UART2 APIs
*/


/**
 * @brief Check if the UART2 transmitter is empty
 *
 * @return The status of UART2 TX empty checking.
 * @retval false the UART2 transmitter is not empty
 * @retval true the UART2 transmitter is empty
 */
bool UART2_is_tx_ready(void);

/**
 * @brief Check if the UART2 receiver is not empty
 *
 * @return The status of UART2 RX empty checking.
 * @retval false the UART2 receiver is empty
 * @retval true the UART2 receiver is not empty
 */
bool UART2_is_rx_ready(void);

/**
 * @brief Check if UART2 data is transmitted
 *
 * @return Receiver ready status
 * @retval false  Data is not completely shifted out of the shift register
 * @retval true   Data completely shifted out if the USART shift register
 */
bool UART2_is_tx_done(void);

/**
  @Summary
    Read a byte of data from the UART2.

  @Description
    This routine reads a byte of data from the UART2.

  @Preconditions
    UART2_Initialize() function should have been called
    before calling this function. This is a blocking function.
    So the recieve status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t UART2_Read(void);

 /**
  @Summary
    Writes a byte of data to the UART2.

  @Description
    This routine writes a byte of data to the UART2.

  @Preconditions
    UART2_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the UART2

  @Returns
    None
*/
void UART2_Write(uint8_t txData);

/**
  @Summary
    Returns the transmitter and receiver status

  @Description
    This returns the transmitter and receiver status. The returned status may 
    contain a value with more than one of the bits
    specified in the UART2_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART2_Initializer function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART2_STATUS value describing the current status 
    of the transfer.

  @Example
    <code>
        while(!(UART2_StatusGet & UART2_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/

//UART2_STATUS UART2_StatusGet (void );

/*Call back*/
int  fprintf2(int, char *);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif
