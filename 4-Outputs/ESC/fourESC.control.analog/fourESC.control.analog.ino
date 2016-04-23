#include <Servo.h>

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int value = 0;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
const int max_value = 70;
const int min_value = 0;

const int pinButtonInc = 13, pinButtonDec = 12;
int stateButtonInc = 0, stateButtonDec = 0;
unsigned long timeButtonPressed = 0;
const int precision = 200; // (ms)

int value_pot_1_3 = 0;
int value_pot_2_4 = 0;


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

  value_pot_1_3 = map(analogRead(A0), 0, 1023, -5, 5);
  value_pot_2_4 = map(analogRead(A1), 0, 1023, -5, 5);

  // potser cal canviar aquests signes
  // aquests valors poden sortir del rang min-max establert
  value1 = value + value_pot_1_3;
  value2 = value + value_pot_2_4;
  value3 = value - value_pot_1_3;
  value4 = value - value_pot_2_4;
  
  ESC1.write(value1);
  ESC2.write(value2);
  ESC3.write(value3);
  ESC4.write(value4);
  
}
