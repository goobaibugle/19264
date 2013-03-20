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
    int8_t clear(void);
    int8_t display_string(uint8_t y, uint8_t x, const char *s);
    int8_t write_16_pixels(uint8_t y, uint8_t x, uint16_t c);
    int8_t cursor_on(void);
    int8_t cursor_off(void);
    int8_t set_cursor(uint8_t y, uint8_t x);
    int8_t display_on(void);
    int8_t display_off(void);
    int8_t graphic_on(void);
    int8_t graphic_off(void);
    int8_t graphic_clear(void);
private:
    // PORTX isn't volatile, but I use it to access PINX,
    // so volatile is required.
    volatile uint8_t *const rs_cs_port_;
    uint8_t const rs_cs_mask_;
    volatile uint8_t *const rw_sid_port_;
    uint8_t const  rw_sid_mask_;
    volatile uint8_t *const e_sclk_port_;
    uint8_t const e_sclk_mask_;
    
    // I/O operation
    void set_cs(void) {*rs_cs_port_ |= 1 << rs_cs_mask_;}
    void reset_cs(void) {*rs_cs_port_ &= ~(1 << rs_cs_mask_);}

    void set_sid(void) {*rw_sid_port_ |= 1 << rw_sid_mask_;}
    void reset_sid(void) {*rw_sid_port_ &= ~(1 << rw_sid_mask_);}
    bool sid(void) {return (*(rw_sid_port_ - 2) >> rw_sid_mask_) & 0x01;}
    void make_sid_in(void) {*(rw_sid_port_ - 1) &= ~(1 << rw_sid_mask_);}
    void make_sid_out(void) {*(rw_sid_port_ - 1) |= 1 << rw_sid_mask_;}

    void set_sclk(void) {*e_sclk_port_ |= 1 << e_sclk_mask_;}
    void reset_sclk(void) {*e_sclk_port_ &= ~(1 << e_sclk_mask_);}

    int8_t initialize(void);

    // Timing sequence
    void write_data(uint8_t b);
    void write_command(uint8_t c);
    // TODO(jks Liu, chinatianma#gmail.com)
    // To complete read_data & read_command.
    // inline is not required.
    uint8_t read_data(void){return 0;}
    uint8_t read_command(void){return 0;}
    // d dosen't include the beginning 4 ones &
    // last 4 zeros.
    void serial_data_transfer(uint16_t d);

    // Instruction set which used bit mask
    // These set must have init value thoeretically.
    // TODO(jks Liu. chinatianma#gmail.com): complete this set.
    //
    // 0b0000 1DCB: bit7...0
    //    D = 1: Display ON
    //    C = 1: Cursor ON
    //    B = 1: Character Blink ON
    uint8_t display_control_;
    // 0b001D xRGx: bit7...0 D(DL) R(RE)
    //    DL = 1: 8-bit interface
    //         0: 4-bit interface
    //    RE = 1: extended instruction
    //         0: basic instruction
    //    G  = 1: graphic display ON  (RE = 1)
    //         0: graphic display OFF (RE = 1)
    uint8_t function_set_;
    int8_t enter_basic(void);
    int8_t enter_extended(void);
};

#endif  // CHIP_ST7920_HPP

















