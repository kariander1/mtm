
#include <iostream>
#include <vector>
#include "Game.h"

using namespace mtm;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
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
    // TODO ask if OK to use math.h
    // TODO check that iterface was not modified
    // Check what to do with exception overriding
enum SelectType
{
    CREATE = 0,
    DESTROY,
    COPY,
    ASSIGN,
    ADD_CHAR,
    MAKE_CHAR,
    MOVE,
    ATTACK,
    RELOAD,
    IS_OVER,
    PRINT,
    TEST_CASE,
    QUIT
};
void printGames();
void runTestCases();

void runTestCases()
{
    std::cout << "------example 1------" << std::endl;
    Game g1(8, 8);
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
    std::cout << "------example 2------" << std::endl;
    g1 = Game(5, 10);
    g1.addCharacter(GridPoint(3, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, 20, 0, 3, 5));
    g1.addCharacter(GridPoint(2, 6), Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(3, 8), Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(3, 6), Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(4, 6), Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 2, 4, 5));
    std::cout << g1 << std::endl;

    try
    {
        g1.attack(GridPoint(3, 0), GridPoint(3, 6));
    }
    catch (mtm::Game::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.move(GridPoint(3, 0), GridPoint(3, 4)); // soldier only moves 3 at a time
    }
    catch (mtm::Game::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << g1 << std::endl; // has not changed

    Game g2 = g1; // copy constructor - games should be independent

    g1.move(GridPoint(3, 0), GridPoint(3, 3));

    std::cout << g1 << std::endl; // changed
    std::cout << g2 << std::endl; // has not changed

    try
    {
        g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // soldier has 0 ammo
    }
    catch (mtm::Game::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.reload(GridPoint(3, 2));
    }
    catch (mtm::Game::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.reload(GridPoint(3, -3));
    }
    catch (mtm::Game::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        g1.reload(GridPoint(3, 13));
    }
    catch (mtm::Game::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    g1.reload(GridPoint(3, 3)); // now soldier has ammo

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // damages 2 medics and 1 sniper in range
    std::cout << g1 << std::endl;                // everyone still alive

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // one medic dies (took 5+5 damage instead of 3+3 like the others)
    std::cout << g1 << std::endl;

    g1.attack(GridPoint(3, 3), GridPoint(3, 6));
    std::cout << g1 << std::endl;

    g1.attack(GridPoint(4, 6), GridPoint(2, 6)); // medic heals sniper
    try
    {
        g1.attack(GridPoint(4, 6), GridPoint(2, 6)); // medic can't heal self
    }
    catch (mtm::Game::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // soldier out of ammo
    }
    catch (mtm::Game::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    g1.reload(GridPoint(3, 3)); // now soldier has ammo
    g1.reload(GridPoint(3, 3)); // can reload twice - no problem (more ammo)

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // medic dead, sniper not dead
    std::cout << g1 << std::endl;

    std::cout << "------Game Initializations------" << std::endl;

    {
        for (int i = 1; i < 20; i++)
        {
            for (int j = 1; j < 20; j++)
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

        TRY_AND_PRINT_CATCH(Game g1(0, 1));
        TRY_AND_PRINT_CATCH(Game g1(1, 0));
        TRY_AND_PRINT_CATCH(Game g1(0, 0));
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
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 0, -1, -1, -1));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 0, -1, 4, 3));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 0, 2, -1, 3));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 0, 2, 4, -1));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 3, -1, -1, -1));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 3, -1, 3, -1));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 3, -1, -1, 3));
    TRY_AND_PRINT_CATCH(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 3, 3, -1, -1));

    std::cout << "------Add Character------" << std::endl;
    std::shared_ptr<mtm::Character> c1 = Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 2, 4, 5);
    std::shared_ptr<mtm::Character> c2 = Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 2, 4, 5);
    g1 = Game(4, 4);
    for (int k = 0; k < 2; k++)
    {

        for (int i = -1; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                TRY_AND_PRINT_CATCH(cout << g1);
                if (i % 2 == 0)
                {
                    TRY_AND_PRINT_CATCH(g1.addCharacter(GridPoint(i, j), c1));
                }
                else
                {
                    TRY_AND_PRINT_CATCH(g1.addCharacter(GridPoint(i, j), c2));
                }
            }
        }
    }
    TRY_AND_PRINT_CATCH(cout << g1);

    std::cout << "------Copy And Assignment------" << std::endl;
    g1 = Game(4, 4);
    g1.addCharacter(GridPoint(0, 0), c1);

    TRY_AND_PRINT_CATCH(Game g2 = g1);
    TRY_AND_PRINT_CATCH(Game g3(4, 4));
    Game g3(4, 4);
    g2 = g1;
    TRY_AND_PRINT_CATCH(g3 = g1);
    TRY_AND_PRINT_CATCH(cout << g1);
    TRY_AND_PRINT_CATCH(cout << g2);
    TRY_AND_PRINT_CATCH(cout << g3);
    TRY_AND_PRINT_CATCH(g1.move(GridPoint(0, 0), GridPoint(0, 1)));
    TRY_AND_PRINT_CATCH(g2.move(GridPoint(0, 0), GridPoint(1, 0)));
    TRY_AND_PRINT_CATCH(g1.move(GridPoint(0, 0), GridPoint(1, 1)));
    TRY_AND_PRINT_CATCH(cout << g1);
    TRY_AND_PRINT_CATCH(cout << g2);
    TRY_AND_PRINT_CATCH(cout << g3);
    std::cout << "------Movement------" << std::endl;
    g1 = Game(4, 4);
    g1.addCharacter(GridPoint(0, 0), c1);
    g1.addCharacter(GridPoint(1, 0), c2);
    g1.addCharacter(GridPoint(1, 1), c1);
    g1.addCharacter(GridPoint(3, 3), c2);
    for (int i = -1; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            TRY_AND_PRINT_CATCH(g1.move(GridPoint(i, j - 1), GridPoint(i, j)));
            TRY_AND_PRINT_CATCH(cout << g1);
        }
    }
    g1 = Game(4, 4);
    g1.addCharacter(GridPoint(0, 0), c1);
    g1.addCharacter(GridPoint(0, 1), c2);
    g1.addCharacter(GridPoint(1, 1), c1);
    g1.addCharacter(GridPoint(3, 3), c2);
    for (int i = -1; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            TRY_AND_PRINT_CATCH(g1.move(GridPoint(j - 1, i), GridPoint(j, i)));
            TRY_AND_PRINT_CATCH(cout << g1);
        }
    }
    g1 = Game(4, 4);
    g1.addCharacter(GridPoint(0, 0), c1);
    TRY_AND_PRINT_CATCH(g1.move(GridPoint(0, 0), GridPoint(3, 3)));
    TRY_AND_PRINT_CATCH(cout << g1);
    std::cout << "------IsOver------" << std::endl;
    g1 = Game(4, 4);
    Team winning_team1 = Team::PYTHON;

    TRY_AND_PRINT_CATCH(std::cout << "isOver: " << g1.isOver(&winning_team1) << std::endl);
    TRY_AND_PRINT_CATCH(std::cout << "is cpp the winning team? " << (winning_team1 == Team::CPP) << std::endl);
    g1.addCharacter(GridPoint(0, 0), c1);
    TRY_AND_PRINT_CATCH(std::cout << "isOver: " << g1.isOver(&winning_team1) << std::endl);
    TRY_AND_PRINT_CATCH(std::cout << "is cpp the winning team? " << (winning_team1 == Team::CPP) << std::endl);
    g1 = Game(4, 4);
    g1.addCharacter(GridPoint(0, 0), c2);
    TRY_AND_PRINT_CATCH(std::cout << "isOver: " << g1.isOver(&winning_team1) << std::endl);
    TRY_AND_PRINT_CATCH(std::cout << "is cpp the winning team? " << (winning_team1 == Team::CPP) << std::endl);

    std::cout << "------Attack------" << std::endl;
    std::shared_ptr<mtm::Character> M(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 10, 4, 4, 3));
    std::shared_ptr<mtm::Character> N(Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 4, 4, 3));
    std::shared_ptr<mtm::Character> S(Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, 10, 4, 4, 3));
    std::shared_ptr<mtm::Character> m(Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 4, 4, 3));
    std::shared_ptr<mtm::Character> n(Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, 4, 4, 3));
    std::shared_ptr<mtm::Character> s(Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 4, 4, 3));
    Game gladiator_arena(6, 6);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            switch ((i + j) % 6)
            {
            case 0:
                gladiator_arena.addCharacter(GridPoint(i, j), M);
                break;
            case 1:
                gladiator_arena.addCharacter(GridPoint(i, j), n);
                break;
            case 2:
                gladiator_arena.addCharacter(GridPoint(i, j), S);
                break;
            case 3:
                gladiator_arena.addCharacter(GridPoint(i, j), m);
                break;
            case 4:
                gladiator_arena.addCharacter(GridPoint(i, j), N);
                break;
            case 5:
                gladiator_arena.addCharacter(GridPoint(i, j), s);
                break;
            default:
                break;
            }
        }
    }
    cout << gladiator_arena;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            GridPoint source(i, j);
            for (int k = 0; k < 6; k++)
            {
                for (int m = 0; m < 6; m++)
                {
                    GridPoint dest(k, m);
                    TRY_AND_PRINT_CATCH(gladiator_arena.attack(source, dest));
                    cout << gladiator_arena;
                }
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                GridPoint source(i, j);
                TRY_AND_PRINT_CATCH(gladiator_arena.reload(source));
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            GridPoint source(i, j);
            for (int k = 0; k < 6; k++)
            {
                for (int m = 0; m < 6; m++)
                {
                    GridPoint dest(k, m);
                    TRY_AND_PRINT_CATCH(gladiator_arena.attack(source, dest));
                    cout << gladiator_arena;
                    Team winning_team = Team::PYTHON;

                    TRY_AND_PRINT_CATCH(std::cout << "isOver: " << gladiator_arena.isOver(&winning_team) << std::endl);
                    TRY_AND_PRINT_CATCH(std::cout << "is cpp the winning team? " << (winning_team == Team::CPP) << std::endl);
                }
            }
        }
    }
    Game assigned_arena = Game(1,1);
    assigned_arena = gladiator_arena;
    std::shared_ptr<mtm::Character> ULTRA_MEGA_SUPER_MEDIC(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 1000, 1000, 40, 50));
    cout << "GENERATING ULTRA_MEGA_SUPER_MEDIC!!" << endl;
    cout << '\a';
    string sup = R"(                                                                                            
