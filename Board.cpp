#include "Board.h"
#include "Player.h"
#include "Bishop.h"
#include "King.h"
#include "Night.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include <cctype>

#include <string>



#include <fstream>


#define box_dim 10



Board::Board(fstream& rdr)
{
	
	
	/*if (file_name == "Save_Chess.txt")
	{
		string m;
		rdr >> m;
		rdr >> m;
		int mn;
		rdr>>mn;
	}*/
    Ps = new Piece ** [dim];
    char x;
    Board* B=this;
    for (int i = 0; i < dim; i++)
    {
        
        Ps[i] = new Piece*[dim];  // So board is a 2D array of Piece type single pointers
        for (int j = 0; j < dim; j++)
        {
			rdr >> x;
            if (x == 'r')
            {
                
                Ps[i][j] = new Rook (i, j, Black, B,x);    
            }
			else if (x == 'R') { Ps[i][j] = new Rook(i, j, White, B, x); }
            else if (x == 'n') { Ps[i][j] = new Night (i, j, Black, B,x);}
            else if (x == 'N') {  Ps[i][j] = new Night (i, j, White, B,x);}
            else if (x == 'b') { Ps[i][j] = new Bishop (i, j, Black, B,x);}
            else if (x == 'B') { Ps[i][j] = new Bishop (i, j, White, B,x);}
            else if (x == 'q') {  Ps[i][j] = new Queen (i, j, Black, B,x);}
            else if (x == 'Q') {  Ps[i][j] = new Queen (i, j, White, B,x);}
            else if (x == 'k') {  Ps[i][j] = new King (i, j, Black, B,x); }
            else if (x == 'K') { Ps[i][j] = new King (i, j, White, B,x);}
            else if (x == 'p') {   Ps[i][j] = new Pawn (i, j, Black, B,x);}
            else if (x == 'P') { Ps[i][j] = new Pawn (i, j, White, B,x);}
            else { Ps[i][j] = nullptr; }

        }
       

    }

}
// For printing circle in Graphical Highlighting
//void circle(int c_x, int c_y, int& r, char x) {  // Helping function 
//	float p_row = 0, p_col = 0;
//
//	for (int th = 0; th < 360; th++)
//	{
//		float rad = th * (3.14 / 180);
//		p_row = ceil(r * sin(rad)) + c_y;
//		p_col = ceil(r * cos(rad)) + c_x;
//		SetClr(LBlue);
//		gotoRowCol(p_row, p_col);
//		cout << x;
//	}
//}


void boundries(int strt_row,int strt_col)
{
	
	SetClr(Red);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == 0 || j == 0 || i == 9 || j == 9)
			{
				gotoRowCol(strt_row + i, strt_col + j);
				cout << char(-37);
			}
			
		}
			
	}
	SetClr(White);


}

void Board::printBox(int turn,int shift_r,int shift_c,int _r,int _c,int start_row,int start_col,int clr, int pick_r, int pick_c, bool is_highlight)
{
	int r = 4,count=0;
	SetClr(clr);  // for board 
    for (int i = 0; i < box_dim; i++)
    {
        for (int j = 0; j < box_dim; j++)
        {
            gotoRowCol((shift_r + start_row + i), (shift_c + start_col + j));
            cout << char(-37);

        }
    }
    int c = 0;
	if (Ps[_r][_c] != nullptr)
    {
        (Ps[_r][_c]->get_clr() == White) ? c = White : c = Red;
		SetClr(c);
		//gotoRowCol(shift_r + start_row + 5, shift_c + start_col+5);
		Position x(shift_r + start_row + 5, shift_c + start_col + 5);
		Ps[_r][_c]->Draw_Piece(x);
		//gotoRowCol(_r, _c);
    }
	Position Drop(_r, _c);
	if (is_highlight == true && Ps[pick_r][pick_c]->Legal_Move(Drop)&& !checkmate(turn))  // legality check
	{                // Checking drop vaidity consitions
		/*if ((Ps[pick_r][pick_c]->get_sym() == 'p' || Ps[pick_r][pick_c]->get_sym() == 'P')&&count==0)
		{
			Ps[pick_r][pick_c]->set_bool(false);
			count = 1;
		}*/
		if (Ps[Drop.row][Drop.col] != nullptr)
		{
			if ((Ps[pick_r][pick_c]->get_clr() != Ps[Drop.row][Drop.col]->get_clr()))
			{
				boundries((10 * Drop.row), (10 * Drop.col));
			}
		}
		else
		{
			boundries((10 * Drop.row), (10 * Drop.col));
		}
		
		
	}
    

}
                            // if we dont want to print board then there default values of coordinates will be zero
