// FALL 2025
// Tufts EWB Malawi Project 
// DISH Technical Group

// Include NewPing Library
#include "NewPing.h"

// sd card stuff
#include <SPI.h>
#include <SD.h>
File myFile;

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 7
#define ECHO_PIN 8

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400	

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Current "Tank" measurements 
int top_diameter = 28.3;
int bottom_diameter = 25;
int diameter = (top_diameter + bottom_diameter) / 2;
int BUCKET_HEIGHT = 34.5;

void setup() {
  Serial.begin(9600);
  // For future dynamic changing of bucket size
  // Serial.print("Enter the diameter of the tank:");
  // diameter = Serial.parseInt();
  // Serial.print(diameter);
  // // Serial.print("Enter the max height of the tank:");
  // BUCKET_HEIGHT = Serial.parseInt();
  // Serial.print(diameter);

  // init sd card
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("harrison.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Readings:");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  Serial.println("After writing testing 1, 2, 3 to the file!");
  // re-open the file for reading:
  // myFile = SD.open("test.txt");
  // if (myFile) {
  //   Serial.println("test.txt:");

  //   // read from the file until there's nothing else in it:
  //   while (myFile.available()) {
  //     Serial.write(myFile.read());
  //   }
  //   // close the file:
  //   myFile.close();
  // } else {
  //   // if the file didn't open, print an error:
  //   Serial.println("error opening test.txt");
  // }
}

void loop() {
  myFile = SD.open("harrison.txt", FILE_WRITE);

  int distance = sonar.ping_cm();
  Serial.println("working");
  Serial.println(distance);
  if (myFile) {
    myFile.println(distance);
    myFile.println(" cm");
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // Dynamically calculate water volume
  // int water_volume = PI * sq(diameter / 2) * (BUCKET_HEIGHT - distance);
  // Serial.print("Water volume = ");
  // Serial.print(water_volume);
  // Serial.println(" mL");
	delay(5000);
}