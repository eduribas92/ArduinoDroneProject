
const int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int senVal = 0, senMax=0, senMin=999999;  // variable to store the value coming from the sensor
int senInt;

unsigned long i=0, n=500, time, k;
double LT;
boolean sensor;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  while(millis()<5000)
  {
      senVal=analogRead(sensorPin);
      if(senVal>senMax) senMax=senVal;
      if(senVal<senMin) senMin=senVal;    
  }
  Serial.print("Min:");
  Serial.print(senMin);
  Serial.print("Max:");
  Serial.println(senMax);
  Serial.print("Mean:");
  senInt=(senMax+senMin)/2;
  Serial.println(senInt);
  i=0;
  k=0;
  time=millis(); 
}

void loop()
{
  if(i==n)
  {
    LT=millis()-time;
    LT=2*LT/n;
    Serial.print("Periode:");
    Serial.println(LT);
    Serial.print("freq:");
    Serial.println(1000./LT);
    i=0;
    k=0;
    time=millis();    
  }
  // read the value from the sensor:
  senVal = analogRead(sensorPin);
  if( senVal > senInt )
  {
    if(sensor)
    {
      k++;
    }
    else
    {
      //Serial.println(k);
      k=0;
      sensor=!sensor;
      i++;
    }
    
  }
  else
  {
    if(sensor)
    {
      //Serial.println(k);
      k=0;
      sensor=!sensor;
      i++;
    }
    else
    {
      k++;
    }
  }
  
}
