
#include <Wire.h>

float rpm = 0;

int pid;
unsigned long millisBefore;
volatile int holes;

void setup()
{
  Serial.begin(115200);
  pinMode(PA0, INPUT);
  attachInterrupt(digitalPinToInterrupt(PA0), count, FALLING);
  delay(1000);
}

void loop()
{
  if (millis() - millisBefore > 60000) {
    rpm = holes / 12.0;
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
