/*
*  Valors
*  - Val = 4 comença a girar
*  - Val = 47 és el màxim (amb aspa), 180 sense
*  - Podem passar de 0 a 27 de cop
*  (Do whatever you want with it.)
*/

// Need the Servo library
#include <Servo.h>

// This is our motor.
Servo myMotor;
int increment = 2;
int val = 0;

// Set everything up
void setup()
{
  // Put the motor to Arduino pin #9
  myMotor.attach(10);
  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
  myMotor.write(0);
  delay(500);
}


void loop(){
  val = val + increment;
  // Convert the string to an integer
  Serial.println(val);
  if (val > -1 && val < 40)
    myMotor.write(val);
  if( val == 40 || val == 0)
    increment = -increment;

    delay(500);
}
