/*
  adding turn functionality
  using three photoresistors to follow a light source.
  
  Tony Askar
  10/4/2014
  link: http://playground.arduino.cc/Learning/PhotoResistor
  
 */
 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(9, 10);

byte addresses[][6] = {"1Node","2Node"};

// Photoresistors variables 
int sensorX1 = 5;  //define a pin for Photo resistor
int sensorX2 = 4;
int sensorY = 3;
double valueX1;
double valueX2;
double valueY;


void setup(){
//  Serial.begin(9600);
  
  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  
  radio.startListening();                 // Start listening
//  radio.printDetails();                   // Dump the configuration of the rf unit for debugging

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  radio.stopListening();                  // now stop listening so we can talk.
}

void loop(){  
  valueX1 = analogRead(sensorX1);  // Top left corner of T
  valueX2 = analogRead(sensorX2);  // Top right corner of T
  valueY = analogRead(sensorY);    // Bottom of T
  
//  Serial.print("sensor X1: ");
//  Serial.println(valueX1);
//  Serial.print("sensor X2: ");
//  Serial.println(valueX2);
//  Serial.print("sensor Y: ");
//  Serial.println(valueY);
//  Serial.println();

  double top_average = (valueX1 + valueX2)/2.0;
//  Serial.print("average: ");
//  Serial.println(top_average);
  
  int f_dir = find_direction(valueY, top_average);
  int t_dir = find_horizontal_direction(valueX1, valueX2);
  
  int dir_to_send = (f_dir * 10) + t_dir;
  
  radio.write( &dir_to_send, sizeof(int) );

  delay(1000);
//  Serial.println("-----------------");

}

int find_direction(float sensorValue1, float sensorValue2){
  // return values: stop, forward, backward
  int return_dir;
  int delta_to_stop = 60;
  float intensity_difference = sensorValue1 - sensorValue2;
  
  if(abs(intensity_difference) < delta_to_stop){
//    Serial.println("stop");
    return_dir = 0;
  }
  else if (sensorValue1 > sensorValue2){
//    Serial.println("forward");
    return_dir = 1;  
  }
  else {
//    Serial.println("backward");
    return_dir = 2;  
  }  
  return return_dir;
}


int find_horizontal_direction(double valueX1, double valueX2){
  int delta_to_go_straight = 60;
  double intensity_difference = valueX1 - valueX2;
  int turn_dir;
  
  if (abs(intensity_difference) < delta_to_go_straight) {
//    Serial.println("going straight");
    turn_dir = 0;
  }
  else if (valueX1 < valueX2) {
//    Serial.println("turning left");
    turn_dir = 1;
  }
  else {
//    Serial.println("turning right");
    turn_dir = 2;
  }
  return turn_dir;
}

