#include <iostream>

using namespace std;

// Player - X (Max)
// Opposition - O (Min)

//Struct move for position
struct Move
{
    int i, j;
};

int Max(int, char[][3], char, char);
int Min(int, char[][3], char, char);

// Print game
void print_game(char game[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << game[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";
}

// Evaluate whether someone is winning
int evaluate_board(char game[3][3], char player, char opp)
{
    // Check the row
    for (int row = 0; row < 3; row++)
    {
        if (game[row][0] == game[row][1] && game[row][1] == game[row][2])
        {
            if (game[row][0] == player)
            {
                return 10;
            }
            else if (game[row][0] == opp)
            {
                return -10;
            }
        }
    }

    // Check the column
    for (int col = 0; col < 3; col++)
    {
        if (game[0][col] == game[1][col] && game[1][col] == game[2][col])
        {
            if (game[0][col] == player)
            {
                return 10;
            }
            else if (game[0][col] == opp)
            {
                return -10;
            }
        }
    }

    // Check the diagonals
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2])
    {
        if (game[0][0] == player)
        {
            return 10;
        }
        else if (game[0][0] == opp)
        {
            return -10;
        }
    }

    if (game[0][2] == game[1][1] && game[1][1] == game[2][0])
    {
        if (game[0][2] == player)
        {
            return 10;
        }
        else if (game[0][2] == opp)
        {
            return -10;
        }
    }
    return 0;
}

// Check if moves are left
bool moves_left(char game[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] == '_')
            {
                return true;
            }
        }
    }
    return false;
}

// Check game status
int check_game(char game[3][3], char player, char opp)
{
    print_game(game);

    int value = evaluate_board(game, player, opp);

    // Player won
    if (value == 10)
    {
        return value;
    }

    // Opposition won
    if (value == -10)
    {
        return value;
    }

    // If no one has won and no moves then a tie
    if (!moves_left(game))
    {
        return 0;
    }

    // None of the above
    return -1;
}

// Max part (Player)
int Max(int depth, char game[3][3], char player, char opp)
{
    int status = check_game(game, player, opp);
    if (status != -1)
    {
        return status;
    }

    cout << status << endl;

    cout << "\nMAX" << endl;
    // Continue with opposition turn
    int best = INT_MIN;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] == '_')
            {
                // Make move
                game[i][j] = player;
                // Call next turn
                int val = Min(depth + 1, game, player, opp);
                if (val > best)
                {
                    best = val;
                }
                // Undo move
                game[i][j] = '_';
            }
        }
    }
    return best;
}

// Min part (Opposition)
int Min(int depth, char game[3][3], char player, char opp)
{
    int status = check_game(game, player, opp);
    if (status != -1)
    {
        return status;
    }
    cout << status << endl;

    cout << "\nMIN" << endl;
    // Continue with player turn
    int best = INT_MAX;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] == '_')
            {
                // Make move
                game[i][j] = opp;
                // Call next turn
                int val = Max(depth + 1, game, player, opp);
                if (val < best)
                {
                    best = val;
                }
                // Undo move
                game[i][j] = '_';
            }
        }
    }
    return best;
}

// Minmax util
int MinMax(int depth, char game[3][3], char player, char opp, char turn)
{
    // Call respective function based on turn
    if (turn == player)
    {
        return Max(depth, game, player, opp);
    }
    else
    {
        return Min(depth, game, player, opp);
    }
}

// Best move
Move best_move(char game[3][3], char player, char opp)
{
    int bestVal = INT_MIN;
    Move bestMove;
    bestMove.i = -1;
    bestMove.j = -1;

    // Traverse all cell and calculate minimax for each. Optimal Value = Best cell
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] == '_')
            {
                // Make move
                game[i][j] = player;
                // Call minmax
                int moveVal = MinMax(0, game, player, opp, opp);
                // Undo move
                game[i][j] = '_';
                // Update best value if needed
                if (moveVal > bestVal)
                {
                    bestMove.i = i;
                    bestMove.j = j;
                    bestVal = moveVal;
                }
                cout << bestVal << " " << bestMove.i << " " << bestMove.j << "\n\n";
            }
        }
    }
    return bestMove;
}

// Main driver
int main()
{
    char game[3][3] =
        {
            {'X', 'O', 'X'},
            {'O', 'O', 'X'},
            {'_', '_', '_'}};

    //Print board
    cout << "\nCURRENT GAME STATE\n";
    print_game(game);

    //Variables
    char player = 'X';
    char opp = 'O';

    //Call best move
    Move bestMove = best_move(game, player, opp);
    cout << "\nOptimal Move : " << bestMove.i << " " << bestMove.j << endl;

    return 0;
}