/*
  using two photoresistors to follow a light source.
  
  Tony Askar
  9/1/2014
  link: http://playground.arduino.cc/Learning/PhotoResistor
  
 */

int lightPin1 = 0;  //define a pin for Photo resistor
int lightPin2 = 1;
double sensorValue1;
double sensorValue2;


void setup(){
  Serial.begin(9600);
}


void loop(){
  sensorValue1 = analogRead(lightPin1);
  sensorValue2 = analogRead(lightPin2);
  
  Serial.print("sensor 1: ");
  Serial.println(sensorValue1);
  Serial.print("sensor 2: ");
  Serial.println(sensorValue2);
  Serial.println();

	//char direction_to_move = find_direction(sensorValue1, sensorValue2);
	find_direction(sensorValue1, sensorValue2);
	// move_car(direction_to_move);
  delay(1000);
}

void find_direction(float sensorValue1, float sensorValue2){
	// return values: stop, forward, backward
	int delta_to_stop = 35;
	float intensity_difference = sensorValue1 - sensorValue2;
	if(abs(intensity_difference) < delta_to_stop){
		Serial.println("stop");
	}
	else if (sensorValue1 > sensorValue2){
		Serial.println("forward");
	}
	else {
		Serial.println("backward");
	}


}














