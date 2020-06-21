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
        unsigned short int attack_count;

    public:
        /// C'tor, Copy C'tor and D'tor, same as character
        Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Sniper(const Sniper &other) = default; // Will also copy attack_count
        ~Sniper() override {} // Also destructs attack_count

        // Overriden public functions: Documentation at character.h
        std::shared_ptr<Character> clone() const override;
        void characterAttack(const GridPoint &src_location, const GridPoint &dst_location,
                             Matrix<std::shared_ptr<Character>> &game_grid) override;
        bool checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const override;
        bool checkTarget(const std::shared_ptr<Character> &target) const override;

        int getMoveRange() const override;
        void characterReload() override;
    };
} // namespace mtm

#endif