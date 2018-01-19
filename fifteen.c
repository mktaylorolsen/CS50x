/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

//to store empty space;
int THIS_ONE, THAT_ONE;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
int starting_pt = (d*d-1);
int board_num = 0;
for(int i = 0; i < d; i++)
{
	for (int j = 0; j < d; j++)
	{
	board[i][j] = starting_pt - board_num;
	board_num++;
	}
}
if (starting_pt % 2)
	{
		int odd_swap;
		int two_position = d-(d-2);
        	odd_swap = board [two_position][two_position];
        	board [two_position][two_position] = board [d-starting_pt][d-starting_pt];
        	board [d-starting_pt][d-starting_pt] = odd_swap;
	}
board [d-1][d-1] = 99;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++)
	{
	    for (int j = 0; j < d; j++)
	    {
		    if (board[i][j] == 99)
			    printf(" _");
		    else
			    printf("%2i", board[i][j]);
	    }
	    printf("\n");
	}
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */

bool move(int tile)
{
    int the_number = tile;
    int open_space = 99;
    for(int i = 0; i < d; i++)
	{
	    for (int j = 0; j < d; j++)
		{
			//attributing the chosen tile to it’s position on the board
			if(tile == board[i][j])
		    {
		        //if the tile in the column to the right is open, then swap it
		        if (board[i][j+1] == open_space)
			    {
				    board[i][j] = open_space;
				    board[i][j+1] = the_number;
				    return true;
			    }
		    //if the tile in the column to the left is open, then swap it
		        else if (board[i][j-1] == open_space)
			    {
				    board[i][j] = open_space;
				    board[i][j-1] = the_number;
				    return true;
			    }
		    //if the tile in the row below is open, then swap it
    		    else if (board[i+1][j] == open_space)
			    {
				    board[i][j] = open_space;
				    board[i+1][j] = the_number;
				    return true;
			    }
		//if the tile in the row above is open, then swap it
	    	    else if (board[i-1][j] == open_space)
			    {
				    board[i][j] = open_space;
				    board[i-1][j] = the_number;
				    return true;
			    }
		    }
		}
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int num_in_tile = 1;
	int final_tile = d-1;

    for(int i = 0; i < d; i++)
	{
	    for (int j = 0; j < d; j++)
		{
		    if (board [i][j] != board[final_tile][final_tile])
		    {
			    if(board[i][j] == num_in_tile)
				{
				    num_in_tile++;
                }
                else
                    return false;
            }
        else
            return true;
        }
    }
    return true;
}

