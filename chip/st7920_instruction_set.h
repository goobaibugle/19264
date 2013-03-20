/*************************************************************
 * Copyright (c) 2013 jks Liu.
 * All rights reserved
 * ***********************************************************/

#ifndef LCD19264_CHIP_ST7920_INSTRUCTION_SET_H_
#define LCD19264_CHIP_ST7920_INSTRUCTION_SET_H_

/* TODO(jks Liu. chinatianma#gmail.com)
 * The instruction set is incomplete */
/* Fill DDRAM with "20H" and set DDRAM address counter (AC) to "00H". */
#define DISPLAY_CLEAR 0x01
/* Set   DDRAM address counter  (AC)  to  "00H",
 * and put cursor to origin £»the content of DDRAM are not changed */
#define RETURN_HOME 0x02  

/* Mask set cannot be used independently */
#define DISPLAY_CONTROL_DISPLAY_ON 0x04
#define DISPLAY_CONTROL_CURSOR_ON 0x02
#define DISPLAY_CONTROL_CHARACTER_BLINK_ON 0x01

#define FUNCTION_SET_8_BIT_INTERFACE 0x10
#define FUNCTION_SET_EXTENDED 0x04
#define FUNCTION_SET_GRAPHIC_DISPLAY_ON 0x02

#define GDRAM_BASE_ADDRESS 0x80
#define DDRAM_BASE_ADDRESS 0x80
#define DDRAM_COLUMN_NUM 0x10

#endif /* LCD19264_CHIP_ST7920_INSTRUCTION_SET_H_ */

