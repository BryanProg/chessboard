/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#include <iostream>
#include "../include/Chessboard.hpp"

#define SCREEN_WIDTH  (1080)
#define SCREEN_HEIGHT (720)

int main()
{
    CBL::chessboard obj(SCREEN_WIDTH, SCREEN_HEIGHT, 8u);

    obj.run();

    return 0;
}