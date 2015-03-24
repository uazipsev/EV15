/* 
 * File:   UART.h
 * Author: Kilburn
 *
 * Created on February 23, 2015, 11:36 PM
 */

#define RX1_T TRISCbits.TRISC7
#define TX1_T TRISCbits.TRISC6
#define RX2_T TRISBbits.TRISB7
#define TX2_T TRISBbits.TRISB6

//Baud rate generator help
#define FP 4000000
#define BAUDRATE384 38400
#define BAUDRATE96 9600
#define BRGVAL ((FP/BAUDRATE384)/16)-1
#define BRGVAL2 ((FP/BAUDRATE96)/16)-1

/*-----------------------------------------------------------------------------
 *     BaudRate Generation Registers
 * -----------------------------------------------------------------------------
 *  -- SPBRGHx:SPBRGx                  register pair    |__  Baud Rate Selection
 *  --   BRGH       and      BRG16      bits            |
 *    TXSTA1 / 2          BAUDCON1 / 2
 *-----------------------------------------------------------------------------
 *     Pin Setup
 * -----------------------------------------------------------------------------
 *      Rx1 = RC7
 *      Tx1 = RC6
 *
 *      Rx2 = RB7
 *      Tx2 = RB6
 * -----------------------------------------------------------------------------
 *     UART Module Setup
 * -----------------------------------------------------------------------------
 *  -- Set TRIS to 1        (RXx / TXx Pins)
 *
 *  -- SPEN = 1             (ENABLE Serial Port)
 *  -- SYNC = 0             (Asynchronous)
 *              TXSTA1 / 2
 *  -- TXxIF = 1 set upon empty buffer
 *  -- RCxIF = 1 upon char transferred from RSR to receive buffer
 *              PIR1 / 3
 *  -- TXxIE = 1            (Transmit interrupt enable)
 *  -- RCxIE = 1            (Receive interrupt enable)
 *              PIE1 / 3
 *  -- GIE/GIEH = 1         (Global Interrupts)
 *  -- PEIE/GIEL = 1        (Peripheral Interrupts)
 *              INTCON
 *  -- CKTXP = 1            (Inverted Transmit Polarity)
 *
 *  -- TXEN = 1             (UART Tx Enable)
 *              TXSTA1 / 2
 *  -- CREN = 1             (UART Rx Enable)
 *              RCSTA1 / 2
 *
 *  -- TXREGx (char)         (Load data to be sent)
 *  -- RCREGx (char)        (Characted received register)
 */

//void initUART()
//{
//    RX1_T=1;
//    TX1_T=1;
//    RX2_T=1;
//    TX2_T=1;
//    SPEN = 1;
//    SYNC = 0;
//    PIR1bits.RCIF=0;
//    PIE1bits.RCIE=1;
//    INTCONbits.GIE=1;
//    TXSTA1bits.TXEN=1;
//    RCSTA1bits.CREN =1
//
//}

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Macro Declarations
*/

#define EUSART1_DataReady  (eusart1RxCount)

/**
  Section: Data Type Definitions
*/

/**
 Section: Global variables
 */
extern volatile uint8_t eusart1TxBufferRemaining;
extern volatile uint8_t eusart1RxCount;


/**
  Section: EUSART1 APIs
*/

/**
  @Summary
    Initialization routine that takes inputs from the EUSART1 GUI.

  @Description
    This routine initializes the EUSART1 driver.
    This routine must be called before any other EUSART1 routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment

  @Example
*/
void EUSART1_Initialize(void);

/**
  @Summary
    Read a byte of data from the EUSART1.

  @Description
    This routine reads a byte of data from the EUSART1.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t EUSART1_Read(void);

 /**
  @Summary
    Writes a byte of data to the EUSART1.

  @Description
    This routine writes a byte of data to the EUSART1.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the EUSART1

  @Returns
    None
*/
void EUSART1_Write(uint8_t txData);

/**
  @Summary
    Maintains the driver's transmitter state machine and implements its ISR.

  @Description
    This routine is used to maintain the driver's internal transmitter state
    machine.This interrupt service routine is called when the state of the
    transmitter needs to be maintained in a non polled manner.

  @Preconditions
    EUSART1_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART1_Transmit_ISR(void);

/**
  @Summary
    Maintains the driver's receiver state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal receiver state
    machine.This interrupt service routine is called when the state of the
    receiver needs to be maintained in a non polled manner.

  @Preconditions
    EUSART1_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART1_Receive_ISR(void);
