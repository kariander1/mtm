#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{
    const int SOLDIER_MOVE_RANGE = 3;
    const int SOLDIER_RELOAD = 3;
    class Soldier : public Character
    {
    public:
        Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Soldier(const Soldier &other) = default;
        ~Soldier() = default;
        Character* clone() const override;
        static bool outOfBounds(const GridPoint &location, const Matrix<Character *> &game_grid);
        static bool checkStopCondition(int distance, const GridPoint &location, const Matrix<Character *> &game_grid);
        void ApplyDamage(int damage, int distance, GridPoint location, Matrix<bool> &affected_cells, Matrix<Character *> &game_grid, bool adjacent_cell = false) const;
        void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const override;
        int getMoveRange() const override;
        void characterReload() override;
        
    };
} // namespace mtm

#endif