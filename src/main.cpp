
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "message_handler.h"
#include "motor_driver.h"

using newborn::MessageHandler;
using newborn::MessageTag;
using newborn::MotorConfig;
using newborn::MotorDriver;

MessageHandler<26> handler(5, 2);

Adafruit_PWMServoDriver servo_driver;

MotorConfig motor_left = {3, 4, 10};
MotorConfig motor_right = {6, 7, 11};
MotorDriver motor_driver(motor_left, motor_right);

void setup()
{
  Serial.begin(9600);

  // set up servo
  Wire.setClock(400000);
  servo_driver.begin();
  servo_driver.setPWMFreq(50);
  // default servo state
  servo_driver.writeMicroseconds(0, 1500);
  servo_driver.writeMicroseconds(1, 1500);
  servo_driver.writeMicroseconds(2, 1500);
  servo_driver.writeMicroseconds(10, 1500);
  servo_driver.writeMicroseconds(11, 1500);

  // configure servo behavior
  handler.SetUp(115200);
  handler.OnKeyUp(MessageTag('q'), [] {
    // It seems unexpected sometimes.
    static_cast<void (*)()>(0)();
  });
  handler.OnKeyUp(MessageTag('1'), [] {
    servo_driver.writeMicroseconds(0, 1575);
    servo_driver.writeMicroseconds(2, 1575);
    servo_driver.writeMicroseconds(1, 1575);
  });
  handler.OnKeyUp(MessageTag('2'), [] {
    servo_driver.writeMicroseconds(0, 1435);
    servo_driver.writeMicroseconds(2, 1435);
    servo_driver.writeMicroseconds(1, 1435);
  });
  handler.OnKeyUp(MessageTag('3'), [] {
    servo_driver.writeMicroseconds(0, 1500);
    servo_driver.writeMicroseconds(2, 1500);
    servo_driver.writeMicroseconds(1, 1500);
  });
  handler.OnKeyUp(MessageTag('5'), [] {
    servo_driver.writeMicroseconds(10, 1575);
  });
  handler.OnKeyUp(MessageTag('6'), [] {
    servo_driver.writeMicroseconds(10, 1425);
  });
  handler.OnKeyUp(MessageTag('7'), [] {
    servo_driver.writeMicroseconds(10, 1500);
  });
  handler.OnKeyUp(MessageTag('9'), [] {
    servo_driver.writeMicroseconds(11, 1575);
  });
  handler.OnKeyUp(MessageTag('a'), [] {
    servo_driver.writeMicroseconds(11, 1425);
  });
  handler.OnKeyUp(MessageTag('b'), [] {
    servo_driver.writeMicroseconds(11, 1500);
  });

  // set up motor driver
  motor_driver.SetUp();
  // configure motor behavior
  handler.OnKeyDown(MessageTag('l'), [] {
    motor_driver.MoveForward();
  });
  handler.OnKeyUp(MessageTag('l'), [] {
    motor_driver.FastStop();
  });

  handler.OnKeyDown(MessageTag('m'), [] {
    motor_driver.MoveBack();
  });
  handler.OnKeyUp(MessageTag('m'), [] {
    motor_driver.FastStop();
  });

  handler.OnKeyDown(MessageTag('n'), [] {
    motor_driver.TurnLeft();
  });
  handler.OnKeyUp(MessageTag('n'), [] {
    motor_driver.FastStop();
  });

  handler.OnKeyDown(MessageTag('o'), [] {
    motor_driver.TurnRight();
  });
  handler.OnKeyUp(MessageTag('o'), [] {
    motor_driver.FastStop();
  });
}

void loop()
{
  handler.Update();
}
