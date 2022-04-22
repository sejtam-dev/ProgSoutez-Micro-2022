#pragma once

#include <button.h>
#include <buzzer.h>

#include <cstdio>
#include <string>
#include <map>

// ### PINS ###
#define BUTTON_LEFT_PIN 9
#define BUTTON_RIGHT_PIN 13

#define LED_SELECT_1_PIN 10
#define LED_SELECT_2_PIN 11
#define LED_SELECT_3_PIN 12
#define LED_VISUAL_PIN 14

#define BUZZER_PIN 15
// --- PINS ---


// ### CALLBACKS ###
typedef void(*output_function)();

extern output_function dot, dash, end_of_symbol, end_of_letter, end_of_message;
// --- CALLBACKS ---


// ### ENUMS ###
enum class State
{
	DEBUG, VISUAL, AUDIO
};
// --- ENUMS ---

// ### VALUES ###
static const std::map<char, std::string> morseCode = {
    { 'a', ".-" },
    { 'b' , "-..." },
    { 'c', "-.-." },
	{ 'd', "-..."},
    { 'e', "."},
    { 'f', "..-."},
    { 'g', "--."},
    { 'h', "...."},
    { 'i', ".."},
    { 'j', ".---"},
    { 'k', "-.-"},
    { 'l', ".-.."},
    { 'm', "--"},
    { 'n', "-."},
    { 'o', "---"},
    { 'p', ".--."},
    { 'q', "--.-"},
    { 'r', ".-."},
    { 's', "..."},
    { 't', "-"},
    { 'u', "..-"},
    { 'v', "...-"},
    { 'w', ".--"},
    { 'x', "-..-"},
    { 'y', "-.--"},
    { 'z', "--.." }
};
// --- VALUES ---

// ### HARDWARE ###
extern Buzzer buzzer;

extern Button buttonLeft;
extern Button buttonRight;

extern State state;
// --- HARDWARE ---

// ### METHODS ###
void core1_main();

void transmit(std::string message);
std::string charToMorse(char c);
// --- METHODS ---