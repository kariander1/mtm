#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{

    Character::Character(const units_t &health_initial, const units_t &ammo_initial,
                  const units_t &range_initial, const units_t &power_initial,const Team &team)
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
    void Character::checkAmmo() const
    {
        if(ammo<=0)
        {
            throw Game::OutOfAmmo();
        }
    }
    void Character::checkAttackPrerequisites(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) const
    {
        checkAttackRange(src_location,dst_location);
        checkAmmo();
        checkTarget(dst_location,game_grid);
    }

} // namespace mtm
