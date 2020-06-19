#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{

    Character::Character(const int &health_initial, const int &ammo_initial,
                         const int &range_initial, const int &power_initial) : health(health_initial),
                                                                               ammo(ammo_initial), range(range_initial), power(power_initial)
    {
    }

} // namespace mtm
