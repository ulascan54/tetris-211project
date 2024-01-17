#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "Logic.h"
#include "Game.h"

int main()
{
    Logic tetris;
    tetris.start_game();
    return 0;
}