//--------------------------------------------------------------
// copyright (c) 2013 jks Liu.
// All rights reserved.
// -------------------------------------------------------------

#ifndef CHIP_ST7920_HPP
#define CHIP_ST7920_HPP

#include <inttypes.h>

//---------------------------------------------------------------
// This class depends on the PINX, DDRX & PORTX is continous.
// I can only make sure it is right on ATmega48-88-168.
// --------------------------------------------------------------
class St7920 {
public:
    // mask is in [0, 8).
    //
    // Only PORTX is needed, PINX and DDRX will be calcuted
    // automaticly.
    St7920(volatile uint8_t *rs_cs_port, uint8_t rs_cs_mask,
            volatile uint8_t *rw_sid_port, uint8_t rw_sid_mask,
            volatile uint8_t *e_sclk_port, uint8_t e_sclk_mask);
    uint8_t initialize(void);
    uint8_t clear(void);
    uint8_t display_string(uint8_t y, uint8_t x, const char *s);
    uini8_t write_16_pixels(uint8_t y, uint8_t x);
    uint8_t cursor_on(void);
    uint8_t cursor_off(void);
private:
    // PORTX isn't volatile, but I use it to access PINX,
    // so volatile is required.
    volatile uint8_t *const rs_cs_port_;
    uint8_t const rs_cs_mask_;
    volatile uint8_t *const rw_sid_port_;
    uint8_t const const rw_sid_mask_;
    volatile uint8_t *const e_sclk_port_;
    uint8_t const e_sclk_mask_;
    
    void set_cs(void) {*rs_cs_port_ |= 1 << rs_cs_mask_;}
    void reset_cs(void) {*rs_cs_port_ &= ~(1 << rs_cs_mask_);}

    void set_sid(void) {*rw_sid_port_ |= 1 << rw_sid_mask_;}
    void reset_sid(void) {*rw_sid_port_ &= ~(1 << rw_sid_mask_);}
    bool sid(void) {return (*(rw_sid_port_ - 2) >> rw_sid_mask_) & 0x01;}
    void make_sid_in(void) {*(rw_sid_port_ - 1)
};

#endif  // CHIP_ST7920_HPP

