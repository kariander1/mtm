#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm{
    class Character
    {
    protected:
        int health;
        int ammo;
        const int range;
        const int power;

    public:
        
        Character(const int& health_initial, const int& ammo_initial, const int& range_initial, const int& power_initial);
        virtual ~Character();
        virtual void character_attack(const GridPoint& location) const = 0;
        virtual void move(); // add arguments and return type
    };
    
}

#endif //CHARACTER_H