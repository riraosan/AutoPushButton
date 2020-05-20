#include <Arduino.h>
#include <Servo.h>

int IR_SENSOR = 0;
int SERVO_NUM = 3;
int intSensorResult = 0;

Servo myservo;            

void setup() {
  myservo.attach(SERVO_NUM);
  pinMode(0, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  intSensorResult = analogRead(IR_SENSOR);

  if(intSensorResult > 380){
    myservo.write(120);
    delay(800);                  
  }else{
    myservo.write(0);
  }  
}