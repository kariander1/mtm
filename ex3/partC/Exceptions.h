#ifndef HW3_EXCEPTIONS_H
#define HW3_EXCEPTIONS_H

#include "Auxiliaries.h"

namespace mtm
{
    // const strings for Matrix exceptions
    const std::string MATRIX_ERROR_PREFIX="Mtm matrix error: ";
    const std::string ILLEGAL_ACCESS=MATRIX_ERROR_PREFIX+"An attempt to access an illegal element";
    const std::string ILLEGAL_INITIAL = MATRIX_ERROR_PREFIX+"Illegal initialization values";
    const std::string MISMATCH=MATRIX_ERROR_PREFIX+"Dimension mismatch: ";
    // const strings for Game exceptions
    const std::string GAME_ERROR_PREFIX = "A game related error has occurred: ";
    const std::string GAME_ILLEGAL_ARGUMENT = GAME_ERROR_PREFIX + "IllegalArgument";
    const std::string GAME_ILLEGAL_CELL = GAME_ERROR_PREFIX + "IllegalCell";
    const std::string GAME_CELL_EMPTY = GAME_ERROR_PREFIX + "CellEmpty";
    const std::string GAME_MOVE_TOO_FAR = GAME_ERROR_PREFIX + "MoveTooFar";
    const std::string GAME_CELL_OCCUPIED = GAME_ERROR_PREFIX + "CellOccupied";
    const std::string GAME_OUT_OF_RANGE = GAME_ERROR_PREFIX + "OutOfRange";
    const std::string GAME_OUT_OF_AMMO = GAME_ERROR_PREFIX + "OutOfAmmo";
    const std::string GAME_ILLEGAL_TARGET = GAME_ERROR_PREFIX + "IllegalTarget";

    /**
    * Class Exception
    * @exception
    * A class to represent all ex3 exceptions, inherits the std::exception class
    */
    class Exception : public std::exception
    {
    private:
        const std::string error_string;

    public:
        Exception(const std::string error_string) : error_string(error_string){};

    /**
    * what()
    * Overrides the standard what function from std:exception.
    * Return a char* representing the detailed exception
    */
        const char *what() const noexcept override;
    };


    /**
    * Class GameException
    * @exception
    * A class to represent all game exceptions, inherits the mtm::Exception class
    */
    class GameException : public mtm::Exception
    {
    public:
        GameException(const std::string &error_string) : Exception(error_string){};
    };
    /**
    * Class IllegalCell
    * @exception
    * If the coordinates are invalid throws an IllegalCell exception. 
    */
    class IllegalCell : public GameException
    {
    public:
        IllegalCell() : GameException(GAME_ILLEGAL_CELL){};
    };
    /**
    * Class IllegalArgument
    * @exception
    * If one of ammo / range / power is less then zero throws an IllegalArgument exception. 
    */
    class IllegalArgument : public GameException
    {
    public:
        IllegalArgument() : GameException(GAME_ILLEGAL_ARGUMENT){};
    };
    /**
    * Class CellEmpty
    * @exception
    * If the cell is empty. 
    */
    class CellEmpty : public GameException
    {
    public:
        CellEmpty() : GameException(GAME_CELL_EMPTY){};
    };
    /**
    * Class MoveTooFar
    * @exception
    * If the move request is to far throws an MoveTooFar exception. 
    */
    class MoveTooFar : public GameException
    {
    public:
        MoveTooFar() : GameException(GAME_MOVE_TOO_FAR){};
    };
    /**
    * Class CellOccupied
    * @exception
    * If the cell is not empty throws an CellOccupied exception.
    */
    class CellOccupied : public GameException
    {
    public:
        CellOccupied() : GameException(GAME_CELL_OCCUPIED){};
    };
    /**
    * Class OutOfRange
    * @exception
    * If the range attack is invalid throws an OutOfRange exception. 
    */
    class OutOfRange : public GameException
    {
    public:
        OutOfRange() : GameException(GAME_OUT_OF_RANGE){};
    };
    /**
    * Class OutOfAmmo
    * @exception
    * If the there is not enough ammo throws an OutOfAmmo exception.
    */
    class OutOfAmmo : public GameException
    {
    public:
        OutOfAmmo() : GameException(GAME_OUT_OF_AMMO){};
    };
    /**
    * Class IllegalTarget
    * @exception
    * If the target coordinates are invalid throws an IllegalTarget exception.
    */
    class IllegalTarget : public GameException
    {
    public:
        IllegalTarget() : GameException(GAME_ILLEGAL_TARGET){};
    };
} // namespace mtm
#endif