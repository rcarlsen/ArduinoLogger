#include "WProgram.h"
#include "SoftwareSerial.h"

// prototypes
void blink(int n, int d);

// variables
int ledPin = 13; // LED connected to digital pin 13

// analog pins
int photoPin = 0;
int accxPin = 3;
int accyPin = 2;
int acczPin = 1;

long timer = 0;
int sampleRate = 1000;

int initPause = 1; // the open logger needs to initialize for 2 seconds
int initTimer = 3000;

void setup(){
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

	Serial.println("----------------------------");
	Serial.println("Telling Stories with Sensors");
	Serial.println("ITP Spring 2010 | OpenLogger");
	Serial.println("----------------------------");
	
	pinMode(ledPin, OUTPUT);      // sets the digital pin as output
	
	// don't think it's necessary but set the analog pins
	pinMode(photoPin, INPUT);
	pinMode(accxPin, INPUT);
	pinMode(accyPin, INPUT);
	pinMode(acczPin, INPUT);
	
}


void loop(){
	// have to wait for about two seconds before it's ready to log
	if (initPause) {
		if(millis() - timer >= initTimer) {
			// print the headers
			Serial.println("time,accx,accy,accz,light");
			initPause = 0;
		}
	} else {
		if(millis() - timer >= sampleRate) {
			// store the current time
			timer = millis();
			long timestamp = timer;
			
			// read the sensors, then construct the string for output
			int photo = analogRead(photoPin);
			int accx = analogRead(accxPin);
			int accy = analogRead(accyPin);
			int accz = analogRead(acczPin);
			
			// to fast track this, just use the print methods.
			Serial.print(timestamp);
			Serial.print(',');
			Serial.print(accx);
			Serial.print(',');
			Serial.print(accy);
			Serial.print(',');
			Serial.print(accz);
			Serial.print(',');
			Serial.println(photo);
			
			// then blink the led as comfirmation of the reading
			//blink(1, 100); // blink led 2 times, 500 ms interval
		}
	}
}




void blink(int n, int d){
  for (int i=0;i<n;i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(d/2);
    digitalWrite(ledPin, LOW);
    delay(d/2);
  }
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

