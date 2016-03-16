double previousTime = 0;
long int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  if(counter == 1000000){
    Serial.println((((double)millis()-previousTime)));
    counter = 0;
    previousTime = millis();
  }
  counter ++;
}