void Board::print_Board(int pick_r,int pick_c, bool is_highlight,int turn)
{
    // shitf_r and shift_c are for hifting board on the console screen
    int shift_r = 0, shift_c = 0;
	gotoRowCol(shift_r, shift_c);
	for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {                  // I am not creating another memory thats why i add 2 function calls
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
					this->printBox( turn,shift_r, shift_c, i, j, i * 10, j * 10, Green,pick_r,pick_c,is_highlight);
				}
				else
				{
					this->printBox(turn, shift_r, shift_c, i, j, i * 10, j * 10, LBlue, pick_r, pick_c, is_highlight);
				}
			}
			else 
			{
				if (j % 2 == 0)
				{
					this->printBox(turn, shift_r, shift_c, i, j, i * 10, j * 10, LBlue, pick_r, pick_c, is_highlight);
				}
				else
				{
					this->printBox(turn, shift_r, shift_c, i, j, i * 10, j * 10, Green, pick_r, pick_c, is_highlight);
				}
			}

			


        }
    }

	cout << "\n\n\n";
	SetClr(White);
}

//void Board::print_Board()
//{
//    
//    for (int i = 0; i < dim; i++)
//    {
//        for (int j = 0; j < dim; j++)
//        {
//            if (Ps[i][j] == nullptr)
//            {
//                cout << "-" << " ";
//            }
//            else
//            {
//                Ps[i][j]->Draw_Piece();
//                cout << " ";
//            }
//            
//        }
//        cout << endl;
//    }
//}
void Board::move_piece(Position src, Position Dst)
{
    Piece* p = Ps[src.row][src.col];
    Ps[src.row][src.col] = nullptr;
    Ps[Dst.row][Dst.col] = p;
    p = nullptr;
    Ps[Dst.row][Dst.col]->move(Dst.row, Dst.col);
}

