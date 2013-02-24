#ifndef LCD19264_H
#define LCD19264_H

/* Copyright (C) 2013 JKS Liu. All rights reserved.
 * License is available in the copying file. */

#include "./config.h"

/* Function return code. */
#define LCD19264_SUCCESS 0
#define LCD19264_ERROR 1

typedef struct {
    int (*initialize)();
    int (*clear)();
    int (*display_string)(int x,
                          int y,
                          const char *s);
    int (*write_pixel)(int x,
                       int y);
    int (*clear_pixel)(int x,
                       int y);
    int (*power_on)();
    int (*power_off)();
    int (*backlight_on)();
    int (*backlight_off)();
} LCD19264;

#ifdef USE_CH19264B
extern const LCD19264 * const PTR_CH19264;
#endif  /* USE_CH19264B */
                            
#endif  /* LCD19264_H */

















