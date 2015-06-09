/* 
 * File:   debug.h
 * Author: User
 *
 * Created on June 8, 2015, 7:10 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdbool.h>
    extern void handleDebugRequests();
    
    extern void sendData2(unsigned char whereToSend);
    extern bool receiveData2();
    extern void ToSend2(const unsigned char where, const unsigned int what);



#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

