
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
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

int16_t ax0, ay0, az0;
int16_t ax1, ay1, az1;
double ax=0, ay=0, az=0;
double vx=0, vy=0, vz=0;
double px=0, py=0, pz=0;

int16_t ptime, dtime;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
int i=0, j=0;

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.begin(38400);

  // initialize device
  Serial.println("Initializing I2C devices...A");
  accelgyro.initialize();
  Serial.println("Initializing I2C devices...B");

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  delay(1000);
  // use the code below to change accel/gyro offset values

  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);
  ax0=0;
  ay0=0;
  az0=0;
  for(i=0; i<100; i++)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax0+=ax;
    ay0+=ay;
    az0+=az;
  }
  ax0/=100;
  ay0/=100;
  az0/=100;
  ptime=millis();
}


void loop() {
  accelgyro.getAcceleration(&ax, &ay, &az);
  accelgyro.getRotation(&gx, &gy, &gz);
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.print(gz); Serial.println("\t");
  delay(1);
/*
  dtime=millis()-ptime;
  ptime=millis();
  // read raw accel/gyro measurements from device
  ax1=0;
  ay1=0;
  az1=0;
  for(i=0; i<100; i++)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax1+=ax;
    ay1+=ay;
    az1+=az;
  }
  ax1/=100;
  ay1/=100;
  az1/=100;

  ax=ax1-ax0;
  ay=ay1-ay0;
  az=az1-az0;
  ax/=200;
  ay/=200;
  az/=200;
  
  vx=vx+ax*dtime;
  vy=vy+ay*dtime;
  vz=vz+az*dtime;

  px=px+vx*dtime;
  py=py+vy*dtime;
  pz=pz+vz*dtime;


  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);

  // display tab-separated accel/gyro x/y/z values
  if(j==10)
  {
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.println("\t");
  Serial.print(vx); Serial.print("\t");
  Serial.print(vy); Serial.print("\t");
  Serial.print(vz); Serial.println("\t");
  Serial.print(px); Serial.print("\t");
  Serial.print(py); Serial.print("\t");
  Serial.print(pz); Serial.println("\t");
   Serial.println("--------------------------------------------------------");
   j=0;
  }
  j++;
/*
#ifdef OUTPUT_BINARY_ACCELGYRO
  Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
  Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
  Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
  Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
  Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
  Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
#endif*/
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  delay(0);

  
}
