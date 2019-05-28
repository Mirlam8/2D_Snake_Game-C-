#pragma once
class Apple
{
public:
	Apple();
	Apple(int col, int row);
	~Apple();
	int get_apple_x();
	int get_apple_y();
	void draw_apple();
	void replace();
	int random(int _min, int _max);
	void eat_apple();
};

