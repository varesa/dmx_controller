//
// Created by esa on 3.5.2016.
//

#ifndef ARM_ETHERNETBOARD_LCD_H
#define ARM_ETHERNETBOARD_LCD_H

#include <stdint.h>

void lcd_write_cmd(uint8_t cmd);

void lcd_init(void);

void lcd_goto_rc(uint8_t row, uint8_t col);
void lcd_putchar(char ch);
void lcd_putstr(char *str);
void lcd_clr_display(void);					// clear display

#endif //ARM_ETHERNETBOARD_LCD_H
