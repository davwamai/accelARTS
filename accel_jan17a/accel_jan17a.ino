#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "SD.h"

Adafruit_MPU6050 mpu;
int CS = 10;
File file; 

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  pinMode(CS, OUTPUT);

  if(!SD.begin(10)){
    Serial.println("SD card initialization failed");
    while(1);
  }
  Serial.println("successfully initialized SD card");
  
  //Try to initialize
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found");

  //documentation is unclear about this member func, 
  //8G outputs most normal values 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  // Get new sensor events with the readings
  // expects three params for some reason  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //prints to file
  file =  SD.open("data.txt", FILE_WRITE);
  if(file){
    file.print(a.acceleration.x); 
    file.print("\t");
    file.print(a.acceleration.y); 
    file.print("\t");
    file.print(a.acceleration.z);
    file.close();
  } else {
    Serial.println("Could not open file...");
  }

  // prints to serial [xm/s^2, ym/s^2, zm/s^2]
  Serial.print(a.acceleration.x);
  Serial.print("\t");
  Serial.print(a.acceleration.y);
  Serial.print("\t");
  Serial.println(a.acceleration.z);
  delay(100);
}