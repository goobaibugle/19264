/* Copyright (C) 2013 JKS Liu. All rights reserved.
 * License is available in the copying file. */

#include "../lcd19264.h"
#include "./config_ch19264b.h"
#include <stdint.h>
#include <util/delay.h>

#define CS_HIGH() (RS_CS_OUT_PORT |= _BV(RS_CS_PIN))
#define CS_LOW() (RS_CS_OUT_PORT &= ~_BV(RS_CS_PIN))

#define SID_HIGH() (RW_SID_OUT_PORT |= _BV(RW_SID_PIN))
#define SID_LOW() (RW_SID_OUT_PORT &= ~_BV(RW_SID_PIN))
#define SID() ((RW_SID_IN_PORT >> _BV(RW_SID_PIN)) & 0x01)
#define SID_IN() (RW_SID_DDR &= ~_BV(RW_SID_PIN))
#define SID_OUT() (RW_SID_DDR |= _BV(RW_SID_PIN))

#define SCLK1_HIGH() (E1_SCLK1_OUT_PORT |= _BV(E1_SCLK1_PIN))
#define SCLK1_LOW() (E1_SCLK1_OUT_PORT &= ~_BV(E1_SCLK1_PIN))

#define SCLK2_HIGH() (E2_SCLK2_OUT_PORT |= _BV(E2_SCLK2_PIN))
#define SCLK2_LOW() (E2_SCLK2_OUT_PORT &= ~_BV(E2_SCLK2_PIN))

// RS
static const int CH19264B_INSTRUCTION = 0;
static const int CH19264B_DATA = 1;

static void write_byte_1st(const uint8_t b,
                           const int rs)
{
    CS_LOW();
    SCLK1_LOW();
    CS_HIGH();
    
    SID_OUT();
    
    /* Synchronizing Bit string */
    SID_HIGH();
    for (int i = 0; i < 5; ++i)
    {
        SCLK1_HIGH();
        SCLK1_LOW();
    }
    /* RW */
    SID_LOW();
    SCLK1_HIGH();
    SCLK1_LOW();
    /* RS */
    if (rs)
    {
        SID_HIGH();
    } else {
        SID_LOW();
    }
    SCLK1_HIGH();
    SCLK1_LOW();
    /* 0 */
    SID_LOW();
    SCLK1_HIGH();
    SCLK1_LOW();
    /* Write higher data */
    for (int i = 7; i >= 4; --i)
    {
        if ((b >> i) & 0x01)
        {
            SID_HIGH();
        } else {
            SID_LOW();
        }
        SCLK1_HIGH();
        SCLK1_LOW();
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK1_HIGH();
        SCLK1_LOW();
    }
    /* Write lower data */
    for (int i = 3; i >= 0; --i)
    {
        if ((b >> i) & 0x01)
        {
            SID_HIGH();
        } else {
            SID_LOW();
        }
        SCLK1_HIGH();
        SCLK1_LOW();        
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK1_HIGH();
        SCLK1_LOW();
    }

    CS_LOW();
}

static void write_byte_2nd(const uint8_t b,
                           const int rs)
{
    CS_LOW();
    SCLK2_LOW();
    CS_HIGH();
    
    SID_OUT();
    
    /* Synchronizing Bit string */
    SID_HIGH();
    for (int i = 0; i < 5; ++i)
    {
        SCLK2_HIGH();
        SCLK2_LOW();
    }
    /* RW */
    SID_LOW();
    SCLK2_HIGH();
    SCLK2_LOW();
    /* RS */
    if (rs)
    {
        SID_HIGH();
    } else {
        SID_LOW();
    }
    SCLK2_HIGH();
    SCLK2_LOW();
    /* 0 */
    SID_LOW();
    SCLK2_HIGH();
    SCLK2_LOW();
    /* Write higher data */
    for (int i = 7; i >= 4; --i)
    {
        if ((b >> i) & 0x01)
        {
            SID_HIGH();
        } else {
            SID_LOW();
        }
        SCLK2_HIGH();
        SCLK2_LOW();
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK2_HIGH();
        SCLK2_LOW();
    }
    /* Write lower data */
    for (int i = 3; i >= 0; --i)
    {
        if ((b >> i) & 0x01)
        {
            SID_HIGH();
        } else {
            SID_LOW();
        }
        SCLK2_HIGH();
        SCLK2_LOW();        
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK2_HIGH();
        SCLK2_LOW();
    }

    CS_LOW();
}


