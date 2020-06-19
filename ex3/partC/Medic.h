#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm{
    class Medic : public Character {

    public:
        void character_attack(const GridPoint& location) const override;
        void move()override; // add arguments and return type
    }; 
}


#endif