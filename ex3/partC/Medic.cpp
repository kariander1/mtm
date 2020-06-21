#include "Medic.h"
#include <math.h>
#include <iostream>

namespace mtm
{
    bool Medic::checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const
    {     
        bool distance_violation = GridPoint::distance(src_location, dst_location) > range;
        return !(distance_violation);

    }
    bool Medic::checkTarget(const std::shared_ptr<Character> &target ) const
    {
        return !(!target || target.get()==this); // Check if pointers will be equal....

    }

    Medic::Medic(units_t health, units_t ammo, units_t range, units_t power, Team team) 
    : Character(health, ammo, range, power, team)
    {
    }
    std::shared_ptr<Character> Medic::clone() const
    {
        return std::shared_ptr<Character>(new Medic(health, ammo, range, power, team));
    }
    int Medic::getMoveRange() const
    {
        return MEDIC_MOVE_RANGE;
    }
    void Medic::characterAttack(const GridPoint &src_location, const GridPoint &dst_location,
                                 Matrix<std::shared_ptr<Character>> &game_grid)
    {

        std::shared_ptr<Character> target = game_grid(dst_location.row, dst_location.col);
        if (target->sameTeam(team))
        {
            target->receiveDamage(-power);
        }
        else
        {
            if (target->receiveDamage(power))
            {
                game_grid(dst_location.row, dst_location.col) = nullptr;
            }
            --ammo;
        }
    }
    bool Medic::checkAmmo(const std::shared_ptr<Character> &target) const
    {
        return (target->sameTeam(team) ? true : !(ammo<=0));
    }
    void Medic::characterReload()
    {
        ammo += MEDIC_RELOAD;
    }
} // namespace mtm