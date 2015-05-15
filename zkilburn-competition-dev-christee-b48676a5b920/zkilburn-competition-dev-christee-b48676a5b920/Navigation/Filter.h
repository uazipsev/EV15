#ifndef Filter_h
#define Filter_h

#include "Arduino.h"
#define DEBUG_CALIBRATE false
class Filter
{
public:
  Filter();
  float filterRawAccel(int raw, float conversionFactor);
  float filterRawGyro(int raw, float conversionFactor);
  void calibrateFilter(int samples[100]);
  void zeroInternalAngle();
  void wipeVelocity();
  int16_t averageSet(int numsamples, int16_t sampled[]);
  void recordOffset(int offset);
  void recordDeadzone(int deadzone);
  float _offset;
  float _deadzone;
  float _rot;
private: 
  float _velocity;
  float _compare;
  float _dt;
  float _now, _lastTime;
  float _filtered;

};


#endif


