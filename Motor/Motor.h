/* 
	My Motor test library.
	Created by Tony B. Askar, Septemeber 10, 2014.
	// based on: http://arduino.cc/en/Hacking/LibraryTutorial
*/

#ifndef Motor
#define Motor


#include "Arduino.h"

class Motor
{
	public:
		Motor(int direction_pin); //, int speed_pin, int brake_pin);
//		void Direction(int pin);
//		void Speed(int pin);
//		void Brake(int pin);
//		release_break();
//		go_forward();
//		go_backward();
	private:
		int _direction_pin;
		int _speed_pin;
		int _brake_pin;
		bool _brake_on;
};


#endif
