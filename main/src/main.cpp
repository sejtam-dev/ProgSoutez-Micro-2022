#include "main.h"

#include <pico.h>
#include <pico/stdio.h>
#include <pico/multicore.h>
#include <hardware/gpio.h>

#include "debug.h"
#include "visual.h"
#include "audio.h"

// ### CALLBACKS ###
output_function dot = &audio_dot;
output_function dash = &audio_dash;
output_function end_of_symbol = &audio_end_of_symbol;
output_function end_of_letter = &audio_end_of_letter;
output_function end_of_message = &audio_end_of_message;
// --- CALLBACKS ---


// ### HARDWARE ###
Buzzer buzzer;

Button buttonLeft(BUTTON_LEFT_PIN, ButtonType::PullUp);
Button buttonRight(BUTTON_RIGHT_PIN, ButtonType::PullUp);

State state = State::AUDIO;
// --- HARDWARE ---


int main()
{
	// Init hardware
	stdio_init_all();

	buttonLeft.init();
	buttonRight.init();

	buzzer.begin(BUZZER_PIN);

	// Init GPIO pins
	gpio_init(LED_SELECT_1_PIN);
	gpio_init(LED_SELECT_2_PIN);
	gpio_init(LED_SELECT_3_PIN);
	gpio_init(LED_VISUAL_PIN);

	gpio_set_dir(LED_SELECT_1_PIN, true);
	gpio_set_dir(LED_SELECT_2_PIN, true);
	gpio_set_dir(LED_SELECT_3_PIN, true);
	gpio_set_dir(LED_VISUAL_PIN, true);

	gpio_put(LED_SELECT_3_PIN, true);

	// Init second core
	multicore_launch_core1(core1_main);

	// Wait for initialization
	sleep_ms(2000);

	// Main loop
	// Used for reading user input
	while(true)
	{
		printf("Ready...\n");

		int c;
		std::string inputMessage;

		// Read Message from UART
		do {
			c = getchar();
			inputMessage += c;
		} while (c != '\n');

		if (inputMessage.size() == 0)
			continue;

		// Transmit message
		transmit(inputMessage);
	}
}

void core1_main()
{
	// Second main loop
	// Used for changing states
	while(true)
	{
		// Update buttons
		buttonLeft.tick();
		buttonRight.tick();

		int8_t stateNumber = static_cast<int8_t>(state);
		bool change = false;

		// Check Left Button (Blue Cap) state
		ButtonState leftButtonState = buttonLeft.getState();
		if(leftButtonState == ButtonState::ShortPress || leftButtonState == ButtonState::LongPress)
		{
			stateNumber--;
			change = true;
		}

		// Check Right Button (Yellow Cap) state
		ButtonState rightButtonState = buttonRight.getState();
		if (rightButtonState == ButtonState::ShortPress || rightButtonState == ButtonState::LongPress)
		{
			stateNumber++;
			change = true;
		}

		if (!change)
			continue;

		// Limits
		if (stateNumber < 0)
			stateNumber = 2;

		if (stateNumber > 2)
			stateNumber = 0;

		// Change state
		state = static_cast<State>(stateNumber);

		gpio_put(LED_SELECT_1_PIN, false);
		gpio_put(LED_SELECT_2_PIN, false);
		gpio_put(LED_SELECT_3_PIN, false);

		// Change callbacks and led diode
		switch (state)
		{
		case State::DEBUG:
			{
			gpio_put(LED_SELECT_1_PIN, true);

			dot = &debug_dot;
			dash = &debug_dash;
			end_of_symbol = &debug_end_of_symbol;
			end_of_letter = &debug_end_of_letter;
			end_of_message = &debug_end_of_message;

			break;
			}
		case State::VISUAL:
			{
			gpio_put(LED_SELECT_2_PIN, true);

			dot = &visual_dot;
			dash = &visual_dash;
			end_of_symbol = &visual_end_of_symbol;
			end_of_letter = &visual_end_of_letter;
			end_of_message = &visual_end_of_message;

			break;
			}
		case State::AUDIO:
			{
			gpio_put(LED_SELECT_3_PIN, true);

			dot = &audio_dot;
			dash = &audio_dash;
			end_of_symbol = &audio_end_of_symbol;
			end_of_letter = &audio_end_of_letter;
			end_of_message = &audio_end_of_message;

			break;
			}
		}
	}
}

void transmit(std::string message) {
	// Read Message
	for (int i = 0; i < message.size(); i++)
	{
		char c = message[i];
		if (c == '\n')
		{
			end_of_message();
			continue;
		}

		// Read morse code chars
		std::string code = charToMorse(c);
		for(int j = 0; j < code.size(); j++)
		{
			char c1 = code[j];
			if (c1 == '.')
				dot();

			if (c1 == '-')
				dash();

			end_of_symbol();
		}
		end_of_letter();
	}
}

std::string charToMorse(char c)
{
	// Get morse code from map
	const auto code = morseCode.find(tolower(c));
	if (code != morseCode.end()) {
		return code->second;
	}

	return "";
}