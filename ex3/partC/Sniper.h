#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{
    const int SNIPER_MOVE_RANGE = 4;
    const int SNIPER_RELOAD = 2;
    class Sniper : public Character
    {
    private:
        int attack_count;

    public:
        Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Sniper(const Sniper &other) = default;
        ~Sniper() = default;
        Character* clone() const override;
        void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const override;
        int getMoveRange() const override;
        void characterReload() override;
    };
} // namespace mtm

#endif