8 8888      88 8 8888   8888888 8888888888 8 888888888o.            .8.                     
8 8888      88 8 8888         8 8888       8 8888    `88.          .888.                    
8 8888      88 8 8888         8 8888       8 8888     `88         :88888.                   
8 8888      88 8 8888         8 8888       8 8888     ,88        . `88888.                  
8 8888      88 8 8888         8 8888       8 8888.   ,88'       .8. `88888.                 
8 8888      88 8 8888         8 8888       8 888888888P'       .8`8. `88888.                
8 8888      88 8 8888         8 8888       8 8888`8b          .8' `8. `88888.               
` 8888     ,8P 8 8888         8 8888       8 8888 `8b.       .8'   `8. `88888.              
  8888   ,d8P  8 8888         8 8888       8 8888   `8b.    .888888888. `88888.             
   `Y88888P'   8 888888888888 8 8888       8 8888     `88. .8'       `8. `88888.            
          .         .                                                                       
         ,8.       ,8.          8 8888888888       ,o888888o.          .8.                  
        ,888.     ,888.         8 8888            8888     `88.       .888.                 
       .`8888.   .`8888.        8 8888         ,8 8888       `8.     :88888.                
      ,8.`8888. ,8.`8888.       8 8888         88 8888              . `88888.               
     ,8'8.`8888,8^8.`8888.      8 888888888888 88 8888             .8. `88888.              
    ,8' `8.`8888' `8.`8888.     8 8888         88 8888            .8`8. `88888.             
   ,8'   `8.`88'   `8.`8888.    8 8888         88 8888   8888888 .8' `8. `88888.            
  ,8'     `8.`'     `8.`8888.   8 8888         `8 8888       .8'.8'   `8. `88888.           
 ,8'       `8        `8.`8888.  8 8888            8888     ,88'.888888888. `88888.          
