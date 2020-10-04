#include <Arduino.h>
#include <Servo.h>
#include <Ticker.h>

int SERVO_NUM = 3;

Servo jr_servo;

//Settings
const unsigned long period = 150 * 1000; //sec(150sec = 2min30sec)
const uint32_t init_angle = 92;          //degree
const uint32_t push_angle = 83;          //degree

void push_button();

Ticker timer1(push_button, period, 0, MICROS);

void setup()
{
  jr_servo.attach(SERVO_NUM);
  Serial.begin(115200);
  jr_servo.write(init_angle);
  timer1.start();
  timer1.interval(150000);

  delay(2000);

  push_button();
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