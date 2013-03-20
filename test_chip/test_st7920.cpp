/* Copyright (C) 2013 JKS Liu. All rights reserved.
 * License is available in the copying file. */

#include "../chip/st7920.hpp"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    class St7920 lcd0(&PORTD, 0, &PORTD, 1, &PORTD, 2);
    class St7920 lcd1(&PORTD, 0, &PORTD, 1, &PORTD, 3);
    DDRC |= 0x0f;
//    PORTC |= 0x01;
    lcd0.display_string(0, 0, "欢迎使用PTJ-5000系列产品");
    lcd0.display_string(1, 0, "powered by:  st7920 cpp1");
    lcd1.graphic_clear();
    lcd1.write_16_pixels(0, 0, 0x7781);
    /* Chinese GB code of my name */
//    lcd1.display_string(1, 0, "    \xc1\xf5\xbd\xf8\xb3\xbf Jks Liu"); 
    for (;;) {
        _delay_ms(500);
       PORTC ^= 0x01;
    }

    return 0;
}

