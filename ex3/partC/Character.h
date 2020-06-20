#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H
#include <string>
#include <iostream>
#include <memory>
#include "Auxiliaries.h"
#include "../partB/Matrix.h"
namespace mtm
{
    class Character
    {
    protected:
        units_t health;
        units_t ammo;
        const units_t range;
        const units_t power;
        const Team team;
       
    public:
        Character(const units_t &health_initial, const units_t &ammo_initial, 
                  const units_t &range_initial, const units_t &power_initial,const Team &team); //C'tor
        Character(const Character& new_character) = default; // Copy c'tor
        virtual ~Character() = default; // D'tor
        
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual void characterReload() = 0;
        virtual int getMoveRange() const = 0; // should be in protected?
    

        bool sameTeam(const Team &other) const;
        virtual void characterAttack(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) = 0;
        bool checkAmmo() const; // Same for all inheriting classes
        virtual bool checkTarget(const GridPoint &dst_location,const std::shared_ptr<Character> &target ) const=0;
        virtual bool checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const =0;
        bool receiveDamage(const int &damage); // True if killed
    };

} // namespace mtm

#endif //CHARACTER_H