/*
  Photocontroller transmits instruction to car based on led movement over two
  photoresistors. 

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.  

  RF24 transmitter code was based off J. Coliz examples, Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
*/


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(9, 10);

byte addresses[][6] = {"1Node","2Node"};

// Photoresistors variables 
int lightPin1 = 0;  //define a pin for Photo resistor
int lightPin2 = 1;
double sensorValue1;
double sensorValue2;


void setup(){
  Serial.begin(57600);
  
   // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
}


void loop(){
  radio.stopListening();                 // First, stop listening so we can talk.

  sensorValue1 = analogRead(lightPin1);
  sensorValue2 = analogRead(lightPin2);
  
  Serial.print("sensor 1: ");
  Serial.println(sensorValue1);
  Serial.print("sensor 2: ");
  Serial.println(sensorValue2);
  Serial.println();

  int dir = find_direction(sensorValue1, sensorValue2);
  
  Serial.println(dir);
  if (!radio.write( &dir, sizeof(int) )){  printf("failed.\n\r");  }

  delay(200);
}

int find_direction(float sensorValue1, float sensorValue2){
  // return values: stop, forward, backward
  int return_dir;
  int delta_to_stop = 60;
  float intensity_difference = sensorValue1 - sensorValue2;
  
  if(abs(intensity_difference) < delta_to_stop){
    Serial.println("stop");
    return_dir = 0;
  }
  else if (sensorValue1 > sensorValue2){
    Serial.println("forward");
    return_dir = 1;  
  }
  else {
    Serial.println("backward");
    return_dir = 2;  
  }  
  
  return return_dir;
}
