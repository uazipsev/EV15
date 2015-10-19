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
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

char UART_buff_put(const unsigned char data) {
    if (UART_ring_buff_In.count < UART_BUFFER_SIZE_IN) {
        UART_ring_buff_In.buf[UART_ring_buff_In.head] = data;
        UART_ring_buff_In.head = UART_ring_buff_In.head + 1;
        ++UART_ring_buff_In.count;
    } else {
        UART_ring_buff_In.buf[UART_ring_buff_In.head] = data;
        UART_ring_buff_In.head = UART_buff_modulo_inc(_this->head, UART_BUFFER_SIZE);
        UART_ring_buff_In.tail = UART_buff_modulo_inc(_this->tail, UART_BUFFER_SIZE);
    }
    return 1;
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char UART_Tx_buff_get() {
    unsigned char c;
    if (UART_ring_buff_Out.count > 0) {
        c = UART_ring_buff_Out.buf[UART_ring_buff_Out.tail];
        UART_ring_buff_Out.tail = UART_ring_buff_Out.tail - 1;
        --UART_ring_buff_Out.count;
    } else {
        c = NULL;
    }
    return (c);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char UART_Rx_buff_get() {
    unsigned char c;
    if (UART_ring_buff_In.count > 0) {
        c = UART_ring_buff_In.buf[UART_ring_buff_In.tail];
        UART_ring_buff_In.tail = UART_ring_buff_In.tail - 1;
        --UART_ring_buff_In.count;
    } else {
        c = NULL;
    }
    return (c);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

void UART_Input_buff_flush() {
    UART_ring_buff_In.count = 0;
    UART_ring_buff_In.head = 0;
    UART_ring_buff_In.tail = 0;
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char UART_buff_peek() {
    return UART_ring_buff_In.buf[UART_ring_buff_In.tail];
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char Receive_peek(void) {
    return UART_buff_peek(&input_buffer);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

int Receive_available(void) {
    return UART_buff_size(&input_buffer);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

int Transmit_available(void) {
    return UART_buff_size(&input_buffer);
}

/*******************************************************************
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
 * @return          None
 * @note            used for serial comm.
 *******************************************************************/

unsigned char Receive_get(void) {
    return UART_buff_get(&input_buffer);
}

/*******************************************************************
 * @brief           UART1 TX ring buffer loader
 * @brief           Loades the ring buffer for transmit out of pic
 * @return          success or fail
 * @note            used for serial comm.
 *******************************************************************/

char Send_put(unsigned char _data) {
    UART_buff_put(&output_buffer, _data);
    if (Transmit_stall == true) {
        Transmit_stall = false;
        U1TXREG = UART_buff_get(&output_buffer);
    }
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
 * @brief           UART1 TX Interupt
 * @brief           Interupt function on UART 1 Transmit buffer empty for reload
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