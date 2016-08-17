/* 
 * File:   UART.h
 * Author: Kilburn
 *
 * Created on February 23, 2015, 11:36 PM
 */

#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

