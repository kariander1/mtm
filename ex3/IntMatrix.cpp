#include <string>
#include <iostream>
#include "IntMatrix.h"
#include "Auxiliaries.h"
#include "Auxiliaries.cpp" //REMOVE BEFORE FLIGHT!!!!!!!!!
using mtm::Dimensions;
using mtm::IntMatrix;
const int MIN_SIZE = 1;
const int IDENTITIY = 1;

IntMatrix::IntMatrix(Dimensions dimensions, int init_number) : array(new int[calcMatSize(dimensions)]), dim(dimensions)
{

    copyMatrixValues(init_number);

}

IntMatrix IntMatrix::Identity(int size)
    {
        Dimensions dims(size, size); 
        IntMatrix new_identity(dims, 0); // initiate the matrix to all zeros
        int matrix_size = new_identity.size();
        
        for (int i = 0 ; i< matrix_size ; i+= size+1){
        new_identity.array[i] =  IDENTITIY; //add "1" in the diagonal
        }
        //for (int j = 0; j<matrix_size;j++ ){
        //    std::cout << new_identity.array[j];
        //}
        return new_identity;
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
        //new_mat.array[i] +=mat2.array[i];
         //Will use iterator
    }
    return new_mat;
}
IntMatrix operator-(const IntMatrix& mat1,const IntMatrix& mat2)
{
    IntMatrix new_mat(mat1);
    // new_mat = new_mat+(-mat2); // Will be ok with unary operator
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
IntMatrix IntMatrix::transpose() const
{  
    int row = height();
    int column = width();
    Dimensions new_dim =(column,row);
    IntMatrix transpose_matrix(new_dim, 0); //create new matrix for transposed values

    int old_size = size();
    for(int i = 0; i < old_size; i++){
        transpose_matrix.array[(i/column) +(i%column)*row] = array[i]; // calculate the new position
    }
    
    //for (int j = 0; j<old_size;j++ ){ print the array
    //    std::cout << transpose_matrix.array[j];
    //}
    return transpose_matrix;
}
IntMatrix IntMatrix::operator-() const
{
    IntMatrix decrease_matrix(dim);
    int matrix_size = size();
    for(int i = 0; i<matrix_size;i++){
        decrease_matrix.array[i] = -array[i]; // set every element to -element
    }
    return decrease_matrix;
}
IntMatrix& IntMatrix::operator+=(const int num)
{
    int matrix_size = size();
    for (int i = 0; i<matrix_size; i++){
        array[i] += num; // add the num to every element in the matrix
    }
    return *this;
}
int& IntMatrix::operator()(const int row, const int column)
 {
     return array[row*width() +column];
 }
 const int& IntMatrix::operator()(const int row, const int column) const
 {
    return array[row*width() +column];
 }
 bool mtm::all(const IntMatrix & mat)
 {
    int mat_columns = mat.width();
    int mat_rows = mat.height();
    for (int row = 0, column = 0; row <mat_rows & column <mat_columns ;){ // don't really need column <mat_columns
        if(mat(row,column)== 0){
            return false;
        }
        column++;
        if (column == mat_columns){
            column = 0;
            row+=1;
        }
        
    }
    return true;
 }
 bool mtm::any(const IntMatrix & mat)
 {
    int mat_columns = mat.width();
    int mat_rows = mat.height();
    for (int row = 0, column = 0; row <mat_rows & column <mat_columns ;){ 
        if(mat(row,column)!= 0){
            return true;
        }
        column++;
        if (column == mat_columns){
            column = 0;
            row+=1;
        }
    }
    return false;
 }
int main(int argc, char **argv)
{
    Dimensions d(2, 4);
    IntMatrix identity_2 = IntMatrix::Identity(2);
    IntMatrix a(d, 4);
    IntMatrix newmatrix = -a;
    std::cout << all(a);
    IntMatrix c = a.transpose();
    
    {
        IntMatrix b(d, 6);
        a = b;
    }
    
    std::cout << "Hi";
    return 0;
}
