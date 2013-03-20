#ifndef CH19264B_CH19264B_HPP
#define CH19264B_CH19264B_HPP

#include <stdint.h>
#include "../chip/st7920.hpp"

class Ch19264b {
public:
    Ch19264b(void);
    uint8_t initialize(void);
    uint8_t clear(void);
    uint8_t display_string(uint8_t y, uint8_t x, const char *s);
    uint8_t write_16_pixels(uint8_t y, uint8_t x);
private:
    class St7920 st7920_top_;
    class St7920 st7920_bottom_;
};

#endif  // CH19264B_CH19264B_HPP