//______________________________
bool Board::Horizontal_move_othenticator(const Position pick, const Position drop)
{
	int strt_point = 0, end_point = 0;

	if (pick.col < drop.col)
	{
		strt_point = pick.col;
		end_point = drop.col;

	}
	else
	{
		strt_point = drop.col;
		end_point = pick.col;
	}

	for (int check = strt_point + 1; check < end_point; check++)
	{


		Piece* p = Ps[pick.row][check];  //pick.row, check;
		if (p != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Board::Verticle_move_othenticator(const Position pick,const Position drop)
{
	int strt_point = 0, end_point = 0;

	if (pick.row < drop.row)
	{
		strt_point = pick.row;
		end_point = drop.row;

	}
	else
	{
		strt_point = drop.row;
		end_point = pick.row;
	}

	for (int check = strt_point + 1; check < end_point; check++)
	{


		Piece* p = Ps[check][pick.col];
		if (p != nullptr)
		{
			return false;
		}
	}
	return true;
}


bool Board::Diagnal_move_othenticator_1(const Position pick, const Position drop) // from top left to bottom right and vice versa
{
	int strt_row = 0, strt_col = 0, end_row = 0, end_col = 0;
	int difference = 0;
	if (pick.row < drop.row)
	{
		difference = (drop.row - pick.row) - 1;
		strt_row = pick.row + 1;
		strt_col = pick.col + 1;
	}
	else
	{
		difference = (pick.row - drop.row) - 1;
		strt_row = drop.row + 1;
		strt_col = drop.col + 1;
	}
	for (int i = 0; i < difference; i++)
	{
		if (Ps[strt_row + i][strt_col + i] != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Board::Diagnal_move_othenticator_2(const Position pick, const Position drop) // from top right to bottom left and vice versa
{

	int strt_row = 0, strt_col = 0, end_row = 0, end_col = 0;
	int difference = 0;
	if (pick.row < drop.row)
	{
		difference = (drop.row - pick.row) - 1;
		strt_row = pick.row + 1;
		strt_col = pick.col - 1;
	}
	else
	{
		difference = (pick.row - drop.row) - 1;
		strt_row = drop.row + 1;
		strt_col = drop.col - 1;
	}
	for (int i = 0; i < difference; i++)
	{
		if (Ps[strt_row + i][strt_col - i] != nullptr)
		{
			return false;
		}
	}
	return true;
}


void Board::Pawn_changer(char x,Position p)
{      // For white pawn
	if (isupper(x))       // if x is upper case return non zero, else zero  #Buitin Function
	{
		delete[]this->Ps[p.row][p.col];
		if (x == 'Q')
		{
			this->Ps[p.row][p.col] =new Queen(p.row, p.col, White, this, x);
		}
		else if (x == 'B')
		{
			this->Ps[p.row][p.col] = new Bishop(p.row, p.col, White, this, x);
		}
		else if (x == 'N')
		{
			this->Ps[p.row][p.col] = new Night(p.row, p.col, White, this, x);
		}
		else if (x == 'R')
		{
			this->Ps[p.row][p.col] = new Rook(p.row, p.col, White, this, x);
		}

	}
	   // For black pawn
	else
	{
		delete[]this->Ps[p.row][p.col];
		if (x == 'q')
		{
			this->Ps[p.row][p.col] = new Queen(p.row, p.col, Black, this, x);
		}
		else if (x == 'b')
		{
			this->Ps[p.row][p.col] = new Bishop(p.row, p.col, Black, this, x);
		}
		else if (x == 'n')
		{
			this->Ps[p.row][p.col] = new Night(p.row, p.col, Black, this, x);
		}
		else if (x == 'r')
		{
			this->Ps[p.row][p.col] = new Rook(p.row, p.col, Black, this, x);
		}
	}

}



bool Board::isPawnPromoted()
{
	Position p;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			p.row = i, p.col = j;
			if (this->Ps[p.row][p.col]!=nullptr)
			{
				if (this->Ps[p.row][p.col]->get_sym() == 'p')
				{
					char x;
					if (p.row == 7)
					{
						cout << "\n\n\nIn which piece Do you want to change\
			        your Black Pawn into( Queen: q  Bishop: b  Night: n  Rook: r )" << endl;
						do
						{
							cout << "give Input: ";
							cin >> x;
							cout << endl;
						} while (!(x == 'q' || x == 'b' || x == 'n' || x == 'r'));
						this->Pawn_changer(x, p);
						return true;
					}


				}
				else if (this->Ps[p.row][p.col]->get_sym() == 'P')
				{
					char x;
					if (p.row == 0)
					{
						cout << "\n\n\nIn which piece Do you want to change\
			        your White Pawn into( Queen: Q  Bishop: B  Night: N  Rook: R )" << endl;
						do
						{
							cout << "give Input: ";
							cin >> x;
							cout << endl;
						} while (!(x == 'Q' || x == 'B' || x == 'N' || x == 'R'));
						this->Pawn_changer(x, p);
						return true;
					}
				}
			}
			


		}
	}
	return false;
}



Position Board::King_position(int turn)
{
	char King;
	     
	(turn == 0) ? King = 'K' : King = 'k';  
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (this->Ps[i][j] != nullptr)
			{
				if (King == this->Ps[i][j]->get_sym())
				{
					return this->Ps[i][j]->get_Org();
				}
			}
		}
	}
}

bool Board::Self_check(int turn)  // Self check 
{
	  // We will check on the king of the player who turn it is 
	Position p = King_position(turn);
	turn = (turn + 1) % 2;   // no need to change it back since its just a copy
	
	  // Checking the legality of all opponents pieces on our king
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (turn == 0) // white's turn
			{
				if (this->Ps[i][j] != nullptr)
				{
					if (this->Ps[i][j]->get_clr() == White) // If the selected piece by i and j is White otherwise false
					{
						if (Ps[i][j]->Legal_Move(p))  // Checks legal move of that piece on the King
						{
							return true;
						}
					}
				}
				
			
			}
			else // black's turn
			{
				if (this->Ps[i][j] != nullptr)
				{
					if (this->Ps[i][j]->get_clr() == Black) // If the selected piece by i and j is White otherwise false
					{
						if (Ps[i][j]->Legal_Move(p))  // Checks legal move of that piece on the King
						{
							return true;
						}
					}
				}
				
			}

		}
	}
	return false;
}


  // checks that if the piece at 'pick' is dropped at 
  // 'Drop' will it deactivate the check or not
