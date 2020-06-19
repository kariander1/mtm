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
        void character_attack(const GridPoint &location) const override;
        void move() override; // add arguments and return type
    };
} // namespace mtm

#endif