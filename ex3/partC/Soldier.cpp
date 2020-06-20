#include "Soldier.h"
#include <math.h>
namespace mtm
{
    Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team) : Character(health, ammo, range, power, team)
    {
    }
    std::shared_ptr<Character> Soldier::clone() const
    {

        return std::shared_ptr<Character>(new Soldier(health, ammo, range, power, team));
    }
    int Soldier::getMoveRange() const
    {
        return SOLDIER_MOVE_RANGE;
    }

    bool Soldier::outOfBounds(const GridPoint &location, const Matrix<std::shared_ptr<Character>> &game_grid)
    {
        if (location.col < 0 || location.row < 0 || location.col >= game_grid.width() || location.row >= game_grid.height())
            return true;
        return false;
    }
    bool Soldier::checkStopCondition(int distance, const GridPoint &location, const Matrix<std::shared_ptr<Character>> &game_grid)
    {
        if (distance < 0)
        {
            return true;
        }
        if (outOfBounds(location, game_grid))
        {
            return true;
        }
        return false;
    }
    void Soldier::ApplyDamage(int damage, int distance, GridPoint location, Matrix<bool> &affected_cells, Matrix<std::shared_ptr<Character>> &game_grid, bool adjacent_cell) const
    {
        if (checkStopCondition(distance, location, game_grid))
        {
            return;
        }
        if (!affected_cells(location.row, location.col))
        {
            std::shared_ptr<Character> target = game_grid(location.row, location.col);
            if (target && !target->sameTeam(this->team))
            {
                if (target->receiveDamage(damage))
                { // Target was killed!

                  game_grid(location.row, location.col) =nullptr;
                }
            }
            affected_cells(location.row, location.col) = true;
        }
        if (!adjacent_cell)
        { // From now on affecting adjcent cells
            adjacent_cell = true;
            damage = ceil((double)damage / 2);
        }
        --distance;
        ApplyDamage(damage, distance, GridPoint(location.row - 1, location.col), affected_cells, game_grid, adjacent_cell);
        ApplyDamage(damage, distance, GridPoint(location.row, location.col - 1), affected_cells, game_grid, adjacent_cell);
        ApplyDamage(damage, distance, GridPoint(location.row + 1, location.col), affected_cells, game_grid, adjacent_cell);
        ApplyDamage(damage, distance, GridPoint(location.row, location.col + 1), affected_cells, game_grid, adjacent_cell);
    }
    bool Soldier::checkTarget(const GridPoint &dst_location, const std::shared_ptr<Character> &target) const
    {
        return true;
    }
    bool Soldier::checkAttackRange(const GridPoint &src_location, const GridPoint &dst_location) const
    {
        bool same_line_col_violation = src_location.col != dst_location.col && src_location.row != dst_location.row;
        bool distance_violation = GridPoint::distance(src_location, dst_location) > range;
        return !(same_line_col_violation || distance_violation);
    }
    void Soldier::characterAttack(const GridPoint &src_location, const GridPoint &dst_location, Matrix<std::shared_ptr<Character>> &game_grid)
    {
        Dimensions matrix_dims(game_grid.height(), game_grid.width());
        Matrix<bool> affected_cells(matrix_dims, false);
        ApplyDamage(power, ceil((double)range / 3), dst_location, affected_cells, game_grid);
        --ammo;
    }
    void Soldier::characterReload()
    {
        ammo += SOLDIER_RELOAD;
    }

} // namespace mtm
