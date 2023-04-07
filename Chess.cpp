#include "Chess.h"
#include "Player.h"
#include <conio.h>






Chess::Chess()
{
	
	string n;
	int Clr = 0;
	char b;

	
	string file_name;
	
	cout << "Do you want to load the last game? (y/n)" << endl;
	do
	{
		cin >> b;
	} while (!(b=='y'||b == 'n'));
	
	if (b == 'n')  /// new file
	{
		file_name = "OOP-Chess.txt";
		fstream rdr(file_name);
		for (int i = 0; i < 2; i++)
		{
			cout << "What is the name of your Player " << i + 1 << endl;
			cin >> n;
			(i == 0) ? Clr = White : Clr = 0;  // 1st player will be white
			Plr[i] = new Player(n, Clr, i + 1);
		}
		turn = 0;
		
		B = new Board(rdr);
	}
	else
	{
		file_name = "Save-Chess.txt";
		fstream rdr(file_name);
		rdr >> n;
		
		Plr[0] = new Player(n,White,0);
		rdr >> n;
		Plr[1] = new Player(n,Black,1);
		rdr >> turn;
		B = new Board(rdr);
	}

	
	
	
	
}
bool Chess::Validate_pick(Player* Pl,Position x)
{
	
	
	if (x.row > 7 || x.col > 7 || x.row < 0 || x.col < 0)
	{
		return false;
	}
	Piece* p = B->get_Piece(x.row, x.col);
	if (p == nullptr)
	{
		return false;
	}
	if (Pl->getclr() != p->get_clr())
	{
		return false;
	}
	return true;
}
bool Chess::Validate_drop(Player* Pl, Position x)
{
	if (x.row > 7 || x.col > 7 || x.row < 0 || x.col < 0)
	{
		return false;
	}
	
	Piece* p = B->get_Piece(x.row, x.col);

	if (p != nullptr)
	{
		if (Pl->getclr() == p->get_clr())
		{
			return false;
		}
	}
	return true;
}
void Chess::turn_change()
{
	this->turn = (this->turn + 1) % 2;
}


//_______________________



bool Chess::piece_legality_check(Position Pick, Position Drop)
{
	return B->get_Piece(Pick.row, Pick.col)->Legal_Move(Drop);
}

void Chess::save_Load(int turn)
{
	ofstream wrt("Save-Chess.txt");
	wrt << (Plr[0]->get_name()) << endl;
	wrt << (Plr[1]->get_name()) << endl;
	wrt << turn << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* p = B->get_Piece(i, j);
			if ( p!= nullptr)
			{
				wrt << B->get_Piece(i, j)->get_sym();
			}
			else
			{
				wrt << "-";
			}

		}
		wrt << endl;
	}

}

void time_sub(int turn,int &p1,int&p2,int subt_time)
{
	if (turn == 0)
	{
		p1 -= subt_time;


	}
	else
	{
		p2 -= subt_time;
	}
}


//__________________________________


