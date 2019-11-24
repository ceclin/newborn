#include <Arduino.h>
#include <Servo.h>

#include "message_handler.h"

using newborn::MessageHandler;
using newborn::MessageTag;

MessageHandler<26> handler(4, 2);

Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(9);
  servo.write(90);
  handler.SetUp(115200);
  handler.OnKeyDown(MessageTag('1'), [] {
    servo.write(86);
  });
  handler.OnKeyDown(MessageTag('2'), [] {
    servo.write(90);
  });
  handler.OnKeyDown(MessageTag('3'), [] {
    servo.write(100);
  });
  handler.OnKeyDown(MessageTag('4'), [] {
    servo.write(90);
  });
}

void loop()
{
  handler.Update();
}
