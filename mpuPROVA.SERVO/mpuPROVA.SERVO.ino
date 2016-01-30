#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Servo.h"
 
MPU6050 mpu;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
Servo myservo;
 
int val;
int prevVal;
 
void setup() 
{
    Wire.begin();
    Serial.begin(38400);
 
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");

    myservo.attach(9);
    
    val = 0;
    Serial.println(val);
    myservo.write(val);
    delay(3000);
    
    val = 10;
    Serial.println(val);
    myservo.write(val);
    delay(1000);
}
 
void loop() 
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
    val = map(gz, -17000, 17000, 0, 35);
    if (val != prevVal)
    {
        Serial.print(gz); Serial.print("\t"); Serial.println(val);
        myservo.write(val);
        prevVal = val;
    }
 
    delay(500);
}
