#ifndef BITSET_H_
#define BITSET_H_

#include <Arduino.h>

namespace newborn
{
template <size_t size>
class BitSet
{
public:
    BitSet()
    {
        memset(container_, 0, sizeof container_ / sizeof *container_);
    }

    void set(size_t index, bool value)
    {
        uint8_t &ref = container_[index / 8];
        uint8_t temp = 0x01 << index % 8;
        if (value)
            ref |= temp;
        else
            ref &= ~temp;
    }

    bool get(size_t index)
    {
        return (container_[index / 8] >> index % 8) & 0x01;
    }

    /**
     * return the value before inverted
     */
    bool invert(size_t index)
    {
        bool temp = get(index);
        set(index, !temp);
        return temp;
    }

private:
    uint8_t container_[size % 8 == 0 ? size / 8 : size / 8 + 1];
};
} // namespace newborn
#endif
