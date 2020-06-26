#ifndef HW3_GAME_H
#define HW3_GAME_H

#include <iostream>
#include <memory>
#include "Matrix.h"
#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
namespace mtm
{   
    
    class Game
    {
      
    private:
        Matrix<std::shared_ptr<Character>> game_grid;
        
    // helper functions
    /**
    * Game::checkGameSize: check if the height and width are valid 
    * and creates a Dimension from them.  
    * If the coordinates are invalid throws an IllegalArgument exception.
    *
    * @param height - The number of rows in the matrix
    * @param width - The number of columns in the matrix
    * @return
    * 	returns a Dimensions of the height and width 
    */
        static Dimensions checkGameSize(const int &height,const int &width);
    /**
    * Game::checkBounds: Check if given coordinates are in boundaries.
    *
    * @param coordinates - The row and columns to check.
    * @return
    * 	Nothing
    * @exception
    * If the coordinates are invalid throws an IllegalCell exception. 
    */
        void checkBounds(const GridPoint& coordinates) const;
    /**
    * Game::checkAttackPrerequisites: Checks if the attack range is valid,
    * if the character has enough ammo and if the target is valid.
    *
    * @param src_coordinates - The position of the attack character.
    * @param dst_coordinates - The position of the target.
    * @return
    * 	Nothing
    * 
    * @exception 
    * If the range attack is invalid throws an OutOfRange exception. 
    * If the there is not enough ammo throws an OutOfAmmo exception.
    * If the target coordinates are invalid throws an IllegalTarget exception.
    */  
        void checkAttackPrerequisites(const GridPoint &src_coordinates,
                                         const GridPoint &dst_coordinates) const;
    /**
    * Game::cloneGameGrid: Copies all the game grid and it's characters.
    *
    * @param source_matrix - The matrix to copy values to.
    * @param other_game - The game to copy values from.
    * @return
    * 	Nothing
    */ 
    static void cloneGameGrid(Matrix<std::shared_ptr<Character>> &source_matrix, const Game &other_game);
    /**
    * Game::isEmpty: Checks if the given coordinates are not empty
    *
    * @param coordinates - The position to check if not empty.
    * @return
    * 	Nothing
    * 
    * @exception 
    * If the cell is empty throws an CellEmpty exception. 
    */
        void isEmpty(const GridPoint& coordinates) const; // for source coordinates
    /**
    * Game::isNotEmpty: Checks if the given coordinates are empty
    *
    * @param coordinates - The position to check if empty.
    * @return
    * 	Nothing
    * 
    * @exception 
    * If the cell is not empty throws an CellOccupied exception. 
    */
        void isNotEmpty(const GridPoint& coordinates) const; // for destination coordinates
    /**
    * Game::outOfCharacterRange: Checks if the move request of the character is valid
    *
    * @param character - The character to check is move range.
    * @param point1, @param point2 - the point to check their distance
    * @return
    * 	Nothing
    * 
    * @exception 
    * If the move request is to far throws an MoveTooFar exception. 
    */
        void outOfCharacterRange(const Character& character,const GridPoint& point1, const GridPoint& point2);
    /**
    * Game::checkWinnerExistance: Checks the number of CPP and PYTHON players on the board game.
    *
    * @param put_winner - The winner if exsists is written to this parameter.
    * @return
    * 	True - if there is a winner
    *   False - otherwise.
    */                              
        bool checkWinnerExistance(Team& put_winner)const;
        
    public:
    /**
    * Game::Game : Game constructor.
    *
    * @param height - The height of the game matrix.
    * @param width - The width of the game matrix.
    * @return
    * 	Nothing
    */ 
        Game(int height, int width); 
    /**
    * ~Game : Game distructor.
    */        
        ~Game() = default;                  
    /**
    * Game::Game : Game copy constructor.
    *
    * @param other - The game to initialize the new game with.
    * @return
    * 	Nothing
    */
        Game(const Game &other);           
    /**
    * Game::&operator=(): assignment operator, assigns the given game to this
    *
    * @param other - The game to copy to this
    * @return
    * 	returns reference to the new copied game
    */
        Game &operator=(const Game &other); // Assignment operator
    /**
    * Game::addCharacter: Adds a new character to the board game.
    *
    * @param coordinates - the coordinates to put the character in
    * @param character - The character to put in the game.
    * @return
    * 	Nothing
    */
        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character); 
    /**
    * Game::makeCharacter: Creates a new character for the game.
    *
    * @param type - The type of the character (Medic / Sniper / Soldier).
    * @param team - The character's team (CPP / PYTHON).
    * @param ammo - The number of ammo the character starts with.
    * @param range - The number of move range of the character.
    * @param power - The power attack of the character.
    * @return
    * 	A pointer to the new character. 
    * @exception 
    * If one of ammo / range / power is less then zero throws an IllegalArgument exception. 
    */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                    units_t health, units_t ammo, units_t range, units_t power);
    /**
    * Game::move: Moves a character from source to destination
    *
    * @param src_coordinates - The coordinates of the character the player wants to move.
    * @param dst_coordinates - The coordinates of the character's destination.
    * @return
    * 	Nothing 
    */
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
    /**
    * Game::attack: tells the character at the source coordinates to attack the character
    * at the destination coordinates
    *
    * @param src_coordinates - The coordinates of the attacker.
    * @param dst_coordinates - The coordinates of the attack target.
    * @return
    * 	Nothing 
    */
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
    /**
    * Game::reload: Adds ammo to the character in the coordinates.
    * at the destination coordinates
    *
    * @param coordinates - The coordinates of the character to reload.
    * @return
    * 	Nothing 
    */
        void reload(const GridPoint &coordinates);
    /**
    * Output operator: Prints the given game.
    * @return
    * 	None
    */
        friend std::ostream &operator<<(std::ostream &os, const Game &game);
        /**
    * Game::isOver: Checks if the game has a winner.
    *
    * @param winningTeam - The winning team , if exsists, is copied to here.
    * @return
    * 	True - if the game has a winner
    *   False - otherwise. 
    */
        bool isOver(Team *winningTeam = NULL) const;

     
    };

} // namespace mtm

#endif //HW3_GAME_H