#ifndef CH19264B_CONFIG_CH19264_H
#define CH19264B_CONFIG_CH19264_H

/* Copyright (C) 2013 JKS Liu. All rights reserved.
 * License is available in the copying file. */

#include <avr/io.h>

#define RS_CS_DDR DDRD
#define RS_CS_OUT_PORT PORTD
#define RS_CS_PIN 0

#define RW_SID_DDR DDRD
#define RW_SID_IN_PORT PIND
#define RW_SID_OUT_PORT PORTD
#define RW_SID_PIN 1

#define E1_SCLK1_DDR DDRD
#define E1_SCLK1_OUT_PORT PORTD
#define E1_SCLK1_PIN 2

#define E2_SCLK2_DDR DDRD
#define E2_SCLK2_OUT_PORT PORTD
#define E2_SCLK2_PIN 3

/* MODIFY: Choose only one */
/* #define PSB_PARALLEL */
#define PSB_SERIAL

#endif  /* CH19264B_CONFIG_CH19264_H */

