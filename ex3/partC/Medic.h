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

     private:
        // Overriden private functions:
        void checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const override;
        void checkTarget(const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) const override;

    public:
        /// C'tor, Copy C'tor and D'tor
        Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Medic(const Medic &other) = default;
        ~Medic() = default;

        // Overriden public functions:
        std::shared_ptr<Character> clone() const override;
        void characterAttack(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) override;
        int getMoveRange() const override;
        void characterReload() override;
    }; 
}


#endif