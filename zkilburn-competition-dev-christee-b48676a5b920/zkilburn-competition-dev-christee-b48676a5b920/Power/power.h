//PINS defined
#define volts A2 //actual pin values need filled in
#define amps A4
#define circuitVolts A1
#define circuitAmps A3


//Calibrations Defined

//Battery Voltage Ratio
#define VOLTAGE_RATIO 0.15
//Main current Sensor calibration
#define OFFSET_AMPS 2050
#define SENSATIVITY 33.3333  //200 //133.3333 

//Voltage for onboard voltage meaure 
#define RATIO_CIRCUIT 0.66206641//0.7328 //0.209

#define OFFSET_CIRCUIT 0//2042
#define SENSATIVITY_CIRCUIT 1 //151 //151- 5A ACS712

//Storage Variables
float wattHours, milliAmphours, milliAmps, voltage, circuitVoltage, circuitCurrent;

//Timers
Timers LED(1000), powerCalculation(1000), sensors(1);

//Quick and often grab readings
void updateSensorReading()
{
  sensors.updateTimer();
  if (sensors.timerDone())
  {
    //Grab Sensor readings and calculate values
    //-----------------------Battery Voltage Reading
    float voltageReading = (analogRead(volts) * (500.0 / 1024.0)) / VOLTAGE_RATIO;

    //----------------------Large Hall Effect Measurement    
    //float milliAmpsReading = (analogRead(amps) * (5000 / 1024)) - OFFSET_AMPS;    
    //milliAmpsReading = milliAmpsReading * SENSATIVITY;    
    
    //------------------REVISION TO THE CURRENT CALCULATION--
    static float oldCurrent, recordThis;
    float newVoltage = ((analogRead(amps) * (5000 / 1024)) - OFFSET_AMPS); 
    if (abs(newVoltage) < 5) newVoltage = 0;
    float newCurrent =newVoltage * SENSATIVITY;
    
    //  Serial2.print("newVoltage: ");
    //  Serial2.println(newVoltage);
    //  Serial2.print("newCurrent: ");
    //  Serial2.println(newCurrent);

    //-----------------------Filtered Voltage Reading on CHIP
    float circuitVoltageReading = (analogRead(circuitVolts) * ( 5000 / 1024))/RATIO_CIRCUIT;

    //-------------------ACS712 Low Current Circuit milliAmps Draw reading
    float circuitCurrentReading = (analogRead(circuitAmps) * (5000 / 1024))-OFFSET_CIRCUIT;
    circuitCurrentReading = circuitCurrentReading/SENSATIVITY_CIRCUIT;

    //-------------------Filtering without storing a buncha stuff
    //milliAmps=((milliAmps*99.0)+milliAmpsReading)/100.0;
    voltage=((voltage*31)+voltageReading)/32;
    circuitVoltage=((circuitVoltage*31)+circuitVoltageReading)/32;
    circuitCurrent=((circuitCurrent*63)+circuitCurrentReading)/64; 

    if ((abs(newCurrent) < 10) && (abs(milliAmps) < 10))
    {
      milliAmps = 0;
    }
    else if (abs(newCurrent - milliAmps) < 3000)
    {
      recordThis = newCurrent;
    } //else if the difference between the old and avg and new and avg are not relatively close
    else if (abs(abs(milliAmps - oldCurrent) - abs(milliAmps - newCurrent)) > 3000)
    {
      recordThis = milliAmps;
    }
    else
    {
      recordThis = oldCurrent;
    }
    oldCurrent = newCurrent;
    milliAmps = ((milliAmps * 63.0) + recordThis) / 64;


    sensors.resetTimer();

    //Debug to calibrate
    //    Serial.print("MilliAmps: ");
    //    Serial.println(milliAmps);
    //    Serial.print("Voltage: ");
    //    Serial.println(voltage);
    //    Serial.print("CircuitVoltage: ");
    //    Serial.println(circuitVoltage);
    //    Serial.print("circuitCurrent: ");
    //    Serial.println(circuitCurrent);
  }

}
//Calculate the power once a second for accurate Ah and Wh
void calculatePower()
{
  powerCalculation.updateTimer();
  if (powerCalculation.timerDone())
  {
    //Integrate milliAmps/t for milliAmphours = (ampHours*1000)
    milliAmphours += (milliAmps / 3600.0);
    //Integrate amps*volts for wattHours
    wattHours += (((milliAmps / 3600.0) / 1000.0) * (circuitVoltage/100));
  }
}

void updateLED()
{
  LED.updateTimer();
  if (LED.timerDone())  
    digitalWrite(13, !digitalRead(13));  
}

