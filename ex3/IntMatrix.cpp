#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "IntMatrix.h"

mtm::IntMatrix::IntMatrix(mtm::Dimensions dimensions ,int start_number): array(new int[dimensions.getRow()*dimensions.getCol()], dim(dimensions) ){}

#endif //INT_MATRIX_H