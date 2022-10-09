
#include <Wire.h>

float rpm = 0;

int pid;
unsigned long millisBefore;
volatile int holes; 
float pickup = 1.0; //number of pick-up sensors

void setup()
{
  Serial.begin(115200);
  pinMode(PA0, INPUT);
  attachInterrupt(digitalPinToInterrupt(PA0), count, FALLING);//In Love <3
  delay(1000);
}

void loop()
{
  if (millis() - millisBefore > 1000) {
    rpm = (holes / pickup)*60;
    holes = 0;
    millisBefore = millis();
  }
  
  Serial.print("RPM :");
  Serial.println(rpm);  
  delay(200);
}

void count() {
  holes++;
}
