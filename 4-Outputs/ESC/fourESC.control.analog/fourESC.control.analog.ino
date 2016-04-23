#include <Servo.h>

Servo ESC1, ESC2, ESC3, ESC4;

int value = 0, value1 = 0, value2 = 0, value3 = 0, value4 = 0;
const int max_value = 70, min_value = 0;

const int pinButtonInc = 13, pinButtonDec = 12;
int stateButtonInc = 0, stateButtonDec = 0;
unsigned long timeButtonPressed = 0;
const int precision = 200; // (ms)

const int pinPot_1_3 = 0, pinPot_2_4 = 1;
int valuePot_1_3 = 0, valuePot_2_4 = 0;


void setup(){
  
  ESC1.attach(6);
  ESC2.attach(9);
  ESC3.attach(10);
  ESC4.attach(11);
  
  pinMode(pinButtonInc, INPUT);
  pinMode(pinButtonDec, INPUT);

  Serial.begin(38400);
  Serial.println("initializing");
  
}


void loop(){
  
  if( ( millis() - timeButtonPressed ) > precision ){
    timeButtonPressed = millis();
    stateButtonInc = digitalRead(pinButtonInc);
    stateButtonDec = digitalRead(pinButtonDec);
    if( stateButtonInc == HIGH ) value = min( value+1, max_value );
    if( stateButtonDec == HIGH ) value = max( value-1, min_value );
  }

  valuePot_1_3 = map(analogRead(pinPot_1_3), 0, 1023, -5, 5);
  valuePot_2_4 = map(analogRead(pinPot_2_4), 0, 1023, -5, 5);

  // potser cal canviar aquests signes
  // aquests valors poden sortir del rang min-max establert
  value1 = value + valuePot_1_3;
  value2 = value + valuePot_2_4;
  value3 = value - valuePot_1_3;
  value4 = value - valuePot_2_4;
  
  ESC1.write(value1);
  ESC2.write(value2);
  ESC3.write(value3);
  ESC4.write(value4);
  
}
