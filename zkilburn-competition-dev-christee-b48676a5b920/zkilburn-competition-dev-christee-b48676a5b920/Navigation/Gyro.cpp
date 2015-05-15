#include "Gyro.h"

extern int macroAngle;
//Init the gyro by removing the sleep bit and ensuring the sensativity setting
Gyro::Gyro(word address)
{
  gyroAddress = address;
}

void Gyro::initGyro() {
  // Clear the 'sleep' bit to start the sensor.
  MPU6050_write_reg(MPU6050_PWR_MGMT_1, 0);
  Serial.println("Power Management");
  MPU6050_write_reg(MPU6050_CONFIG,MPU6050_CONFIG_DLPF);
  Serial.println("DLPF");
  MPU6050_write_reg(MPU6050_SAMPLE_RATE,19);
  Serial.println("Sample Rate");
  //Set Gyro Sensativity
  MPU6050_write_reg(MPU6050_GYRO_CONFIG, MPU6050_FS_SEL_3); //+-2000deg/sec (/16.4)
   if(DEBUG_CALIBRATE)
    {
      Serial.print("Gyro Address ");
      Serial.print(gyroAddress);
      Serial.println(" has finished setup");
    }
  calibrateZero(250);
}
//Main loop ran from communications.ino
//Handles updating the gyro information through I2C device and storing data in register for other systems to use
int Gyro::updateGyro() {
  now = millis();
  if (abs(now - lastTime) > 20)
  {
    //store the old value of the raw
    compare = zRaw;

    //calculate the time between samples for integrating
    dt = ((now - lastTime) / 1000.0);

    //take in new value minus the offset calibration
    zRaw = sampleGyroZ() - offset;
    if(DEBUG_CALIBRATE)
    {
      Serial.print("Reading from ");
      Serial.print(gyroAddress);
      Serial.print(": ");
      Serial.println(zRaw);
    }
    //store time of this sample
    lastTime = millis();

    //If the point taken in is not outside of the deadzone
    if (((zRaw > -(z_dead_g / 2)) && (zRaw < (z_dead_g / 2))))// || abs(zRaw - compare) > 1000)
      //make it a pretty zero
      zFilt = 0;
    else
      //store the value that was outside the deadzone
      zFilt = zRaw / 16.4;

    latestFilteredSample = zFilt;
    //Integrate to store angle
    zRot += zFilt * dt;   
  }
  return (int) zRot;
}

// --------------------------------------------------------
// MPU6050_read
int Gyro::MPU6050_read(int starts, uint8_t *buffer, int sized)
{
  int i, n, error;

  Wire.beginTransmission(gyroAddress);
  n = Wire.write(starts);
  if (n != 1)
    return (-10);

  n = Wire.endTransmission(false);    // hold the I2C-bus
  if (n != 0)
    return (n);

  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(gyroAddress, sized, true);
  i = 0;
  while (Wire.available() && i < sized)
  {
    buffer[i++] = Wire.read();
  }
  if ( i != sized)
    return (-11);

  return (0);  // return : no error
}

// --------------------------------------------------------
// MPU6050_write
int Gyro::MPU6050_write(int starts, const uint8_t *pData, int sized)
{
  int n, error;
  Wire.beginTransmission(gyroAddress);
  n = Wire.write(starts);        // write the start address
  if (n != 1)
    return (-20);

  n = Wire.write(pData, sized);  // write data bytes
  if (n != sized)
    return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);
  return (0);         // return : no error
}

// --------------------------------------------------------
// MPU6050_write_reg
int Gyro::MPU6050_write_reg(int reg, uint8_t data)
{
  int error;
  error = MPU6050_write(reg, &data, 1);
  return (error);
}

//Method used to average a set up data
int16_t Gyro::averageSet(int numsamples, int16_t sampled[]) {
  float temp;
  temp = 0;
  for (int i = 0; i < numsamples; i++) {
    temp = temp + sampled[i];
  }
  return (int16_t)(temp / numsamples);
}

//Take a single sample from the gyro Z axis
inline int Gyro::sampleGyroZ()
{
  MPU6050_read (MPU6050_GYRO_YOUT_H, (uint8_t *) &gyro, sizeof(gyro));
  SWAP (gyro.reg.z_gyro_h, gyro.reg.z_gyro_l);
  return gyro.value.z_gyro;
}

//Run a calibration of a certain length to ensure deadzone and offset from zero
void Gyro::calibrateZero(int length)
{
  for (int i = 0; i < length; i++)
  {
    //TAKE A BUNCHA SAMPLES
    samples[i] = sampleGyroZ();

    //AFTER THE FIRST SAMPLE
    //CHECK TO SEE IF THE DIFFERENCE BETWEEN THE CALIBRATION
    //SAMPLES IS LARGER THAN 1000... IF SOO.. STORE PREVIOUS
    //SAMPLE INTO THIS SAMPLE// (AVOIDING JUMPS AND BUMPS)
    if ((i > 1) && (abs(samples[i] - samples[i - 1]) > 1000))
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
  offset = averageSet(length, samples);

  if(DEBUG_CALIBRATE)
  {
    Serial.println(offset, DEC);
  }
  //SET the high and low values to the offset center
  high = offset;
  low = offset;

  //Run through the samples again to determine the greatest
  //fluctuations from the center point
  for (int i = 0; i < length; i++)
  {
    if (samples[i] > high) {
      high = samples[i];
    }
    if (samples[i] < low) {
      low = samples[i];
    }
  }

  //The established deadzone is the peak to peak measured
  //noise on the signal line
  z_dead_g = (high - low);///2;
  zeroInternalAngle();
  //an attempt to allow for updating to resume without timer error
  lastTime = millis();
}



//wipes the internal integrated value to zero for integrity.
void Gyro::zeroInternalAngle()
{
  zRot=0;
}



