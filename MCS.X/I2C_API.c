#include <xc.h>
#include <stdbool.h>
#include "I2C_API.h"


void I2C1Init(void)
{
    I2C1CONbits.I2CEN = 1;   //enable I2c
    I2C1CONbits.I2CSIDL = 1; //Stop module in idle mode
    I2C1CONbits.IPMIEN = 0;  //diable IPMIEN
    I2C1CONbits.A10M = 0;    //7bit address
    I2C1CONbits.DISSLW = 1;  //Shut off slew rate
    I2C1CONbits.SMEN = 0;    //disable SMbus Logic levels
    I2C1CONbits.ACKDT = 0;   //Send ACk during Ack

}

void I2C1ACK(void)
{
        I2C1CONbits.ACKEN = 1;   //Send ACK
}

void I2C1RXEN(void)
{
    I2C1CONbits.RCEN = 1;    //RX EN
}


void InitI2Cone(void)
{
    I2C1BRG = 591; // set baud rate 
    IPC4bits.MI2C1IP = 2; // priority level 2
    IFS1bits.MI2C1IF = 0; // clear flag
    IEC1bits.MI2C1IE = 1; // enable interrupt flag
    I2C1CONbits.I2CEN = 1; // enable i2c one
}


// initiates a send of an array containing a set number of data

bool SendI2Cone(unsigned char s_address, unsigned char * dat, unsigned char how_much)
{
    // see if a transmit or receive is in prograss
    if ((I2C_1_values.status == SUCCESS) || (I2C_1_values.status == FAILED))
    {
        //populate struct with needed data
        I2C_1_values.slave_address = s_address;
        I2C_1_values.data = dat;
        I2C_1_values.how_much_data = how_much;
        I2C_1_values.data_index = 0;
        I2C_1_values.direction = TRANSMIT;
        I2C_1_values.status = PENDING;
        FunctionI2Cone = &SendSlaveAddressI2Cone; // load the send slave address function
        I2C1CONbits.SEN = 1; // send start condition
        return true; // return successful
    } else
    {
        return false; // return failed if an i2c request is already running
    }
}

// initiate a receive moving data to an array of a set number of data

bool ReceiveI2Cone(unsigned char s_address, unsigned char d_address, unsigned char * dat, unsigned char how_much)
{
    //see if a transmit or receive is in prograss
    if ((I2C_1_values.status == SUCCESS) || (I2C_1_values.status == FAILED))
    {
        //populate struct with needed data
        I2C_1_values.slave_address = s_address;
        I2C_1_values.data_address = d_address;
        I2C_1_values.data = dat;
        I2C_1_values.how_much_data = how_much;
        I2C_1_values.data_index = 0;
        I2C_1_values.direction = RECEIVE;
        I2C_1_values.status = PENDING;
        FunctionI2Cone = &SendSlaveAddressI2Cone; // load the send slave address function
        I2C1CONbits.SEN = 1; // send start condition
        return true; // return successful
    } else
    {
        return false; // return failed if an i2c request is already running
    }
}

// send the slave address

void SendSlaveAddressI2Cone(void)
{
    I2C1TRN = I2C_1_values.slave_address; // load slave address into buffer
    FunctionI2Cone = &SendDataAddressI2Cone; // load the send data address function
}

// send data address if receivin or send firs byte if sending

