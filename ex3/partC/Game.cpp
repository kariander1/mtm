#include <memory>
#include "Game.h"
#include "Auxiliaries.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

namespace mtm
{
    const Team LOWER_CASE_TEAM = PYTHON;
    const std::string REPRESENTING_STRING_INIT ="";
    const char STRING_DELIMITER =' ';
    const char SOLDIER_LITERAL = 'S';
    const char SNIPER_LITERAL = 'N';
    const char MEDIC_LITERAL = 'M';


    Game::Game(int height, int width) : game_grid(checkGameSize(height, width), nullptr) // initial with nullptr
    {
    }
    Dimensions Game::checkGameSize(const int &height, const int &width)
    {
        if (height <= 0 || width <= 0)
        {
            throw IllegalArgument();
        }
        return Dimensions(height, width);
    }
    void Game::cloneGameGrid(Matrix<std::shared_ptr<Character>> &source_matrix, const Game &other_game)
    {
        int grid_rows = other_game.game_grid.height();
        int grid_columns = other_game.game_grid.width();
        for (int i = 0; i < grid_rows; i++)
        {
            for (int j = 0; j < grid_columns; j++)
            {
                if (other_game.game_grid(i, j) != nullptr)
                { 
                    source_matrix(i, j) = other_game.game_grid(i, j)->clone(); // Clone might throw bad_alloc
                }
            }
        }
    }

    Game::Game(const Game &other) : game_grid(Dimensions(other.game_grid.height()
                                            ,other.game_grid.width()),nullptr) 
    {
        cloneGameGrid(game_grid, other);
    }
    Game &Game::operator=(const Game &other)
    {

        Dimensions other_dimensions(other.game_grid.height(),other.game_grid.width());
        Matrix<std::shared_ptr<Character>> temp_matrix(other_dimensions,nullptr);
        
        cloneGameGrid(temp_matrix, other); // First try and copy values to temp matrix. might throw bad_alloc!
                                        // If an exception is thrown, the d'tor of temp_matirx will be called
        game_grid =temp_matrix; // apply changes to games matrix
        return *this;
    }
    void Game::isEmpty(const GridPoint &coordinates) const
    {
        if (game_grid(coordinates.row, coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }
    }
    void Game::isNotEmpty(const GridPoint &coordinates) const
    {
        if (game_grid(coordinates.row, coordinates.col) != nullptr)
        {
            throw CellOccupied();
        }
    }
    void Game::checkBounds(const GridPoint &coordinates) const
    {     
        if(coordinates.row<0 || coordinates.row>=game_grid.height() ||
            coordinates.col<0 || coordinates.col>=game_grid.width())
        {
            throw IllegalCell();
        }
    }
    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        checkBounds(coordinates);
        isNotEmpty(coordinates);
        game_grid(coordinates.row, coordinates.col) = character;
    }
    void Game::checkAttackPrerequisites(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) const
    {
        std::shared_ptr<Character> character = game_grid(src_coordinates.row, src_coordinates.col);
        std::shared_ptr<Character> target = game_grid(dst_coordinates.row, dst_coordinates.col);
        if (!character->checkAttackRange(src_coordinates, dst_coordinates))
        {
            throw OutOfRange();
        }
        if (!character->checkAmmo(target))
        {
            throw OutOfAmmo();
        }
        if (!character->checkTarget(game_grid(dst_coordinates.row, dst_coordinates.col)))
        {
            throw IllegalTarget();
        }
    }
    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkBounds(src_coordinates);
        checkBounds(dst_coordinates);
        isEmpty(src_coordinates);
        checkAttackPrerequisites(src_coordinates, dst_coordinates);

        // All Prerequisites checked, ready to attack. No exceptions expected from here on
       std::vector<GridPoint> killed_characters= game_grid(src_coordinates.row, src_coordinates.col)
                ->characterAttack(src_coordinates,dst_coordinates, game_grid);

