/*
 * LCD.h
 *
 * Created: 2024-09-15(일) 오후 10:52:52
 *  Author: step
 */ 


#ifndef LCD_H_
#define LCD_H_

/////////////////////////////////////////////////////
//lcd
#define COMMAND_4_BIT_MODE 0x28 //0010 1000
#define RS_PIN 0
#define RW_PIN 1
#define E_PIN 2
#define RS_LOW_EN_high 0x04
#define RS_LOW_EN_low 0x00
#define RS_HIGH_EN_high 0x05
#define RS_HIGH_EN_low 0x01
#define Backlight 0x08
#define COMMAND_DISPLAY_ON_OFF_BIT 2 //0000 0010
#define COMMAND_CLEAR_DISPLAY 0x01 //0000 0001
#define Set_CGRAM_Address 0x40  //0100 0000
#define Set_CGRAM_Address2 0x48 //0100 1000
/////////////////////////////////////////////////////

void LCD_init(void);
void lcd_goto_XY(unsigned char row, unsigned char col);
void LCD_write_string(unsigned char *string);
void show_lcd_screen_by_lcd_screen_data(void);
void write_lcd_screen_data(int row, int col, unsigned char data);
void move_right_to_left_lcd_screen_data(void);
void lcd_message_start(void);
void lcd_message_end(void);
void LCD_write_command_4bit(unsigned char command);
void LCD_write_command_8bit(unsigned char command);
void LCD_clear(void);
void LCD_write_data(unsigned char data);




#endif /* LCD_H_ */