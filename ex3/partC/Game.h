#ifndef HW3_GAME_H
#define HW3_GAME_H

#include <iostream>
#include <memory>
#include "../partB/Matrix.h"
#include "Auxiliaries.h"
#include "Character.h"
namespace mtm
{
    const std::string GAME_ERROR_PREFIX="A game related error has occurred: ";
    const std::string GAME_ILLEGAL_ARGUMENT = GAME_ERROR_PREFIX + "IllegalArgument";
    const std::string GAME_ILLEGAL_CELL = GAME_ERROR_PREFIX + "IllegalCell";
    const std::string GAME_CELL_EMPTY = GAME_ERROR_PREFIX + "CellEmpty";
    const std::string GAME_MOVE_TOO_FAR = GAME_ERROR_PREFIX + "MoveTooFar";
    const std::string GAME_CELL_OCCUPIED = GAME_ERROR_PREFIX + "CellOccupied";
    const std::string GAME_OUT_OF_RANGE = GAME_ERROR_PREFIX + "OutOfRange";
    const std::string GAME_OUT_OF_AMMO = GAME_ERROR_PREFIX + "OutOfAmmo";
    const std::string GAME_ILLEGAL_TARGET = GAME_ERROR_PREFIX + "IllegalTarget";
    class Game
    {
      
    private:
        Matrix<std::shared_ptr<Character>> game_grid;
        // helper functions
        void checkBounds(const GridPoint& coordinates) const;
        void checkAttackPrerequisites(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, std::shared_ptr<Character> &character) const;
        void cloneGameGrid(Game* new_game, const Game& other_game );
        void isEmpty(const GridPoint& coordinates) const; // for source coordinates
        void isNotEmpty(const GridPoint& coordinates) const; // for destination coordinates
        void outOfCharacterRange(const Character& character,const GridPoint& point1, const GridPoint& point2);
        bool checkWinnerExsistance(Team& put_winner)const;
        
    public:
        Game(int height, int width);        // C'tor
        ~Game() = default; // why delete?   // D'tor
        Game(const Game &other);            // Copt c'tor
        Game &operator=(const Game &other); // Assignment operator
        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character); // need TODO
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                    units_t health, units_t ammo, units_t range, units_t power);// need TODO
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void reload(const GridPoint &coordinates);
        friend std::ostream &operator<<(std::ostream &os, const Game &game);
  
        bool isOver(Team* winningTeam=NULL) const;

        class Exception : public mtm::Exception{};
        class IllegalArgument;
        class IllegalCell;
        class CellEmpty;
        class CellOccupied;
        class OutOfRange;
        class OutOfAmmo;
        class IllegalTarget;
        class MoveTooFar;
    };

     class Game::IllegalArgument : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_ILLEGAL_ARGUMENT;
        }
    };

    class Game::IllegalCell : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_ILLEGAL_CELL;
        }
    };
    class Game::CellEmpty : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_CELL_EMPTY;
        }
    };
    class Game::MoveTooFar : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_MOVE_TOO_FAR;
        }
    };
    class Game::CellOccupied : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_CELL_OCCUPIED;
        }
    };
    class Game::OutOfRange : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_OUT_OF_RANGE;
        }
    };
    class Game::OutOfAmmo : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_OUT_OF_AMMO;
        }
    };
    class Game::IllegalTarget : public Exception{
    public:
        std::string what() noexcept
        {
            return GAME_ILLEGAL_TARGET;
        }
    };
   
    
    
   
} // namespace mtm

#endif //HW3_GAME_H