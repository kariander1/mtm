#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{

    class Soldier : public Character
    {
    private:
        static bool outOfBounds(const GridPoint &location, const Matrix<Character *> &game_grid);
        static bool checkStopCondition(int distance, const GridPoint &location, const Matrix<Character *> &game_grid);
        void ApplyDamage(int damage, int distance, GridPoint location, Matrix<bool> &affected_cells, Matrix<Character *> &game_grid, bool adjacent_cell = false) const;
        void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const override;
        void move() override; // add arguments and return type
    };
} // namespace mtm

#endif