/*
  adding turn functionality
  using three photoresistors to follow a light source.
  
  Tony Askar
  10/4/2014
  link: http://playground.arduino.cc/Learning/PhotoResistor
  
 */

int sensorX1 = 0;  //define a pin for Photo resistor
int sensorX2 = 1;
int sensorY = 2;
double valueX1;
double valueX2;
double valueY;

void setup(){
  Serial.begin(9600);
}

void loop(){
  valueX1 = analogRead(sensorX1);  // Top left corner of T
  valueX2 = analogRead(sensorX2);  // Top right corner of T
  valueY = analogRead(sensorY);    // Bottom of T
  
  Serial.print("sensor X1: ");
  Serial.println(valueX1);
  Serial.print("sensor X2: ");
  Serial.println(valueX2);
  Serial.print("sensor Y: ");
  Serial.println(valueY);
  Serial.println();

  double top_average = (valueX1 + valueX2)/2.0;
  Serial.print("average: ");
  Serial.println(top_average);
  
  find_direction(valueY, top_average);
  find_horizontal_direction(valueX1, valueX2);
  delay(1000);
  Serial.println("-----------------");

}

void find_direction(float sensorValue1, float sensorValue2){
  // return values: stop, forward, backward
  int delta_to_stop = 30;
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

int find_horizontal_direction(double valueX1, double valueX2){
  int delta_to_go_straight = 60;
  double intensity_difference = valueX1 - valueX2;
  int turn_dir;
  
  if (abs(intensity_difference) < delta_to_go_straight) {
    Serial.println("going straight");
    turn_dir = 0;
  }
  else if (valueX1 < valueX2) {
    Serial.println("turning left");
    turn_dir = 1;
  }
  else {
    Serial.println("turning right");
    turn_dir = 2;
  }
  return turn_dir;
}

