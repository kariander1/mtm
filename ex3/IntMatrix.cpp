#include <string>
#include <iostream>
#include "IntMatrix.h"
using mtm::Dimensions;
using mtm::IntMatrix;

IntMatrix::IntMatrix(const IntMatrix& matrix):
    array(new int[size]),
    dims(matrix.dims) // Should copy dims!
{
   
}
IntMatrix::IntMatrix(mtm::Dimensions dimensions ,int init_number): array(new int[dimensions.getRow()*dimensions.getCol()], dim(dimensions) ){
    
}
int main(int argc,char** argv)
{
    std::cout << "Hi";
    return 0;
}
