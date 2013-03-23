//--------------------------------------------------------------
// copyright (c) 2013 jks Liu.
// All rights reserved.
// -------------------------------------------------------------

#include "ch19264b.hpp"

Ch19264b::Ch19264b(volatile uint8_t *cs_port, uint8_t cs_mask,
                   volatile uint8_t *sid_port, uint8_t sid_mask,
                   volatile uint8_t *sclk1_port, uint8_t sclk1_mask,
                   volatile uint8_t *sclk2_port, uint8_t sclk2_mask):
    st7920_top_(cs_port, cs_mask, sid_port, sid_mask,
                sclk1_port, sclk1_mask),
    st7920_bottom_(cs_port, cs_mask, sid_port, sid_mask,
                   sclk2_port, sclk2_mask)
{}

int8_t Ch19264b::clear(void) {
    st7920_top_.clear();
    st7920_bottom_.clear();
}

int8_t Ch19264b::display_string(uint8_t y, uint8_t x, const char *s) {
    if (y < 2) {
        return st7920_top_.display_string(y, x, s);
    } else if (y < 4) {
        return st7920_bottom_.display_string(y - 2, x, s);
    } else {
        return -1;
    }
 }

int8_t Ch19264b::write_16_pixels(uint8_t y, uint8_t x, uint16_t s) {
    if (y < 2) {
        return st7920_top_.write_16_pixels(y, x, s);
    } else if (y < 4) {
        return st7920_bottom_.write_16_pixels(y, x, s);
    } else {
        return -1;
    }
}

int8_t Ch19264b::clear_graphic(uint8_t y0, uint8_t x0,
                               uint8_t y1, uint8_t x1) {
    for (int8_t i = y0; i < y1; ++i) {
        for (int8_t j = x0; j < x1; ++j) {
            write_16_pixels(i, j, 0x0000);
        }
    }
}
                



















