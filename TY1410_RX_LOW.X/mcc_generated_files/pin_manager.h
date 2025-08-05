/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1936
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set HiBeam aliases
#define HiBeam_TRIS                 TRISAbits.TRISA0
#define HiBeam_LAT                  LATAbits.LATA0
#define HiBeam_PORT                 PORTAbits.RA0
#define HiBeam_ANS                  ANSELAbits.ANSA0
#define HiBeam_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define HiBeam_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define HiBeam_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define HiBeam_GetValue()           PORTAbits.RA0
#define HiBeam_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define HiBeam_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define HiBeam_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define HiBeam_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DriveLight aliases
#define DriveLight_TRIS                 TRISAbits.TRISA1
#define DriveLight_LAT                  LATAbits.LATA1
#define DriveLight_PORT                 PORTAbits.RA1
#define DriveLight_ANS                  ANSELAbits.ANSA1
#define DriveLight_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DriveLight_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DriveLight_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DriveLight_GetValue()           PORTAbits.RA1
#define DriveLight_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DriveLight_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DriveLight_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DriveLight_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

// get/set UART_TX aliases
#define UART_TX_TRIS                 TRISCbits.TRISC4
#define UART_TX_LAT                  LATCbits.LATC4
#define UART_TX_PORT                 PORTCbits.RC4
#define UART_TX_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define UART_TX_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define UART_TX_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define UART_TX_GetValue()           PORTCbits.RC4
#define UART_TX_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define UART_TX_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/