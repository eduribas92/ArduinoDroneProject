// INCLUDES
#include <Servo.h> // ESC controller

// Serial variables
String incomingString;
int counter_values = 0;
bool new_value = true;

// ESC variables
Servo ESC1, ESC2, ESC3, ESC4;
int ESC1_pin = 6, ESC2_pin = 9, ESC3_pin = 10, ESC4_pin = 11;
int ESC_value = 0, ESC1_value = 0, ESC2_value = 0, ESC3_value = 0, ESC4_value = 0;
const int ESC_max_value = 90, ESC_min_value = 0;


//----------------------------------------------------------------------------------


// INITIAL SETUP
void setup() {

  // Serial initialization
  Serial.begin(9600);
  Serial.println("initializing");
  
  // ESC definitions
  ESC1.attach(ESC1_pin);
  ESC2.attach(ESC2_pin);
  ESC3.attach(ESC3_pin);
  ESC4.attach(ESC4_pin);

}


// MAIN LOOP
void loop() {
  
  read_input_and_set_output();
  
  if(new_value)
    ESC_set_values();
    
  delay(10);
}


//----------------------------------------------------------------------------------

// FUNCTIONS

void read_input_and_set_output(){

  // read values from Serial
  if(Serial.available() > 0){
    char ch = Serial.read();
    if (ch != 10){ // If ch isn't a newline (linefeed) character, we will add the character to the incomingString
      incomingString += ch;
    }else{
      counter_values =  (counter_values + 1) % 4;
      ESC_value = incomingString.toInt();
      Serial.print(ESC_value);
      Serial.print(" ");
      switch(counter_values){        
        case 1:
          ESC1_value = min(max(ESC_value, ESC_min_value), ESC_max_value);    
          break;       
        case 2:
          ESC2_value = min(max(ESC_value, ESC_min_value), ESC_max_value);
          break;        
        case 3:
          ESC3_value = min(max(ESC_value, ESC_min_value), ESC_max_value);
          break;
        case 0:
          ESC4_value = min(max(ESC_value, ESC_min_value), ESC_max_value);
          Serial.print("\n");
          new_value = true;
          break;      
      }
      incomingString = "";
    }
  }
  
  return;
}


void ESC_set_values(){//int value1, int value2, int value3, int value4){

  new_value = false;

  ESC1.write(ESC1_value);
  ESC2.write(ESC2_value);
  ESC3.write(ESC3_value);
  ESC4.write(ESC4_value);

  Serial.print("(");
  Serial.print(ESC1_value);
  Serial.print(",");
  Serial.print(ESC2_value);
  Serial.print(",");
  Serial.print(ESC3_value);
  Serial.print(",");
  Serial.print(ESC4_value);
  Serial.print(")\n");  

  return;
}
