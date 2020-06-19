#include "Sniper.h"
#include <math.h> 
#include <iostream>

namespace mtm
{
    Sniper::Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team):
            Character(health, ammo,range, power, team )        
    {
        
    }
    Character* Sniper::clone() const{
        return new Sniper(*this);
    }
}