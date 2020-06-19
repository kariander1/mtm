#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include <string>
#include <iostream>
#include <stdexcept> 
#include "Auxiliaries.h"

//=============================================================================
// Matrix template class
//=============================================================================

namespace mtm {
template <class T>
class Matrix{
private:
    // Matrix data
    Dimensions dim;
    T* data;
    //static Matrix<bool> BinaryIntMatToBool(const Matrix<int>& int_mat);
public:
    //c'tor & d'tor ido
    Matrix(Dimensions dim_t, T initial_value=T()); // initial_value is by the deafult constracor of T
    Matrix(const Matrix& copy_matrix); 
    Matrix& operator=(const Matrix& other_matrix);
    ~Matrix(); 

    //-------------------------------------------------------------
    // Returns the number of rows in this matrix.
    //-------------------------------------------------------------
    int height() const{
        return dim.getRow();
    }
    //-------------------------------------------------------------
    // Returns the number of columns in this matrix.
    //-------------------------------------------------------------
    int width() const{
        return dim.getCol();
    } 
    //-------------------------------------------------------------
    // Returns the total size of this matrix.
    //-------------------------------------------------------------
    int size() const{
        return dim.getCol()*dim.getRow();
    }

    //create special matrices mor VVV
    static Matrix Diagonal(int size_n,const T& value);
    Matrix transpose() const;
    template <class Function>
    Matrix apply(Function f) const;

    //matrix operators ido vvv
    Matrix operator-() const;
    Matrix& operator+=(const T object);
    const T& operator()(int row, int col) const;
    T& operator()(int row, int col); 

    //logical operators mor VVV  
    Matrix<bool> operator==(const T object) const; 
    Matrix<bool> operator!=(const T object) const;
    Matrix<bool> operator<=(const T object) const;
    Matrix<bool> operator<(const T object) const;
    Matrix<bool> operator>=(const T object) const;
    Matrix<bool> operator>(const T object) const;

    //iterators 
    class iterator; 
    iterator begin();
    iterator end();
    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

    //exceptions 
    class AccessIllegalElement : public std::logic_error {
        public:
        AccessIllegalElement(): std::logic_error("Mtm matrix error: An attempt to access an illegal element"){}
    };
	class IllegalInitialization : public std::logic_error {
        public:
        IllegalInitialization(): std::logic_error("Mtm matrix error: Illegal initialization values"){}
    };
    class DimensionMismatch {
        public:
        Dimensions dim1;
        Dimensions dim2;
        DimensionMismatch(Matrix mat1,Matrix mat2) : dim1(mat1.dim), dim2(mat2.dim) {}
        const std::string what() const 
        {
            std::string left_dim=dim1.toString();
            std::string right_dim=dim2.toString();
            return "Mtm matrix error: Dimension mismatch: " + left_dim + " " + right_dim;
        }
    };
};
//=======================================================================
// Matrix non-member functions.
//=======================================================================

template <class T>
Matrix<T> operator+(const Matrix<T>& matrix1,const Matrix<T>& matrix2);
template <class T>
Matrix<T> operator-(const Matrix<T>& matrix1,const Matrix<T>& matrix2);

//ido VVV
template <class T>
Matrix<T> operator+(const Matrix<T>& matrix,const T object);
template <class T>
Matrix<T> operator+(const T object,const Matrix<T>& matrix);
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

//mor VVV
template <class T>
bool all(const Matrix<T>& matrix);
template <class T>
bool any(const Matrix<T>& matrix);

//=======================================================================
// iterator class.
//=======================================================================

template <class T>
class Matrix<T>::iterator {
    Matrix* matrix;
    int index; 
    iterator(Matrix* matrix, int index);
    friend class Matrix;
public:
    T& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    iterator(const iterator& it)=default;
    iterator& operator=(const iterator& it) = default;
}; 

//=======================================================================
// const_iterator class.
//=======================================================================

template <class T>
class Matrix<T>::const_iterator {
    const Matrix* matrix;
    int index; 
    const_iterator(const Matrix* matrix, int index);
    friend class Matrix;
public:
    const T& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator(const const_iterator& it)=default;
    const_iterator& operator=(const const_iterator& it) = default;
}; 

/*=============================================================================*/
/*                                                                             */
/* Implementation of matrix template class:                                    */
/*                                                                             */
/* 1. Constructors, destructor and assignment Operator.                        */
/* 2. Matrix creating functions.                                               */
/* 3. Operators.                                                               */
/* 4. Logical comparison operators.                                            */
/* 5. Boolean grouping.                                                        */
/* 6. Implementation of iterator class.                                        */
/* 7. Implementation of const_Iterator class.                                  */
/*                                                                             */
/*=============================================================================*/

//=======================================================================
// Constructors, destructor and assignment Operator.
//=======================================================================

//assumptions: T has operator=, T has non-parameter constructor 
template <class T>
Matrix<T>::Matrix(Dimensions dim_t, T initial_value) : dim(dim_t){
    if (dim.getCol()<=0 or dim.getRow()<=0){
        throw IllegalInitialization();
    }
    data=new T[dim_t.getCol()*dim_t.getRow()];
    try{
        for (int i = 0; i < size(); i++)
        {
            data[i]=initial_value;
        }
    }catch(...){
        delete[] data;
        throw;
    }
}

//assumptions: T has operator=
template <class T>
Matrix<T>::Matrix(const Matrix& copy_matrix) : dim(copy_matrix.dim), data(new T[copy_matrix.size()]){
    try{
        for (int i = 0; i < size(); i++)
        { 
            data[i]=copy_matrix.data[i];
        }
    }catch(...){
        delete[] data;
        throw;
    }
}

//assumptions: T has operator=
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other_matrix){
    if (dim!=other_matrix.dim){
        throw typename Matrix<T>::DimensionMismatch(*this, other_matrix);
    }
    T* temp=new T[other_matrix.size()]; 
    try{
        for (int i = 0; i < size(); i++)
        {
            temp[i]=other_matrix.data[i];
        }
    }catch(...){
        delete[] data;
        throw;
    }
    delete[] data;
    data=temp;
    return *this;
}

