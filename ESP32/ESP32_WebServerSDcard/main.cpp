#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define SD_CS 5

//Menulis File
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

//Baca File
void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

//Menulis Kembali File yang sudah ada
void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SD.begin(SD_CS);
  if (!SD.begin(SD_CS)) {
    Serial.println("Gagal Memuat Kartu SD");
    return;
  }

  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("Tidak Ada Kartu SD");
    return;
  }
  Serial.println("Menginisialisasi kartu SD...");
  
  writeFile(SD, "/RobotikID.txt", "Hai, Ini Robotik Indonesia ");
  /*
  Menyimpan Tulisan atau String "Hai, Ini Robotik Indonesia "
  pada file yang bernama RobotikID.txt
  */ 

  readFile(SD, "/RobotikID.txt");
  /*
  Membaca Tulisan atau String atau nilai yang berada
  pada file yang bernama RobotikID.txt
  */ 
 
  appendFile(SD, "/RobotikID.txt", "Kita akan belajar bersama ");
  /*
  Menambahkan String "Kita akan belajar bersama "
  pada file yang bernama RobotikID.txt
  Sehingga akan menjadi "Hai, Ini Robotik Indonesia Kita akan belajar bersama"
  */ 
  
  readFile(SD, "/RobotikID.txt");

}

void loop() {
  // put your main code here, to run repeatedly:
}