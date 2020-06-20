#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm{
    const int MEDIC_MOVE_RANGE = 5;
    const int MEDIC_RELOAD = 5;
    class Medic : public Character {

    public:
        Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Medic(const Medic &other) = default;
        ~Medic() = default;
        Character* clone() const override;
        void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const override;
        int getMoveRange() const override; // add arguments and return type
        void characterReload() override;
    }; 
}


#endif