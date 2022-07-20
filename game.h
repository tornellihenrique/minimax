#include <iostream>
#include <algorithm>
#include <limits>

#define SIZE 3

#define X_PLAYER 'X'
#define O_PLAYER 'O'
#define EMPTY '_'

using namespace std;

struct Move
{
    int row, col;
};

class Game
{

public:
    char **board;
    bool isX;
    bool XIA;
    bool OIA;

    Game() {}
    Game(char **_board, bool _isX, bool _XIA, bool _OIA) : board(_board), isX(_isX), XIA(_XIA), OIA(_OIA) {}
    Game(char _board[SIZE][SIZE], bool _isX, bool _XIA, bool _OIA) : isX(_isX), XIA(_XIA), OIA(_OIA)
    {
        board = new char *[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            board[i] = new char[SIZE];
            for (int j = 0; j < SIZE; j++)
            {
                board[i][j] = _board[i][j];
            }
        }
    }

    bool isMovesLeft()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY)
                    return true;

        return false;
    }

    char currPlayer()
    {
        return isX ? X_PLAYER : O_PLAYER;
    }

    // Check current board score
    int evaluate()
    {
        // Checking for Rows for X_PLAYER or O_PLAYER victory.
        for (int row = 0; row < 3; row++)
        {
            if (board[row][0] == board[row][1] &&
                board[row][1] == board[row][2])
            {
                if (board[row][0] == X_PLAYER)
                    return +10;
                else if (board[row][0] == O_PLAYER)
                    return -10;
            }
        }

        // Checking for Columns for X_PLAYER or O_PLAYER victory.
        for (int col = 0; col < 3; col++)
        {
            if (board[0][col] == board[1][col] &&
                board[1][col] == board[2][col])
            {
                if (board[0][col] == X_PLAYER)
                    return +10;

                else if (board[0][col] == O_PLAYER)
                    return -10;
            }
        }

        // Checking for Diagonals for X_PLAYER or O_PLAYER victory.
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            if (board[0][0] == X_PLAYER)
                return +10;
            else if (board[0][0] == O_PLAYER)
                return -10;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        {
            if (board[0][2] == X_PLAYER)
                return +10;
            else if (board[0][2] == O_PLAYER)
                return -10;
        }

        // Else if none of them have won then return 0
        return 0;
    }

    int minimax(int depth, bool isX)
    {
        int score = evaluate();

        // If Maximizer has won the game return his/her
        // evaluated score
        if (score == 10)
            return score;

        // If Minimizer has won the game return his/her
        // evaluated score
        if (score == -10)
            return score;

        // If there are no more moves and no winner then
        // it is a tie
        if (!isMovesLeft())
            return 0;

        // If this maximizer's move
        if (isX)
        {
            int best = -1000;

            // Traverse all cells
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Check if cell is empty
                    if (board[i][j] == EMPTY)
                    {
                        // Make the move
                        board[i][j] = X_PLAYER;

                        // Call minimax recursively and choose
                        // the maximum value
                        best = max(best, minimax(depth + 1, !isX));

                        // Undo the move
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        }

        // If this minimizer's move
        else
        {
            int best = 1000;

            // Traverse all cells
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Check if cell is empty
                    if (board[i][j] == EMPTY)
                    {
                        // Make the move
                        board[i][j] = O_PLAYER;

                        // Call minimax recursively and choose
                        // the minimum value
                        best = min(best, minimax(depth + 1, !isX));

                        // Undo the move
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        }
    }

    int minimaxAB(int depth, bool isX, int alpha, int beta)
    {
        int score = evaluate();

        // If Maximizer has won the game return his/her
        // evaluated score
        if (score == 10)
            return score;

        // If Minimizer has won the game return his/her
        // evaluated score
        if (score == -10)
            return score;

        // If there are no more moves and no winner then
        // it is a tie
        if (!isMovesLeft())
            return 0;

        // If this maximizer's move
        if (isX)
        {
            int best = -1000;

            // Traverse all cells
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Check if cell is empty
                    if (board[i][j] == EMPTY)
                    {
                        // Make the move
                        board[i][j] = X_PLAYER;

                        // Call minimax recursively and choose
                        // the maximum value
                        int value = minimaxAB(depth + 1, !isX, alpha, beta);
                        best = max(best, value);

                        // Undo the move
                        board[i][j] = EMPTY;

                        // Update alpha
                        alpha = max(alpha, best);

                        // Cut if possible
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return best;
        }

        // If this minimizer's move
        else
        {
            int best = 1000;

            // Traverse all cells
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Check if cell is empty
                    if (board[i][j] == EMPTY)
                    {
                        // Make the move
                        board[i][j] = O_PLAYER;

                        // Call minimax recursively and choose
                        // the minimum value
                        int value = minimaxAB(depth + 1, !isX, alpha, beta);
                        best = min(best, value);

                        // Undo the move
                        board[i][j] = EMPTY;

                        // Update beta
                        beta = min(beta, best);

                        // Cut if possible
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return best;
        }
    }

    Move getMoveInput()
    {
        Move move;

        for (;;)
        {
            cout << "Enter the move (like this: 'R C'): ";

            if (cin >> move.row && cin >> move.col)
            {
                if (move.col >= 1 && move.col <= SIZE && move.row >= 1 && move.row <= SIZE)
		{
		    move.row--;
        	    move.col--;

		    if (board[move.row][move.col] == EMPTY) break;
		}
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        return move;
    }

    Move findBestMove(bool useABCut)
    {
        int bestVal = isX ? -1000 : 1000;
        Move bestMove;
        bestMove.row = -1;
        bestMove.col = -1;

        // Traverse all cells, evaluate minimax function for
        // all empty cells. And return the cell with optimal
        // value.
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == EMPTY)
                {
                    // Make the move
                    board[i][j] = currPlayer();

                    // compute evaluation function for this move.
                    int moveVal = useABCut ? minimaxAB(0, !isX, -1000, 1000) : minimax(0, !isX);

                    // Undo the move
                    board[i][j] = EMPTY;

                    // If the value of the current move is
                    // more than the best value, then update
                    // best/
                    if (isX ? moveVal > bestVal : moveVal < bestVal)
                    {
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        cout << "The value of the best Move is: " << bestVal << endl
             << endl;

        return bestMove;
    }

    void play(bool useABCut)
    {
        while (isMovesLeft() && evaluate() == 0)
        {
            cout << currPlayer() << " turn! Board:" << endl
                 << endl;
            printBoard(board);

            Move move;

            if ((isX && XIA) || (!isX && OIA))
                move = findBestMove(useABCut);
            else
                move = getMoveInput();

            // Actually make the move
            board[move.row][move.col] = currPlayer();

            isX = !isX;
        }

        printResult();
        printBoard(board);
    }

    static void printBoard(char **b)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << b[i][j] << " ";
            }

            cout << endl;
        }

        cout << endl
             << endl;
    }

    void printResult()
    {
        int result = evaluate();

        if (result == 0)
        {
            cout << "Game ended with a tie! Board:" << endl
                 << endl;

            return;
        }

        if (result == 10)
        {
            cout << "Game ended with a WIN FOR X! Board:" << endl
                 << endl;

            return;
        }

        cout << "Game ended with a WIN FOR O! Board:" << endl
             << endl;
    }
};
