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
        /// C'tor, Copy C'tor and D'tor - Same as character
        Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Medic(const Medic &other) = default;
       ~Medic() override{}

        // Overriden public functions. Documentation at character.h
        std::shared_ptr<Character> clone() const override;
        void characterAttack(const GridPoint &src_location, const GridPoint &dst_location,
                             Matrix<std::shared_ptr<Character>> &game_grid) override;
        bool checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const override;
        bool checkTarget(const std::shared_ptr<Character> &target ) const override;
        bool checkAmmo(const std::shared_ptr<Character> &target) const override;
        int getMoveRange() const override;
        void characterReload() override;

       
    }; 
}


#endif