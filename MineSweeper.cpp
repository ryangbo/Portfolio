#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 5;	// number of rows and columns for square board

struct Position 
{
	int x;
	int y;
}; // struct for user selection of position on board
enum Status {INIT = '*', MINE = '@', HIT = 'X'};	// enum for game board type with supported values

// function prototypes
void printStudentInfo();
void printIntro(int num_of_mines);
void initBoard(Status board[][SIZE]);
bool assignMine(Status board[][SIZE]);
void dispBoard(Status board[][SIZE]); 
void dispUserBoard(int board[][SIZE]);
int getNumber(Position select, Status board[][SIZE]);
bool checkPosition(Position select, Status board[][SIZE]);

int main()
{
	int num_of_mines;		// number of mines entered by user
	int numTurns=1;
	Status board[SIZE][SIZE];	// game board implemented as enum type
	int displayBoard[SIZE][SIZE]; 	// for user display
	Position select;
	select.x = -1;
	select.y = -1;
	
	for (int nRow = 0; nRow < SIZE; nRow++) 
	{
		for (int nCol = 0; nCol < SIZE; nCol++)
		{
			displayBoard[nRow][nCol] = -1; // initialize our display array
		}
	}


	srand(time(0));		// seed random number generator

	printStudentInfo();	// call function to display student info

	cout << "           Welcome to Minesweeper!             " << endl << endl;

	// prompt for and read in number of mines between 5 and 10, inclusively
	// re-prompted if invalid number entered
	do
	{
		cout << "Enter number of mines to place on board (5 - 10): ";
		cin  >> num_of_mines;
	} while ((num_of_mines < 5) || (num_of_mines > 10));

	cout << endl;

	printIntro(num_of_mines);	// call function to print game information

	cout << "Initializing board...";
	initBoard(board);	// call function to initialize board

	cout << "assigning mines...";

	// loop to assign correct number of mines
	for (int i = 0; i < num_of_mines; i++)
	{
		// loop until assign mine
		while (!assignMine(board))
		{
			// nothing to do here, just make sure it assigns a mine
		}
	}

	cout << "now let's begin..." << endl << endl;;
	dispUserBoard(displayBoard); // call function to display initial game board
	
	do{
		cout << "Please enter in 2 integers from [0,0] to [4,4]" << endl << endl;
		cout << "This is your #" << numTurns << " attempt of 10:" << endl;
		
		cin >> select.x >> select.y;
		
		if((select.x >= 0 && select.x <= 4) && (select.y >= 0 && select.y <= 4))
		{
			//boolean function to check what postion char is
			if(!checkPosition(select, board))
			{
				displayBoard[select.x][select.y] = getNumber(select, board);
			}
			else
			{
				cout << "Invalid input: Input already used." << endl;
				cout << "Please enter in 2 integers from [0,0] to [4,4]: ";
				cin >> select.x >> select.y;
				displayBoard[select.x][select.y] = getNumber(select, board);
			}
			dispBoard(board);
			dispUserBoard(displayBoard);
			
			numTurns++;
		}
		else
		{
			cout << "Invalid input. Try again:" << endl;
		}
	}while(numTurns <= 10);
	
	dispBoard(board);
	
	return 0;
}

/*
 ============================================================================
 Function    : printStudentInfo
 Parameters  : nothing
 Return      : nothing
 Description : This function prints out student information
 ============================================================================
 */
void printStudentInfo()
{
	// display student information
	cout << "     +----------------------------------------------+" << endl;
	cout << "     |       Computer Science and Engineering       |" << endl;
	cout << "     |        CSCE 1030 - Computer Science I        |" << endl;
	cout << "     |          Ryan Gibeault    rg0385             |" << endl;
	cout << "     +----------------------------------------------+" << endl;
	cout << endl;

	return;
}

/*
 ============================================================================
 Function    : printIntro
 Parameters  : integer for number of mines
 Return      : nothing
 Description : This function prints out game information, including number of
	           mines, size of board, and objective of the game
 ============================================================================
 */
void printIntro(int num_of_mines)
{
	cout << "----------------------------------------------------------" << endl;
	cout << "This computer program will randomly assign ";
	cout.width(2);
	cout << num_of_mines << " mines to the " << endl;
	cout << SIZE << " by " << SIZE << " board. Your objective will be to select ten squares" << endl;
	cout << "on the board that do not contain mines using the given in-" << endl;
	cout << "formation from the adjacent squares. The game is over when" << endl;
	cout << "you either select 10 squares without hitting a mine or you" << endl;
	cout << "select a square containing a mine.                        " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << endl;

	return;
}

