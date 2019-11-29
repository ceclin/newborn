#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "message_handler.h"

using newborn::MessageHandler;
using newborn::MessageTag;

MessageHandler<26> handler(5, 2);

Adafruit_PWMServoDriver servo_driver;

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

  // set up bluetooth message handler
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
    servo_driver.writeMicroseconds(0, 1425);
    servo_driver.writeMicroseconds(2, 1400);
    servo_driver.writeMicroseconds(1, 1425);
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
}

void loop()
{
  handler.Update();
}
