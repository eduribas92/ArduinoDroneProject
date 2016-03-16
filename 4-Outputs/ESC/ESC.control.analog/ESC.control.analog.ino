#include <Servo.h>
 
Servo esc;
int potencia = 0;
int potenciaInc = 341;
 
void setup(){
  esc.attach(10);
  Serial.begin(9600);
}
 
void loop(){
  
  int potenciaPWM = map(potencia, 0, 1023, 0, 179);
  esc.write(potenciaPWM);
  potencia = potencia + potenciaInc;  
  if (potencia == 0 || potencia == 1023) {
    potenciaInc = - potenciaInc;
  }
  Serial.println(potencia);
  delay(5000);
}
