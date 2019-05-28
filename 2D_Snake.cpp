// 2D_Snake.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <GL/glut.h>
#include <iostream>
#include "Snake.h"
#include "Apple.h"

// 가로 세로 화면 나누기
// 가로 40 칸 세로 40칸 
// 좌표계는 좌측 아래쪽이 (0,0) 
// 그리는 방향은 좌표에서 위로 한칸이 필요하기 때문에 최대 좌표는 (39,39)
#define ROWS 40.0
#define COLUMNS 40.0
// direction 입력 정의
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

void init();
void display();
void draw_wall();
void initGrid(int, int);
void input_key(int, int, int);
void reshape_callback(int, int);
void timer_callback(int);
void unit(int, int);

// 초기설정
bool game_over = false;
int direction = RIGHT;
int rows = 0, columns = 0;
Snake *snake;
Apple *apple;

void input_key(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (direction != DOWN)
			direction = UP;
		break;
	case GLUT_KEY_DOWN:
		if (direction != UP)
			direction = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (direction != LEFT)
			direction = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (direction != RIGHT)
			direction = LEFT;
		break;
	}
}

// fps 조절
void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(100, timer_callback, 0);
}


// 화면 초기화
void initGrid(int x, int y)
{
	columns = x;
	rows = y;
}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	initGrid(COLUMNS, ROWS);
}

// openGL 의 좌표계를 윈도우 좌표계로 변환
void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLfloat)w, GLfloat(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 벽만들기

void unit(int x, int y)
{
	glLoadIdentity();
	if (x == 0 || x == columns - 1 || y == 0 || y == rows - 1)
	{
		glLineWidth(2.0);
		glColor3f(0.5, 0.5, 0.5);
	}
	else
	{
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(1.0);
	}
	glBegin(GL_LINES);
	glVertex2d(x, y); glVertex2d(x + 1, y);
	glVertex2d(x + 1, y); glVertex2d(x + 1, y + 1);
	glVertex2d(x + 1, y + 1); glVertex2d(x, y + 1);
	glVertex2d(x, y + 1); glVertex2d(x, y);
	glEnd();
}

void draw_wall()
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			unit(i, j);
		}
	}
}

void display()
{
	if (game_over)
	{
		exit(0);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//그리기
	draw_wall();	
	apple->draw_apple();
	snake->draw_snake(direction);

	// 충돌감지 체크
	if(snake->check_over())
	{
		exit(0);
	}
	if (snake->get_head_x() == apple->get_apple_x() && snake->get_head_y() == apple->get_apple_y()) {
		snake->eat_apple();
		apple->replace();
	}
	glutSwapBuffers();
}

	int main(int argc, char**argv)
	{
		snake = new Snake(COLUMNS, ROWS);
		apple = new Apple(COLUMNS, ROWS);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowPosition(10, 10);
		glutInitWindowSize(600, 600);
		glutCreateWindow("2D SNAKE GAME");
		glutDisplayFunc(display);
		glutReshapeFunc(reshape_callback);
		glutSpecialFunc(input_key);
		glutTimerFunc(100, timer_callback, 0);
		init();
		glutMainLoop();
	return 0;
}
