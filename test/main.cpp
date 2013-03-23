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
    return 0;
}














