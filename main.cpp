#include <iostream>

#include "game.h"

using namespace std;

int main()
{
    char board[3][3] =
        {
            {EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY}};

    // board, isX, XIA, OIA
    Game game(board, true, true, false);

    game.play(true);

    return 0;
}