void Chess::play_Chess()
{
	Position source;
	Position dst;
	
	Board* undo_B_arr=new Board(*this->B); // 100 Boards space for undo redo
	Board* redo_B_arr = new Board(*this->B);
	int index = 0,Board_count=0;// index for index off array of boards, while Board_count wil keep the count of total boards created 
	int p1 = 300, p2 = 300;
	long long int ini_time,final_time;
	bool in_check = false;
	bool should_rehighlight = false,casteling_check=false;
	int prow_check = -1, pcol_check = -1; // for stoping the repitition of source and destination in SelectPosition function 
	bool undo_bool = 0;
	bool redo_bool = 0;
	int undo_int = 0, redo_int = 0;
	system("cls");
	undo_button();
	redo_button();
	while (true)
	{
		// Windows size
        // Width = 166
        // Height = 86
		gotoRowCol(20, (166 / 2)+13);
		cout << Plr[0]->get_name() << "'s remaining time is: " << p1;
		gotoRowCol(22, (166 / 2) + 13);
		cout << Plr[1]->get_name() << "'s remaining time is: " << p2;
		if (p1 <= 0)
		{

			system("cls");
			gotoRowCol(86 / 2, (166 / 2) - 6);
			cout << Plr[0]->get_name() << " with White side has lost because his time has run out";
			return;
		}
		else if(p2<= 0)
		{
			system("cls");
			gotoRowCol(86 / 2, (166 / 2) - 6);
			cout << Plr[1]->get_name() << " with Black side has lost because his time has run out";
			return;
		}

		B->print_Board(0,0,false,turn);
		
		if (B->isPawnPromoted())
		{
			B->print_Board(0, 0, false,turn);
		}
		
		if (in_check == false) { cout << "\n\n                                                       "; }
		do 
		{
			

			in_check = false;   
			if (B->Self_check(turn)) // Checking if the king is in check
			{
				if (B->checkmate(turn))
				{
					system("cls");
					gotoRowCol(86 / 2, (166 / 2) - 6);
					cout << Plr[turn]->get_name() << " \n\nlost the game because he is in checkmate!!!!" << endl;
					return;
				}
				SetClr(Red);
				gotoRowCol((86 / 2) + 6, (166 / 2) + 15);
				cout << "Your King is in check" << endl;
				SetClr(White);
			}
			else
			{
				if (B->stale_Mate(turn))
				{
					system("cls");
					gotoRowCol(86 / 2, (166 / 2) - 6);
					cout << Plr[turn]->get_name() << "\n\nIs in stale mate so game is draw" << endl;
					return;
				}
			}
			do
			{
				do
				{
					if (should_rehighlight)
					{
						B->print_Board(0, 0, false,turn);
					}
					should_rehighlight = false;
					do
					{
					
						do
						{
							do
							{
								
								if (redo_bool == true || undo_bool == true)
								{
									B->print_Board(0, 0, false, turn);
								}
								redo_bool = false; undo_bool = false;

								gotoRowCol(25, (166 / 2) + 15); cout << "It is "<<Plr[turn]->get_name();
								if (turn == 0) { cout << "'s turn with White Pieces"; }
								else { cout << "'s turn with Black Pieces"; }
								ini_time = time(0);
								source = Plr[turn]->Selectposition(prow_check, pcol_check);
								if (undo_signal(source))
								{
									
									
									if (undo_int ==0)
									{
										B->undo(undo_B_arr);
										turn_change();
										undo_bool = true;
									}
									undo_int++;
									
									
								}


							} while (undo_bool);
							if (redo_signal(source))
							{
								
								
								if (redo_int == 0 && undo_int>0)
								{
									B->redo();
									turn_change();
									redo_bool = true;
								}
								redo_int++;
							   
							}
						
						} while (redo_bool);
					
					} while (!Validate_pick(Plr[turn], source));
					B->print_Board(source.row, source.col, true, turn);
					dst = Plr[turn]->Selectposition(prow_check, pcol_check);
					if (B->casteling(source, dst, turn, undo_B_arr))
					{
						casteling_check = true;
						break;
					}
					
					if (!Validate_drop(Plr[turn], dst))
					{
						should_rehighlight = true;
					}

				} while (should_rehighlight);
				should_rehighlight = false;
				if (casteling_check == true) { break; }
				      // is the drop of piece present at position (source) legal at position (dst)
			} while (!piece_legality_check(source, dst));
			if (casteling_check != true) 
			{
				if (B->checker(source, dst, turn))
				{
					SetClr(Red);
					gotoRowCol((86 / 2)+6, (166 / 2)+15);
					cout << "NOTE: Your king will be in check";
					in_check = true;
					SetClr(White);
				}
			}
			
		
		} while (in_check);
		gotoRowCol((86 / 2) + 6, (166 / 2) + 15);
		cout << "                                 ";
		gotoRowCol((86 / 2) + 6, (166 / 2) + 14);
		cout << "                                                ";
		undo_bool = false;  
		redo_bool = false;
		undo_int = 0; 
 		redo_int = 0;
		
		
		if(casteling_check == false){
			B->undo_Board_Loader(undo_B_arr);
			B->move_piece(source, dst); 
			turn_change();
		}
		final_time = time(0);
		time_sub(turn, p1, p2, final_time - ini_time);  // calculating the time of players
		save_Load(turn);
		casteling_check = false;
	}
	_getch();
}

