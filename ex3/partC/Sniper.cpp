#include "Sniper.h"
#include <iostream>

namespace mtm
{
    const int SNIPER_MOVE_RANGE = 4;
    const int SNIPER_RELOAD = 2;
    const int SNIPER_DISTANCE_MODIFIER = 2;
    const int SNIPER_ATTACK_COUNT_FOR_MODIFIER = 3;
    const int SNIPER_DAMAGE_MODIFIER = 2;
    Sniper::Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team) 
                            : Character(health, ammo, range, power, team), attack_count(0)
    {
    }
    std::shared_ptr<Character> Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(health, ammo, range, power, team));
    }
    bool Sniper::checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const
    {
        int distance = GridPoint::distance(src_location, dst_location);
        int min_distance = ceil((double)range / SNIPER_DISTANCE_MODIFIER);
        return !(min_distance > distance || distance > range);
    }
    bool Sniper::checkTarget(const std::shared_ptr<Character> &target ) const
    {
       
        return !(!target || target->sameTeam(team));

    }
    void Sniper::characterAttack(const GridPoint &src_location, const GridPoint &dst_location,
                                 Matrix<std::shared_ptr<Character>> &game_grid)
    {
        ++attack_count;
        int current_power=power;
        if(attack_count==SNIPER_ATTACK_COUNT_FOR_MODIFIER)
        {
            current_power*=SNIPER_DAMAGE_MODIFIER;
            attack_count=0;
        }

        std::shared_ptr<Character> target = game_grid(dst_location.row, dst_location.col);
        if(target->receiveDamage(current_power))
        {
            game_grid(dst_location.row, dst_location.col) =nullptr;
           
        }

        --ammo;
    }
    int Sniper::getMoveRange() const
    {
        return SNIPER_MOVE_RANGE;
    }
    void Sniper::characterReload()
    {
        ammo += SNIPER_RELOAD;
    }
} // namespace mtm