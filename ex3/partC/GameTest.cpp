
#include <iostream>
#include "Game.h"

using namespace mtm;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define TRY_AND_PRINT_CATCH(X)                 \
                                               \
    try                                        \
    {                                          \
        std::cout << "Trying: " << #X << endl; \
        X;                                     \
    }                                          \
    catch (std::exception & e)                 \
    {                                          \
        std::cout << e.what() << '\n';         \
    }                                          \
                                               \
    // TODO ask i can use math and str copy method to char*

void runTestCases()
{
    std::cout << "------Game Initializations------" << std::endl;

    {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                Game g1(i, j);
                Game g2 = g1;
                g2 = g1;
                g2 = Game(j, i);
                g2 = g1;

                const Game g3(i, j);
                Game g4 = g3;
                g4 = g3;
                g4 = Game(j, i);
                g4 = g3;

                Game g5(i, j);
                const Game g6 = g5;
                const Game g7 = g3;
            }
        }

        TRY_AND_PRINT_CATCH(Game g1(-1, 1));
        TRY_AND_PRINT_CATCH(Game g1(1, -1));
        TRY_AND_PRINT_CATCH(Game g1(-1, -1));
    }
    std::cout << "------Character Init------" << std::endl;
    for (int i = -2; i < 5; i++)
    {
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, i, 2, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::CPP, i, 2, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, i, 2, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, i, 2, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, i, 2, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, i, 2, 4, 5));
    }
    for (int i = -2; i < 5; i++)
    {
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 10, i, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, i, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, 10, i, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, i, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, i, 4, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, i, 4, 5));
    };
        for (int i = -2; i < 5; i++)
    {
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 10, 2, i, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 2, i, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, 10, 2, i, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 2, i, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, 2, i, 5));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 2, i, 5));
    };
            for (int i = -2; i < 5; i++)
    {
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 10, 2, 4, i));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 2, 4, i));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, 10, 2, 4, i));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 2, 4, i));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, 2, 4, i));
        TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 2, 4, i));
    };
    Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 2, 4, 5);
    Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 2, 4, 5);
    g1.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(1, 4), Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(6, 1), Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(6, 4), Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 2, 4, 5));
    std::cout << g1 << std::endl;
    g1.move(GridPoint(1, 1), GridPoint(1, 2));
    std::cout << g1 << std::endl;

    try
    {
        g1.attack(GridPoint(1, 4), GridPoint(1, 2)); // can't attak ally
    }
    catch (mtm::Game::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.attack(GridPoint(1, 4), GridPoint(6, 1)); // should not work - not in range
    }
    catch (mtm::Game::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(1, 4), GridPoint(3, 2));
    std::cout << g1 << std::endl;
    try
    {
        g1.attack(GridPoint(1, 4), GridPoint(6, 4)); // character moved away
    }
    catch (mtm::Game::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }

    g1.attack(GridPoint(3, 2), GridPoint(6, 1)); // now it can hit

    g1.move(GridPoint(6, 1), GridPoint(4, 2));
    std::cout << g1 << std::endl;

    try
    {
        g1.attack(GridPoint(3, 2), GridPoint(4, 2)); // sniper can't attack close targets
    }
    catch (mtm::Game::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(4, 2), GridPoint(6, 2));
    std::cout << g1 << std::endl;

    g1.attack(GridPoint(3, 2), GridPoint(6, 2)); // now it can hit
    std::cout << g1 << std::endl;

    try
    {
        g1.move(GridPoint(6, 2), GridPoint(6, 1)); // soldier was killed and removed
    }
    catch (mtm::Game::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(3, 2), GridPoint(3, 4));

    try
    {
        g1.attack(GridPoint(3, 4), GridPoint(6, 4)); // sniper out of ammo
    }
    catch (mtm::Game::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.attack(GridPoint(6, 4), GridPoint(6, 4)); // medic can't heal itself
    }
    catch (mtm::Game::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }

    Team winning_team = Team::PYTHON;

    std::cout << "isOver: " << g1.isOver(&winning_team) << std::endl;
    std::cout << "is cpp the winning team? " << (winning_team == Team::CPP) << std::endl;

    g1.reload(GridPoint(3, 4));
    g1.attack(GridPoint(3, 4), GridPoint(6, 4)); // now can shoot

    std::cout << g1 << std::endl;

    try
    {
        g1.move(GridPoint(6, 4), GridPoint(6, 1)); // medic was killed and removed
                                                   // the kill was possible because of the sniper double power third attack
    }
    catch (mtm::Game::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "isOver: " << g1.isOver(&winning_team) << std::endl;
    std::cout << "is cpp the winning team? " << (winning_team == Team::CPP) << std::endl;
}
int main()
{
    cout << "Matrix Tester V1.0 C Shelly Francis & Shai Yehezkel" << endl;
    Game new_game(2, 2);
    Game new_game2(new_game);

    return 0;
}