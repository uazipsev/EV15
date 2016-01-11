#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UART.h"
#include "PinDef.h"

/*******************************************************************
 * @brief           UART1 Setup
 * @brief           Sets up uart for a 8n1 w/ baude rate set in .h
 * @return          None
 * @note            Does not including pps pin configs. used for serial comm.
 *******************************************************************/

void UART_init(void) {
    // UART config
    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-baud disabled
    U1BRG = BAUD_RATE; // Baud Rate setting for 57600
    U1STAbits.URXISEL = 0b01; // Interrupt after all TX character transmitted
    U1STAbits.URXISEL = 0b00; // Interrupt after one RX character is received
    IFS0bits.U1RXIF = 0; // Clear RX interrupt flag
    IFS0bits.U1TXIF = 0; // Clear TX interrupt flag
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    IEC0bits.U1RXIE = 1; // Enable RX interrupt
    IEC0bits.U1TXIE = 1; // Enable TX interrupt
    UARTBuffInit(1,1,UART_BUFFER_SIZE_OUT,UART_BUFFER_SIZE_IN);
}


/*******************************************************************
 * @brief           UART buffer init
 * @brief           This function inits the two ring buffers
 * @return          returns a 1 if sucsess
 * @note            used for serial comm.
 *******************************************************************/
char UARTBuffInit(bool txbuff, bool rxbuff, int sizetx, int sizerx){
    if(txbuff){
        //RingBuffOut *myRingBuffer = (RingBuffOut *)calloc(1, sizeof(RingBuffOut));
        RingBuffOut.sizeOfBuffer = sizetx;
        RingBuffOut.currentIndex = 0;
    }
    if(rxbuff){
        //RingBuffIn *myRingBuffer = (RingBuffIn *)calloc(1, sizeof(RingBuffIn));
        RingBuffIn.sizeOfBuffer = sizerx;
        RingBuffIn.currentIndex = 0;
    }
    return 1;
}

/*******************************************************************
 * @brief           UART buffer stuffer :)
 * @brief           This function takes a char and addes it to the ring buffer
 * @return          returns a 1.
 * @note            used for serial comm.
 *******************************************************************/

char UART_buff_put(char myData) {
    // -1 for our binary modulo in a moment
    int buffLen = RingBuffOut.sizeOfBuffer - 1;
    int lastWrittenSample = RingBuffOut.currentIndex;

    int idx;
    // modulo will automagically wrap around our index
    idx = (1 + lastWrittenSample) & buffLen;
    RingBuffOut.data[idx] = myData;
    
    // Update the current index of our ring buffer.
    RingBuffOut.currentIndex += 1;
    RingBuffOut.currentIndex &= RingBuffOut.sizeOfBuffer - 1;

    return 1;
}

/*******************************************************************
 * @brief           UART1 TX buff pull (FIFO)
 * @brief           Grabs the "oldest" data in the buffer
 * @return          unsigned char
 * @note            used for serial comm.
 *******************************************************************/

unsigned char UART_Tx_buff_get() {
    unsigned char c = 1;
    return (c);
}

/*******************************************************************
 * @brief           UART1 RX buff pull (FIFO)
 * @brief           Grabs the "oldest" data in the buffer
 * @return          unsigned char
 * @note            used for serial comm.
 *******************************************************************/

unsigned char UART_Rx_buff_get() {
    unsigned char c = 1;
    return (c);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

void UART_Input_buff_flush() {

}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char UART_buff_peek() {
    //return UART_ring_buff_In.buf[UART_ring_buff_In.tail];
    return 1;
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char Receive_peek(void) {
    return 1; //UART_buff_peek(&input_buffer);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

int Receive_available() {
    return RingBuffIn.sizeOfBuffer;
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

int Transmit_available() {
    return RingBuffOut.sizeOfBuffer;
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char Receive_get() {
    return 1; //UART_buff_get(&input_buffer);
}

/*******************************************************************
 * @brief           UART1 TX ring buffer loader
 * @brief           Loades the ring buffer for transmit out of pic
 * @return          success or fail
 * @note            used for serial comm.
 *******************************************************************/

char Send(unsigned char _data) {
//    UART_buff_put(&output_buffer, _data);
//    if (Transmit_stall == true) {
//        Transmit_stall = false;
//        U1TXREG = UART_buff_get(&output_buffer);
//    }
    return 1;
}

/*******************************************************************
 * @brief           UART1 RX Interupt
 * @brief           Interupt function on UART 1 recive
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    if (U1STAbits.OERR) {
        U1STAbits.OERR = 0;
    }
    unsigned char data = U1RXREG;
    UART_buff_put(data);
    IFS0bits.U1RXIF = 0; // Clear RX interrupt flag
}

/*******************************************************************
 * @brief           UART1 RX Interupt
 * @brief           Interupt function on UART 1 TX
 * @return          None
 * @note            used for serial comm. 
 *******************************************************************/

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    //LED ^= 1;
    if (Transmit_available() > 0) {
        U1TXREG = UART_Tx_buff_get();
    } else {
        Transmit_stall = true;
    }
    IFS0bits.U1TXIF = 0; // Clear TX interrupt flag
}