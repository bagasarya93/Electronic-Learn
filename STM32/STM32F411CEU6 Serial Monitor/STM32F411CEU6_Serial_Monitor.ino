/* 
 * Program Serial Monitor for STM32
 * Programming STM32F411CEU6 Serial Monitor using Arduino IDE
 * https://diystron.blogspot.com/2022/08/programming-stm32f411ceu6-serial.html
 *
 */

void setup() {
  Serial.begin(115200);  //memulai serial dengan baudrate 115200
}

void loop() {
  Serial.println("Hello World from DIYSTRON");  //menulis kata ke serial monitor
  delay(1000);  //delay 1 detik
}
