#pragma once
#include "Utilities.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

unsigned char keyState[255];
unsigned char MouseState[3];

void Keyboard_Down(unsigned char key, int x, int y)
{
	keyState[key] = INPUT_HOLD;
}

void Keyboard_Up(unsigned char key, int x, int y)
{
	keyState[key] = INPUT_RELEASED;
}

void Mouse(int button, int glutState, int x, int y)
{
	if (button < 3)
	{
		MouseState[button] = (glutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	}
}

void ResetFalse()
{
	for (int i = 0; i < 255; i++)
	{
		keyState[i] = FALSE;
	}
}