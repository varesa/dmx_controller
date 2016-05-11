//
// Created by esa on 3.5.2016.
//

#include <hal.h>

#include <board/board.h>
#include "lcd.h"


inline void lcd_E_high(void) {
    palSetPad(LCD_CTRL_GPIO, LCD_E);
}

inline void lcd_E_low(void) {
    palClearPad(LCD_CTRL_GPIO, LCD_E);
}

inline void lcd_RW_read(void) {
    palSetPad(LCD_CTRL_GPIO, LCD_RW);
}

inline void lcd_RW_write(void) {
    palClearPad(LCD_CTRL_GPIO, LCD_RW);
}

inline void lcd_RS_cmd(void) {
    palClearPad(LCD_CTRL_GPIO, LCD_RS);
}

inline void lcd_RS_data(void) {
    palSetPad(LCD_CTRL_GPIO, LCD_RS);
}

inline void lcd_set_data(uint8_t data) {
    palWriteGroup(LCD_DATA_GPIO, 0xFF, 8, data);  // put command to port
}

void lcd_write_cmd(uint8_t cmd)
{
    lcd_RW_write();							// Write ...
    lcd_RS_cmd();							// command to LCD
    lcd_E_high();							// set LCD enable high
    chThdSleepMicroseconds(100);				// short delay
    lcd_set_data(cmd);
    chThdSleepMicroseconds(100);
    lcd_E_low();							// now command will be written
}

void lcd_putchar(char data)
{
    lcd_RW_write();								// Write ...
    lcd_RS_data();								// data to LCD
    lcd_E_high();								// E = 1
    chThdSleepMicroseconds(100);				// short delay
    lcd_set_data(data);
    chThdSleepMicroseconds(100);				// short delay
    lcd_E_low();								// now command will be written
}

void lcd_init(void) {
    chThdSleepMilliseconds(100);
    lcd_write_cmd(0x38);					// wake up
    chThdSleepMilliseconds(50);				// wait
    lcd_write_cmd(0x38);					// wake up

    lcd_write_cmd(0x0C);                    // Display on

    lcd_write_cmd(0x01);					// clear display
    lcd_write_cmd(0x06);					// entry mode
    chThdSleepMilliseconds(2);
}


void lcd_goto_rc(uint8_t row, uint8_t col)
{
    if (row == 0)
        lcd_write_cmd(0x80 + col);
    else
        lcd_write_cmd(0xC0 + col);
}

void lcd_clr_display() {
    lcd_write_cmd(0x01);
}

void lcd_putstr(char *str)
{
    while (*str != 0)
    {
        lcd_putchar(*str++);
    }
}