#include <xc.h>
#define _SUPPRESS_PLIB_WARNING
#include <plib.h>
#include "constants.h"
#include "initialize.h"
#include "queue.h"
#include "buffer.h"
#include "FastTransfer.h"
#include "variables.h"

struct dmaSettings
{
    unsigned char *dma_array;
    volatile unsigned int *dmacon;
    unsigned int con_busy_mask;
    unsigned int con_en_mask;
    volatile unsigned int *dmasize;
    volatile unsigned int *dmaecon;
    unsigned int econ_force_mask;
};

struct queue_wrapper
{
Queue_handler * queue_pointer[7];
};

void initialize(void)
{
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); // sets up perifiral and clock configuration

    DMA(); //initialize dma settings
    Buffers(); //initialize buffers
    Settings(); // initialize settings
    Queue(); // initialize queue
    UART(); // initialize uart settings
}

void UART(void)
{
    INTEnableSystemMultiVectoredInt();

    // uart 1
    U1MODEbits.BRGH = 0; // set to standard speed mode
    U1BRG = 85; // 57600 baud
    U1MODEbits.PDSEL = 0b00; // 8-bit no parity
    U1MODEbits.STSEL = 0; // 1 stop bit
    IEC0bits.U1RXIE = 1; // recieve interrupt enable
    IPC6bits.U1IP = 1; // priority 1
    IPC6bits.U1IS = 1; // sub priority 1
    U1STAbits.UTXISEL = 0; // interrupt when transmit complete
    U1STAbits.URXISEL = 0; // interrupt generated with every reception
    U1STAbits.URXEN = 1; // enable uart recieve
    U1STAbits.UTXEN = 1; // enable uart transmit
    U1MODEbits.ON = 1; // enable whole uart module



    // uart 2 LED
    U2MODEbits.BRGH = 0; // set to standard speed mode
    U2BRG = 85; // 57600 baud
    U2MODEbits.PDSEL = 0b00; // 8-bit no parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    IEC1bits.U2RXIE = 1; // enable uart recieve
    IPC8bits.U2IP = 1; // priority 1
    IPC8bits.U2IS = 2; // sub priority 2
    U2STAbits.URXEN = 1; // enable uart recieve
    U2STAbits.URXISEL = 0b00; // interrupt generated with every reception
    U2STAbits.UTXEN = 1; // enable uart transmit
    U2MODEbits.ON = 1; // enable whole uart module



    // uart 3 power
    U3MODEbits.BRGH = 0; // set to standard speed mode
    U3BRG = 85; // 57600 baud
    U3MODEbits.PDSEL = 0b00; // 8-bit no parity
    U3MODEbits.STSEL = 0; // 1 stop bit
    IEC1bits.U3RXIE = 1; // enable uart recieve
    IPC7bits.U3IP = 1; // priority 1
    IPC7bits.U3IS = 2; // sub priority 2
    U3STAbits.URXEN = 1; // enable uart recieve
    U3STAbits.URXISEL = 0b00; // interrupt generated with every reception
    U3STAbits.UTXEN = 1; // enable uart transmit
    U3MODEbits.ON = 1; // enable whole uart module


    // uart 4
    U4MODEbits.BRGH = 0; // set to standard speed mode
    U4BRG = 85; // 57600 baud
    U4MODEbits.PDSEL = 0b00; // 8-bit no parity
    U4MODEbits.STSEL = 0; // 1 stop bit
    IEC2bits.U4RXIE = 1; // enable uart recieve
    IPC12bits.U4IP = 1; // priority 1
    IPC12bits.U4IS = 2; // sub priority 2
    U4STAbits.URXEN = 1; // enable uart recieve
    U4STAbits.URXISEL = 0b00; // interrupt generated with every reception
    U4STAbits.UTXEN = 1; // enable uart transmit
    U4MODEbits.ON = 1; // enable whole uart module



    // uart 5 lantronix
    AD1PCFGbits.PCFG8 = 1; //disable analog on RX pin
    AD1PCFGbits.PCFG14 = 1; //disable analog on TX5 pin
    U5MODEbits.BRGH = 0; // set to standard speed mode
    U5BRG = 42; // 115200 baud  //85; // 57600 baud
    U5MODEbits.PDSEL = 0b00; // 8-bit no parity
    U5MODEbits.STSEL = 0; // 1 stop bit
    IEC2bits.U5RXIE = 1; // enable uart recieve
    IPC12bits.U5IP = 1; // priority 1
    IPC12bits.U5IS = 2; // sub priority 2
    U5STAbits.URXEN = 1; // enable uart recieve
    U5STAbits.URXISEL = 0b00; // interrupt generated with every reception
    U5STAbits.UTXEN = 1; // enable uart transmit
    U5MODEbits.ON = 1; // enable whole uart module


    // uart 6 motor
    U6MODEbits.BRGH = 0; // set to standard speed mode
    U6BRG = 85; // 57600 baud
    U6MODEbits.PDSEL = 0b00; // 8-bit no parity
    U6MODEbits.STSEL = 0; // 1 stop bit
    IEC2bits.U6RXIE = 1; // enable uart recieve
    IPC12bits.U6IP = 1; // priority 1
    IPC12bits.U6IS = 2; // sub priority 2
    U6STAbits.URXEN = 1; // enable uart recieve
    U6STAbits.URXISEL = 0b00; // interrupt generated with every reception
    U6STAbits.UTXEN = 1; // enable uart transmit
    U6MODEbits.ON = 1; // enable whole uart module

    INTEnableInterrupts(); // enable interrupts
}

