/* Copyright (C) 2013 JKS Liu. All rights reserved.
 * License is available in the copying file. */

#include <avr/io.h>
#include <util/delay.h>
#include "../lcd19264.h"

int main(void)
{
    const LCD19264 * const lcd = &CH19264B;
    DDRC |= 0x0f;
    PORTC |= 0x02;
    lcd->initialize();
    PORTC |= 0x04;
    lcd->display_string(0, 0, "powered by:  3");
    lcd->display_string(1, 0, 
        "    \xc1\xf5\xbd\xf8\xb3\xbf Jks Liu"); /* Chinese GB code
                                                    of my name */
    for (;;) {
        _delay_ms(500);
        PORTC ^= 0x01;
    }

    return 0;
}