bool Board::checker(Position pick, Position Drop, int turn)
{
	Board decoy_b(*this);
	if (decoy_b.Ps[pick.row][pick.col]->Legal_Move(Drop))
	{
		decoy_b.move_piece(pick, Drop);
		if (!decoy_b.Self_check(turn))
		{
			decoy_b.move_piece(Drop, pick);
			return false;   // Agr ya move chalna sa check khatam hota ha too return false karda 


		}
		else
		{
			decoy_b.move_piece(Drop, pick);
			return true; // or agr nhi khatam hota too return true karda  
		}
	}

}
          // this beta version is for board
bool Board::Validate_drop_beta(int turn, Position x)  // x is drop position
{
	if (x.row > 7 || x.col > 7 || x.row < 0 || x.col < 0)
	{
		return false;
	}

	Piece* p = Ps[x.row][x.col];

	if (p != nullptr)
	{
		if (turn == 0 && p->get_clr() == White)
		{
			return false;
		}
		else if (turn == 1 && p->get_clr() == Black)
		{
			return false;
		}
		
	}
	return true;
}

bool Board::checkmate_extention(int p_row,int p_col,int turn)
{
	Position Pick, Drop;
	Pick.row = p_row;
	Pick.col = p_col;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{       
			Drop.row=i, Drop.col = j;
			    // if i and j are the legal coordinates for the drop of piece at p_row and p_col
			if (Ps[p_row][p_col]->Legal_Move(Drop) &&!(Drop.row==Pick.row && Drop.col==Pick.col) && this->Validate_drop_beta(turn,Drop))
			{        // if it is a legal move try it and if the check terminates it means that its not checkmate
				if (!this->checker(Pick, Drop, turn))
				{
					return false;  // is ka matlab abhi asi move ha jis sa check khatam ho rha ha
				}
				
			}


        }
	}
	return true;


}


bool Board::checkmate(int turn)
{         // searching all the pieces of the turn player on the board
	
	
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			
			if (this->Ps[i][j] != nullptr)
			{             // if turn is 0 than we only need to check the moves of white pieces
				if(turn ==0 && this->Ps[i][j]->get_clr() == White)
				{
					if (this->checkmate_extention(i, j, turn) == false)
					{
						return false; // abhi checkmate nhi laga
				    }



				}
				if (turn == 1 && this->Ps[i][j]->get_clr() == Black)
				{
					if (this->checkmate_extention(i, j, turn) == false)
					{
						return false; // abhi checkmate nhi laga
					}



				}
				

			}

		}
	}
	return true;
}

bool Board::stale_Mate(int turn)
{
	return checkmate(turn);
}