//assumptions: d'tor for T
template <class T>
Matrix<T>::~Matrix() {
    delete[] data;
}


//=======================================================================
// Matrix creating functions.
//=======================================================================

//assumptions: T has operator =
template <class T>
Matrix<T> Matrix<T>::Diagonal(int size_n,const T& value){
    if (size_n<=0) {
        throw IllegalInitialization();
    }
    Dimensions diagonal_dim(size_n,size_n);
    Matrix Diagonal(diagonal_dim);
    for (int i=0; i<size_n;i++){
            Diagonal(i,i)=value;
        }
    return Diagonal;
}

//assumptions: operator =
template <class T>
Matrix<T> Matrix<T>::transpose() const{
    Dimensions transpose_dim(dim.getCol(),dim.getRow());
    Matrix transpose(transpose_dim);
    for (int i=0; i<height(); i++){
        for (int j=0; j<width(); j++){
            transpose(j,i)=this->operator()(i,j);
        }
    }
    return transpose;
}

//assumptions: f() operates on T and returns T, and T has operator =
template <class T>
template <class Function>
Matrix<T> Matrix<T>::apply(Function f) const{
    Matrix result=*this; 
    for (Matrix::iterator it=result.begin(); it!=result.end();it++){
       *it=f(*it);
    }
    return result;
}

//=======================================================================
// Operators.
//=======================================================================

//assumptions: T has += operator, T has oprator=
template <class T>
Matrix<T> operator+(const Matrix<T>& matrix1,const Matrix<T>& matrix2)
{
    if ((matrix1.height()!=matrix2.height()) || (matrix1.width()!=matrix2.width())){
        throw typename Matrix<T>::DimensionMismatch(matrix1, matrix2);
    }
    Matrix<T> result=matrix1;
    typename Matrix<T>::const_iterator it2=matrix2.begin();
    for (typename Matrix<T>::iterator it1=result.begin(); it1!=result.end();++it1,++it2)
    {
        *it1+=*it2;
    }
    return result;
}

//assumptions: T has unary operator-, T has operator=
template <class T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix minus_matrix(dim);
    for (int i=0; i<size();i++){
        minus_matrix.data[i]=-data[i];
    }
    return minus_matrix;
}

//assumptions: T has operator+=
template <class T>
Matrix<T>& Matrix<T>::operator+=(const T object)
{
    for (int i=0; i<size();i++){
        data[i]+=object;
    }
    return *this;
}

//assumptions: T has unary operator-, T has operator=, T has += operator
template <class T>
Matrix<T> operator-(const Matrix<T>& matrix1,const Matrix<T>& matrix2)
{

    if ((matrix1.height()!=matrix2.height()) || (matrix1.width()!=matrix2.width())){
        throw typename Matrix<T>::DimensionMismatch(matrix1, matrix2);
    }
    return matrix1+(-matrix2);
}

template <class T>
const T& Matrix<T>::operator()(int row, int col) const
{
    if ((row<0||col<0)||(col>=width())||(row>=height())){
        throw AccessIllegalElement();
    }
    return data[row*width()+col];
}

template <class T>
T& Matrix<T>::operator()(int row, int col)
{
    if ((row<0||col<0)||(col>=width())||(row>=height())){
        throw AccessIllegalElement();
    }
    return data[row*width()+col];
}

//assumptions: T has operator<<
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
    typename Matrix<T>::const_iterator it_begin=matrix.begin();
    typename Matrix<T>::const_iterator it_end=matrix.end();
    int width=matrix.width();
    return printMatrix(os, it_begin, it_end, width);
}

//assumptions: T has operator+=, T has operator=
template <class T>
Matrix<T> operator+(const Matrix<T>& matrix, const T object)
{
    Matrix<T> result=matrix;
    return result+=object;
}

//assumptions: T has operator+, T has operator=
template <class T>
Matrix<T> operator+(const T object, const Matrix<T>& matrix)
{
    Matrix<T> result=matrix;
    for (typename Matrix<T>::iterator it=result.begin(); it!=result.end();++it)
    {
        *it=object+*it;
    }
    return (result);
}

