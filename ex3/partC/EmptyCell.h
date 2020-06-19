#ifndef HW3_EMPTY_CELL_H
#define HW3_EMPTY_CELL_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm
{

    class EmptyCell : public Character
    {

    public:
        void characterAttack(const GridPoint &location) const override{};
        void move() override {}; // add arguments and return type
        bool isEmpty() const override {return true;};
    };

} // namespace mtm

#endif //HW3_EMPTY_CELL_H