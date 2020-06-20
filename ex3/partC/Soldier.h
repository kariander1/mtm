#ifndef HW3_SOLDIER_H
#define HW3_SOLDIER_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{
    const int SOLDIER_MOVE_RANGE = 3;
    const int SOLDIER_RELOAD = 3;
    class Soldier : public Character
    {
    private:
        // Overriden private functions:
        void checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const override;
        void checkTarget(const GridPoint &dst_location,Matrix<std::shared_ptr<Character>> &game_grid) const override{}

        // Helper functions
        static bool outOfBounds(const GridPoint &location, const Matrix<std::shared_ptr<Character>> &game_grid); // Used for recursion
        static bool checkStopCondition(int distance, const GridPoint &location, const Matrix<std::shared_ptr<Character>> &game_grid);
        void ApplyDamage(int damage, int distance, GridPoint location, Matrix<bool> &affected_cells, Matrix<std::shared_ptr<Character>> &game_grid, bool adjacent_cell = false) const;
    public:

        /// C'tor, Copy C'tor and D'tor
        Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Soldier(const Soldier &other) = default;
        ~Soldier() = default;

        // Overriden public functions:
        std::shared_ptr<Character> clone() const override;
        void characterAttack(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid) override;
        int getMoveRange() const override;
        void characterReload() override;
    };
} // namespace mtm

#endif