#include <Arduino.h>
#include <Servo.h>
#include <Ticker.h>

int SERVO_NUM = 3;

Servo jr_servo;

//Settings
//int period = 10; //sec(2min30sec)
int period = 150; //sec(2min30sec)
int init_angle = 92;//degree
int push_angle = 83;//degree

void push_button();

Ticker timer1(push_button, 1000 * period);

void setup()
{
  jr_servo.attach(SERVO_NUM);
  Serial.begin(115200);
  jr_servo.write(init_angle);
  timer1.start();
}

void loop()
{
  timer1.update();
}

void push_button()
{
  Serial.print("Push Button! Count = ");
  Serial.println(timer1.counter());

  jr_servo.write(push_angle);
  delay(100);
  jr_servo.write(init_angle);
}