#include "Medic.h"
#include <math.h>
#include <iostream>

namespace mtm
{
    bool Medic::checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const
    {
        bool same_line_col_violation = src_location.col != dst_location.col && src_location.row != dst_location.row;
        bool distance_violation = GridPoint::distance(src_location, dst_location) > range;
        return !(same_line_col_violation || distance_violation);

    }
    bool Medic::checkTarget(const GridPoint &dst_location,const std::shared_ptr<Character> &target ) const
    {
        return !(!target || target.get()==this); // Check if pointers will be equal....

    }

    Medic::Medic(units_t health, units_t ammo, units_t range, units_t power, Team team) : Character(health, ammo, range, power, team)
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
    void Medic::characterAttack(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid)
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
                target = nullptr;
            }
            --ammo;
        }
    }

    void Medic::characterReload()
    {
        ammo += MEDIC_RELOAD;
    }
} // namespace mtm