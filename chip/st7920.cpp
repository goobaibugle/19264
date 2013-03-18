#include "st7920.hpp"
#include <util/delay.h>

St7920::St7920(volatile uint8_t *rs_cs_port, uint8_t rs_cs_mask,
            volatile uint8_t *rw_sid_port, uint8_t rw_sid_mask,
            volatile uint8_t *e_sclk_port, uint8_t e_sclk_mask)
: rs_cs_port_(rs_cs_port), rs_cs_mask_(rs_cs_mask),
    rw_sid_port_(rw_sid_port), rw_sid_mask_(rw_sid_mask),
    e_sclk_port_(e_sclk_port), e_sclk_mask_(e_sclk_mask)
{}

void St7920::write_data(uint8_t b) {
    // Found in practice that delay is require
    _delay_ms(1);               
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
    // Found in practice that delay is require
    _delay_ms(1);               
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



                         



