//=======================================================================
// Logical comparison operators.
//=======================================================================

// Matrix<bool> BinaryIntMatToBool(const Matrix<int>& int_mat)
// {
//     Matrix<bool> result(int_mat.dim);
//     for (int i=0; i<int_mat.size();i++){
//         result.data[i]=int_mat.data[i];
//     }
//     return result;
// }

//assumptions: T has operator==
template <class T>
Matrix<bool> Matrix<T>::operator==(const T object) const
{
    Matrix<bool> result(dim,false);
    Matrix<bool>::iterator it=result.begin();
    for (int i = 0; i < size(); i++, it++)
    {
        if (data[i]==object)
        {
            *it=true;
        }
    }
    return result;
}

//assumptions: T has < operator , T has operator-, bool has + operator for different values (true and false)
template <class T>
Matrix<bool> Matrix<T>::operator!=(const T object) const{
    return(this->operator>(object))+(this->operator<(object));
}

//assumptions: T has <= operator
template <class T>
Matrix<bool> Matrix<T>::operator<=(const T object) const{
    Matrix<bool> result(dim,0);
    Matrix<bool>::iterator it=result.begin();
    for (int i = 0; i < size(); i++, it++)
    {
        if (data[i]<=object)
        {
            *it=true;
        }
    }
    return result;
}

//assumptions: T has < operator
template <class T>
Matrix<bool> Matrix<T>::operator<(const T object) const{
    Matrix<bool> result(dim,false);
    Matrix<bool>::iterator it=result.begin();
    for (int i = 0; i < size(); i++, it++)
    {
        if (data[i]<object)
        {
            *it=true;
        }
    }
    return result;
}

//assumptions: T has <= operator, unary operator-
template <class T>
Matrix<bool> Matrix<T>::operator>=(const T object) const{
    return (-*this)<=(-object); // minus arguments provide same expression
}

//assumptions: T has < operator, unary operator-
template <class T>
Matrix<bool> Matrix<T>::operator>(const T object) const{
    return (-*this)<(-object); // minus arguments provide same expression    
}  

//=======================================================================
// Boolean grouping.
//=======================================================================

//assumptions: T has (any kind of) cast to bool 
template <class T>
bool all(const Matrix<T>& matrix)
{
    for (typename Matrix<T>::const_iterator it=matrix.begin(); it!=matrix.end();++it){
        if (static_cast<bool>(*it)==false){
            return false;
        }
    }
    return true;
}

//assumptions: T has (any kind of) cast to bool 
template <class T>
bool any(const Matrix<T>& matrix)
{
    for (typename Matrix<T>::const_iterator it=matrix.begin(); it!=matrix.end();++it){
        if (static_cast<bool>(*it)==true){
            return true;
        }
    }
    return false;
}

//=======================================================================
// Implementation of iterator class.
//=======================================================================

template <class T>
Matrix<T>::iterator::iterator(Matrix* matrix, int index): matrix(matrix), index(index){}

template <class T>
typename Matrix<T>::iterator Matrix<T>::begin()
{
    return iterator(this,0);
}

template <class T>
typename Matrix<T>::iterator Matrix<T>::end()
{
    return iterator(this,size());
}

template <class T>
T& Matrix<T>::iterator::operator*() const
{
    if (index>=matrix->size()){
        throw AccessIllegalElement();
    }
    return(matrix->data[index]);
}

template <class T>
typename Matrix<T>::iterator& Matrix<T>::iterator::operator++()
{
    index++;
    return *this;
}

template <class T>
typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int)
{
    iterator result=*this;
    ++*this;
    return result;
}

template <class T>
bool Matrix<T>::iterator::operator==(const iterator& it) const
{
    return (matrix==it.matrix) && (index==it.index);
}

template <class T>
bool Matrix<T>::iterator::operator!=(const iterator& it) const
{
    return !(*this==it);
}

//=======================================================================
// implementation of const_iterator class .
//=======================================================================

template <class T>
Matrix<T>::const_iterator::const_iterator(const Matrix* matrix, int index): matrix(matrix), index(index){}

template <class T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const
{
    return const_iterator(this,0);
}

template <class T>
typename Matrix<T>::const_iterator Matrix<T>::end() const
{
    return const_iterator(this,size());
}

template <class T>
const T& Matrix<T>::const_iterator::operator*() const
{
    if (index>=matrix->size()){
        throw AccessIllegalElement();
    }
    return(matrix->data[index]);
}

template <class T>
typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++()
{
    index++;
    return *this;
}

template <class T>
typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int)
{
    const_iterator result=*this;
    ++*this;
    return result;
}

template <class T>
bool Matrix<T>::const_iterator::operator==(const const_iterator& it) const
{
    return (matrix==it.matrix) && (index==it.index);
}

template <class T>
bool Matrix<T>::const_iterator::operator!=(const const_iterator& it) const
{
    return !(*this==it);
}

}
#endif //EX3_MATRIX_H
