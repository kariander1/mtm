#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H
#include <string>
#include <iostream>
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
                  const units_t &range_initial, const units_t &power_initial,const Team &team);
        Character(const Character& new_character) = default;
        virtual ~Character();
        virtual Character *clone() const = 0;
        virtual void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const = 0;
        bool receiveDamage(const int &damage); // True if killed
        bool sameTeam(const Team &other) const; // True if killed
        // virtual void reload() = 0; just for now
        virtual void move() = 0;      // add arguments and return type
        virtual bool isEmpty() const; // add arguments and return type
        int getRange() const;
    };

} // namespace mtm

#endif //CHARACTER_H