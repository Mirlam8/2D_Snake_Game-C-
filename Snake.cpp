#include "pch.h"
#include "Snake.h"
#include "gl/glut.h"

#define MAX 50
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

int posx[MAX + 1] = { 4,3,2,1,0,-1,-1 };
int posy[MAX + 1] = { 10,10,10,10,10,10,10 };
int length = 7;
int s_game_col;
int s_game_row;
bool s_game_over = false;

Snake::Snake(int col, int row)
{
	s_game_col = col;
	s_game_row = row;
}
Snake::~Snake()
{
}

int Snake::get_head_x() {
	return posx[0];
}
int Snake::get_head_y() {
	return posy[0];
}

void Snake::eat_apple() {
	length += 1;
}

void Snake::draw_snake(int direction)
{
	for (int i = length - 1; i > 0; i--)
	{
		posx[i] = posx[i - 1];
		posy[i] = posy[i - 1];
	}
	for (int i = 0; i < length; i++)
	{
		// ¸ö»ö
		glColor3f(0.0, 0.6, 0.0);
		if (i == 0)
		{
			// ¸Ó¸®»ö
			glColor3f(0.0, 0.4, 0.0);
			switch (direction)
			{
			case UP:
				posy[i]++;
				break;

			case DOWN:
				posy[i]--;
				break;

			case RIGHT:
				posx[i]++;
				break;

			case LEFT:
				posx[i]--;
				break;
			}
			// º®¿¡ ºÎµúÈ÷¸é
			if (posx[i] == 0 || posx[i] == s_game_col -1 || posy[i] == 0 || posy[i] == s_game_row -1) {
				s_game_over = true;
			}
			// ÀÚ±â ¸ö¿¡ ºÎµúÈ÷¸é
			for (int j = 1; j < length; j++)
			{
				if (posx[j] == posx[0] && posy[j] == posy[0])
					s_game_over = true;
			}
		}
		glBegin(GL_QUADS);
		glVertex2d(posx[i], posy[i]); glVertex2d(posx[i] + 1, posy[i]); glVertex2d(posx[i] + 1, posy[i] + 1); glVertex2d(posx[i], posy[i] + 1);
		glEnd();
	}
}

bool Snake::check_over() {
	return s_game_over;
}