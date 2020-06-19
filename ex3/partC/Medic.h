#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm{
    class Medic : public Character {

    public:
        void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const override;
        void move()override; // add arguments and return type
    }; 
}


#endif