void SendDataAddressI2Cone(void)
{
    // if ack is recieved then slave responded
    if (I2C1STATbits.ACKSTAT == 0) //ack received
    {
        // check the direction sending or receiving
        if (I2C_1_values.direction == RECEIVE) // receiving
        {
            I2C1TRN = I2C_1_values.data_address; // load data address value
            FunctionI2Cone = &SendRestartI2Cone; // load send restart function
        } else if (I2C_1_values.direction == TRANSMIT) // transmitting
        {
            // check if something is sitting in the array
            if (I2C_1_values.data_index < I2C_1_values.how_much_data) // data found
            {
                I2C1TRN = I2C_1_values.data[I2C_1_values.data_index]; // load data
                I2C_1_values.data_index++; // increment index
                FunctionI2Cone = &SendDataI2Cone; // load function that will continue sending
            } else //all data has been sent
            {
                StopFunctionI2Cone(); // since all data hase been sent initiate stop
                FunctionI2Cone = &SuccessFunctionI2Cone; // load sucess function
            }
        } else //neither transmit or receive (just in case)
        {
            StopFunctionI2Cone(); // initiate stop
            FunctionI2Cone = &FailFunctionI2Cone; // load fail function
        }
    } else //nack received
    {
        StopFunctionI2Cone(); // since nack redeived stop the buss
        FunctionI2Cone = &FailFunctionI2Cone; // load fail function
    }
}

void SendDataI2Cone(void)
{
    if (I2C1STATbits.ACKSTAT == 0) //ack received
    {
        //if index is less than how much data, send data and increment index
        if (I2C_1_values.data_index < I2C_1_values.how_much_data)
        {
            I2C1TRN = I2C_1_values.data[I2C_1_values.data_index]; // load data into buffer
            I2C_1_values.data_index++; // increment index
        } else //all data has been sent
        {
            StopFunctionI2Cone(); // since all data hase been sent initiate stop
            FunctionI2Cone = &SuccessFunctionI2Cone; // load sucess function
        }
    } else //nack received
    {
        StopFunctionI2Cone(); // since nack redeived stop the buss
        FunctionI2Cone = &FailFunctionI2Cone; // load fail function
    }
}

// send a stop to then later send start

void SendRestartI2Cone(void)
{
    I2C1CONbits.PEN = 1; //send stop
    FunctionI2Cone = &SendStartI2Cone; // load start function
}

// send start as a followup to the restart

void SendStartI2Cone(void)
{
    I2C1CONbits.SEN = 1; // send start condition
    FunctionI2Cone = &SendReadRequestI2Cone; // load send read request function
}

// send read request

void SendReadRequestI2Cone(void)
{
    I2C1TRN = (I2C_1_values.slave_address + 1); // send slave address plus 1
    FunctionI2Cone = &FirstReceiveI2Cone; // load first receive function
}

void FirstReceiveI2Cone(void)
{
    if (I2C1STATbits.ACKSTAT == 0) //ack received
    {
        I2C1CONbits.RCEN = 1; // enable receive
        FunctionI2Cone = &ReceiveByteI2Cone;
    } else //nack received
    {
        StopFunctionI2Cone();
        FunctionI2Cone = &FailFunctionI2Cone;
    }
}

void ReceiveByteI2Cone(void)
{
    I2C_1_values.data[I2C_1_values.data_index] = I2C1RCV;
    I2C_1_values.data_index++;
    if (I2C_1_values.data_index < I2C_1_values.how_much_data)
    {
        I2C1CONbits.ACKEN = 1; // send ACK
        FunctionI2Cone = &EnableReceiveI2Cone;
    } else
    {
        StopFunctionI2Cone();
        FunctionI2Cone = &SuccessFunctionI2Cone;
    }
}

void EnableReceiveI2Cone(void)
{
    I2C1CONbits.RCEN = 1; // enable receive
    FunctionI2Cone = &ReceiveByteI2Cone;
}

void StopFunctionI2Cone(void)
{
    I2C1CONbits.PEN = 1; //send stop
}

void FailFunctionI2Cone(void)
{
    I2C_1_values.status = FAILED;
}

void SuccessFunctionI2Cone(void)
{
    I2C_1_values.status = SUCCESS;
}

unsigned char StatusI2Cone(void)
{
    return I2C_1_values.status;
}

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
{
    if (I2C1STATbits.BCL == 1)
    {
        StopFunctionI2Cone();
        FunctionI2Cone = &FailFunctionI2Cone;
    } else
    {
        FunctionI2Cone();
    }
    IFS1bits.MI2C1IF = 0; // clear interrupt flag
}