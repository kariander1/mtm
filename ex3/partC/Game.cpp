#include "Game.h"

namespace mtm
{
    void Game::checkBounds(const GridPoint &coordinates) const
    {
        if (coordinates.col >= game_grid.width() || coordinates.row < 0)
        {
            throw IllegalCell();
        }
    }
    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        checkBounds(coordinates);
        if (!game_grid(coordinates.row, coordinates.col)->isEmpty())
        {
            throw CellOccupied();
        }
        game_grid(coordinates.row, coordinates.col) = character->clone();
    }
    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkBounds(src_coordinates);
        checkBounds(dst_coordinates);
        if (game_grid(src_coordinates.row, src_coordinates.col)->isEmpty())
        {
            throw CellEmpty();
        }
        game_grid(src_coordinates.row, src_coordinates.col)->characterAttack(dst_coordinates,game_grid);
    }
} // namespace mtm
