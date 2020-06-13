#ifndef INT_MATRIX_H
#define INT_MATRIX_H

#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm
{
    enum MATRIX_BOOLEAN_STATUS
    {
        ALL_TRUE = -1,
        TRUE_EXISTS,
        ALL_FALSE
    };

    template <class T>
    class Matrix
    {
    private:
        //Private fields
        T *array;
        Dimensions dim;

        // Helper Functions

        int calcMatSize(const mtm::Dimensions &dim) const
        {
            return dim.getCol() * dim.getRow();
        }
        void copyMatrixValues(const Matrix &matrix);
        void copyMatrixValues(const T &init_value)
        {
            for (int i = 0; i < size(); i++) //size is the amount of elements in *this
            {
                array[i] = init_value; //Or maybe should use iterator?
            }
        }
        Matrix<bool> operator!();
      //  class MatrixError;

    public:
        /**
        *   Constructors and Destructors:
        * 
        *   Matrix(mtm::Dimensions dimensions,int init_number=0):
        * 
        *   Default constructor, with given dimensions, enables to init the matrix values or default them to 0.
        *   @param dimensions - Dimensions to init the matrix
        *   @param init_number - Init value for matrix values
        *   @return
        * 	instance of a intMatrix
        * 
        *   Matrix(const Matrix &)
        * 
        *   Copy constructor, given a mtrix, this constructor copies all values by value to a new copy of matrix
        *   @param dimensions - Dimensions to init the matrix
        *   @param init_number - Init value for matrix values
        *   @return
        * 	instance of a intMatrix
        *  ~Matrix()
        *    and replace the old value for the new value (frees the old value)
        *
        *   ~Matrix()
        * 
        *   Destructor. Deletes allocated area.
        */
        Matrix(mtm::Dimensions dimensions, T init_value = T()) :
        array(new T[calcMatSize(dimensions)]), // New will throw bad_alloc if allocation failed
        dim(dimensions)
        {
            if(dim.getCol()<0 || dim.getRow()<0)
                throw IllegalInitialization();
            copyMatrixValues(init_value);
        }
        Matrix(const Matrix & matrix): array(new T[calcMatSize(matrix.dim)]),
                                                    dim(matrix.dim){}  // Copy constructor 
        ~Matrix(){//Destructor
            delete[] array;
        }           

        // Operators
        /**
        * Matrix::&operator=(): assignment operator, assigns the given matrix to this
        *
        * @param matrix - The matrix to copy to this
        * @return
        * 	returns reference to the new copied matrix
        */
        Matrix &operator=(const Matrix &matrix); // Assignment operator
        /**
        * Matrix::&operator__(): execute the logical operation for every element in the matrix and creates 
        * a new matrix in the same size. if the logical operation of the element was true then the element in
        * the new_matrix is 1, otherwise the element is 0.
        *
        * @param num - The number to compare to
        * @return
        * 	returns the new matrix with zeros and ones according to the output of the logic operation.
        */
        Matrix<bool> operator!()
        {
            for (int i = 0; i < size(); i++)
            {
                (array[i] = (array[i] == false ? true : false));
            }
            return *this;
        }
        Matrix<bool> operator<(const T &value) const
        {
            Matrix<bool> new_matrix(dim);
            for (int i = 0; i < size(); i++)
            {           
                (new_matrix.array[i] = (array[i] < value ? true : false));
            }
            return new_matrix;
        }
        Matrix<bool> operator<=(const T &value) const
        {
            Matrix<bool> new_matrix(dim, value);
            for (int i = 0; i < size(); i++)
            {
                (new_matrix.array[i] = array[i] <= value ? true : false);
            }
            return new_matrix;
        }
        Matrix<bool> operator>(const T &value) const
        {
            return !(*(this)<= value);
        }
        Matrix<bool> operator>=(const T &value) const
        {
            return !(*(this) < value);
        }   
        Matrix<bool> operator==(const T &value) const
        {
            Matrix<bool> new_matrix(dim, value);
            for (int i = 0; i < size(); i++)
            {
                (new_matrix.array[i] = array[i] == value ? true : false);
            }
            return new_matrix; 
        }
        Matrix<bool> operator!=(const T &value) const
        {
            return !(*(this) == value);
        }
        /**
        * Matrix::&operator-(): creates a new matrix where each value is the negative of the current value.
        *
        * @return
        * 	returns the new matrix with negative values.
        */
        Matrix operator-() const
        {
            Matrix negative_matrix(dim);
            int matrix_size = size();
            for (int i = 0; i < matrix_size; i++)
            {
                negative_matrix.array[i] = -array[i]; // Assuming T has a - unary operator!!!
            }
            return negative_matrix;
        }
        /**
        * Matrix::&operator+=(): adds to each element in the exsisting matrix the num specified.
      
        *
        * @param num - The number to add to the exsisting value
        * @return
        * 	returns a reference to the modified matrix
        */
        Matrix &operator+=(const T init_value){
            *this = *this + init_value;
            return *this;

        }
        /**
        * Matrix::&operator+(): creates a new matrix with the current element value plus the num specified.
      
        *
        * @param num - The number to add to the exsisting value
        * @return
        * 	returns a copy of the new matrix
        */
      Matrix operator+(const T init_value) const{
            int matrix_columns = width();
            int matrix_rows = height();
            Dimensions d(matrix_rows, matrix_columns);
            Matrix init_matrix(d, init_value);
            return *this + init_matrix;
        }
        /**
        *   "operator()" operators
        * 
        *   Operator with parenthesis to handle indices indicating exact position in matrix.
        *   int& operator() for enabling lvalue assignment, and const int& operator() for handling const values.
        * 
        *   @param row - Row index
        *   @param column - Column Index
        *   @return
        * 	int value of value stored in matrix in defined position
        */
        int &operator()(const int row, const int column)
        {
            int shifted_index = row * width() + column;
            if (row < 0 || column < 0 || shifted_index >= size())
                throw AccessIllegalElement();
            return array[shifted_index];
        }
        const int &operator()(const int row, const int column) const
        {
            Matrix temp = *this;
            return temp(row, column);
        }
        /**
        * Matrix::&operator<<(): Prints the given matrix.
        * @return
        * 	None
        */
        friend std::ostream& operator<<(std::ostream & os, const Matrix<T>& matrix){ // should we add const th the declerastion?
            Matrix::iterator begin = matrix.begin();
            Matrix::iterator end = matrix.end();
            int width = matrix.width();
            mtm::printMatrix(os, begin, end, width);
            return os;
        }


        /**
        * Matrix::height/width/size(): calculates the height/width/size of the given matrix
        *
        * @return
        * 	returns the height/width/size of the given matrix
        */
        int height() const{
            return dim.getRow();
        }
        int width() const{
            return dim.getCol();
        }
        int size() const{
            return dim.getCol() * dim.getRow();
        }

        /**
        *   Matrix transpose()
        * 
        *   Transposes the matrix and switches position of values according to mathematical transpose operator.
        * 
        *   @return
        * 	Returns a COPY of the transposed matrix. does not change original matrix.
        */
        Matrix transpose() const
        {
            int row = height();
            int column = width();
            Dimensions new_dim(column, row);
            Matrix transpose_matrix(new_dim); //create new matrix for transposed values

            int old_size = size();
            for (int i = 0; i < old_size; i++)
            {
                transpose_matrix.array[(i / column) + (i % column) * row] = array[i]; // calculate the new position
            }

            return transpose_matrix;
        }
        /**
        *    static Matrix Identity
        * 
        *   Returns an identity cubic matrix defined by the size arguemnet
        * 
        *   @param size - size for dimensions of matrix. [ size X size ]
        *   @return
        * 	Returns a COPY of the transposed matrix. does not change original matrix.
        */
        static Matrix Diagonal(const int size,const T init_value)
        {
                Dimensions dims(size, size);
                Matrix new_diagonal(dims); // initiate the matrix to T() values. Will throw illegal init/bad alloc from constructor
                int matrix_size = new_diagonal.size();

                for (int i = 0; i < matrix_size; i += size + 1)
                {
                    new_diagonal.array[i] = init_value;
                }
                return new_diagonal;
        }

        class iterator;
        /**
        * Matrix::begin/end(): creates an iterator for the given matrix and retets it 
        * to be the begin/end of the matrix
        *
        * @return
        * 	returns the new iterator
        */
        iterator begin();
        iterator end();

        /**
         * same as the end and begin, the difference is that the return iterator 
         * is constant and the matrix is constant
         */
        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const;

        class AccessIllegalElement;
        class IllegalInitialization;
        class DimensionsMismatch;
    };
    template <class T>
    class Matrix<T>::AccessIllegalElement
    {
    private:
        const std::string description = "Mtm matrix error: An attempt to access an illegal element";

    public:
        const std::string what() const
        {
            return description;
        }
    };
    template <class T>
    class Matrix<T>::IllegalInitialization
    {
    private:
        const std::string description = "Mtm matrix error: Illegal initialization values";

    public:
        const std::string what() const
        {
            return  description;
        }
    };
    template <class T>
    class Matrix<T>::DimensionsMismatch
    {
    private:
        const std::string description = "Mtm matrix error: Dimensions mismatch: ";
        const Dimensions dim_a;
        const Dimensions dim_b;

    public:
        DimensionsMismatch(const Dimensions dim_a, const Dimensions dim_b)
            : dim_a(dim_a), dim_b(dim_b)
        {
        }

        const std::string what() const
        {
            return description + dim_a.toString() + " " + dim_b.toString();// to_string works?
        }
    };
    template<class T>
    class Matrix<T>::iterator
    {

        Matrix<T> *matrix; // pointer to matrix
        int max_index;
        int index;      // index indicating postion in matrix
        /**
        *    Default constructor
        * 
        *   Default constructor, initializing iterator attributes.
        * 
        *   @return
        * 	Reference the value at the current index
        */
        iterator(Matrix<T> *matrix, int index);

        friend class Matrix<T>; // For enabling accessing private fields of Matrix

    public:
        iterator(const iterator &it) = default;            // Copy constructor
        iterator &operator=(const iterator &it) = default; // Assingment operator
        ~iterator() = default;                             // D'tor
        /**
        *    operator*()
        * 
        *   Returns by reference the value at the current index
        * 
        *   @return
        * 	Reference the value at the current index
        */
        int &operator*() const;
        /**
        * iretaror::operator++(): promotes the iterator index by 1. 
        *
        * @return
        *  --The prefix increment returns the value of a variable after it has been incremented.
        *  --The postfix increment returns the value of a variable before it has been incremented. 
        */
        iterator &operator++();   // Prefix
        iterator operator++(int); // Postfix
        /**
        *    operator==, operator!=
        *   @param it - An iterator to make comparison with
        *   @return
        * 	Returns a boolean of whether the pointer points to the same value or not
        *   In the same matrix.
        */
        bool operator==(const iterator &it) const;
        bool operator!=(const iterator &it) const;
    };
    template<class T>
    Matrix<T>::iterator<T>(Matrix<T> *matrix, int index): matrix(matrix), index(index),max_index(matrix->size())
        {

        }
    /**
    *    Class const_iterator
    *   same as iterator, inly differences is in handling a const matrix.
    *   Differences in decalrations are in:
    * 
    *   Const Matrix *matrix
    *   const_iterator(const Matrix *matrix, int index);     
    *   const int &operator*() const;
    */
   template<class T>
    class Matrix<T>::const_iterator
    {
        const Matrix<T> *matrix; // Const version of int matrix
        int index;
        const_iterator(const Matrix<T> *matrix, int index); // Arguement is const for intMatrix
        friend class Matrix<T>;

    public:
        const int &operator*() const;   // Returns a const int
        const_iterator &operator++();   // Prefix
        const_iterator operator++(int); // Postfix
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
        const_iterator(const const_iterator &it) = default;            // Copy constructor
        const_iterator &operator=(const const_iterator &it) = default; // Assingment operator
        ~const_iterator() = default;                                   // D'tor
    };
    template <class T>
    void checkDimensions(const Matrix<T> matrix_a, const Matrix<T> matrix_b)
    {
        int matrix_a_rows = matrix_a.height();
        int matrix_a_columns = matrix_a.width();
        int matrix_b_rows = matrix_b.height();
        int matrix_b_columns = matrix_b.width();
        if (matrix_a_rows != matrix_b_rows || matrix_a_columns != matrix_b_columns)
        {
            throw typename Matrix<T>::DimensionsMismatch(Dimensions(matrix_a_rows,matrix_a_columns),Dimensions(matrix_b_rows,matrix_b_columns));
        }
    }
    /**
    * operator+(): creates a new matrix with the current element value plus the num specified.
    *
    * @param num - The number to add to the exsisting value
    * @param matrix_a - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    template<class T>
    mtm::Matrix<T> operator+(const int num, const Matrix<T> &matrix_a);

    /**
    * operator+(): creates a new matrix with the current element value of matrix_a plus
    * the current element value of matrix_b.
    *
    * @param matrix_a - The matrix to take the values from
    * @param matrix_b - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    template<class T>
    Matrix<T> operator+(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b); // Outside class to support symetric +

    /**
    * operator-(): creates a new matrix with the current element value of matrix_a
    * minus the current element value of matrix_b.
    *
    * @param matrix_a - The matrix to take the values from
    * @param matrix_b - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    template <class T>
    Matrix<T> operator-(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) // Outside class to support symetric -
    {
        checkDimensions(matrix_a,matrix_b);
        Matrix<T> new_matrix(matrix_a);
        new_matrix = new_matrix + (-matrix_b); // Ok when operator + will be implemented
        return new_matrix;
    }
    template<class T> 
    MATRIX_BOOLEAN_STATUS checkBooleanMatrix(const Matrix<T> &matrix)
    {
        int number_of_trues = 0;
        for (int i = 0; i < matrix.height(); i++)
        {
            for (int j = 0; j < matrix.width(); j++)
            {
                if (bool(matrix(i, j))) // Assumed there is a conversion of T to bool
                {
                    number_of_trues += 1;
                }
            }
        }

        if (number_of_trues == matrix.size())
        {
            return ALL_TRUE;
        }

        return number_of_trues > 0 ? TRUE_EXISTS : ALL_FALSE;
    }
    /**
    * all: checks if all the the matrix's values are different from 0
    * @return
    * 	True if all the the matrix's values are different from 0.
    *   False otherwise
    */
   template<class T>
    bool all(const Matrix<T> &matrix)
    {        
        return checkBooleanMatrix(matrix) == ALL_TRUE ? true : false;
    }
    /**
    * any: checks if at least one of the matrix's values are different from 0.
    * @return
    * 	True if at least one of the matrix's values are different from 0.
    *   False otherwise
    */
    template<class T>
    bool any(const Matrix<T> &matrix)
    {
         return checkBooleanMatrix(matrix) == TRUE_EXISTS ? true : false;
    }

} // namespace mtm

#endif //INT_MATRIX_H
