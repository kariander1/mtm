#include "Medic.h"
#include <math.h> 
#include <iostream>

namespace mtm
{
    Medic::Medic(units_t health, units_t ammo, units_t range, units_t power, Team team):
            Character(health, ammo,range, power, team )        
    {
        
    }
    Character* Medic::clone() const{
        return new Medic(*this);
    }
}