void DMA(void)
{
    DMACONbits.ON = 1; // dma module enabled
    DCRCCON = 0; // crc module disabled

    //dam  1
    DCH1CONbits.CHPRI = 2; // channel priority 2
    DCH1ECONbits.CHSIRQ = 28; // uart 1 tx IRQ
    DCH1ECONbits.SIRQEN = 1; // enable cell transfer when IRQ triggered
    DCH1INT = 0; // clear all existing flags, disable all interrupts
    DCH1SSA = (unsigned int) &dma_one_array & 0x1FFFFFFF; // physical address convertion for transmit buffer
    DCH1DSA = (unsigned int) &U1TXREG & 0x1FFFFFFF; // physical address convertion for uart send buffer
    DCH1DSIZ = 1;
    DCH1CSIZ = 1;

    //dam  2
    DCH2CONbits.CHPRI = 2; // channel priority 2
    DCH2ECONbits.CHSIRQ = 42; // uart 2 tx IRQ
    DCH2ECONbits.SIRQEN = 1; // enable cell transfer when IRQ triggered
    DCH2INT = 0; // clear all existing flags, disable all interrupts
    DCH2SSA = (unsigned int) &dma_two_array & 0x1FFFFFFF; // physical address convertion for transmit buffer
    DCH2DSA = (unsigned int) &U2TXREG & 0x1FFFFFFF; // physical address convertion for uart send buffer
    DCH2DSIZ = 1;
    DCH2CSIZ = 1;


    //dam  3
    DCH3CONbits.CHPRI = 2; // channel priority 2
    DCH3ECONbits.CHSIRQ = 39; // uart 3 tx IRQ
    DCH3ECONbits.SIRQEN = 1; // enable cell transfer when IRQ triggered
    DCH3INT = 0; // clear all existing flags, disable all interrupts
    DCH3SSA = (unsigned int) &dma_three_array & 0x1FFFFFFF; // physical address convertion for transmit buffer
    DCH3DSA = (unsigned int) &U3TXREG & 0x1FFFFFFF; // physical address convertion for uart send buffer
    DCH3DSIZ = 1;
    DCH3CSIZ = 1;


    //dam  4
    DCH4CONbits.CHPRI = 2; // channel priority 2
    DCH4ECONbits.CHSIRQ = 69; // uart 4 tx IRQ
    DCH4ECONbits.SIRQEN = 1; // enable cell transfer when IRQ triggered
    DCH4INT = 0; // clear all existing flags, disable all interrupts
    DCH4SSA = (unsigned int) &dma_four_array & 0x1FFFFFFF; // physical address convertion for transmit buffer
    DCH4DSA = (unsigned int) &U4TXREG & 0x1FFFFFFF; // physical address convertion for uart send buffer
    DCH4DSIZ = 1;
    DCH4CSIZ = 1;


    //dam  5
    DCH5CONbits.CHPRI = 2; // channel priority 2
    DCH5ECONbits.CHSIRQ = 75; // uart 5 tx IRQ
    DCH5ECONbits.SIRQEN = 1; // enable cell transfer when IRQ triggered
    DCH5INT = 0; // clear all existing flags, disable all interrupts
    DCH5SSA = (unsigned int) &dma_five_array & 0x1FFFFFFF; // physical address convertion for transmit buffer
    DCH5DSA = (unsigned int) &U5TXREG & 0x1FFFFFFF; // physical address convertion for uart send buffer
    DCH5DSIZ = 1;
    DCH5CSIZ = 1;


    //dam  6
    DCH6CONbits.CHPRI = 2; // channel priority 2
    DCH6ECONbits.CHSIRQ = 72; // uart 6 tx IRQ
    DCH6ECONbits.SIRQEN = 1; // enable cell transfer when IRQ triggered
    DCH6INT = 0; // clear all existing flags, disable all interrupts
    DCH6SSA = (unsigned int) &dma_six_array & 0x1FFFFFFF; // physical address convertion for transmit buffer
    DCH6DSA = (unsigned int) &U6TXREG & 0x1FFFFFFF; // physical address convertion for uart send buffer
    DCH6DSIZ = 1;
    DCH6CSIZ = 1;
}

