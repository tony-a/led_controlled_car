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

void Motor::move(int dir, int speed){
    // dir = 1  => forward
    // dir = 2  => backward
    stop();
    if (dir == 1){
        digitalWrite(_direction_pin, HIGH);
        release_brake();
        analogWrite(_speed_pin, speed);
    }
    else if (dir == 2){
        digitalWrite(_direction_pin, LOW);
        release_brake();
        analogWrite(_speed_pin, speed);
    }
    else{
        stop();
    }
}

void Motor::stop() {
    digitalWrite(_brake_pin, HIGH);
}

void Motor::release_brake() {
    digitalWrite(_brake_pin, LOW);
}
