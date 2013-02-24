#ifndef LCD19264_H
#define LCD19264_H

/* Copyright (C) 2013 JKS Liu. All rights reserved.
 * License is available in the copying file. */

#include "./config.h"

/* Function return code. */
#define LCD19264_SUCCESS 0
#define LCD19264_ERROR 1

typedef struct {
    int (*initialize)(void);
    int (*clear)(void);
    int (*display_string)(int x,
                          int y,
                          const char *s);
    int (*write_pixel)(int x,
                       int y);
    int (*clear_pixel)(int x,
                       int y);
    int (*power_on)(void);
    int (*power_off)(void);
    int (*backlight_on)(void);
    int (*backlight_off)(void);
} LCD19264;

#ifdef USE_CH19264B
extern const LCD19264 CH19264B;
#endif  /* USE_CH19264B */
                            
#endif  /* LCD19264_H */

