bool Board::castling_legality(Position pick, Position Drop,int turn)
{
	   // Agr king or Rook ka darmian koi or piece ha ya pick and drop Horizontal 
	    // coordinates nhi han to usi waqt fasle kar da
 	if (Horizontal_move_othenticator(pick, Drop))
	{
		if (turn == 0) // For white pieces
		{             // checking ka king check ma too nhi ha
			if (((pick.row == 7 && pick.col == 3) && (Drop.row == 7 && (Drop.col == 0 || Drop.col == 7))) || ((Drop.row == 7 && Drop.col == 3) && (pick.row == 7 && (pick.col == 0 || pick.col == 7))))
			{
				if (!Self_check(turn))
				{
					if (Ps[pick.row][pick.col]->get_clr() == White && Ps[Drop.row][Drop.col]->get_clr() == White)
					{
						if ((Ps[pick.row][pick.col]->get_sym() == 'K' && Ps[Drop.row][Drop.col]->get_sym() == 'R') || (Ps[pick.row][pick.col]->get_sym() == 'R' && Ps[Drop.row][Drop.col]->get_sym() == 'K'))
						{
							return true;
						}
					}

				}
			}
		
		}
		else  // For black pieces
		{
			if (((pick.row == 0 && pick.col == 3) && (Drop.row == 0 && (Drop.col == 0 || Drop.col == 7))) || ((Drop.row == 0 && Drop.col == 3) && (pick.row == 0 && (pick.col == 0 || pick.col == 7))))
			{        // checking ka king check ma too nhi ha
				if (!Self_check(turn))
				{
					if (Ps[pick.row][pick.col]->get_clr() == Black && Ps[Drop.row][Drop.col]->get_clr() == Black)
					{
						if ((Ps[pick.row][pick.col]->get_sym() == 'k' && Ps[Drop.row][Drop.col]->get_sym() == 'r') || (Ps[pick.row][pick.col]->get_sym() == 'r' && Ps[Drop.row][Drop.col]->get_sym() == 'k'))
						{
							return true;
						}
					}

				}
			}
		}
	}
	return false;


}

bool Board::casteling(Position pick, Position Drop,int &turn,Board* undo_B)
{
	
	if (castling_legality(pick, Drop, turn))
	{
		this->undo_Board_Loader(undo_B);

		Position d_pick_k, d_drop_k;
		Position d_pick_R, d_drop_R;
		if (turn == 0)
		{  // first moving the king 
			d_pick_k.row = 7, d_pick_k.col = 3;
			d_drop_k.row = 7;  //  this is fixed
			
		   // Now movig the rook
			    // First checking the pick coordinates of Roook 
			if (pick.col == 0 || pick.col == 7) // Agr pick coordinate Rook pa ha
			{
				d_pick_R.col = pick.col;
				d_pick_R.row = pick.row;
			}
			else  // Agr drop coordinate dono ma sa ksi ak rook pa ha
			{
				d_pick_R.col = Drop.col;
				d_pick_R.row = Drop.row;

			}
			  // Now we know which rook we picked, we will decide our drop according to it
			d_drop_R.row = 7;
			if (d_pick_R.col == 0)
			{
				d_drop_R.col = 2;
			}
			else
			{
				d_drop_R.col = 4;
			}
			this->move_piece(d_pick_R, d_drop_R); // For rook
			
			if(d_pick_R.col==7)// Determining Kings column of drop according to rook picked
			{
				d_drop_k.col = 5;
			}
			else
			{ 
				d_drop_k.col = 1;
			}
			
			
			this->move_piece(d_pick_k, d_drop_k); // For king
			
			turn = (turn + 1) % 2;
			return true;
		}
		else   // For black pieces
		{
			d_pick_k.row = 0, d_pick_k.col = 3;
			d_drop_k.row = 0;  //  this is fixed

			// Now movig the rook
				 // First checking the pick coordinates of Rook 
			if (pick.col == 0 || pick.col == 7) // Agr pick coordinate Rook pa ha
			{
				d_pick_R.col = pick.col;
				d_pick_R.row = pick.row;
			}
			else  // Agr drop coordinate dono ma sa ksi ak rook pa ha
			{
				d_pick_R.col = Drop.col;
				d_pick_R.row = Drop.row;

			}
			// Now we know which rook we picked, we will decide our drop according to it
			d_drop_R.row = 0;
			if (d_pick_R.col == 0)
			{
				d_drop_R.col = 2;
			}
			else
			{
				d_drop_R.col = 4;
			}
			this->move_piece(d_pick_R, d_drop_R); // For rook
			if (d_pick_R.col == 7) // Determining Kings column of drop according to rook picked
			{
				d_drop_k.col = 5;
			}
			else { d_drop_k.col = 1; }
			this->move_piece(d_pick_k, d_drop_k); // For king
			
			turn = (turn + 1) % 2;
			return true;
		}


	}
	return false;

}
           // Copy constructor

