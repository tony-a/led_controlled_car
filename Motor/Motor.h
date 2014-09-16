/* 
	My Motor test library.
	Created by Tony B. Askar, Septemeber 10, 2014.
	// based on: http://arduino.cc/en/Hacking/LibraryTutorial
*/

#ifndef Motor_H
#define Motor_H


#include "Arduino.h"

class Motor
{
	public:
		Motor(int direction_pin, int speed_pin, int brake_pin);
		void release_brake();
		void move(char dir, int speed);
		void stop();
	private:
		int _direction_pin;
		int _speed_pin;
		int _brake_pin;
};


#endif
