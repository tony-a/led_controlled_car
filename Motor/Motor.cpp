// based on: http://arduino.cc/en/Hacking/LibraryTutorial


#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int direction_pin, int speed_pin, int brake_pin)
{
        pinMode(direction_pin, OUTPUT);
	pinMode(speed_pin, OUTPUT);
	pinMode(brake_pin, OUTPUT);
  	_direction_pin = direction_pin;
	_speed_pin = speed_pin;
        _brake_pin = brake_pin;	
	
}

void Motor::move(char direction, int speed){
	//release_brake;
	if (direction == 'forward'){
		digitalWrite(_direction_pin, HIGH);
		analogWrite(_speed_pin, speed);
	}
	else if (direction == 'backward') {
		digitalWrite(_direction_pin, LOW);
		analogWrite(_speed_pin, speed);
	}
}

void Motor::stop() {
	digitalWrite(_brake_pin, HIGH);
}

void Motor::release_brake() {
	digitalWrite(_brake_pin, LOW);
}

// void Motor::set_brake()
// {
// 	digitalWrite(_brake_pin, HIGH);
// }
