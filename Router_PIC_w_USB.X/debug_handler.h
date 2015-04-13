/* 
 * File:   debug_handler.h
 * Author: Igor
 *
 * Created on January 24, 2015, 9:03 PM
 */

#ifndef DEBUG_HANDLER_H
#define	DEBUG_HANDLER_H

#ifdef	__cplusplus
extern "C"
{
#endif

    extern void USBInit(void);
    extern void USBUpdate(void);
    void USBProcsessIO(void);

    class DebugOut
    {
    private:
        unsigned char ringBufS_get(struct ringBuff* _this);
        unsigned char CRC8(const unsigned char * data, unsigned char len);
        unsigned int modulo_inc(const unsigned int value, const unsigned int modulus);

    public:
        void queue_put(unsigned char * _where, unsigned char how_many, unsigned char where, unsigned char from_where);
        void begin(void);
    };

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_HANDLER_H */

