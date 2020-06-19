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
        int health;
        int ammo;
        const int range;
        const int power;
        const Team team;
    public:
        Character(const int &health_initial, const int &ammo_initial, const int &range_initial, const int &power_initial,const Team &team);
        virtual ~Character();
        virtual Character *clone() const = 0;
        virtual void characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const = 0;
        bool receiveDamage(const int &damage); // True if killed
        bool sameTeam(const Team &other) const; // True if killed
        virtual void reload() = 0;
        virtual void move() = 0;      // add arguments and return type
        virtual bool isEmpty() const; // add arguments and return type
    };

} // namespace mtm

#endif //CHARACTER_H