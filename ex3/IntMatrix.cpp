#include <string>
#include <iostream>
#include "IntMatrix.h"
#include "Auxiliaries.h"
#include "Auxiliaries.cpp" //REMOVE BEFORE FLIGHT!!!!!!!!!
using mtm::Dimensions;
using mtm::IntMatrix;

IntMatrix::IntMatrix(Dimensions dimensions, int init_number) : array(new int[calcMatSize(dimensions)]),
                                                               dim(dimensions)
{
    // Should initialize all values?
    // I added this:
    copyMatrixValues(init_number);

    // This will be better :
    //(*this)+=init_number // Will be okay when += operator will be implemented
}
IntMatrix::IntMatrix(const IntMatrix &matrix) : array(new int[calcMatSize(matrix.dim)]),
                                                dim(matrix.dim)
{
   copyMatrixValues(matrix);
}

IntMatrix::~IntMatrix()
{
    delete[] array;
}
IntMatrix operator+(const IntMatrix& mat1,const IntMatrix& mat2)
{
    IntMatrix new_mat(mat1);
    for (int i = 0; i < mat1.size(); i++) //size is the amount of elements in *this
    {
        //mat1[i] +=mat2[i];
         //Will use iterator
    }
    return new_mat;
}
IntMatrix operator-(const IntMatrix& mat1,const IntMatrix& mat2)
{
    IntMatrix new_mat(mat1);
    new_mat = new_mat+(-mat2); // Will be ok with unary operator
    return new_mat;
}
IntMatrix &IntMatrix::operator=(const IntMatrix &matrix)
{
    if (this == &matrix)
    {
        return *this; // Same matrix being assigned
    }
    dim = matrix.dim;
    delete[] array;

    array = new int[size()];
    
    copyMatrixValues(matrix);

    return *this;
}

IntMatrix IntMatrix::operator<(const int& num) const
{
    IntMatrix new_mat(dim,0);
    for (int i = 0; i < size(); i++)
    {
        (new_mat.array[i] = array[i]<num ? 1 : 0);
    }
    return new_mat;
}
IntMatrix IntMatrix::operator>(const int& num) const
{
    return (*this)<(-num);
}
IntMatrix IntMatrix::operator>=(const int& num) const
{
    return (*this)<=(-num);
}
IntMatrix IntMatrix::operator<=(const int& num) const
{
    return (*this)<(num+1);
}
IntMatrix IntMatrix::operator==(const int& num) const
{
    return (*this>=(num))-(*this>(num)); // >= (minus operator) >
}
IntMatrix IntMatrix::operator!=(const int& num) const
{
    IntMatrix all_diff_mat(dim,1);
    return (all_diff_mat-((*this)==num));
}
void IntMatrix::copyMatrixValues(const IntMatrix &matrix)
{
    for (int i = 0; i < size(); i++) //size is the amount of elements in *this
    {
        array[i] = matrix.array[i]; //Or maybe should use iterator?
    }
}
void IntMatrix::copyMatrixValues(const int& init_value)
{
    for (int i = 0; i < size(); i++) //size is the amount of elements in *this
    {
        array[i] = init_value; //Or maybe should use iterator?
    }
}
int IntMatrix::calcMatSize(const Dimensions& dim) const
{
    return dim.getCol() * dim.getRow();
}

int IntMatrix::height() const
{
    return dim.getRow();
}
int IntMatrix::width() const
{
    return dim.getCol();
}
int IntMatrix::size() const
{
    return calcMatSize(dim);
}
int main(int argc, char **argv)
{
    Dimensions d(2, 4);
    IntMatrix a(d, 4);
    {
        IntMatrix b(d, 6);
        a = b;
    }

    std::cout << "Hi";
    return 0;
}
