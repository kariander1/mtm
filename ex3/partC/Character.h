#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H
#include <string>
#include <iostream>
#include <memory>
#include "Game.h"
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

        void checkAmmo() const; // Same for all inheriting classes
        virtual void checkTarget(const GridPoint &dst_location,Matrix<std::shared_ptr<Character>> &game_grid ) const;
    private:
        virtual void checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const;
       
    public:
        Character(const units_t &health_initial, const units_t &ammo_initial,
                  const units_t &range_initial, const units_t &power_initial,const Team &team);
        Character(const Character& new_character) = default;
        virtual ~Character() = default;
        bool sameTeam(const Team &other) const;
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual void characterAttack(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) = 0;
        bool receiveDamage(const int &damage); // True if killed
        void checkAttackPrerequisites(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) const; // Same for all
        virtual void characterReload() = 0;
        virtual int getMoveRange() const = 0; // should be in protected?
    };

} // namespace mtm

#endif //CHARACTER_H