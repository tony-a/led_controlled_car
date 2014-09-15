// tonys_motor.ino
// based on: http://arduino.cc/en/Hacking/LibraryTutorial

#include <Motor.h>

Motor motor(12, 3, 9);

void setup() {



}

void loop() {
	motor.move('forward', 50);


}

