#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;
MPU6050 accelgyro(0x68);

int16_t axi, ayi, azi;
double gx, gy, gz;
double factConv;
double ax, ay, az;
double vx, vy, vz;
double px, py, pz;

unsigned long int ptime;
double dtime;

int i=0, j=0;
unsigned int icycle, tcycle;


// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO


void setup()
{
	// join I2C bus (I2Cdev library doesn't do this automatically)
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
		Wire.begin();
	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
		Fastwire::setup(400, true);
	#endif
	
	Serial.begin(38400);
	Serial.println("Inici");
	accelgyro.initialize();
	
	// verify connection
	Serial.println("Testing device connections...");
	Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
	
	Serial.println("Calibrant: g");
	delay(1000);
	gx=0.;
	gy=0.;
	gz=0.;
	axi=0;
	ayi=0;
	azi=0;
	for(i=0; i<100; i++)
	{
		accelgyro.getAcceleration(&axi, &ayi, &azi);
		gx+=axi/100.;
		gy+=ayi/100.;
		gz+=azi/100.;
		
	}
	//sqrt(gx*gx+gy*gy+gz*gz)==g==9.81m/s²
	
	//Unitats m/s²
	factConv=9.81/sqrt(gx*gx+gy*gy+gz*gz); 
	ax=0.; ay=0.; az=0.;
	vx=0.; vy=0.; vz=0.;
	px=0.; py=0.; pz=0.;
	ptime=0; dtime=0.;
	
	icycle=0; tcycle=0;
	
	Serial.println("Començant loop:");
	ptime=micros();
	tcycle=millis();
}


void loop()
{
	while( (micros()-ptime) < 10 ) //aqui exigim que cada cicle sigui com a mínim de 10 µs
	{
		
	}
 
	dtime=(micros()-ptime)*1.e-6; //dtime conté la duració del pas en s
	ptime=micros();
	
	//Unitats m/s²
	accelgyro.getAcceleration(&axi, &ayi, &azi);
	ax=(axi-gx)*factConv;
	ay=(ayi-gy)*factConv;
	az=(azi-gz)*factConv;
	
	vx=vx+ax*dtime;
	vy=vy+ay*dtime;
	vz=vz+az*dtime;
	
	px=px+vx*dtime;
	py=py+vy*dtime;
	pz=pz+vz*dtime;
	
	if( millis()-tcycle > 500 ) //Cada mig segon printem els valors de accel. velocitat i posició
	{
		Serial.print("a=\t");Serial.print(ax, 2);Serial.print("\t");Serial.print(ay, 2);Serial.print("\t");Serial.print(az, 2);Serial.println("\t");
		Serial.print("v=\t");Serial.print(vx, 2);Serial.print("\t");Serial.print(vy, 2);Serial.print("\t");Serial.print(vz, 2);Serial.println("\t");
		Serial.print("p=\t");Serial.print(px, 2);Serial.print("\t");Serial.print(py, 2);Serial.print("\t");Serial.print(pz, 2);Serial.println("\t");
		Serial.println("-----------------------------------------------------")
		tcycle=millis();
	}
}