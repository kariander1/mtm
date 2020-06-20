#include <memory>
#include "Game.h"
#include "Auxiliaries.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
namespace mtm
{
    
    Game::Game(int height, int width) : game_grid(Dimensions(height, width), nullptr) // resent the game grid with all nullptr 
    {
        if (height <= 0 || width <=0){
            throw IllegalArgument();
        }
    };

    void Game::cloneGameGrid(Game* new_game, const Game& other_game )
    {
        int grid_rows = other_game.game_grid.height();
        int grid_columns = other_game.game_grid.width();
        for (int i = 0; i<grid_rows;i++){
            for(int j = 0; j < grid_columns; j++){
                new_game->game_grid(i,j) = other_game.game_grid(i,j)->clone(); // copy pointers and their value
            }
        }
    }

    Game::Game(const Game &other): game_grid(other.game_grid) // copy only pointers
    {
        cloneGameGrid(this, other);
        
    }
    Game& Game::operator=(const Game &other)
    {
        game_grid = other.game_grid; // copy only pointers
        cloneGameGrid(this, other);
        return *this;

    }
    void Game::isEmpty(const GridPoint& coordinates) const
    {
        if (game_grid(coordinates.row, coordinates.col) == nullptr){
            throw CellEmpty();
        }
    }
    void Game::isNotEmpty(const GridPoint& coordinates) const
    {
        if (game_grid(coordinates.row, coordinates.col) != nullptr){
            throw CellOccupied();
        }
    }
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
        isNotEmpty(coordinates);
        /*if (!game_grid(coordinates.row, coordinates.col)->isEmpty())
        {
            throw CellOccupied();
        }*/
        game_grid(coordinates.row, coordinates.col) = character->clone();
    }
    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkBounds(src_coordinates);
        checkBounds(dst_coordinates);
        isEmpty(src_coordinates);
        /*if (game_grid(src_coordinates.row, src_coordinates.col)->isEmpty())
        {
            throw CellEmpty();
        }*/
        game_grid(src_coordinates.row, src_coordinates.col)->characterAttack(dst_coordinates,game_grid);
    }
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type,
        Team team, units_t health, units_t ammo, units_t range, units_t power)
    {
        if (health<=0){
            throw IllegalArgument();
        }
        if (type == SOLDIER){
            std::shared_ptr<Character> character_ptr ( new Soldier(health, ammo, range, power, team));
            return character_ptr;
        }
        else if (type == MEDIC){
            std::shared_ptr<Character> character_ptr ( new Medic(health, ammo, range, power, team));
            return character_ptr;
        }
        else if (type == SNIPER){
            std::shared_ptr<Character> character_ptr ( new Sniper(health, ammo, range, power, team));
            return character_ptr;
        }
        return nullptr; // should not get here
        
    }

    
    void Game::outOfCharacterRange(const Character& character, const GridPoint& point1, const GridPoint& point2)
    {
        if (GridPoint::distance(point1, point2) > character.getMoveRange()){
            throw Game::MoveTooFar();
        }
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkBounds(src_coordinates);
        checkBounds(dst_coordinates);
        isEmpty(src_coordinates); // check if the src cell is empty (shouldn't be)
        outOfCharacterRange(*(game_grid(src_coordinates.row, src_coordinates.col)), src_coordinates,dst_coordinates);
        isNotEmpty(dst_coordinates); // check if the dst cell is empty (should be)
        game_grid(dst_coordinates.row, dst_coordinates.col) = game_grid(src_coordinates.row, src_coordinates.col); // moves the character
        game_grid(src_coordinates.row, src_coordinates.col) = nullptr;//  reset the old coordinates to point to Null
    }

    void Game::reload(const GridPoint &coordinates)
    {
        checkBounds(coordinates);
        isEmpty(coordinates);
        int row = game_grid.height();
        int column = game_grid.width();
        game_grid(row,column)->Character::characterReload();
    }
    
    bool Game::checkWinnerExsistance(Team& put_winner) const{
        int player_python = 0;
        int players_cpp = 0;
        int grid_rows = game_grid.height();
        int grid_columns = game_grid.width();
        for (int i = 0; i<grid_rows;i++){
            for(int j = 0; j < grid_columns; j++){
                if (game_grid(i,j) == nullptr){
                    continue;
                }
                if (game_grid(i,j)->sameTeam(CPP) ){
                    players_cpp++;
                }
                else if (game_grid(i,j)->sameTeam(PYTHON)){
                   player_python++; 
                }
            }
        }
        if (player_python ==0 ||players_cpp ==0 ){
            put_winner = (player_python == 0 ? CPP : PYTHON);
            return true;
        }
        return false;
    }
    bool Game::isOver(Team* winningTeam) const
    {
        Team winner;
        if (checkWinnerExsistance(winner))
        {
            if (winningTeam != nullptr){
                *winningTeam = winner;
            }
            return true;
        }
    }
} // namespace mtm
