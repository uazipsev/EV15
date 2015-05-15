#include <xc.h>
#include "PWM.h"

#define ON         0
#define OFF        1
#define INDICATOR1 LATEbits.LATE5
#define INDICATOR2 LATEbits.LATE6
#define INDICATOR3 LATGbits.LATG7
#define INDICATOR4 LATGbits.LATG8
#define WATCHDOG   LATEbits.LATE7
//Linear Representation of Servo:
//y = 150.56x + 9683.3
//scaling PDC output to avoid using float variables --> make slope = m/10
// y = (m/10)x + b+offset

//    PDC1 = 9800;      //0 Degrees
//    PDC1 = 23000;     //90 degrees
//    PDC1 = 36900;     //180 Degrees

static int slope_1 = 2;//1.66; //     m/10    [1.66 @100Hz][15   @300Hz][SLOPE REPRESENTS CLOCK DIVIDER/PERIOD]
static int slope_2 = 2;//1.66; //     m/10    [1.66 @100Hz][15   @300Hz][SLOPE REPRESENTS CLOCK DIVIDER/PERIOD]
static int offset_1 = 4125;//                 [4125 @100Hz][9683 @300Hz]
static int offset_2 = 4125;//                 [4125 @100Hz][9683 @300Hz]

static unsigned int current_angle_1 = 900; //  angle*10
static unsigned int current_angle_2 = 900; //  angle*10

void initPWM1(int offset_correction)
{
    offset_1 = offset_1 + (slope_1 * offset_correction);
    PTCONbits.PTEN = 0; //pwm module disabled
    PTCON2bits.PCLKDIV = 0b101; //clock divider of [32->0b101 @ 100Hz]  [8->0b011]  [SLOPE dependent]
    //PTPER = [Fosc]        / [(Fpwm)*(PWMClockPrescaler)]   = Period
    //PTPER = [120Mhz/8(^)] / [(200 Hz)*(64)]                = 6250
    PTPER = 65535; //master time base              [37500->100Hz @ 32 div]  []               [50000-> 300Hz @ 8 div]
    //    (200 Hz is total period @ 500 usec)
    //    45degree marks are +-400usec @# +-2500 Hz for each 45 degrees
    IOCON1bits.PENH = 1; //Output on PWM1H is active low
    IOCON1bits.PMOD = 3; /* Select True Independent Output PWM mode == 00*/

    setAngle1(current_angle_1);
    PTCONbits.PTEN = 1; //pwm module enabled
}

void initPWM2(int offset_correction)
{
    offset_2 = offset_2 + (slope_2 * offset_correction);
    PTCONbits.PTEN = 0; //pwm module disabled
    PTCON2bits.PCLKDIV = 0b101; //clock divider of 8
    //PTPER = [Fosc]/[(Fpwm)*(PWMClockPrescaler)]
    PTPER = 65535; //master time base
    //        PTPER = [80Mhz] / [(200 Hz)*(64)] = 6250
    //        200 Hz is total period @ 500 usec)
    //        45degree marks are +-400usec @# +-2500 Hz for each 45 degrees
    IOCON2bits.PENH = 1; //Output on PWM2H is active low
    IOCON2bits.PMOD = 3; /* Select True Independent Output PWM mode == 00 */
    setAngle2(current_angle_2);
    PTCONbits.PTEN = 1; //pwm module enabled
}

void setAngle1(unsigned int update_angle)
{
    if(update_angle>SERVO_MIN && update_angle<SERVO_MAX){
    PDC1 = (int)(((float)update_angle * (float)slope_1) + offset_1); //update PWM pulse width for PWM1
    current_angle_1 = update_angle; //update the PWM angle with the angle input to function call
    }
}

void setAngle2(unsigned int update_angle)
{
    if(update_angle>SERVO_MIN && update_angle<SERVO_MAX){
    PDC2 = (int)(((float)update_angle * (float)slope_2) + offset_2); //update PWM pulse width for PWM2
    current_angle_2 = update_angle; //update the PWM angle with the angle input to function call
    }
}

unsigned int presentAngle1(void)
{
    return current_angle_1;
}

unsigned int presentAngle2(void)
{
    return current_angle_2;
}