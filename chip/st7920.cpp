#include "st7920.hpp"

St7920::St7920(volatile uint8_t *rs_cs_port, uint8_t rs_cs_mask,
            volatile uint8_t *rw_sid_port, uint8_t rw_sid_mask,
            volatile uint8_t *e_sclk_port, uint8_t e_sclk_mask)
: rs_cs_port_(rs_cs_port), rs_cs_mask_(rs_cs_mask),
    rw_sid_port_(rw_sid_port), rw_sid_mask_(rw_sid_mask),
    e_sclk_port_(e_sclk_port), e_sclk_mask_(e_sclk_mask)
{}



