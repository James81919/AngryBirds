#pragma once
#include "Utilities.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

unsigned char g_cKeyState[255];
unsigned char g_cMouseState[3];

glm::vec2 g_mousePos;

void Keyboard_Down(unsigned char key, int x, int y)
{
	g_cKeyState[key] = INPUT_HOLD;
}

void Keyboard_Up(unsigned char _iKey, int _iX, int _iY)
{
	g_cKeyState[_iKey] = INPUT_RELEASED;
}

void Mouse(int _iButton, int _iGlutState, int _x, int _y)
{
	if (_iButton < 3)
	{
		g_cMouseState[_iButton] = (_iGlutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	}

	//g_mousePos.x = ((float)_x / WINDOW_WIDTH) * 25;
	//g_mousePos.y = (1 - (float)_y / WINDOW_HEIGHT) * 15;
}

void Mouse_Down(int x, int y)
{
	g_mousePos.x = ((float)x / WINDOW_WIDTH) * 25;
	g_mousePos.y = (1 - (float)y / WINDOW_HEIGHT) * 15;
}

bool GetMouseButtonDown(int _iButton)
{
	if (_iButton < 3)
	{
		return (g_cMouseState[_iButton] == INPUT_HOLD) ? true : false;
	}
}

bool GetMouseButtonUp(int _iButton)
{
	if (_iButton < 3)
	{
		return (g_cMouseState[_iButton] == INPUT_RELEASED) ? true : false;
	}
}

bool GetKeyDown(unsigned char _cKey)
{
	return (g_cKeyState[_cKey] == INPUT_HOLD) ? true : false;
}

bool GetKeyUp(unsigned char _cKey)
{
	return (g_cKeyState[_cKey] == INPUT_RELEASED) ? true : false;
}

glm::vec2 GetMousePosition()
{
	return (g_mousePos);
}

void ResetFalse()
{
	for (int i = 0; i < 255; i++)
	{
		g_cKeyState[i] = FALSE;
	}
}