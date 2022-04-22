#include "debug.h"

#include <cstdio>

void debug_dot()
{
	printf(".");
}

void debug_dash()
{
	printf("-");
}

void debug_end_of_symbol()
{
}

void debug_end_of_letter()
{
	printf("|");
}

void debug_end_of_message()
{
	printf("\n");
}