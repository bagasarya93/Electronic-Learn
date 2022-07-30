/* 
 * Program Serial Monitor for STM32
 * Programming STM32F411CEU6 Serial Monitor using Arduino IDE
 *
 *
 */

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hello World from DIYSTRON");
  delay(1000);
}
