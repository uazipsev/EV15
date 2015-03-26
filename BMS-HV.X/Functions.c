#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/pin_manager.h"
#include "Functions.h"
#include <xc.h>

void Set_4051(int Channel)
{
    if (Channel & 0x01)
    {
       MUX_A_Toggle();
    }
    if ((Channel>>1) & 0x01)
    {
       MUX_B_Toggle();
    }
    if ((Channel>>2) & 0x01)
    {
       MUX_C_Toggle();
    }
}

 unsigned int data[10];
 unsigned char modes[10];

 unsigned char getMode(void)
 {
   unsigned char i,j,c,m,n;
   unsigned int k;
   unsigned char counts[10],isMode[10];

   for(i=0;i<10;i++) isMode[i]=0;

   // count how many times we see each value

   for(i=0;i<10;i++)
   {
     c=0;
     for(j=0;j<10;j++) if(data[j]==data[i] c++;
     counts[i]=c;
   }

   // find maximum

   m=0;
   for(i=0;i<10;i++) if(counts[i]>m) m=counts[i];

   // set isMode[i] to 1 if data[i] is the mode value

   for(i=0;i<10;i++) if(counts[i]==m) isMode[i]=1;

   // de-dupe isMode

   for(i=0;i<10;i++) for(j=i+1;j<10;j++)
   {
     if(isMode[i] && data[j]==data[i]) isMode[j]=0;
   }

   // fill the output array

   n=0;
   for(i=0;i<10;i++) if(isMode[i]) modes[n++]=data[i];

   // return the number of modes

   return n;
 }
