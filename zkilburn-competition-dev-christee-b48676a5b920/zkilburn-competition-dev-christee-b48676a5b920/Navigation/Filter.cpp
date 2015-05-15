#include "Filter.h"

Filter::Filter()
{
  _lastTime=millis();
}
//Main loop ran from communications.ino
//Handles updating the gyro information through I2C device and storing data in register for other systems to use
float Filter::filterRawAccel(int raw, float conversionFactor) {
  _now = millis();
  //if (abs(_now - _lastTime) > 50)
  //{
  //calculate the time between samples for integrating
  _dt = ((_now - _lastTime) / 1000.0);

  //store time of this sample
  _lastTime = _now;    
  //take in new value minus the offset calibration
  raw = raw - _offset;
  //if input value is nortoriously low, ignore it and make it zero
  if(abs(raw)<200) raw=0;


  if(DEBUG_CALIBRATE)
  {      
    Serial.print(raw-_offset);
  }    

  //If the point taken in is not outside of the deadzone
  if (((raw > -(_deadzone)) && (raw < (_deadzone ))))// || abs(raw - _compare) > 2000)
    //make it a pretty zero
    _filtered = 0;
  else
    //store the value that was outside the deadzone
    _filtered = (raw / conversionFactor)*980.0;

  //store the old value of the raw
  _compare = raw;

  //DO EXTERNAL TO THIS METHOD (INTEGRATION)
  //Integrate to store angle
  _velocity += _filtered * _dt;
  if((abs(_velocity)<5)||(abs(raw)<(_deadzone)))
  {
    _velocity=0;
  }   
  //}
  return _velocity;
}

float Filter::filterRawGyro(int raw, float conversionFactor) {
  _now = millis();
  //calculate the time between samples for integrating
  _dt = ((_now - _lastTime) / 1000.0);

  //take in new value minus the offset calibration
  raw = raw - _offset;
  if(abs(raw)<5) raw=0;
  if(DEBUG_CALIBRATE)
  {      
    Serial.print(raw);
  }
  //store time of this sample
  _lastTime = millis();

  //If the point taken in is not outside of the deadzone
  if (((raw > -(_deadzone / 2)) && (raw < (_deadzone/ 2))))// || abs(zRaw - compare) > 1000)
    //make it a pretty zero
    _filtered = 0;
  else
    //store the value that was outside the deadzone
    _filtered = raw / conversionFactor;
  //store the old value of the raw
  _compare = raw;
  //Integrate to store angle
  _rot += _filtered * _dt;   

  return _rot;
}

void Filter::calibrateFilter(int samples[100])
{
  for (int i = 1; i < 100; i++)
  { 
    //CHECK TO SEE IF THE DIFFERENCE BETWEEN THE CALIBRATION
    //SAMPLES IS LARGER THAN 1000... IF SOO.. STORE PREVIOUS
    //SAMPLE INTO THIS SAMPLE// (AVOIDING JUMPS AND BUMPS)
    if ((abs(samples[i] - samples[i - 1]) > 1000))
    {
      //STORE PREVIOUS VALUE
      samples[i] = samples[i - 1];
    }

    if(DEBUG_CALIBRATE)
    {
      Serial.println(samples[i], DEC);
    }

    delay(5);
  }

  //Get the offset value by averaging the set of samples
  _offset = averageSet(100, samples);

  if(DEBUG_CALIBRATE)
  {
    Serial.print("Calibrated with offset: ");
    Serial.println(_offset);
  }

  //SET the high and low values to the offset center
  int high = _offset;
  int low = _offset;

  //Run through the samples again to determine the greatest
  //fluctuations from the center point
  for (int i = 0; i < 100; i++)
  {
    if (samples[i] > high) {
      high = samples[i];
    }
    if (samples[i] < low) {
      low = samples[i];
    }
  }
  if(DEBUG_CALIBRATE)
  {
    Serial.print("High Recorded Value: ");
    Serial.println(high);
    Serial.print("Low Recorded Value: ");
    Serial.println(low);
  }
  //The established deadzone is the peak to peak measured
  //noise on the signal line
  _deadzone = (high - low);
  //an attempt to allow for updating to resume without timer error
  _lastTime = millis();
}

void Filter::recordOffset(int offset){
  _offset=offset;
}

void Filter::recordDeadzone(int deadzone){
  _deadzone=deadzone;
}

void Filter::zeroInternalAngle()
{
  _rot=0;
}

void Filter::wipeVelocity()
{
  _velocity=0; 
}


int16_t Filter::averageSet(int numsamples, int16_t sampled[]) {
  float temp;
  temp = 0;
  for (int i = 0; i < numsamples; i++) {
    temp = temp + sampled[i];
  }
  return (int16_t)(temp / numsamples);
}



