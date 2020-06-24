#include "Medic.h"

#include <iostream>

namespace mtm
{
    const units_t MEDIC_MOVE_RANGE = 5;
    const units_t MEDIC_RELOAD = 5;
    bool Medic::checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const
    {     
        bool distance_violation = GridPoint::distance(src_location, dst_location) > range;
        return !(distance_violation);

    }
    bool Medic::checkTarget(const std::shared_ptr<Character> &target ) const
    {
        return !(!target || target.get()==this); // Check if pointers will be equal

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
    std::vector<GridPoint> Medic::characterAttack(const GridPoint &src_location, const GridPoint &dst_location,
                                 Matrix<std::shared_ptr<Character>> &game_grid)
    {
        std::vector<GridPoint> killed_characters;
        std::shared_ptr<Character> target = game_grid(dst_location.row, dst_location.col);
        if (target->sameTeam(team))
        {
            target->receiveDamage(-power);
        }
        else
        {
            if (target->receiveDamage(power))
            {
                killed_characters.push_back(dst_location);
            }
            --ammo;
        }
        return killed_characters;
    }
    bool Medic::checkAmmo(const std::shared_ptr<Character> &target) const
    {
        bool ammo_non_negative=!(ammo<=0);
        if(target)
        {
            return (target->sameTeam(team) ? true : ammo_non_negative);
        }
        return ammo_non_negative;   
    }
    void Medic::characterReload()
    {
        ammo += MEDIC_RELOAD;
    }
} // namespace mtm