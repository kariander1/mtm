#ifndef HW3_GAME_H
#define HW3_GAME_H

#include <iostream>
#include <memory>
#include "../partB/Matrix.h"
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{
    class Game
    {
    private:
        Matrix<Character*> game_grid;
        void checkBounds(const GridPoint& coordinates) const;
    public:
        Game(int height, int width);        // C'tor
        ~Game() =delete;                    // D'tor
        Game(const Game &other);            // Copt c'tor
        Game &operator=(const Game &other); // Assignment operator
        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void reload(const GridPoint &coordinates);
        std::ostream &printGameBoard(std::ostream &os, const char *begin,
                                     const char *end, unsigned int width) const;
        bool isOver(Team* winningTeam=NULL) const;

        class Exception : public mtm::Exception{};
        class IllegalArgument;
        class IllegalCell;
        class CellEmpty;
        class CellOccupied;
        class OutOfRange;
        class OutOfAmmo;
        class IllegalTarget;
    };
   
} // namespace mtm

#endif //HW3_GAME_H