void Chess::undo_button()
{
	SetClr(85);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			gotoRowCol(0 + i, 127 + j);
			cout << char(-37);


		}
	}
	SetClr(82);
	gotoRowCol(0+2, 127 + 2);
	cout << "UNDO";
	SetClr(White);


}

void Chess::redo_button()
{
	SetClr(85);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			gotoRowCol(10 + i, 137 + j);
			cout << char(-37);


		}
	}
	SetClr(82);
	gotoRowCol(10 + 2, 137 + 2);
	cout << "REDO";
	SetClr(White);

}

bool Chess::undo_signal(Position x)
{
	if ((x.row == 0 && x.col == 12))
	{
		return true;
	}
	return false;
}

bool Chess::redo_signal(Position x)
{
	if (((x.row == 1 || x.row == 2) && x.col == 13))
	{
		return true;
	}
	return false;
}







/*
bool Chess::Horizontal_move_othenticator(const Position& drop)
{
	int strt_point = 0, end_point = 0;

	if (this->Origin.col < drop.col)
	{
		strt_point = this->Origin.col;
		end_point = drop.col;

	}
	else
	{
		strt_point = drop.col;
		end_point = this->Origin.col;
	}

	for (int check = strt_point + 1; check < end_point; check++)
	{


		Piece* p = B->get_Piece(this->Origin.row, check);
		if (p != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Chess::Verticle_move_othenticator(const Position& drop)
{
	int strt_point = 0, end_point = 0;

	if (this->Origin.row < drop.row)
	{
		strt_point = this->Origin.row;
		end_point = drop.row;

	}
	else
	{
		strt_point = drop.row;
		end_point = this->Origin.row;
	}

	for (int check = strt_point + 1; check < end_point; check++)
	{


		Piece* p = B->get_Piece(check, this->Origin.col);
		if (p != nullptr)
		{
			return false;
		}
	}
	return true;
}


bool Chess::Diagnal_move_othenticator_1(const Position& drop) // from top left to bottom right and vice versa
{
	int strt_row = 0, strt_col = 0, end_row = 0, end_col = 0;
	int difference = 0;
	if (this->Origin.row < drop.row)
	{
		difference = (drop.row - this->Origin.row) - 1;
		strt_row = this->Origin.row + 1;
		strt_col = this->Origin.col + 1;
	}
	else
	{
		difference = (this->Origin.row - drop.row) - 1;
		strt_row = drop.row + 1;
		strt_col = drop.col + 1;
	}
	for (int i = 0; i < difference; i++)
	{
		if (B->get_Piece(strt_row + i, strt_col + i) != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Chess::Diagnal_move_othenticator_2(const Position& drop) // from top right to bottom left and vice versa
{

	int strt_row = 0, strt_col = 0, end_row = 0, end_col = 0;
	int difference = 0;
	if (this->Origin.row < drop.row)
	{
		difference = (drop.row - this->Origin.row) - 1;
		strt_row = this->Origin.row + 1;
		strt_col = this->Origin.col + 1;
	}
	else
	{
		difference = (this->Origin.row - drop.row) - 1;
		strt_row = drop.row + 1;
		strt_col = drop.col + 1;
	}
	for (int i = 0; i < difference; i++)
	{
		if (B->get_Piece(strt_row + i, strt_col - i) != nullptr)
		{
			return false;
		}
	}
	return true;
}
*/






 



