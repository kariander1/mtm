#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{
    class Sniper : public Character
    {
    private:
        int attack_count;

    public:
        Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Sniper(const Sniper &other) = default;
        Character* clone() const override;
        void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const override;
        void move() override; // add arguments and return type
        
    };
} // namespace mtm

#endif