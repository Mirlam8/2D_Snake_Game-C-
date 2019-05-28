#pragma once
class Snake
{
public:
	Snake(int, int);
	~Snake();
	int get_head_x();
	int get_head_y();
	void eat_apple();
	void draw_snake(int direction);
	bool check_over();
};

