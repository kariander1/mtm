#include <string>
#include <iostream>
#include "IntMatrix.h"
#include "Auxiliaries.h"
#include "Auxiliaries.cpp"
using mtm::Dimensions;
using mtm::IntMatrix;

/*IntMatrix::IntMatrix(const IntMatrix& matrix): array(new int[matrix.dim.getRow()*matrix.dim.getCol()], dim(matrix.dim) // Should copy dims!
{
   
}*/

IntMatrix::IntMatrix(Dimensions dimensions ,int init_number): array(new int[(dimensions.getRow())*(dimensions.getCol())]), dim(dimensions) {
    
}
int main(int argc,char** argv)
{
    std::cout << "Hi";
    return 0;
}