void Board::assign(const Board& Bs)
{
	this->dim = Bs.dim;
	this->Ps = new Piece * *[dim];
	Board* B = this;
	char x;
	for (int i = 0; i < dim; i++)
	{

		this->Ps[i] = new Piece * [dim];  // So board is a 2D array of Piece type single pointers
		for (int j = 0; j < dim; j++)
		{
			if (Bs.Ps[i][j] != nullptr)
			{
				x = Bs.Ps[i][j]->get_sym();
				if (x == 'r')
				{

					this->Ps[i][j] = new Rook(i, j, Black, B, x);
				}
				else if (x == 'R') { this->Ps[i][j] = new Rook(i, j, White, B, x); }
				else if (x == 'n') { this->Ps[i][j] = new Night(i, j, Black, B, x); }
				else if (x == 'N') { this->Ps[i][j] = new Night(i, j, White, B, x); }
				else if (x == 'b') { this->Ps[i][j] = new Bishop(i, j, Black, B, x); }
				else if (x == 'B') { this->Ps[i][j] = new Bishop(i, j, White, B, x); }
				else if (x == 'q') { this->Ps[i][j] = new Queen(i, j, Black, B, x); }
				else if (x == 'Q') { this->Ps[i][j] = new Queen(i, j, White, B, x); }
				else if (x == 'k') { this->Ps[i][j] = new King(i, j, Black, B, x); }
				else if (x == 'K') { this->Ps[i][j] = new King(i, j, White, B, x); }
				else if (x == 'p') { this->Ps[i][j] = new Pawn(i, j, Black, B, x); }
				else if (x == 'P') { this->Ps[i][j] = new Pawn(i, j, White, B, x); }
			}
			else { this->Ps[i][j] = nullptr; }

		}

	}
}

Board::Board(const Board &Bs)
{
	this->assign(Bs);
}

Board Board::operator= (const Board& B)
{
	
	for (int i = dim - 1; i >= 0; i--)
	{
		for (int j = dim - 1; j >= 0; j--)
		{
			delete[]this->Ps[i][j];
		}
	}
	delete[]Ps;
	this->assign(B);
	return *this;
}

Board::~Board()
{
	for (int i = dim-1; i >= 0; i--)
	{
		for (int j = dim - 1; j >= 0; j--)
		{
			delete[]this->Ps[i][j];
		}
	}

}

void Board::undo_Board_Loader(Board* B)
{
	
	*B = (*this);
}


void Board::undo(Board* B)
{
	*this = (*B);
	
}

                 // dc is goingto be the board at readed from save_chess file
void Board::redo()
{
	
	
	fstream rdr("Save-Chess.txt");
	//___ Dummy parameters ro remove name and turn from buffer
	string x;
	rdr >> x;
	rdr >> x;
	int n;
	rdr >> n;
	//_____
	Board dc(rdr);
	*this = dc;


}

























