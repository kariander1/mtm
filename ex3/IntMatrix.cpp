#include <string>
#include <iostream>
#include "IntMatrix.h"
using mtm::Dimensions;

IntMatrix::IntMatrix(const IntMatrix& matrix):
    array(new int[size]),
    dims(matrix.dims) // Should copy dims!
{
   
}
int main(int argc,char** argv)
{
    std::cout << "Hi";
    return 0;
}