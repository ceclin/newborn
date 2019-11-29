#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>

namespace newborn
{
struct MotorConfig
{
    uint8_t in_x_pin;
    uint8_t in_y_pin;
    uint8_t en_pin;
};

class MotorDriver
{
public:
    static constexpr uint8_t DEFAULT_SPEED = 200;

    MotorDriver(MotorConfig a, MotorConfig b) : left_{a}, right_{b} {}

    void set_left_speed(uint8_t pwm)
    {
        analogWrite(left_.en_pin, pwm);
    }

    void set_right_speed(uint8_t pwm)
    {
        analogWrite(right_.en_pin, pwm);
    }

    void SetUp();

    void MoveForward();

    void MoveBack();

    void FastStop();

    void TurnLeft();

    void TurnRight();

private:
    MotorConfig left_;
    MotorConfig right_;
};

} // namespace newborn

#endif
