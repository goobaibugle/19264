#ifndef CHIP_ST7920_HPP
#define CHIP_ST7920_HPP

#include <stdint.h>

class St7920 {
public:
    St7920(void);
    uint8_t initialize(void);
    uint8_t clear(void);
    uint8_t display_string(uint8_t y, uint8_t x, const char *s);
    uini8_t write_16_pixels(uint8_t y, uint8_t x);
    uint8_t cursor_on(void);
    uint8_t cursor_off(void);
};

#endif  // CHIP_ST7920_HPP

