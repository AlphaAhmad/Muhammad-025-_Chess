#pragma once
#include <string>
#include <iostream>
#include "Piece.h"

using namespace std;





class Player
{
protected:
	string name;
	int clr;
	int turn;
public:
	Player(){}
	Player(string name, int clr, int Turn);
	
	int getclr() { return clr; }
	int get_turn() { return turn; }
	string get_name() { return name; }
	
	Position Selectposition(int& prow_check,int& pcol_check);

	// is the pic valid will be decided by the chess 
	
};

