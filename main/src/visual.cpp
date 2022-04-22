#include "visual.h"

#include "main.h"

void visual_dot()
{
	gpio_put(LED_VISUAL_PIN, true);
	sleep_ms(200);
	gpio_put(LED_VISUAL_PIN, false);
}

void visual_dash()
{
	gpio_put(LED_VISUAL_PIN, true);
	sleep_ms(500);
	gpio_put(LED_VISUAL_PIN, false);
}

void visual_end_of_symbol()
{
	sleep_ms(500);
}

void visual_end_of_letter()
{
	sleep_ms(1000);
}

void visual_end_of_message()
{
	
}