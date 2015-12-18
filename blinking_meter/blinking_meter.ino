
int led = 13;
double meanT=0, T;
long int n=50000, i=0;
unsigned long time, time1;
boolean lout = false;
int j=0;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600); 
}

// the loop routine runs over and over again forever:
void loop() {
  
  if(i==n)
  {
    
    time1=time;
    time=millis();
    meanT=(time-time1)*1./n;
    
    Serial.print("T:");
    Serial.print(2*meanT);
    Serial.print("f:");
    Serial.println(1000/(meanT*2));
    
    i=0;
    time1=millis();
    i++;
  }
  else
  {
    i++;
  }
  
  
  lout=!lout;
  digitalWrite(led, lout);   // turn the LED on (HIGH is the voltage level)         // wait for a second

  //delay(1);
  
}
