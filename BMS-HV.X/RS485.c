#include <xc.h>
#include "Define.h"

/*
 *
 * Lets process if we have data....
 *
 */


void RS485_init(int numofdata, int * data...)
{
    //Lets get ready!


}



int dataprocess()
{
    int buffer[30];
    int i = 0;
    int id = 0;
    int datanum = 0;
    if (NULL == EUSART1_Read())
    {
        return 0;
    }
    else
    {
        while(NULL != EUSART1_Read())
        {
            buffer[i++] = EUSART1_Read();
        }
    }
    // so we have data.....lets do somthing with it....

    /*
     * Document packet = [0x55,0xA7,0x55,ID,num of data points (two bytes per point),data...,CRC,
     */
    //This is debug
    for(i = 0;i<30;i++)
    {
        //printf("%c",buffer[i]);
    }
    for(i = 0; i <30; i++)
    {
        // first pre
        if (buffer[i] == 0x55)
        {
            // second pre
            if (buffer[i++] == 0xA7)
            {
                // third pre
                if (buffer[i++] == 0x55)
                {
                    //we fount a start
                    //is it for us?
                    id = buffer[i++];
                    if (id != RS485ID)
                    {
                        // it is not.....get out
                        return 0;
                    }
                    else
                    {
                        //It is for us....
                        //Lets find out how much data is in the packet
                        datanum = buffer[i++];
                        
                    }
                }
            }
        }
    }

}