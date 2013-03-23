//--------------------------------------------------------------
// copyright (c) 2013 jks Liu.
// All rights reserved.
// -------------------------------------------------------------

#include "st7920.hpp"
#include "st7920_instruction_set.h"
#include <util/delay.h>

St7920::St7920(volatile uint8_t *rs_cs_port, uint8_t rs_cs_mask,
            volatile uint8_t *rw_sid_port, uint8_t rw_sid_mask,
            volatile uint8_t *e_sclk_port, uint8_t e_sclk_mask)
: rs_cs_port_(rs_cs_port), rs_cs_mask_(rs_cs_mask),
    rw_sid_port_(rw_sid_port), rw_sid_mask_(rw_sid_mask),
    e_sclk_port_(e_sclk_port), e_sclk_mask_(e_sclk_mask),
    // Register flag initial setting,
    // refer to st7920 datasheet
    display_control_(0x08), function_set_(0x38)
{
    initialize();
    cursor_off();
}

void St7920::write_data(uint8_t b) {
    serial_data_transfer(
        0x8000 |                // Bit15: Synchronizing Bit string
        0x0000 |                // Bit14: RW: low write
        0x2000 |                // Bit13: RS: high data
        0x0000 |                // Bit12: just 0
        ((0x00f0 & b) << 4) |   // Bit11...8: data7...4
        0x0000 |                // Bit7...4: just 0
        (0x000f & b));          // Bit3...0: data3...0
} // St7920::write_data

void St7920::write_command(uint8_t b) {
    serial_data_transfer(
        0x8000 |                // Bit15: Synchronizing Bit string
        0x0000 |                // Bit14: RW: low write
        0x0000 |                // Bit13: RS: low instruction
        0x0000 |                // Bit12: just 0
        ((0x00f0 & b) << 4) |   // Bit11...8: data7...4
        0x0000 |                // Bit7...4: just 0
        (0x000f & b));          // Bit3...0: data3...0
} // St7920::write_command

void St7920::serial_data_transfer(uint16_t d) {
    reset_cs();
    reset_sclk();
    set_cs();
    make_sid_out();
    
    // Synchronizing Bit String
    set_sid();
    for (uint8_t i = 0; i < 4; ++i) {
        set_sclk();
        reset_sclk();
    }
    for (uint8_t i = 0; i < 16; ++i) {
        (d & (0x8000 >> i)) ? set_sid() : reset_sid();
        set_sclk();
        reset_sclk();
    }
    reset_sid();
    for (uint8_t i = 0; i < 4; ++i) {
        set_sclk();
        reset_sclk();
    }
    
    reset_cs();
}

int8_t St7920::initialize(void) {
    // Set CS & SCLK out mode
    *(rs_cs_port_ - 1) |= 1 << rs_cs_mask_;
    *(e_sclk_port_ - 1) |= 1 << e_sclk_mask_;
    enter_basic();
    clear();
    display_on();
    return 0;
}

int8_t St7920::clear(void) {
    enter_basic();
    write_command(DISPLAY_CLEAR);
    // Found in practice that delay is require
    _delay_ms(2);               
    return 0;
}

int8_t St7920::set_cursor(uint8_t y, uint8_t x) {
    enter_basic();
    write_command(DDRAM_BASE_ADDRESS + y * DDRAM_COLUMN_NUM + x);
    return 0;
}

int8_t St7920::display_string(uint8_t y, uint8_t x, const char *s) {
    if ((y >= 2) || (x >= (DDRAM_COLUMN_NUM * 2))) {
        return -1;
    }
    set_cursor(y, x);
    while (*s) {
        write_data(*s++);
    }
    return 0;
}

int8_t St7920::write_16_pixels(uint8_t y, uint8_t x, uint16_t c) {
    write_command(GDRAM_BASE_ADDRESS + y);
    write_command(GDRAM_BASE_ADDRESS + x);
    write_data(c >> 8);
    write_data(c & 0xff);
    return 0;
}

int8_t St7920::cursor_on(void) {
    enter_basic();
    display_control_ |= DISPLAY_CONTROL_CURSOR_ON;
    write_command(display_control_);
    return 0;
}

int8_t St7920::cursor_off(void) {
    enter_basic();
    display_control_ &= ~DISPLAY_CONTROL_CURSOR_ON;
    write_command(display_control_);
    return 0;
}

int8_t St7920::display_on(void) {
    enter_basic();
    display_control_ |= DISPLAY_CONTROL_DISPLAY_ON;
    write_command(display_control_);
    return 0;
}

int8_t St7920::display_off(void) {
    enter_basic();
    display_control_ &= ~DISPLAY_CONTROL_DISPLAY_ON;
    write_command(display_control_);
    return 0;
}

int8_t St7920::graphic_on(void) {
    enter_extended();
    function_set_ |= FUNCTION_SET_GRAPHIC_DISPLAY_ON;
    write_command(function_set_);
    return 0;
}

int8_t St7920::graphic_off(void) {
    enter_extended();
    function_set_ &= ~FUNCTION_SET_GRAPHIC_DISPLAY_ON;
    write_command(function_set_);
    return 0;
}

int8_t St7920::graphic_clear(void) {
    enter_extended();
    graphic_on();
    for (uint8_t i = 0; i < 0x3f; ++i) {
        for (uint8_t j = 0; j < 0x0f; ++j) {
            write_16_pixels(i, j, 0x0000);
        }
    }
}

int8_t St7920::enter_basic(void) {
    function_set_ &= ~FUNCTION_SET_EXTENDED;
    write_command(function_set_);
    return 0;
}

int8_t St7920::enter_extended(void) {
    function_set_ |= FUNCTION_SET_EXTENDED;
    write_command(function_set_);
    return 0;
}





















