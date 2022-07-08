#include <iostream>

#include "game.h"

using namespace std;

// Driver code
int main()
{
    char board[3][3] =
        {
            {EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY}};

    Game game(board, true, true, true);

    game.play(true);

    return 0;
}