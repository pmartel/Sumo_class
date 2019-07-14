#include <NewPing.h>
const int left_forward = 10;//while pwm is high moves left motor forward
const int left_backward = 11;//while pwm is high moves left motor backward
const int right_forward = 9;//while pwm is high moves right motor forward
const int right_backward = 8;//while pwm is high moves right motor backward
const int left_side = 13;//left edge sensor
const int right_side = 12;//right edge sensor
NewPing Sonar(5,6, 60);
void setup() {
  // put your setup code here, to run once:
  //Pin setup is declared here.
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
  pinMode(left_side, INPUT);
  pinMode(right_side, INPUT);
  Serial.begin(9600);
}
bool obstacle_mode = true;// Obstacle mode is declared true by default until an edge is reached where it is inverted from there.
int duration = 50;// Duration of the robots scan for other nearby robots is decalred here.
void loop() {
 
  int  dist;// Sonar.ping_cm() is this variables near equivilent.
  // put your main code here, to run repeatedly:
  Serial.println(Sonar.ping_cm());// Prints the robots sonar readings for debugging

  //If the robot is in the near center of the arena and obstacle mode is true the robot moves forward.
  if (digitalRead(left_side) == HIGH && digitalRead(right_side) == HIGH && obstacle_mode == true){
    forward(255);
  }
  //If the robot is on an edge of the arena obstacle mode is inverted, the robot moves backwards, and then turns left.
  if (digitalRead(left_side) == LOW || digitalRead(right_side) == LOW){
    backward(200);
    delay(1000);
    Left(255);
    delay(500);
    if (obstacle_mode == false){
      obstacle_mode = true;
    }
    else{
      obstacle_mode = false; 
    }
  }
  //if obstacle mode is false robot scans the arena for another bot. The duration of the scan is defined above the loop. 
  if (obstacle_mode == false){
    Left(255); 
    delay(15);
    Stop();
    delay(30);
    duration -= 1;
    dist= Sonar.ping_cm();
    Serial.println(dist);
    if (dist <= 30 && dist != 0 || duration <= 0){//if the scan turns up something obstacle mode becomes true and the robot will run over the other bot. 
      duration = 50;
      obstacle_mode = true;
    }
  }
}
void backward(int Speed){//backwards code is defined here.
  analogWrite(left_backward, Speed);
  analogWrite(left_forward, 0);
  analogWrite(right_forward, Speed);
  analogWrite(right_backward, 0);
}
void forward(int Speed){//forward code is defined here.
  analogWrite(left_backward, 0);
  analogWrite(left_forward, Speed);
  analogWrite(right_forward, 0);
  analogWrite(right_backward, Speed);
}
void Left(int Speed){//Left code is defined here.
  analogWrite(left_backward, Speed);
  analogWrite(left_forward, 0);
  analogWrite(right_forward, 0);
  analogWrite(right_backward, Speed);
}
void Stop()//robot stop code is defined here if need be
{
  analogWrite(left_backward, 0);
  analogWrite(left_forward, 0);
  analogWrite(right_forward, 0);
  analogWrite(right_backward, 0);
}