void Buffers(void)
{
    ring_buff_init(&buffer_one);
    ring_buff_init(&buffer_two);
    ring_buff_init(&buffer_three);
    ring_buff_init(&buffer_four);
    ring_buff_init(&buffer_five);
    ring_buff_init(&buffer_six);
}

void Settings(void)
{



    //DMA 1 settings
    arrayOFdmaSetting[1].dma_array = (unsigned char*) &dma_one_array;
    arrayOFdmaSetting[1].dmacon = &DCH1CON;
    arrayOFdmaSetting[1].con_busy_mask = _DCH1CON_CHBUSY_MASK;
    arrayOFdmaSetting[1].con_en_mask = _DCH1CON_CHEN_MASK;
    arrayOFdmaSetting[1].dmasize = &DCH1SSIZ;
    arrayOFdmaSetting[1].dmaecon = &DCH1ECON;
    arrayOFdmaSetting[1].econ_force_mask = _DCH1ECON_CFORCE_MASK;



    //DMA 2 settings
    arrayOFdmaSetting[2].dma_array = (unsigned char*) &dma_two_array;
    arrayOFdmaSetting[2].dmacon = &DCH2CON;
    arrayOFdmaSetting[2].con_busy_mask = _DCH2CON_CHBUSY_MASK;
    arrayOFdmaSetting[2].con_en_mask = _DCH2CON_CHEN_MASK;
    arrayOFdmaSetting[2].dmasize = &DCH2SSIZ;
    arrayOFdmaSetting[2].dmaecon = &DCH2ECON;
    arrayOFdmaSetting[2].econ_force_mask = _DCH2ECON_CFORCE_MASK;


    //DMA 3 settings
    arrayOFdmaSetting[3].dma_array = (unsigned char*) &dma_three_array;
    arrayOFdmaSetting[3].dmacon = &DCH3CON;
    arrayOFdmaSetting[3].con_busy_mask = _DCH3CON_CHBUSY_MASK;
    arrayOFdmaSetting[3].con_en_mask = _DCH3CON_CHEN_MASK;
    arrayOFdmaSetting[3].dmasize = &DCH3SSIZ;
    arrayOFdmaSetting[3].dmaecon = &DCH3ECON;
    arrayOFdmaSetting[3].econ_force_mask = _DCH3ECON_CFORCE_MASK;


    //DMA 4 settings
    arrayOFdmaSetting[4].dma_array = (unsigned char*) &dma_four_array;
    arrayOFdmaSetting[4].dmacon = &DCH4CON;
    arrayOFdmaSetting[4].con_busy_mask = _DCH4CON_CHBUSY_MASK;
    arrayOFdmaSetting[4].con_en_mask = _DCH4CON_CHEN_MASK;
    arrayOFdmaSetting[4].dmasize = &DCH4SSIZ;
    arrayOFdmaSetting[4].dmaecon = &DCH4ECON;
    arrayOFdmaSetting[4].econ_force_mask = _DCH4ECON_CFORCE_MASK;


    //DMA 5 settings
    arrayOFdmaSetting[5].dma_array = (unsigned char*) &dma_five_array;
    arrayOFdmaSetting[5].dmacon = &DCH5CON;
    arrayOFdmaSetting[5].con_busy_mask = _DCH5CON_CHBUSY_MASK;
    arrayOFdmaSetting[5].con_en_mask = _DCH5CON_CHEN_MASK;
    arrayOFdmaSetting[5].dmasize = &DCH5SSIZ;
    arrayOFdmaSetting[5].dmaecon = &DCH5ECON;
    arrayOFdmaSetting[5].econ_force_mask = _DCH5ECON_CFORCE_MASK;


    //DMA 6 settings
    arrayOFdmaSetting[6].dma_array = (unsigned char*) &dma_six_array;
    arrayOFdmaSetting[6].dmacon = &DCH6CON;
    arrayOFdmaSetting[6].con_busy_mask = _DCH6CON_CHBUSY_MASK;
    arrayOFdmaSetting[6].con_en_mask = _DCH6CON_CHEN_MASK;
    arrayOFdmaSetting[6].dmasize = &DCH6SSIZ;
    arrayOFdmaSetting[6].dmaecon = &DCH6ECON;
    arrayOFdmaSetting[6].econ_force_mask = _DCH6ECON_CFORCE_MASK;
}

