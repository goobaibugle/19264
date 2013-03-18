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
    void make_sid_in(void) {*(rw_sid_port_ - 1) &= ~(1 << rw_sid_mask_);}
    void make_sid_out(void) {*(rw_sid_port_ - 1) |= 1 << rw_sid_mask_;}

    void set_sclk(void) {*e_sclk_port_ |= 1 << e_sclk_mask_;}
    void reset_sclk(void) {*e_sclk_port_ &= ~(1 << e_sclk_mask_);}

    void write_data(uint8_t b);
    void write_command(uini8_t c);
    // TODO(jks Liu, chinatianma#gmail.com)
    // To complete read_data & read_command.
    // inline is not required.
    uint8_t read_data(void){return 0};
    uini8_t read_command(void){return 0};
    // d dosen't include the beginning 4 ones &
    // last 4 zeros.
    void serial_data_transfer(uint16_t d);
};

#endif  // CHIP_ST7920_HPP

















