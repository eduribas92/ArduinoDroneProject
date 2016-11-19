#include "I2Cdev.h"
#include "MPU6050.h"
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;
MPU6050 accelgyro(0x68); // <-- use for AD0 high

double ax0, ay0, az0;

int num_samples=100;
// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

bool setup_accel() {
	
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize device
  accelgyro.initialize();
  
  // TODO : reportar error
  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  return accelgyro.testConnection();
}

void reset_offset_accel(int n_sample)
{
  //use the code below to change accel/gyro offset values
  double ax=0, ay=0, az=0;
  double gx=0, gy=0, gz=0;
  num_samples=n_sample;
  ax0=0;
  ay0=0;
  az0=0;
  for(i=0; i<num_samples; i++)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax0+=ax;
    ay0+=ay;
    az0+=az;
  }
  ax0/=num_samples;
  ay0/=num_samples;
  az0/=num_samples;
}


void get_accel(double* ax, double* ay, double* az, double* gx, double* gy, double* gz) {
  
  accelgyro.getMotion6(ax, ay, az, gx, gy, gz);

  // read raw accel/gyro measurements from device
  double ax1=0, ay1=0, az1=0, gx1=0, gy1=0, gz1=0;
  double axs=0, ays=0, azs=0, gxs=0, gys=0, gzs=0;;
  for(i=0; i<num_samples; i++)
  {
    accelgyro.getMotion6(ax1, ay1, az1, gx1, gy1, gz1);
    axs+=ax1-ax0;
    ays+=ay1-ay0;
    azs+=az1-az0;
	gxs+=gx1;
    gys+=gy1;
    gzs+=gz1;
  }
  *ax=axs/100.;
  *ay=ays/100.;
  *az=azs/100.;
  *gx=gxs/100.;
  *gy=gys/100.;
  *gz=gzs/100.;  
}
