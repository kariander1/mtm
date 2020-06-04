#include <string>
#include <iostream>
#include "IntMatrix.h"
using mtm::Dimensions;
using mtm::IntMatrix;
#include "Auxiliaries.cpp"

int calcDimSize(Dimensions dim);

IntMatrix::IntMatrix(const IntMatrix& matrix):
array(new int[calcDimSize(matrix.dim)]),
dim(matrix.dim)
{
   
}

IntMatrix::IntMatrix(Dimensions dimensions ,int init_number):
array(new int[calcDimSize(dimensions)]),
dim(dimensions)
{
    
}
int calcDimSize(Dimensions dim)
{
    return dim.getCol()*dim.getRow();
}
int main(int argc,char** argv)
{
    Dimensions d(2,4);
    Dimensions d2 =d;

    std::cout << "Hi";
    return 0;
}
