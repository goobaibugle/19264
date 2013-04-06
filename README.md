19264
=====

lcd19264, including ch1264b.

Only support atmega48/88/168.

CH19264B
========

In this version, CH19264B is the only type I can support.
Because I have only it.

CH19264B use 2 st7920 chips, but you can ignore the details.

101
===

1. You should include this file:
    * lcd19264.hpp
1. You should add these files to yout project.
    * chip/st7920.cpp 
    * ch19264b/ch19264b.cpp

Example
-------
An exampe and its makefile can be find in test/

API
===

Define a lcd19264
-----------------
```c++
Lcd19264 lcd(volatile uint8_t *cs_port, uint8_t cs_mask,
             volatile uint8_t *sid_port, uint8_t sid_mask,
             volatile uint8_t *sclk1_port, uint8_t sclk1_mask,
             volatile uint8_t *sclk2_port, uint8_t sclk2_mask);
```

You can replace the name lcd to what you want.

Only support serial port. Parameters in the construction 
is used to config the hardware I/O port of AVR.

Method
------

The method details pleasd refer class Ch19264b
if file ch1264b/ch1264b.hpp.






