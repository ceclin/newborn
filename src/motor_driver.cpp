#include "motor_driver.h"

void newborn::MotorDriver::SetUp()
{
    pinMode(left_.in_x_pin, OUTPUT);
    pinMode(left_.in_y_pin, OUTPUT);
    pinMode(right_.in_x_pin, OUTPUT);
    pinMode(right_.in_y_pin, OUTPUT);
    set_left_speed(DEFAULT_SPEED);
    set_right_speed(DEFAULT_SPEED);
}

void newborn::MotorDriver::MoveForward()
{
    digitalWrite(left_.in_x_pin, HIGH);
    digitalWrite(left_.in_y_pin, LOW);
    digitalWrite(right_.in_x_pin, HIGH);
    digitalWrite(right_.in_y_pin, LOW);
}

void newborn::MotorDriver::MoveBack()
{
    digitalWrite(left_.in_x_pin, LOW);
    digitalWrite(left_.in_y_pin, HIGH);
    digitalWrite(right_.in_x_pin, LOW);
    digitalWrite(right_.in_y_pin, HIGH);
}

void newborn::MotorDriver::FastStop()
{
    digitalWrite(left_.in_x_pin, LOW);
    digitalWrite(left_.in_y_pin, LOW);
    digitalWrite(right_.in_x_pin, LOW);
    digitalWrite(right_.in_y_pin, LOW);
}

void newborn::MotorDriver::TurnLeft()
{
    digitalWrite(left_.in_x_pin, HIGH);
    digitalWrite(left_.in_y_pin, LOW);
    digitalWrite(right_.in_x_pin, LOW);
    digitalWrite(right_.in_y_pin, HIGH);
}

void newborn::MotorDriver::TurnRight()
{
    digitalWrite(right_.in_x_pin, HIGH);
    digitalWrite(right_.in_y_pin, LOW);
    digitalWrite(left_.in_x_pin, LOW);
    digitalWrite(left_.in_y_pin, HIGH);
}
