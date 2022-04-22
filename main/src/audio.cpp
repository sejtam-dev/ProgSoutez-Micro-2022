#include "audio.h"

#include "main.h"
#include "pitches.h"

void audio_dot()
{
	buzzer.play(NOTE_A2);
	sleep_ms(200);
	buzzer.stop();
}

void audio_dash()
{
	buzzer.play(NOTE_A2);
	sleep_ms(500);
	buzzer.stop();
}

void audio_end_of_symbol()
{
	sleep_ms(500);
}

void audio_end_of_letter()
{
	sleep_ms(1000);
}

void audio_end_of_message()
{
	
}