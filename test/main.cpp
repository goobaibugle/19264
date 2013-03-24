//--------------------------------------------------------------
// copyright (c) 2013 jks Liu.
// All rights reserved.
// -------------------------------------------------------------

#include "lcd19264.hpp"
#include <avr/io.h>
#include <util/delay.h>

Lcd19264 g_lcd(&PORTD, 0, &PORTD, 1, &PORTD, 2, &PORTD, 3);

int main(int argc, char *argv[])
{
    g_lcd.display_string(0, 0, "Hello world");
    g_lcd.display_string(1, 0, "ƒ„∫√ ¿ΩÁ");

    for (;;) {
        g_lcd.reverse_toggle(1);
        g_lcd.reverse_toggle(3);
        g_lcd.write_16_pixels(37, 2, 0x7e0f);
        _delay_ms(888);
        g_lcd.display_string(3, 2, "Hello jks2");
        _delay_ms(888);
    }

    return 0;
}














