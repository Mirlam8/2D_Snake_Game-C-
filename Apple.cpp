#include "pch.h"
#include "Apple.h"
#include "gl/glut.h"
#include <ctime>

int apple_x;
int apple_y;
int game_col;
int game_row;
bool seedflag = false;

Apple::Apple(int col, int row)
{
	game_col = col;
	game_row = row;
	apple_x = random(2, game_col - 2);
	apple_y = random(2, game_row - 2);
}

Apple::~Apple()
{
}

int Apple::get_apple_x()
{
	return apple_x;
}
int Apple::get_apple_y()
{
	return apple_y;
}

void Apple::draw_apple() 
{
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.0, 0.0);
	glVertex2d(apple_x, apple_y);
	glVertex2d(apple_x + 1, apple_y);
	glVertex2d(apple_x + 1, apple_y + 1);
	glVertex2d(apple_x, apple_y + 1);
	glEnd();
}
void Apple::replace() {
	apple_x = random(2, game_col - 2);
	apple_y = random(2, game_row - 2);
}

int Apple::random(int _min, int _max)
{
	if (!seedflag)
	{
		srand(time(NULL));
		seedflag = true;
	}
	else
		seedflag = false;
	return _min + rand() % (_max - _min);
}