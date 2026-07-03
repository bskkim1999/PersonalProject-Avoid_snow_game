/*
 * LCD.c
 *
 * Created: 2024-09-15(일) 오후 10:53:30
 *  Author: step
 */ 
#include "../main.h"

//lcd control source code
void LCD_init(void){
	
	_delay_ms(50);
	
	/*step1 : 3의 값을 3번 줌.*/
	LCD_write_command_4bit(0x30); _delay_ms(5); // 0011 0000
	//status[0] = TWSR;
	
	LCD_write_command_4bit(0x30); _delay_us(100); // 0011 0000
	//status[1] = TWSR;
	
	LCD_write_command_4bit(0x30); _delay_us(100); // 0011 0000
	//status[2] = TWSR;
	
	LCD_write_command_4bit(0x20); _delay_us(100); // 0011 0000
	//status[3] = TWSR;
	
	/*step2 : Function set*/ //4비트, 2행, 5*8 폰트
	LCD_write_command_8bit(0x28); _delay_us(50);
	//status[4] = TWSR;
	
	/*step3 : display on / off control */
	LCD_write_command_8bit(0x08); _delay_us(50);
	//status[5] = TWSR;
	
	/*step4 : clean screen*/
	LCD_clear();  //화면 지움
	//status[6] = TWSR;
	
	/*step5 : entry mode set */
	//출력 후 커서를 오른쪽으로 옮김. DDRAM의 주소가 증가하며 화면 이동은 없음.
	LCD_write_command_8bit(0x06);
	//status[7] = TWSR;
	/*step6 : display on, cursor & cursor blink off*/
	LCD_write_command_8bit(0x0c);
	//status[8] = TWSR;
	
}

void lcd_goto_XY(unsigned char row, unsigned char col)
{
	unsigned char address = (0x40 * row) + col;
	unsigned char command = 0x80 | address;
	
	LCD_write_command_8bit(command);
}

void LCD_write_string(unsigned char *string){
	unsigned char i;
	for(i=0 ; string[i] != '\0' ; i++){
		LCD_write_data(string[i]);
	}
}


void show_lcd_screen_by_lcd_screen_data(void){
	
	for(int row = 0 ; row < 2 ; row++){
		for(int col = 0; col<16 ; col++){
			lcd_goto_XY(row, col);   //lcd의 지정된 행과 열로 커서를 옮긴 후
			LCD_write_data( lcd_screen_data[row][col]);  // 그 자리에 글자를 write한다.
			
		}
	}
	
}

void write_lcd_screen_data(int row, int col, unsigned char data){
	
	unsigned char (*ptr) [16] = lcd_screen_data;  //2차원 배열의 포인터이다.
	ptr[row][col] = data;
	
	
}

void move_right_to_left_lcd_screen_data(void){
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 1; j < 16 - 1; ++j) {
			lcd_screen_data[i][j] = lcd_screen_data[i][j + 1];
		}
	}
}

void lcd_message_start(void){
	lcd_goto_XY(0,0);
	LCD_write_data('a');
	LCD_write_data('v');
	LCD_write_data('o');
	LCD_write_data('i');
	LCD_write_data('d');
	LCD_write_data(' ');
	LCD_write_data('t');
	LCD_write_data('h');
	LCD_write_data('e');
	LCD_write_data(' ');
	LCD_write_data('s');
	LCD_write_data('n');
	LCD_write_data('o');
	LCD_write_data('w');
	lcd_goto_XY(1,0);
	LCD_write_data('M');
	LCD_write_data('a');
	LCD_write_data('d');
	LCD_write_data('e');
	LCD_write_data(' ');
	LCD_write_data('b');
	LCD_write_data('y');
	LCD_write_data(' ');
	LCD_write_data('b');
	LCD_write_data('o');
	LCD_write_data('s');
	LCD_write_data('e');
	LCD_write_data('o');
	LCD_write_data('k');
}

void lcd_message_end(void){
	LCD_clear();
	lcd_goto_XY(0,0);
	LCD_write_data('g');
	LCD_write_data('a');
	LCD_write_data('m');
	LCD_write_data('e');
	LCD_write_data(' ');
	LCD_write_data('o');
	LCD_write_data('v');
	LCD_write_data('e');
	LCD_write_data('r');
	LCD_write_data(' ');
	LCD_write_data(1);
	LCD_write_data(' ');
	LCD_write_data(1);
	LCD_write_data(' ');
	LCD_write_data(1);
	lcd_goto_XY(1,0);
	LCD_write_data('s');
	LCD_write_data('c');
	LCD_write_data('o');
	LCD_write_data('r');
	LCD_write_data('e');
	LCD_write_data(':');
	
	
}

void LCD_write_command_4bit(unsigned char command){
	// 상위 4비트만 twi 전송함.
	int lcd_buf[2]={0};
	
	lcd_buf[0] = (command & 0xF0) | RS_LOW_EN_high | Backlight ;  //상위 4비트
	lcd_buf[1] = ( command & 0xF0) | RS_LOW_EN_low | Backlight;
	
	TWI_Write(lcd_buf[0]);  // task1
	again_write_address();
	
	TWI_Write(lcd_buf[1]);  // task2
	again_write_address();
	
	_delay_ms(2);
}

void LCD_write_command_8bit(unsigned char command){
	// 상위 4비트와 하위 4비트를 twi 전송함.
	int lcd_buf[4]={0};
	
	lcd_buf[0] = (command & 0xF0) | RS_LOW_EN_high | Backlight;  //상위 4비트
	lcd_buf[1] = ( command & 0xF0) | RS_LOW_EN_low | Backlight;
	lcd_buf[2] = ( (command << 4)  & 0xF0) | RS_LOW_EN_high | Backlight;  //하위 4비트
	lcd_buf[3] = ( (command << 4) & 0xF0) | RS_LOW_EN_low | Backlight;
	
	TWI_Write(lcd_buf[0]);  // task1
	again_write_address();
	
	TWI_Write(lcd_buf[1]);  // task1
	again_write_address();
	
	TWI_Write(lcd_buf[2]);  // task2
	again_write_address();
	
	TWI_Write(lcd_buf[3]);  // task2
	again_write_address();
	
}

void LCD_clear(void){
	LCD_write_command_8bit(COMMAND_CLEAR_DISPLAY);   //command = 0x01
	_delay_ms(5);
}

void LCD_write_data(unsigned char data){
	
	// 상위 4비트와 하위 4비트를 twi 전송함.
	int lcd_buf[4]={0};
	
	lcd_buf[0] = (data & 0xF0) | RS_HIGH_EN_high | Backlight;  //상위 4비트
	lcd_buf[1] = ( data & 0xF0) | RS_HIGH_EN_low | Backlight;
	lcd_buf[2] = ( (data << 4)  & 0xF0) | RS_HIGH_EN_high | Backlight;  //하위 4비트
	lcd_buf[3] = ( (data << 4) & 0xF0) | RS_HIGH_EN_low | Backlight;
	
	TWI_Write(lcd_buf[0]);  // task1
	again_write_address();
	
	TWI_Write(lcd_buf[1]);  // task1
	again_write_address();
	
	TWI_Write(lcd_buf[2]);  // task2
	again_write_address();
	
	TWI_Write(lcd_buf[3]);  // task2
	again_write_address();
	
}
