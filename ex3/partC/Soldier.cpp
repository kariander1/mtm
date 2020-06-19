#include "Soldier.h"
#include <math.h>       
namespace mtm
{
    Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team):
            Character(health, ammo,range, power, team )        
    {
        
    }
    Character* Soldier::clone() const{
        return new Soldier(*this);
    }

    bool Soldier::outOfBounds(const GridPoint &location, const Matrix<Character *> &game_grid)
    {
        if (location.col < 0 || location.row < 0 || location.col >= game_grid.width() || location.row >= game_grid.height())
            return true;
        return false;
    }
    bool Soldier::checkStopCondition(int distance,const GridPoint &location, const Matrix<Character *> &game_grid)
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
    void Soldier::ApplyDamage(int damage, int distance, GridPoint location, Matrix<bool> &affected_cells, Matrix<Character *> &game_grid, bool adjacent_cell) const
    {
        if(checkStopCondition(distance,location,game_grid))
        {
            return;
        }
        if(!affected_cells(location.row,location.col))
        {
            Character* target =game_grid(location.row,location.col);
            if(!target->isEmpty() || target->sameTeam(this->team))
            {
                if(target->receiveDamage(damage))
                { // Target was killed!
                
                    delete target; // Not sure about this
                    // TODO Should assign an empty cell there?
                }
            }
            affected_cells(location.row,location.col)=true;
        }
        if(!adjacent_cell)
        { // From now on affecting adjcent cells
            adjacent_cell=true;
            damage=ceil(damage/2);
        }
        ApplyDamage(damage,distance,GridPoint(location.row-1,location.col),affected_cells,game_grid,adjacent_cell); //dont you should send distance -1? (for all the below functions)
        ApplyDamage(damage,distance,GridPoint(location.row,location.col-1),affected_cells,game_grid,adjacent_cell);
        ApplyDamage(damage,distance,GridPoint(location.row+1,location.col),affected_cells,game_grid,adjacent_cell);
        ApplyDamage(damage,distance,GridPoint(location.row,location.col+1),affected_cells,game_grid,adjacent_cell);
        
    }
    void Soldier::characterAttack(const GridPoint &location, Matrix<Character *> &game_grid) const
    {
        Dimensions matrix_dims(game_grid.height(), game_grid.width());
        Matrix<bool> affected_cells(matrix_dims, false);

        ApplyDamage(power,ceil(range/3), location, affected_cells, game_grid);
    }

} // namespace mtm
