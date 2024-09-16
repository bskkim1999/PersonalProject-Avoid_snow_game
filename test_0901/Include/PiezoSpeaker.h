/*
 * PiezoSpeaker.h
 *
 * Created: 2024-09-15(일) 오후 10:53:16
 *  Author: step
 */ 


#ifndef PIEZOSPEAKER_H_
#define PIEZOSPEAKER_H_

void speaker_tone(int freq, int duration_ms);
void speaker_tone_stop(void);
void speaker_tone_init(void);
void speaker_tone_message_start(void);
void speaker_tone_message_end(void);



#endif /* PIEZOSPEAKER_H_ */