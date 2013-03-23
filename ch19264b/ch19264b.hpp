//--------------------------------------------------------------
// copyright (c) 2013 jks Liu.
// All rights reserved.
// -------------------------------------------------------------

#ifndef CH19264B_CH19264B_HPP
#define CH19264B_CH19264B_HPP

#include <stdint.h>
#include "../chip/st7920.hpp"

class Ch19264b {
public:
    Ch19264b(volatile uint8_t *cs_port, uint8_t cs_mask,
             volatile uint8_t *sid_port, uint8_t sid_mask,
             volatile uint8_t *sclk1_port, uint8_t sclk1_mask,
             volatile uint8_t *sclk2_port, uint8_t sclk2_mask);
    // Clear the whole screen.
    int8_t clear(void);
    // In this version, I will not ckeck the parameter carefully,
    // The behavior of a wrong parameter is undefined.
    //
    // Input:
    //    y: the line, in [0, 4).
    //    x: the colume, in [0, 24). But you must be care of the
    //       lengrh of the string which incoming from parameter s.
    //    s: the string.
    // Output:
    //    0: Success.
    //    <0: Failed.
    int8_t display_string(uint8_t y, uint8_t x, const char *s);
    // y in [0, 64), x in [0, 24).
    int8_t write_16_pixels(uint8_t y, uint8_t x, uint16_t s);
    // (y0, x0) are included, but (y1, x1) are not.
    int8_t clear_graphic(uint8_t y0, uint8_t x0,
                          uint8_t y1, uint8_t x1);
private:
    class St7920 st7920_top_;
    class St7920 st7920_bottom_;
};

#endif  // CH19264B_CH19264B_HPP











