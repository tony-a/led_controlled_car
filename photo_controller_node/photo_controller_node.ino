/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
//2014 - TMRh20 - Updated along with Optimized RF24 Library fork
 */

/**
 * Example for Getting Started with nRF24L01+ radios. 
 */


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(9, 10);

byte addresses[][6] = {"1Node","2Node"};

// Photoresistors variables 
int lightPin1 = 2; 
int lightPin2 = 3;
double sensorValue1;
double sensorValue2;


void setup() {

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging

  printf("*** CHANGING TO TRANSMIT ROLE *** \n\r");
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);

}

void loop(void){

  radio.stopListening();                                    // First, stop listening so we can talk.
  
  printf("Now sending \n\r");

  unsigned long time = micros();    // Take the time, and send it.  This will block until complete
  int dir = 1; 
   if (!radio.write( &dir, sizeof(int) )){  printf("failed.\n\r");  }
      
  radio.startListening();                                    // Now, continue listening
  
  unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
  
  while ( ! radio.available() ){                             // While nothing is received
    if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
        timeout = true;
        break;
    }      
  }
      
  if ( timeout ){                                             // Describe the results
      printf("Failed, response timed out.\n\r");
  }else{
      unsigned long got_time;         // Grab the response, compare, and send to debugging spew
      int got_dir;
      radio.read( &got_dir, sizeof(int) );

      // Spew it
      printf("Sent %d, Got response %d. \n\r",dir,got_dir);
  }

  // Try again 1s later
  delay(1000);
}


void find_direction(float sensorValue1, float sensorValue2){
  // return values: stop, forward, backward
  int delta_to_stop = 60;
  float intensity_difference = sensorValue1 - sensorValue2;
  if(abs(intensity_difference) < delta_to_stop){
    int dir = 0;
  }
  else if (sensorValue1 > sensorValue2){
    int dir = 1;
  }
  else {
    int dir = 2;
  }

}
