
#include <iostream>

#include <cassert>

#include "Auxiliaries.h"
#include "Game.h"
#include "Character.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "../partB/Matrix.h"
#include "Auxiliaries.cpp"
#include "Game.cpp"
#include "Character.cpp"
#include "Soldier.cpp"
#include "Medic.cpp"
#include "Sniper.cpp"

using namespace mtm;

int main()
{
    Game new_game(2,2);
    Game new_game2(new_game);

    return 0;
}