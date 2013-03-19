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
    display_control_(0x08), function_set_(0x18)
{}

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
    // Found in practice that delay is require
    _delay_ms(1);               
}

int8_t St7920::initialize(void) {
    // Set CS & SCLK out mode
    *(rs_cs_port_ - 1) |= rs_cs_mask_;
    *(e_sclk_port_ - 1) |= e_sclk_mask_;
    clear();
    display_on();
    return 0;
}

int8_t St7920::clear(void) {
    write_command(DISPLAY_CLEAR);
    // Found in practice that delay is require
    _delay_ms(1);               
    return 0;
}

int8_t St7920::set_cursor(uint8_t y, uint8_t x) {
    write_command(DDRAM_BASE_ADDRESS + y * DDR_COLUMN_NUM + x);
    return 0;
}

int8_t St7920::display_string(uint8_t y, uint8_t x, const char *s) {
    if ((y >= 2) || (x >= (DDR_COLUMN_NUM * 2))) {
        return -1;
    }

    while (*s) {
        write_data(*s++);
    }
    return 0;
}

                         



