        // Remove dead characters
         for (std::vector<GridPoint>::iterator it = killed_characters.begin() ; it != killed_characters.end(); ++it)
         {
             game_grid(it->row,it->col) =nullptr;
         }

    }
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health,
                                                   units_t ammo, units_t range, units_t power)
    {
        if ((health <= 0) || (ammo < 0) || (range < 0) || (power < 0))
        {
            throw IllegalArgument();
        }
        if (type == SOLDIER)
        {
            std::shared_ptr<Character> character_ptr(new Soldier(health, ammo, range, power, team));
            return character_ptr;
        }
        else if (type == MEDIC)
        {
            std::shared_ptr<Character> character_ptr(new Medic(health, ammo, range, power, team));
            return character_ptr;
        }
        else if (type == SNIPER)
        {
            std::shared_ptr<Character> character_ptr(new Sniper(health, ammo, range, power, team));
            return character_ptr;
        }
        return nullptr; // should not get here
    }

    void Game::outOfCharacterRange(const Character &character, const GridPoint &point1, const GridPoint &point2)
    {
        if (GridPoint::distance(point1, point2) > character.getMoveRange())
        {
            throw MoveTooFar();
        }
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkBounds(src_coordinates);
        checkBounds(dst_coordinates);
        isEmpty(src_coordinates); // check if the source cell is empty (shouldn't be)
        outOfCharacterRange(*(game_grid(src_coordinates.row, src_coordinates.col)), src_coordinates, dst_coordinates);
        isNotEmpty(dst_coordinates);             // check if the destination cell is empty (should be)
         // moves the character
        game_grid(dst_coordinates.row, dst_coordinates.col) = game_grid(src_coordinates.row, src_coordinates.col);
        game_grid(src_coordinates.row, src_coordinates.col) = nullptr;  //  reset the old coordinates to point to Null                                         
    }

    void Game::reload(const GridPoint &coordinates)
    {
        checkBounds(coordinates);
        isEmpty(coordinates);
        game_grid(coordinates.row, coordinates.col)->characterReload();
    }

    bool Game::checkWinnerExistance(Team &put_winner) const
    {
        int player_python = 0;
        int players_cpp = 0;
        int grid_rows = game_grid.height();
        int grid_columns = game_grid.width();
        for (int i = 0; i < grid_rows; i++)
        {
            for (int j = 0; j < grid_columns; j++)
            {
                if (game_grid(i, j) == nullptr)
                {
                    continue;
                }
                if (game_grid(i, j)->sameTeam(CPP))
                {
                    players_cpp++;
                }
                else
                {
                    player_python++;
                }
            }
        }
        if (player_python*players_cpp == 0 && (players_cpp+player_python)>0) // There is a winner!
        {
            put_winner = (player_python > 0 ? PYTHON : CPP);
            return true;
        }
        return false;
    }
    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        std::string representing_String = REPRESENTING_STRING_INIT;
        for (mtm::Matrix<std::shared_ptr<Character>>::const_iterator it = game.game_grid.begin();
             it != game.game_grid.end(); it++)
        {
            const Soldier *soldier = dynamic_cast<const Soldier *>((*it).get());
            const Medic *medic = dynamic_cast<const Medic *>((*it).get());
            const Sniper *sniper = dynamic_cast<const Sniper *>((*it).get());
            char char_to_concatenate = STRING_DELIMITER;
            if (soldier)
            {
                char_to_concatenate = SOLDIER_LITERAL;
            }
            else if (medic)
            {
                char_to_concatenate = MEDIC_LITERAL;
            }
            else if (sniper)
            {
                char_to_concatenate = SNIPER_LITERAL;
            }

            if (*it && (*it)->sameTeam(LOWER_CASE_TEAM))
            { 
                char_to_concatenate = tolower(char_to_concatenate);
            }
            representing_String += char_to_concatenate;
        }

        const char *start = representing_String.c_str();
        const char *end_ptr = start + representing_String.length();
        return printGameBoard(os, start, end_ptr, game.game_grid.width());
    }
    bool Game::isOver(Team *winningTeam) const
    {
        Team winner;
        if (checkWinnerExistance(winner))
        {
            if (winningTeam)
            {
                *winningTeam = winner;
            }
            return true;
        }
        return false;
    }

    
} // namespace mtm