static uint8_t read_byte_1st(int rs)
{
    uint8_t b = '\0';
    
    CS_LOW();
    SCLK1_LOW();
    CS_HIGH();
    
    SID_IN();
    
    /* Synchronizing Bit string */
    SID_HIGH();
    for (int i = 0; i < 5; ++i)
    {
        SCLK1_HIGH();
        SCLK1_LOW();
    }
    /* RW */
    SID_HIGH();
    SCLK2_HIGH();
    SCLK2_LOW();
    /* RS */
    if (rs)
    {
        SID_HIGH();
    } else {
        SID_LOW();
    }
    SCLK1_HIGH();
    SCLK1_LOW();
    /* 0 */
    SID_LOW();
    SCLK1_HIGH();
    SCLK1_LOW();
    /* Read higher data */
    for (int i = 0; i < 4; ++i)
    {
        SCLK1_HIGH();
        b <<= 1;
        b |= SID();
        SCLK1_LOW();
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK1_HIGH();
        SCLK1_LOW();
    }
    /* Read lower data */
    for (int i = 0; i < 4; ++i)
    {
        SCLK1_HIGH();
        b <<= 1;
        b |= SID();
        SCLK1_LOW();
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK1_HIGH();
        SCLK1_LOW();
    }

    CS_LOW();
    
    return b;
}

static uint8_t read_byte_2nd(int rs)
{
    uint8_t b = '\0';
    
    CS_LOW();
    SCLK2_LOW();
    CS_HIGH();
    
    SID_IN();
    
    /* Synchronizing Bit string */
    SID_HIGH();
    for (int i = 0; i < 5; ++i)
    {
        SCLK2_HIGH();
        SCLK2_LOW();
    }
    /* RW */
    SID_HIGH();
    SCLK2_HIGH();
    SCLK2_LOW();
    /* RS */
    if (rs)
    {
        SID_HIGH();
    } else {
        SID_LOW();
    }
    SCLK2_HIGH();
    SCLK2_LOW();
    /* 0 */
    SID_LOW();
    SCLK2_HIGH();
    SCLK2_LOW();
    /* Read higher data */
    for (int i = 0; i < 4; ++i)
    {
        SCLK2_HIGH();
        b <<= 1;
        b |= SID();
        SCLK2_LOW();
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK2_HIGH();
        SCLK2_LOW();
    }
    /* Read lower data */
    for (int i = 0; i < 4; ++i)
    {
        SCLK2_HIGH();
        b <<= 1;
        b |= SID();
        SCLK2_LOW();
    }
    /* 0000 */
    SID_LOW();
    for (int i = 0; i < 4; ++i)
    {
        SCLK2_HIGH();
        SCLK2_LOW();
    }

    CS_LOW();
    
    return b;
}

int display_clear(void)
{
    write_byte_1st(0x01, CH19264B_INSTRUCTION);
    write_byte_2nd(0x01, CH19264B_INSTRUCTION);
    write_byte_1st(0x0f, CH19264B_INSTRUCTION);
    write_byte_2nd(0x0f, CH19264B_INSTRUCTION);

    return 0;
}

int initialize(void)
{
    RS_CS_DDR |= _BV(RS_CS_PIN);
    E1_SCLK1_DDR |= _BV(E1_SCLK1_PIN);
    E2_SCLK2_DDR |= _BV(E2_SCLK2_PIN);
    
    display_clear();

    return 0;
}

int display_string(int x,
                   int y,
                   const char *s)
{
    write_byte_1st(0x80 + 0x10 * y + x, CH19264B_INSTRUCTION);
    _delay_ms(1); /* for 8Mhz avr, this delay is necessary. */
    while (*s) {
        write_byte_1st(*s++, CH19264B_DATA);
    }
    
    return 0;
}

const LCD19264 CH19264B = {initialize,
                           display_clear,
                           display_string,
                           (void *)0,
                           (void *)0,
                           (void *)0,
                           (void *)0,
                           (void *)0,
                           (void *)0,};
                           




