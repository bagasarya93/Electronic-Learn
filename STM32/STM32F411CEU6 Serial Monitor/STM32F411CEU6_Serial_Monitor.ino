/* 
 * Program Serial Monitor for STM32
 * Programming STM32F411CEU6 Serial Monitor using Arduino IDE
 *
 *
 */

void setup() {
  Serial.begin(115200);  //memulai serial dengan baudrate 115200
}

void loop() {
  Serial.println("Hello World from DIYSTRON");  //menulis kata ke serial monitor
  delay(1000);  //delay 1 detik
}
