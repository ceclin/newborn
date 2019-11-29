#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "bitset.h"

namespace newborn
{
constexpr int8_t MessageTag(char c)
{
    return c >= '1' && c <= '9' ? c - '1' : c >= 'a' && c <= 'z' ? 9 + c - 'a' : -1;
}

template <size_t max>
class MessageHandler
{
public:
    MessageHandler(uint8_t receive_pin, uint8_t transmit_pin)
        : state_{}, bt_{receive_pin, transmit_pin}
    {
        for (size_t i = 0; i < max; ++i)
        {
            down_[i] = up_[i] = nullptr;
        }
    }

    void SetUp(long speed)
    {
        bt_.begin(speed);
    }

    void Update();

    void OnKeyDown(size_t index, void (*callback)())
    {
        down_[index] = callback;
    }

    void OnKeyUp(size_t index, void (*callback)())
    {
        up_[index] = callback;
    }

private:
    BitSet<max> state_;
    void (*down_[max])();
    void (*up_[max])();

    SoftwareSerial bt_;
};

template <size_t max>
void MessageHandler<max>::Update()
{
    while (bt_.available() >= 3)
    {
#ifdef _DEBUG_MESSAGE_HANDLER_
        Serial.print("current available: ");
        Serial.println(bt_.available());
#endif
        uint8_t arr[3];
        bt_.readBytes(arr, 3);
#ifdef _DEBUG_MESSAGE_HANDLER_
        Serial.println("read from bluetooth: ");
        for (size_t i = 0; i < 3; ++i)
        {
            Serial.print(static_cast<char>(arr[i]));
        }
        Serial.println("\nread end");
#endif
        if (arr[0] == '$' && arr[2] == '!')
        {
            int8_t index = MessageTag(arr[1]);
            if (index != -1)
            {
                void (*temp)() = nullptr;
                if (state_.invert(index))
                {
                    if ((temp = up_[index]) != nullptr)
                        temp();
                }
                else
                {
                    if ((temp = down_[index]) != nullptr)
                        temp();
                }
            }
        }
    }
}

} // namespace newborn
#endif
