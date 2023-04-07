#pragma once
#include<windows.h>
//enum color { Black = 0, White = 15 };
#define Black 0
#define Brown 6
#define White 15
#define Green 2
#define Red 4
#define LBlue 9


void gotoRowCol(int rpos, int cpos);

void SetClr(int clr);
class Position
{
public:
	int row = 0;
	int col = 0;

	Position();
	Position(int x, int y);
};

void getRowColbyLeftClick(int& rpos, int& cpos);
