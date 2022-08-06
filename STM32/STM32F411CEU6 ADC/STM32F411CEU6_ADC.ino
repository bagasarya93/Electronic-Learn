/*
 * Program ADC fot STM32
 * Programming STM32F411CEU6 ADC using Arduino IDE
 * https://diystron.blogspot.com/2022/08/programming-stm32f411ceu6-adc-using.html
 */

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(PA0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
