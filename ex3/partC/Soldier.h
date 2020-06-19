#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm{
    
    class Soldier : public Character {
    private:
        int attack_count;
    public:
        void characterAttack(const GridPoint& location) const override;
        void move()override; // add arguments and return type
    }; 
}


#endif