/*
 ============================================================================
 Function    : initBoard
 Parameters  : enum type for 2D game board array
 Return      : nothing
 Description : This function initializes the game board to its initial values
 ============================================================================
 */
void initBoard(Status board[][SIZE])
{
	// loop through rows
	for (int row = 0; row < SIZE; row++)
	{
		// loop through columns
		for (int col = 0; col < SIZE; col++)
		{
			// assign enum value for '*' to row-column position
			board[row][col] = INIT;
		}
	}
}

/*
 ============================================================================
 Function    : assignMine
 Parameters  : enum type for 2D game board array
 Return      : bool that indicates whether or not mine assignment successful
 Description : This function attempts to assign one single mine to a randomly
	           generated row-column position and returns true if the mine as-
	           signment was successful or false otherwise
 ============================================================================
 */
bool assignMine(Status board[][SIZE])
{
	int row = (rand() % SIZE);	// generate random row in board
	int col = (rand() % SIZE);	// generate random column in board

	// check if mine already present at random row-column position
	if (board[row][col] == INIT)
	{
		// no mine present, so assign mine to location
		board[row][col] = MINE;
		return true;
	}
	else
	{
		// mine already present at location, so just return false
		return false;
	}
}

/*
 ============================================================================
 Function    : dispBoard
 Parameters  : enum type for 2D game board array
 Return      : nothing
 Description : This function displays the game board to the screen
 ============================================================================
 */
void dispBoard(Status board[][SIZE])
{
	cout << "    0 1 2 3 4  " << endl;
	cout << "  +-----------+" << endl;

	// loop through to display row information
	for (int row = 0; row < SIZE; row++)
	{
		cout << " " << row << "|";

		// loop through to display column information
		for (int col = 0; col < SIZE; col++)
		{
			// display board based on values contained
			cout << " " << static_cast<char>(board[row][col]);
		}

		cout << " |" << endl;
	}

	cout << "  +-----------+" << endl;
}

void dispUserBoard(int board[][SIZE])
{
	cout << "    0 1 2 3 4  " << endl;
	cout << "  +-----------+" << endl;

	// loop through to display row information
	for (int row = 0; row < SIZE; row++)
	{
		cout << " " << row << "|";

		// loop through to display column information
		for (int col = 0; col < SIZE; col++)
		{
			if(board[row][col] == -1)
			{
				cout << " *" ;
			}
			else
			{
				// display board based on values contained
				cout << " " << board[row][col];
			}
		}

		cout << " |" << endl;
	}

	cout << "  +-----------+" << endl;
}

int getNumber(Position select, Status board[][SIZE])
{
	int count=0;
	int x = select.x;
	int y = select.y;

	// checks if row/ col are valid
	if(((x > 0) && (y > 0)) && (x < 4) && (y < 4))
	{
		for (int row = x-1; row <= x+1; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y-1; col <= y+1; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((x == 4)) && (y == 4))
	{
		for (int row = x-1; row <= x; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y-1; col <= y; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((x == 0)) && (y == 0))
	{
		for (int row = x; row <= x+1; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y; col <= y+1; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((x == 0)) && (y == 4))
	{
		for (int row = x; row <= x+1; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y-1; col <= y; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((x == 4)) && (y == 0))
	{
		for (int row = x-1; row <= x; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y; col <= y+1; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((x > 0) && (x < 4)) && (y == 0))
	{
		for (int row = x-1; row <= x+1; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y; col <= y+1; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((x > 0) && (x < 4)) && (y == 4))
	{
		for (int row = x-1; row <= x+1; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y-1; col <= y; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((y > 0) && (y < 4)) && (x == 0))
	{
		for (int row = x; row <= x+1; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y-1; col <= y+1; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	else if(((y > 0) && (y < 4)) && (x == 4))
	{
		for (int row = x-1; row <= x; row++) // starts 1 row back and goes till 1 row forward
		{		
			for (int col = y-1; col <= y+1; col++) // starts 1 col up and goes till 1 col down
			{
				if(board[row][col] == MINE)
				{
					count++;
				}
			}
		}
	}
	return count;

}		
	
bool checkPosition(Position select, Status board[][SIZE])
{
	int x = select.x;
	int y = select.y;
	
	if(board[x][y] == MINE)
	{
		board[x][y] = HIT;
		cout << "Mine hit! Sorry, you lose." << endl;
		dispBoard(board);
		exit(true);
	}
	else if(board[x][y] == INIT)
	{
		return false;
	}
	else
	{
		cout << "Invalid input: Input already used.";
		return false;
	}
}


