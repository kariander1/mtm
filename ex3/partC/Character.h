#ifndef HW3_CHARACTER_H
#define HW3_CHARACTER_H
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include "Auxiliaries.h"
#include "Matrix.h"
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
        /**
        * Character: C'tor
        * Constructor of character. Gets the five defining properties of charcter:
        * Health,Ammo,Range,Power and team. Character type is defined via inheritence
        */
        Character(const units_t &health_initial, const units_t &ammo_initial, 
                  const units_t &range_initial, const units_t &power_initial,const Team &team); //C'tor
        
        /**
        * Character: Copy C'tor
        * Copies an instance of character. all properties are basic types int and ENUM.
        */
        Character(const Character& new_character) = default; // Copy c'tor
        /**
        * Character: D'tor
        * Destroies and instace of a character. It is being inherited
        */
        virtual ~Character() = default; // D'tor
        
        /**
        * Clone: Virtual function to clone character.
        * 
        * @return
        * 	Shared pointer to the character cloned
        */
        virtual std::shared_ptr<Character> clone() const = 0;
        /**
        * characterReload: reload the characters ammo
        * 
        * @return
        * 	None
        */
        virtual void characterReload() = 0;
        /**
        * getMoveRange: gets the character's distance range property
        * 
        * @return
        * 	int of character's distance range property
        */
        virtual int getMoveRange() const = 0; // should be in protected?
    
        /**
        * sameTeam: returns whether the characters is on the same team given
        * @param other - The team to check on
        * @return
        * 	whether the characters is on the same team given
        */
        bool sameTeam(const Team &other) const;
        /**
        * characterAttack: performs a character attack from a given cell to a given cell
        * @param src_location - The source cell
        * @param dst_location - The destination cell
        * @param game_grid - The game_grid, in order to perform a an attack on characters there
        * @return
        * 	Return a vector with all dead characters locations.
        */
        virtual std::vector<GridPoint> characterAttack(const GridPoint &src_location, const GridPoint &dst_location,
                                                          Matrix<std::shared_ptr<Character>> &game_grid) = 0;
        /**
        * checkAmmo: checks if the character has ammo to perform the action
        * @param target - The target the character has to consier when cheking ammo
        * @return
        * 	whether the characters can perform the attack considering ammo. Being overriden in Medic.
        */
        virtual bool checkAmmo(const std::shared_ptr<Character> &target) const;
        /**
        * checkTarget: checks if the dest character is legal
        * @param target - The target the character has to consier when cheking
        * @return
        * 	whether the dest character is legal
        */
        virtual bool checkTarget(const std::shared_ptr<Character> &target, const GridPoint &src_location
                                                        , const GridPoint &dst_location) const=0;
        /**
        * checkAttackRange: checks if dst location is within atack racnge
        * @param src_location - The source location of character
        * @param dst_location - The dest location to attack
        * @return
        * 	whether the dest character is legal
        */
        virtual bool checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const =0;
        /**
        * receiveDamage: receives given damage to health, can be negative(healing)
        * @param damage - The amount of damage to apply
        * @return
        * 	whether the character was killed
        */
        bool receiveDamage(const int &damage); // True if killed
    };

} // namespace mtm

#endif //CHARACTER_H