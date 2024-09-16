/*
 * PiezoSpeaker.c
 *
 * Created: 2024-09-15(일) 오후 10:53:45
 *  Author: step
 */ 
#include "../main.h"

void speaker_tone(int freq, int duration_ms){
	//설명 : 피에조스피커는 주파수에 의해서 소리 음높이가 정해진다. Mode : 14, datasheet(ATmega128) : p.132
	int temp, temp2;
	
	//Top
	//공식에 의해서 TOP을 조절하여 pwm frequency를 조절한다. 소수점은 버려진다. temp가 int형이기 때문이다. (정수형) temp는 top이다.
	temp = (16000000/freq-64)*0.015625;  
	
	//duty-cycle
	temp2 = temp/2;
	OCR1A=temp2; //duty cycle : 50%
	
	//Top
	ICR1= temp;
	
	
	custom_delay(duration_ms);
}


void speaker_tone_stop(void){
	
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	speaker_tone(250000, 0);  //speaker_tone() 함수의 temp를 0으로 주기 위해서이다.
	
}

void speaker_tone_init(void){
	DDRB = 0x20; //0010 0000 (PB5)
	
	//모드 : 10 bit fast pwm, non-inverting mode
	TCCR1B |= (1 << WGM13) |(1 << WGM12);
	TCCR1A |= (1 << WGM11) | (0 << WGM10) | (1<<COM1A1) | (0 << COM1A0);
	
	//pre-scaler
	TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10);  //pre-scaler : 64
	
	
}

void speaker_tone_message_start(void){
	speaker_tone(262, 100);  //도
	speaker_tone(294, 100);  //레
	speaker_tone(330, 100);  //미
	speaker_tone(349, 100);  //파
	speaker_tone(392, 100);  //솔
}

void speaker_tone_message_end(void){
	speaker_tone(392, 100);  //솔
	speaker_tone(349, 100);  //파
	speaker_tone(330, 100);  //미
	speaker_tone(294, 100);  //레
	speaker_tone(262, 100);  //도
}