,8'         `         `8.`8888. 8 888888888888     `8888888P' .8'       `8. `88888.         
                                                                                            
   d888888o.   8 8888      88 8 888888888o   8 8888888888   8 888888888o.                   
 .`8888:' `88. 8 8888      88 8 8888    `88. 8 8888         8 8888    `88.                  
 8.`8888.   Y8 8 8888      88 8 8888     `88 8 8888         8 8888     `88                  
 `8.`8888.     8 8888      88 8 8888     ,88 8 8888         8 8888     ,88                  
  `8.`8888.    8 8888      88 8 8888.   ,88' 8 888888888888 8 8888.   ,88'                  
   `8.`8888.   8 8888      88 8 888888888P'  8 8888         8 888888888P'                   
    `8.`8888.  8 8888      88 8 8888         8 8888         8 8888`8b                       
8b   `8.`8888. ` 8888     ,8P 8 8888         8 8888         8 8888 `8b.                     
`8b.  ;8.`8888   8888   ,d8P  8 8888         8 8888         8 8888   `8b.                   
 `Y8888P ,88P'    `Y88888P'   8 8888         8 888888888888 8 8888     `88.                 
          .         .                                                                       
         ,8.       ,8.          8 8888888888   8 888888888o.       8 8888     ,o888888o.    
        ,888.     ,888.         8 8888         8 8888    `^888.    8 8888    8888     `88.  
       .`8888.   .`8888.        8 8888         8 8888        `88.  8 8888 ,8 8888       `8. 
      ,8.`8888. ,8.`8888.       8 8888         8 8888         `88  8 8888 88 8888           
     ,8'8.`8888,8^8.`8888.      8 888888888888 8 8888          88  8 8888 88 8888           
    ,8' `8.`8888' `8.`8888.     8 8888         8 8888          88  8 8888 88 8888           
   ,8'   `8.`88'   `8.`8888.    8 8888         8 8888         ,88  8 8888 88 8888           
  ,8'     `8.`'     `8.`8888.   8 8888         8 8888        ,88'  8 8888 `8 8888       .8' 
 ,8'       `8        `8.`8888.  8 8888         8 8888    ,o88P'    8 8888    8888     ,88'  
