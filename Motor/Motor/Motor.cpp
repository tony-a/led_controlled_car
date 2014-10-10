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
    int _direction_facing = 0;  
}


void Motor::move(int dir, int speed){
    // dir = 1  => forward
    // dir = 2  => backward
    stop();
    if (dir == 2){
        digitalWrite(_direction_pin, HIGH);
        release_brake();
        analogWrite(_speed_pin, speed);
    }
    else if (dir == 3){
        digitalWrite(_direction_pin, LOW);
        release_brake();
        analogWrite(_speed_pin, speed);
    }
    else{        //this last else clause is unnecessary.
        stop();
    }
}

void Motor::stop() {
    digitalWrite(_brake_pin, HIGH);
}

void Motor::release_brake() {
    digitalWrite(_brake_pin, LOW);
}

void Motor::turn(int dir_to_turn) {
    // dir_to_turn = 0 => no turn, go straight by applying breaks, so motor doesn't spin
    // dir_to_turn = 1 => turn right. release break, then turn motor
    // dir_to_turn = 2 => turn left. release break, then turn motor opposite way.
    static int _direction_facing = 0;

    if (dir_to_turn == 1){
        _direction_facing = 1;
        stop();
    }
    else if (dir_to_turn ==  2 && _direction_facing == 2){
        // pass. keep facing right.
        _direction_facing = 2;
    }
    else if (dir_to_turn ==  2){
        _direction_facing = 2;
        move(2, 200);

    }
    else if (dir_to_turn == 3 && _direction_facing == 3){
        // pass. keep facing left.
        _direction_facing = 3;
    }
    else if (dir_to_turn == 3){
        _direction_facing = 3;
        move(3, 200);
    }
    else{
        _direction_facing = 1;
        stop();
    }

}








