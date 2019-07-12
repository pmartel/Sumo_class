#include <NewPing.h>

NewPing Sonar(5,6, 60);
void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool obstacle_mode = true;
  // put your main code here, to run repeatedly:
  Serial.println(Sonar.ping_cm());
  if (digitalRead(13) == HIGH && digitalRead(12) == HIGH && obstacle_mode == true){
    forward(255);
  }
  if (digitalRead(13) == LOW || digitalRead(12) == LOW){
    backward(200);
    delay(1000);
    Left(255);
    delay(500);
    if (obstacle_mode == true){
      obstacle_mode = false;
    }
    if (obstacle_mode == false){
      obstacle_mode = true; 
    }
  }
  if (obstacle_mode == false){
    Left(150);
    if (Sonar.ping_cm() <= 30 && Sonar.ping_cm() != 0){
      forward(255);
    }
  }
}
void backward(int Speed){
  analogWrite(11, Speed);
  analogWrite(10, 0);
  analogWrite(9, Speed);
  analogWrite(8, 0);
}
void forward(int Speed){
  analogWrite(11, 0);
  analogWrite(10, Speed);
  analogWrite(9, 0);
  analogWrite(8, Speed);
}
void Left(int Speed){
  analogWrite(11, Speed);
  analogWrite(10, 0);
  analogWrite(9, 0);
  analogWrite(8, Speed);
}
void Stop()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  analogWrite(8, 0);
}

