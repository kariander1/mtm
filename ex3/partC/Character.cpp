#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{

    Character::Character(const int &health_initial, const int &ammo_initial,
                         const int &range_initial, const int &power_initial, const Team &team)
                         : health(health_initial),
                        ammo(ammo_initial), range(range_initial), power(power_initial), team(team)
    {
    }
    bool Character::sameTeam(const Team &other) const
    {
        return team == other;
    }
    bool Character::receiveDamage(const int &damage)
    {
        health -= damage;
        return health <= 0;
    }

} // namespace mtm