,8'         `         `8.`8888. 8 888888888888 8 888888888P'       8 8888     `8888888P'    )";
    cout << sup << endl;
    gladiator_arena.addCharacter(GridPoint(0, 0), ULTRA_MEGA_SUPER_MEDIC);
    cout << "ULTRA_MEGA_SUPER_MEDIC :\"You have killed my brothers. Prepare to die.\"" << endl;
    cout << gladiator_arena;
    cout << "ULTRA_MEGA_SUPER_MEDIC has spawned in (0,0)!" << endl;
    GridPoint source(0, 0);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            GridPoint dest(i, j);
            try
            {
                gladiator_arena.move(source, dest);
                source = dest;
            }
            catch (const std::exception &e)
            {
                //   std::cerr << e.what() << '\n';
            }

            try
            {
                gladiator_arena.attack(source, GridPoint(i + 1, j));
            }
            catch (const std::exception &e)
            {
            }
            try
            {
                gladiator_arena.attack(source, GridPoint(i - 1, j));
            }
            catch (const std::exception &e)
            {
            }

            try
            {
                gladiator_arena.attack(source, GridPoint(i, j + 1));
            }
            catch (const std::exception &e)
            {
            }

            try
            {
                gladiator_arena.attack(source, GridPoint(i, j - 1));
            }
            catch (const std::exception &e)
            {
            }
        }
    }
    cout << gladiator_arena;
    TRY_AND_PRINT_CATCH(std::cout << "isOver: " << gladiator_arena.isOver(&winning_team) << std::endl);
    TRY_AND_PRINT_CATCH(std::cout << "is cpp the winning team? " << (winning_team == Team::CPP) << std::endl);
}
vector<Game> games;
vector<std::shared_ptr<Character>> saved_characters;
vector<string> saved_char_att;

void initCharacter()
{
    saved_characters.push_back(Game::makeCharacter(CharacterType::MEDIC, Team::CPP, 10, 4, 4, 3));
    saved_char_att.push_back("MEDIC CPP Health:10 Ammo:4 Range:4 Power:3");
    saved_characters.push_back(Game::makeCharacter(CharacterType::SNIPER, Team::CPP, 10, 4, 4, 3));
    saved_char_att.push_back("SNIPER CPP Health:10 Ammo:4 Range:4 Power:3");
    saved_characters.push_back(Game::makeCharacter(CharacterType::SOLDIER, Team::CPP, 10, 4, 4, 3));
    saved_char_att.push_back("SOLDIER CPP Health:10 Ammo:4 Range:4 Power:3");
    saved_characters.push_back(Game::makeCharacter(CharacterType::MEDIC, Team::PYTHON, 10, 4, 4, 3));
    saved_char_att.push_back("MEDIC PYTHON Health:10 Ammo:4 Range:4 Power:3");
    saved_characters.push_back(Game::makeCharacter(CharacterType::SNIPER, Team::PYTHON, 10, 4, 4, 3));
    saved_char_att.push_back("SNIPER PYTHON Health:10 Ammo:4 Range:4 Power:3");
    saved_characters.push_back(Game::makeCharacter(CharacterType::SOLDIER, Team::PYTHON, 10, 4, 4, 3));
    saved_char_att.push_back("SOLDIER PYTHON Health:10 Ammo:4 Range:4 Power:3");
}
GridPoint getPoint()
{
    cout << "To what row?" << endl;
    int row = 0;
    cin >> row;
    cout << "To what column?" << endl;
    int col = 0;
    cin >> col;
    return GridPoint(row, col);
}
int getSelGames(string str)
{
    printGames();
    cout << "Which game would you like to " << str << "? 0-" << games.size()-1 << endl;
    int sel = 0;
    cin >> sel;
    return sel;
}
void reload()
{
    int sel = getSelGames("Reload");
    cout << "Now input the source coordinates:" << endl;
    GridPoint source = getPoint();

    TRY_AND_PRINT_CATCH(games.at(sel).reload(source));
}
void charMove()
{
    int sel = getSelGames("Move");
    cout << "Now input the source coordinates:" << endl;
    GridPoint source = getPoint();
    cout << "Now input the dest coordinates:" << endl;
    GridPoint dest = getPoint();
    TRY_AND_PRINT_CATCH(games.at(sel).move(source, dest));
}
void charAttack()
{
    int sel = getSelGames("Attack");
    cout << "Now input the source coordinates:" << endl;
    GridPoint source = getPoint();
    cout << "Now input the dest coordinates:" << endl;
    GridPoint dest = getPoint();
    TRY_AND_PRINT_CATCH(games.at(sel).attack(source, dest));
}
void isOver()
{
    int sel = getSelGames("isOver");
    Team winning_team = Team::PYTHON;

    std::cout << "isOver: " << games.at(sel).isOver(&winning_team) << std::endl;
    std::cout << "is cpp the winning team? " << (winning_team == Team::CPP) << std::endl;
}
void makeCharacter()
{
    cout << "Select Type : [s-Soldier, m-Medic, n-Sniper]" << endl;
    char ctype;
    cin >> ctype;
    CharacterType ct;
    switch (ctype)
    {
    case 's':
        ct = SOLDIER;
        break;
    case 'm':
        ct = MEDIC;
        break;
    default:
        ct = SNIPER;
        break;
    }
    cout << "Select Team : [c - CPP, p - PYTHON]" << endl;
    char team;
    cin >> team;
    Team t;
    switch (team)
    {
    case 'c':
        t = CPP;
        break;

    default:
        t = PYTHON;
        break;
    }
    cout << "Choose health:" << endl;
    int he;
    cin >> he;

    cout << "Choose ammo" << endl;
    int ammo;
    cin >> ammo;
    cout << "Choose range" << endl;
    int range;
    cin >> range;
    cout << "Choose power" << endl;
    int power;
    cin >> power;
    //Health:10 Ammo:4 Range:4 Power:3");
    TRY_AND_PRINT_CATCH(Game::makeCharacter(ct, t, he, ammo, range, power));
    saved_characters.push_back(Game::makeCharacter(ct, t, he, ammo, range, power));
    saved_char_att.push_back(std::to_string(ct) + " " + std::to_string(t) + " Health:" + to_string(he) + " Ammo:" + to_string(ammo) + " Range:" + to_string(range) + " Power:" + to_string(power));
}
void addCharacter()
{
    int sel = getSelGames("add a character");
    cout << "Pick a character:" << endl;
    for (int i = 0; i < (int)saved_char_att.size(); i++)
    {
        cout << i << " - " << saved_char_att[i] << endl;
    }
    int sel2 = 0;
    cin >> sel2;
    Game & selected_game = games.at(sel);
    std::shared_ptr<Character> ch = saved_characters[sel2];

    cout << "To what row?" << endl;
    int row = 0;
    cin >> row;
    cout << "To what column?" << endl;
    int col = 0;
    cin >> col;
    TRY_AND_PRINT_CATCH(selected_game.addCharacter(GridPoint(row, col), ch));
    saved_characters.erase(saved_characters.begin() +sel2 );
    saved_char_att.erase(saved_char_att.begin() +sel2 );
}
void createGame()
{
    cout << "What is the width of the game grid?" << endl;
    int width = 0;
    cin >> width;
    cout << "What is the height of the game grid?" << endl;
    int height = 0;
    cin >> height;
    TRY_AND_PRINT_CATCH(Game(height, width));
    games.push_back(Game(height, width));
}
void copyGame()
{
    int sel = getSelGames("copy");
    TRY_AND_PRINT_CATCH(Game newGame = games.at(sel));
    Game & newGame = games.at(sel);
    games.push_back(newGame);
}
void assignGame()
{
    int sel1 = getSelGames("assign");
    int sel2 = getSelGames("assigned");
    TRY_AND_PRINT_CATCH(games.at(sel2) = games.at(sel1));
}
void destroyGame()
{
    int sel = getSelGames("remove");
    games.erase(games.begin() + sel);
}
void printGames()
{
    for (int i = 0; i < (int)games.size(); i++)
    {
          TRY_AND_PRINT_CATCH(cout << games.at(i));
   
    }
    cout<<endl;
}

string enum_to_string(SelectType s)
{
    switch (s)
    {
    case CREATE:
        return "Create Game";
        break;
    case DESTROY:
        return "Destroy Game";
        break;
    case COPY:
        return "Copy Game";
        break;
    case ASSIGN:
        return "Assign Game";
        break;
    case RELOAD:
        return "Reload";
        break;
    case MOVE:
        return "Move";
        break;
    case ATTACK:
        return "Attack";
        break;
    case PRINT:
        return "Print Game";
        break;
    case ADD_CHAR:
        return "Add Character";
        break;
    case MAKE_CHAR:
        return "Make Character";
        break;
    case IS_OVER:
        return "Is over";
        break;
    case TEST_CASE:
        return "Run test cases";
        break;
    case QUIT:
        return "Quit";
        break;
    default:
        return "Unknown";
        break;
    }
}
bool sel_to_op(int sel)
{
    switch (sel)
    {
    case CREATE:
        createGame();
        break;
    case DESTROY:
        destroyGame();
        break;
    case COPY:
        copyGame();
        break;
    case ASSIGN:
        assignGame();
        break;
    case RELOAD:
        reload();
        break;
    case MOVE:
        charMove();
        break;
    case ATTACK:
        charAttack();
        break;
    case PRINT:
        printGames();
        break;
    case ADD_CHAR:
        addCharacter();
        break;
    case MAKE_CHAR:
        makeCharacter();
        break;
    case IS_OVER:
        isOver();
        break;
    case TEST_CASE:
        runTestCases();
        break;
    case QUIT:
        return true;
        break;
    default:

        break;
    }
    return false;
}
int main()
{
    string cred = R"( .d8888b.                                       88888888888                888                         888     888  .d8888b.  
d88P  Y88b                                          888                    888                         888     888 d88P  Y88b 
888    888                                          888                    888                         888     888        888 
888         8888b.  88888b.d88b.   .d88b.           888   .d88b.  .d8888b  888888 .d88b.  888d888      Y88b   d88P      .d88P 
888  88888     "88b 888 "888 "88b d8P  Y8b          888  d8P  Y8b 88K      888   d8P  Y8b 888P"         Y88b d88P   .od888P"  
888    888 .d888888 888  888  888 88888888          888  88888888 "Y8888b. 888   88888888 888            Y88o88P   d88P"      
Y88b  d88P 888  888 888  888  888 Y8b.              888  Y8b.          X88 Y88b. Y8b.     888             Y888P    888"       
 "Y8888P88 "Y888888 888  888  888  "Y8888           888   "Y8888   88888P'  "Y888 "Y8888  888              Y8P     888888888  
                                                                                                                              
                                                                                                                              
                                                                                                                              
 .d8888b.  888               d8b      Y88b   d88P       888                       888               888                       
d88P  Y88b 888               Y8P       Y88b d88P        888                       888               888                       
Y88b.      888                          Y88o88P         888                       888               888                       
 "Y888b.   88888b.   8888b.  888         Y888P  .d88b.  88888b.   .d88b. 88888888 888  888  .d88b.  888                       
    "Y88b. 888 "88b     "88b 888          888  d8P  Y8b 888 "88b d8P  Y8b   d88P  888 .88P d8P  Y8b 888                       
      "888 888  888 .d888888 888          888  88888888 888  888 88888888  d88P   888888K  88888888 888                       
Y88b  d88P 888  888 888  888 888          888  Y8b.     888  888 Y8b.     d88P    888 "88b Y8b.     888                       
 "Y8888P"  888  888 "Y888888 888          888   "Y8888  888  888  "Y8888 88888888 888  888  "Y8888  888                       
                                                                                                                              
                                                                                                                              
                                                                                                                              
 .d8888b.  888               888 888               8888888888                                d8b                              
d88P  Y88b 888               888 888               888                                       Y8P                              
Y88b.      888               888 888               888                                                                        
 "Y888b.   88888b.   .d88b.  888 888 888  888      8888888 888d888 8888b.  88888b.   .d8888b 888 .d8888b                      
    "Y88b. 888 "88b d8P  Y8b 888 888 888  888      888     888P"      "88b 888 "88b d88P"    888 88K                          
      "888 888  888 88888888 888 888 888  888      888     888    .d888888 888  888 888      888 "Y8888b.                     
Y88b  d88P 888  888 Y8b.     888 888 Y88b 888      888     888    888  888 888  888 Y88b.    888      X88                     
 "Y8888P"  888  888  "Y8888  888 888  "Y88888      888     888    "Y888888 888  888  "Y8888P 888  88888P'                     
                                          888                                                                                 
                                     Y8b d88P                                                                                 
                                      "Y88P"                                                                                  )";
    cout << cred << endl;
    initCharacter();
    bool stop = false;

   
    while (!stop)
    {

        for (int i = CREATE; i <= QUIT; i++)
        {
            SelectType foo = static_cast<SelectType>(i);
            cout << i << " - " << enum_to_string(foo) << endl;

         
        }
    cout << "Please select option: ";
            int sel;
            cin >> sel;
            stop = sel_to_op(sel);
    }
           games.clear();
        saved_characters.clear();
        saved_char_att.clear();
    return 0;
}