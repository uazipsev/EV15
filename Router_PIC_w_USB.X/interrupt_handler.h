/* 
 * File:   interrupt_handler.h
 * Author: Igor
 *
 * Created on September 7, 2014, 8:01 PM
 */

#ifndef INTERRUPT_HANDLER_H
#define	INTERRUPT_HANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

void __ISR(_UART_1_VECTOR, IPL1AUTO) Uart1Handler(void);
void __ISR(_UART_2_VECTOR, IPL1AUTO) Uart2Handler(void);
void __ISR(_UART_3_VECTOR, IPL1AUTO) Uart3Handler(void);
void __ISR(_UART_4_VECTOR, IPL1AUTO) Uart4Handler(void);
void __ISR(_UART_5_VECTOR, IPL1AUTO) Uart5Handler(void);
void __ISR(_UART_6_VECTOR, IPL1AUTO) Uart6Handler(void);

//void __ISR(_TIMER_1_VECTOR, IPL7SRS) Timer1Handler(void);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_HANDLER_H */

