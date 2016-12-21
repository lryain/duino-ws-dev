#include "pitches.h"
#define buzzer_pin 8
// notes in the melody:
int melody[] = {
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500; // 500 miliseconds

void setup() {

}

void loop() {
for ( int thisNote = 0; thisNote< 8; thisNote++) {
// 在pin8 上输出声音，每个音阶响0.5 秒
tone(buzzer_pin, melody[thisNote], duration);

// 间隔一段时间后再播放下一个音阶
delay(300);
}

// 两秒后重新播放
delay(1000);
}
