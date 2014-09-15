// tonys_motor.ino
// based on: http://arduino.cc/en/Hacking/LibraryTutorial

#include <tonys_motor.h>

Motor motor(12, 3, 9);

void setup() {



}

void loop() {
	motor.move('forward', 50);


}

