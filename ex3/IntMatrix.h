#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

class IntMatrix {
    private:
    int* array;
    mtm::Dimensions dim;
    public:
    IntMatrix(mtm::Dimensions dimensions,int start_number=0);
}


#endif //INT_MATRIX_H

int main(){
    std::cout << "Hello";
}