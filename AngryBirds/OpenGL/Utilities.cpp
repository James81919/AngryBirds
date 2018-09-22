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

void Keyboard_Up(unsigned char _iKey, int _iX, int _iY)
{
	keyState[_iKey] = INPUT_RELEASED;
}

void Mouse(int _iButton, int _iGlutState, int _x, int _y)
{
	if (_iButton < 3)
	{
		MouseState[_iButton] = (_iGlutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	}
}

bool GetMouseButtonDown(int _iButton)
{
	if (_iButton < 3)
	{
		return (MouseState[_iButton] == INPUT_HOLD) ? true : false;
	}
}

bool GetKeyDown(unsigned char _cKey)
{
	return (keyState[_cKey] == INPUT_HOLD) ? true : false;
}

void ResetFalse()
{
	for (int i = 0; i < 255; i++)
	{
		keyState[i] = FALSE;
	}
}