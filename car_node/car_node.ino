/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
//2014 - TMRh20 - Updated along with Optimized RF24 Library fork
 */

/**
 * Example for Getting Started with nRF24L01+ radios. 
 * Note: For a more efficient call-response scenario see the GettingStarted_CallResponse.ino example.
 * Note: When switching between sketches, the radio may need to be powered down to clear settings that are not "un-set" otherwise
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <Motor.h>

Motor motor(2, 3, 9);

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(5, 6);

byte addresses[][6] = {"1Node","2Node"};

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

  printf("*** CHANGING TO RECEIVE ROLE ***\n\r");
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);

}

void loop(void){
 
  if( radio.available()){
    int dir;                              // variable for direction to move 
    while (radio.available()) {            // While there is data ready
      radio.read( &dir, sizeof(int) );             // Get the payload
    }    
    printf("Got the following direction: %d \n\r",got_dir);
    motor.move(dir, 100);
  }

  

}
