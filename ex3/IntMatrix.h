#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
namespace mtm {
    class IntMatrix {
        int* array;
        mtm::Dimensions dim;
    public:
        IntMatrix(mtm::Dimensions dimensions,int start_number=0);
    };
}

#endif //INT_MATRIX_H