void Queue(void)
{


    DMA_one.queue_begin(arrayOFdmaSetting, 1);
    DMA_two.queue_begin(arrayOFdmaSetting, 2);
    DMA_three.queue_begin(arrayOFdmaSetting, 3);
    DMA_four.queue_begin(arrayOFdmaSetting, 4);
    DMA_five.queue_begin(arrayOFdmaSetting, 5);
    DMA_six.queue_begin(arrayOFdmaSetting, 6);

    queue_pointer[1] = &DMA_one;
    queue_pointer[2] = &DMA_two;
    queue_pointer[3] = &DMA_three;
    queue_pointer[4] = &DMA_four;
    queue_pointer[5] = &DMA_five;
    queue_pointer[6] = &DMA_six;

    

    receive_one.begin(&buffer_one, queue_pointer);
    receive_two.begin(&buffer_two, queue_pointer);
    receive_three.begin(&buffer_three, queue_pointer);
    receive_four.begin(&buffer_four, queue_pointer);
    receive_five.begin(&buffer_five, queue_pointer);
    receive_six.begin(&buffer_six, queue_pointer);
}

//void Timer1(void) {
//    T1CONbits.TCS = 0; // perifial clock as source
//    T1CONbits.TCKPS = 0b11; //256 prescalar
//    T1CONbits.TGATE = 0;
//    TMR1 = 31250;
//    IEC0SET = _IEC0_T1IE_MASK;
//    IPC1SET = ((0x7 << _IPC1_T1IP_POSITION) | (0x3 << _IPC1_T1IS_POSITION));
//    T1CONbits.ON = 1;
//
//
//}