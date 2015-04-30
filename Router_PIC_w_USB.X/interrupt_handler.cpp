#include <xc.h>
#include <sys/attribs.h>
#include <stdlib.h>
#include "interrupt_handler.h"
#include "buffer.h"
#include "constants.h"
#include "queue.h"
#include "FastTransfer.h"
#include "variables.h"

void __ISR(_UART_1_VECTOR, IPL1AUTO) Uart1Handler(void)
{
    ring_buff_put(&buffer_one, U1RXREG); //move data to software buffer
    IFS0CLR = _IFS0_U1RXIF_MASK; // clear interrupt flag
}

void __ISR(_UART_2_VECTOR, IPL1AUTO) Uart2Handler(void)
{
    ring_buff_put(&buffer_two, U2RXREG);
    IFS1CLR = _IFS1_U2RXIF_MASK;
}

void __ISR(_UART_3_VECTOR, IPL1AUTO) Uart3Handler(void)
{
    ring_buff_put(&buffer_three, U3RXREG);
    IFS1CLR = _IFS1_U3RXIF_MASK;
}

void __ISR(_UART_4_VECTOR, IPL1AUTO) Uart4Handler(void)
{
    ring_buff_put(&buffer_four, U4RXREG);
    IFS2CLR = _IFS2_U4RXIF_MASK;
}

void __ISR(_UART_5_VECTOR, IPL1AUTO) Uart5Handler(void)
{
    ring_buff_put(&buffer_five, U5RXREG);
    IFS2CLR = _IFS2_U5RXIF_MASK;
}

void __ISR(_UART_6_VECTOR, IPL1AUTO) Uart6Handler(void)
{
    ring_buff_put(&buffer_six, U6RXREG);
    IFS2CLR = _IFS2_U6RXIF_MASK;
}