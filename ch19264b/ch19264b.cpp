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
{
     clear();
     clear_graphic(0, 0, 64, 12);
     st7920_top_.display_on();
     st7920_bottom_.display_on();
}

int8_t Ch19264b::clear(void) {
    st7920_top_.enter_basic();
    st7920_bottom_.enter_basic();
    st7920_top_.clear();
    st7920_bottom_.clear();
    return 0;
}

int8_t Ch19264b::display_string(uint8_t y, uint8_t x, const char *s) {
    if (y < 2) {
        st7920_top_.enter_extended();
        st7920_top_.graphic_off();
        st7920_top_.enter_basic();
        return st7920_top_.display_string(y, x, s);
    } else if (y < 4) {
        st7920_bottom_.enter_extended();
        st7920_bottom_.graphic_off();
        st7920_bottom_.enter_basic();
        return st7920_bottom_.display_string(y - 2, x, s);
    } else {
        return -1;
    }
 }

int8_t Ch19264b::write_16_pixels(uint8_t y, uint8_t x, uint16_t s) {
    if (y < 32) { 
        st7920_top_.enter_basic();
        st7920_top_.clear();
        st7920_top_.enter_extended();
        st7920_top_.graphic_on();
        st7920_top_.write_16_pixels(y, x, s);
    } else if (y < 64) {
        st7920_bottom_.enter_basic();
        st7920_bottom_.clear();
        st7920_bottom_.enter_extended();
        st7920_bottom_.graphic_on();
        st7920_bottom_.write_16_pixels(y - 32, x, s);
    } else {
        return -1;
    }
    return 0;
}

int8_t Ch19264b::clear_graphic(uint8_t y0, uint8_t x0,
                               uint8_t y1, uint8_t x1) {
    for (int8_t i = y0; i < y1; ++i) {
        for (int8_t j = x0; j < x1; ++j) {
            write_16_pixels_(i, j, 0x0000);
        }
    }
    return 0;
}

int8_t Ch19264b::reverse_toggle(uint8_t y) {
    if (y < 2) {
        st7920_top_.reverse_toggle(y);
    } else if (y < 4) {
        st7920_bottom_.reverse_toggle(y - 2);
    } else {
        return -1;
    }

    return 0;
}
                



















