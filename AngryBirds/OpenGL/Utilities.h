#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <Box2D\Box2D.h>
#include "Dependencies\Box2D\Common\b2Draw.h"
#include "b2GLDraw.h"

#include <glm.hpp>
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;

enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASED,
	INPUT_FIRST_PRESS,
	INPUT_HOLD
};

void Keyboard_Down(unsigned char key, int x, int y);

void Keyboard_Up(unsigned char key, int x, int y);