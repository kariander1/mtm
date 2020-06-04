#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

class IntMatrix {

private:    
    int* array;
    mtm::Dimensions dims;
    int size;

public:
    IntMatrix(mtm::Dimensions dim,int init_number=0);
    IntMatrix(const IntMatrix&);
};

#endif //INT_MATRIX_H
