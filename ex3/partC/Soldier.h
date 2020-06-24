#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H

#include "Character.h"

namespace mtm
{
    
    class Soldier : public Character
    {
    private:
        // Helper functions

        /**
        * outOfBounds: checks whether given locations exceeds game grid boundries
        * @param location - The given location
        * @param game_grid - The game_grid to check boundries
        * @return
        * 	whether the location is within boundries
        */
        static bool outOfBounds(const GridPoint &location,
                                const Matrix<std::shared_ptr<Character>> &game_grid); // Used for recursion
        /**
        * checkStopCondition: checks whther to stop the applyDamage function
        * @param distance - Distance remaining for area of damage
        * @param location - Current location of damage
        * @param game_grid - The game grid
        * @return
        * 	whether to continue applying damge
        */
        static bool checkStopCondition(int distance, const GridPoint &location,
                                       const Matrix<std::shared_ptr<Character>> &game_grid);
        /**
        * ApplyDamage: apply damage to location. Recursive
        * @param damage - The damage to inflict on the target
        * @param distance - Distance remaining for area of damage
        * @param location - Current location of damage
        * @param affected_cells - already affected cells from damage
        * @param game_grid - The game grid
        * @param adjacent_cell - If the attack is on an adjacent cell
        * @return
        * 	whether to continue applying damge
        */
        void ApplyDamage(int damage, int distance, GridPoint location, Matrix<bool> &affected_cells,
                         Matrix<std::shared_ptr<Character>> &game_grid,std::vector<GridPoint> &killed_characters
                         , bool adjacent_cell = false) const;

    public:
        /// C'tor, Copy C'tor and D'tor, same as character
        Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Soldier(const Soldier &other) = default;
        ~Soldier() override {}

        // Overriden public functions:
        std::shared_ptr<Character> clone() const override;
        std::vector<GridPoint> characterAttack(const GridPoint &src_location
                                                                , const GridPoint &dst_location,
                             Matrix<std::shared_ptr<Character>> &game_grid) override;
        bool checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const override;
        bool checkTarget(const std::shared_ptr<Character> &target) const override;

        int getMoveRange() const override;
        void characterReload() override;
    };
} // namespace mtm

#endif