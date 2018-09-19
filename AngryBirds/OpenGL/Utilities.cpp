#pragma once
#include "Utilities.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

unsigned char keyState[255];

void Keyboard_Down(unsigned char key, int x, int y)
{
	keyState[key] = INPUT_HOLD;
}

void Keyboard_Up(unsigned char key, int x, int y)
{
	keyState[key] = INPUT_RELEASED;
}

void ResetFalse()
{
	for (int i = 0; i < 255; i++)
	{
		keyState[i] = FALSE;
	}
}