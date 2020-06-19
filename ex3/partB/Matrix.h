#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm
{
    const std::string ERROR_PREFIX="Mtm matrix error: ";
    const std::string ILLEGAL_ACCESS=ERROR_PREFIX+"An attempt to access an illegal element";
    const std::string ILLEGAL_INITIAL = ERROR_PREFIX+"Illegal initialization values";
    const std::string MISMATCH=ERROR_PREFIX+"Dimension mismatch: ";
    //-------------------------------------------------------------
    // Enum values for checking all/any functions implemented later in file
    //-------------------------------------------------------------
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

        // Helper Functions, see implementation
        int calcMatSize(const mtm::Dimensions &dim) const;
        void copyMatrixValues(const Matrix &matrix);
        void copyMatrixValues(const T &initial_value);
        static void checkDimensions(const Matrix<T> matrix_a, const Matrix<T> matrix_b);
        //-------------------------------------------------------------
        // Helper class BooleanNot for boolean matrices in operators
        //-------------------------------------------------------------
        class BooleanNot;
        //-------------------------------------------------------------
        // Helper class Negative for operator-
        //-------------------------------------------------------------
        class Negative;

    public:
        //-------------------------------------------------------------
        // Matrix C'tor
        // ASSUMPTIONS: T has a default constructor.
        //-------------------------------------------------------------
        Matrix(mtm::Dimensions dimensions, T initial_value = T()) : array(new T[calcMatSize(dimensions)]), // New will throw bad_alloc if allocation failed
                                                                 dim(dimensions)
        {

            copyMatrixValues(initial_value);
        }
        //-------------------------------------------------------------
        // Matrix Copy constructor
        // ASSUMPTIONS: T has a default constructor
        //-------------------------------------------------------------
        Matrix(const Matrix &matrix) : array(new T[calcMatSize(matrix.dim)]),
                                       dim(matrix.dim)
        {
            copyMatrixValues(matrix);
        }
        //-------------------------------------------------------------
        // Matrix D'tor
        // ASSUMPTIONS: T has destructor
        //-------------------------------------------------------------
        ~Matrix()
        { //Destructor
            delete[] array;
        }

        //-------------------------------------------------------------
        // Matrix operators
        // ASSUMPTIONS: T has destructor
        //-------------------------------------------------------------
        Matrix &operator=(const Matrix &matrix);

        Matrix<bool> operator<(const T &value) const;

        Matrix<bool> operator<=(const T &value) const;

        Matrix<bool> operator>(const T &value) const;

        Matrix<bool> operator>=(const T &value) const;

        Matrix<bool> operator==(const T &value) const;

        Matrix<bool> operator!=(const T &value) const;

        Matrix operator-() const;

        Matrix &operator+=(const T initial_value);

        Matrix operator+(const T initial_value) const;

        T &operator()(const int &row, const int &column);

        const T operator()(const int &row, const int &column) const;

        int height() const;

        int width() const;

        int size() const;

        Matrix transpose() const;

        static Matrix Diagonal(const int size, const T initial_value);

        template <class ApplyFunctor>
        Matrix apply(ApplyFunctor functor) const;

        class iterator;
        /**
        * IntMatrix::begin/end(): creates an iterator for the given matrix and retets it 
        * to be the begin/end of the matrix
        *
        * @return
        * 	returns the new iterator
        */
        iterator begin()
        {
            return iterator(this, 0);
        }
        iterator end()
        {
            return iterator(this, this->size());
        }

        class const_iterator;
        /*
         * same as the end and begin, the difference is that the return iterator 
         * is constant and the matrix is constant
         */
        const_iterator begin() const
        {
            return const_iterator(this, 0);
        }
        const_iterator end() const
        {
            return const_iterator(this, this->size());
        }
        
       
        class AccessIllegalElement;

        class IllegalInitialization;

        class DimensionMismatch;
    };
    // ********* Helper functions **********
    /**
    * Matrix::calcMatSize: gets the size of the matrix (rows*columns). 
    * @param dim - The dimentions of the matrix
    * @return
    * 	returns the size of the matrix (rows*columns) .
    */
    template <class T>
    int Matrix<T>::calcMatSize(const mtm::Dimensions &dim) const
    {
        if (dim.getCol() < 0 || dim.getRow() < 0)
            throw IllegalInitialization();
        return dim.getCol() * dim.getRow();
    }
    /**
    * Matrix::copyMatrixValues: copys all the values from the given matrix
    * to the "this" matrix. 
    * @param matrix - The matrix to copy its values
    * @return
    * 	Nothing.
    */
    template <class T>
    void Matrix<T>::copyMatrixValues(const Matrix &matrix)
    {
        int max_size = size();
        for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
        {
            array[i] = matrix.array[i]; //Or maybe should use iterator?
        }
    }
    /**
    * Matrix::copyMatrixValues: sets all the values of the given matrix 
    * to the init_number.
    * @param initial_value - The value to initiate the matrix with
    * @return
    * 	Nothing.
    */
    template <class T>
    void Matrix<T>::copyMatrixValues(const T &initial_value)
    {
        int max_size = size();
        for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
        {
            array[i] = initial_value; //Or maybe should use iterator?
        }
    }

    //*************** helper classes ************
    template <class T>
    class Matrix<T>::BooleanNot
    {
    public:
    
        bool operator()(bool val)
        {
            return !val;
        }
    };
    //-------------------------------------------------------------
    // Negative
    // ASSUMPTIONS: T has unary operator-
    //-------------------------------------------------------------
    template <class T>
    class Matrix<T>::Negative
    {
    public:
        T operator()(T val)
        {
            return -val;
        }
    };
    /**
    * Matrix::apply: creates a new matrix containing the given matrix elements 
    * after applying the given function on them. 
    * @param functor - function to apply on each the matrix's elements.
    * @return
    * 	a new matrix with the values after applying the functor.
    */
    template <class T>
    template <class ApplyFunctor>
    Matrix<T> Matrix<T>::apply(ApplyFunctor functor) const
    {
        int row = height();
        int column = width();
        Dimensions new_dim(row, column);
        Matrix function_matrix(new_dim);
        int matrix_size = function_matrix.size();
        for (int i = 0; i < matrix_size; i++)
        {
            function_matrix.array[i] = functor(array[i]);
        }
        return function_matrix;
    }

    // *********** Matrix operators*************
    /**
    *   "operator()" operators
    * 
    *   Operator with parenthesis to handle indices indicating exact position in matrix.
    *   T& operator() for enabling lvalue assignment, and const T& operator() for handling const values.
    * 
    *   @param row - Row index
    *   @param column - Column Index
    *   @return
    * 	T value of value stored in matrix in defined position
    */
    template <class T>
    const T Matrix<T>::operator()(const int &row, const int &column) const
    {
        Matrix temp = *this;
        return temp(row, column);
    }
    // written before the operator()
    template <class T>
    T &Matrix<T>::operator()(const int &row, const int &column)
    {
        const int shifted_index = row * width() + column;
        if (row < 0 || column < 0 || shifted_index >= size())
            throw AccessIllegalElement();

        return array[shifted_index];
    }
/**
    * Matrix::&operator+(): creates a new matrix with the current element value plus the value specified.
    * ASSUMPTIONS: T has + operator
    *
    * @param initial_value - The value to add to the exsisting value
    * @return
    * 	returns a copy of the new matrix
    */
    template <class T>
    Matrix<T> Matrix<T>::operator+(const T initial_value) const
    {
        int matrix_columns = width();
        int matrix_rows = height();
        Dimensions d(matrix_rows, matrix_columns);
        Matrix initial_matrix(d, initial_value);
        return *this + initial_matrix;
    }
    /**
    * Matrix::&operator+=(): adds to each element in the exsisting matrix the value specified.  
    * ASSUMPTIONS: T has + operator
    * 
    * @param initial_value - The value to add to the exsisting value
    * @return
    * 	returns a reference to the modified matrix
    */
    template <class T>
    Matrix<T> &Matrix<T>::operator+=(const T initial_value)
    {
        *this = *this + initial_value;
        return *this;
    }

    /**
    * Matrix::&operator-(): creates a new matrix where each value is the negative of the current value.
    *
    * @return
    * 	returns the new matrix with negative values.
    */
    template <class T>
    Matrix<T> Matrix<T>::operator-() const
    {

        return apply(Negative());
    }


    /**
    * Matrix::&operator=(): assignment operator, assigns the given matrix to this
    *
    * ASSUMPTIONS: T has destructor and default c'tor
    * @param matrix - The matrix to copy to this
    * @return
    * 	returns reference to the new copied matrix
    */
    template <class T>
    Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
    {
        dim = matrix.dim;
        T *temp_array = new T[size()]; // Will throw bad_alloc if allocation failed.

        delete[] array; // If reached here, then allocation was successful
        array = temp_array;

        copyMatrixValues(matrix);

        return *this;
    }

    /**
    * Matrix::&operator__(): execute the logical operation for every element in the matrix and creates 
    * a new matrix in the same size. if the logical operation of the element was true then the element in
    * the new_matrix is true, otherwise the element is false.
    *
    * @param value - The value to compare to
    * @return
    * 	returns the new matrix with true and false according to the output of the logic operation.
    */
    template <class T>
    Matrix<bool> Matrix<T>::operator!=(const T &value) const
    {
        return ((*this) == value).apply(BooleanNot());
    }
    //-------------------------------------------------------------
    // operator<
    // ASSUMPTIONS: T has an operator< definition
    //-------------------------------------------------------------
    template <class T>
    Matrix<bool> Matrix<T>::operator<(const T &value) const
    {
        Matrix<bool> new_matrix(dim);
        int max_height = height();
        int max_width = width();
        for (int i = 0; i < max_height; i++)
        {
            for (int j = 0; j < max_width; j++)
            {
                (new_matrix(i, j)) = ((*this)(i, j) < value); // << use of operator here
            }
        }
        return new_matrix;
    }    
    //-------------------------------------------------------------
    // operator<=
    // ASSUMPTIONS: T has an operator== and operator< definition
    //-------------------------------------------------------------
    template <class T>
    Matrix<bool> Matrix<T>::operator<=(const T &value) const
    {
        return (((*this) == value) + ((*this) < value));
    }
    //-------------------------------------------------------------
    // operator>
    // ASSUMPTIONS: T has an operator< definition
    //-------------------------------------------------------------
    template <class T>
    Matrix<bool> Matrix<T>::operator>(const T &value) const
    {
        return ((*this) < value).apply(BooleanNot());
    }
    //-------------------------------------------------------------
    // operator>=
    // ASSUMPTIONS: T has an operator== and operator< definition
    //-------------------------------------------------------------
    template <class T>
    Matrix<bool> Matrix<T>::operator>=(const T &value) const
    {

        return ((*this) > value) + ((*this) == value);
    }
    //-------------------------------------------------------------
    // operator==
    // ASSUMPTIONS: T has an operator== definition
    //-------------------------------------------------------------
    template <class T>
    Matrix<bool> Matrix<T>::operator==(const T &value) const
    {

        Matrix<bool> new_matrix(dim);
        int max_height = height();
        int max_width = width();
        for (int i = 0; i < max_height; i++)
        {
            for (int j = 0; j < max_width; j++)
            {
                (new_matrix(i, j)) = ((*this)(i, j) == value);
            }
        }
        return new_matrix;
    }

    //*********** Member Functions **************

    /**
    *   Diagonal
    * 
    *   Returns a diagonal cubic marix with T values initiated on the matrix's daigonal
    * 
    *   @param size - size for dimensions of matrix. [ size X size ]
    *   @param initial_value - the T value for initializing.
    *   @return
    * 	Returns a new diagonal matrix.
    *   ASSUMPTIONS: T has a default constructor as used by new_diagonal(dims);
    */
    template <class T>
    Matrix<T> Matrix<T>::Diagonal(const int size, const T initial_value)
    {
        Dimensions dims(size, size);
        Matrix new_diagonal(dims); // initiate the matrix to T() values. Will throw illegal init/bad alloc from constructor
        int matrix_size = new_diagonal.size();

        for (int i = 0; i < matrix_size; i += size + 1)
        {
            new_diagonal.array[i] = initial_value;
        }
        return new_diagonal;
    }
    /**
    *   Matrix transpose()
    * 
    *   Transposes the matrix and switches position of values according to algebric transpose operator.
    * 
    *   @return
    * 	Returns a COPY of the transposed matrix. does not change original matrix.
    */
    template <class T>
    Matrix<T> Matrix<T>::transpose() const
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
    * IntMatrix::height/width/size(): calculates the height/width/size of the given matrix
    *
    * @return
    * 	int representing the height/width/size of the given matrix
    */
    template <class T>
    int Matrix<T>::height() const
    {
        return dim.getRow();
    }

    template <class T>
    int Matrix<T>::width() const
    {
        return dim.getCol();
    }

    template <class T>
    int Matrix<T>::size() const
    {
        return dim.getCol() * dim.getRow();
    }
        /**
        * Output operator: Prints the given matrix.
        * @return
        * 	None
        * ASSUMPTIONS: T has an operator<< definition (which is being used in mtm::printMatrix)
        */
    template <class T>
    std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
    {
        typename Matrix<T>::const_iterator begin = matrix.begin();
        typename Matrix<T>::const_iterator end = matrix.end();
        int width = matrix.width();
        return mtm::printMatrix(os, begin, end, width);
    }
        /**
        *   Exception Class
        * 
        *   A generic expection in mtm namespace providing a mother class to be inherited.
        *   The class inherits the std exception
        */
        /**
        *   AccessIllegalElement Class
        * 
        *   An exception an accesss to an illegal elemnt when iterating over matrix
        */
    template <class T>
    class Matrix<T>::AccessIllegalElement : public Exception
    {
    private:
        const std::string description;

    public:
        std::string what() noexcept
        {
            return ILLEGAL_ACCESS;
        }
    };
        /**
        *   IllegalInitialization Class
        * 
        *   An exception representing and illegal initialization of matrix dimensions
        */
    template <class T>
    class Matrix<T>::IllegalInitialization : public Exception
    {
    private:
    public:
        std::string what() noexcept
        {
            return ILLEGAL_INITIAL;
        }
    };
        /**
        *   DimensionMismatch Class
        * 
        *   An exception representing when dimensions of two matrices are not the same.
        */
    template <class T>
    class Matrix<T>::DimensionMismatch : public Exception
    {
    private:
        const Dimensions dim_a;
        const Dimensions dim_b;

    public:
        /**
        *   DimensionMismatch C'tor
        * 
        *   Receives two dimensions which mismatched, and saves them for later throwing the appropriate error.
        */
        DimensionMismatch(const Dimensions dim_a, const Dimensions dim_b)
            : dim_a(dim_a), dim_b(dim_b)
        {
        }

        std::string what() noexcept
        {
            return MISMATCH+ dim_a.toString() + " " + dim_b.toString();
        }
    };
    template <class T>
    class Matrix<T>::iterator
    {

        Matrix<T> *matrix; // pointer to matrix
        int max_index;
        int index; // index indicating postion in matrix
        /**
        *    Default constructor
        * 
        *   Default constructor, initializing iterator attributes.
        */
        iterator(Matrix *matrix, int index) : matrix(matrix), max_index(matrix->size()), index(index)
        {
        }

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
        T &operator*() const
        {
            if (index >= max_index || index<0) // Index cannot go negative
            {
                throw Matrix::AccessIllegalElement();
            }
            return matrix->array[index];
        }
        /**
        * iretaror::operator++(): promotes the iterator index by 1. 
        *
        * @return
        *  --The prefix increment returns the value of a variable after it has been incremented.
        *  --The postfix increment returns the value of a variable before it has been incremented. 
        */
        iterator &operator++() // Prefix
        {
            ++index;
            return *this;
        }
        iterator operator++(int) // Postfix
        {
            iterator result = *this;
            ++*this;
            return result;
        }
        /**
        *    operator==, operator!=
        *   @param it - An iterator to make comparison with
        *   @return
        * 	Returns a boolean of whether the pointer points to the same value or not
        *   In the same matrix.
        */
        bool operator==(const iterator &it) const
        {
            return index == it.index;
        }
        
        bool operator!=(const iterator &it) const
        {
            return !(*this == it);
        }
    };
    /**
    *    Class const_iterator
    *   same as iterator, inly differences is in handling a const matrix.
    *   Differences in decalrations are in:
    * 
    *   Const Matrix<T> *matrix
    *   const_iterator(const Matrix *matrix, int index);     
    *   const T &operator*() const;
    */
    template <class T>
    class Matrix<T>::const_iterator
    {
        const Matrix<T> *matrix; // Const version of matrix
        int max_index;
        int index;

        const_iterator(const Matrix<T> *matrix, int index) : matrix(matrix), max_index(matrix->size()), index(index)
        {
        }
        friend class Matrix<T>;

    public:
        const_iterator(const const_iterator &it) = default;            // Copy constructor
        const_iterator &operator=(const const_iterator &it) = default; // Assingment operator
        ~const_iterator() = default;                                   // D'tor
        const T &operator*() const                                     // Returns a const int
        {
            if (index >= max_index || index<0)
            {
                throw Matrix::AccessIllegalElement();
            }
            return matrix->array[index];
        }
        const_iterator &operator++() // Prefix
        {
            ++index;
            return *this;
        }
        const_iterator operator++(int) // Postfix
        {
            iterator result = *this;
            ++*this;
            return result;
        }
        bool operator==(const const_iterator &it) const
        {
            return index == it.index;
        }
        bool operator!=(const const_iterator &it) const
        {
            return !(*this == it);
        }
    };
    /**
    * checkDimensions: Checks whether two dimensions of matrices are equal, and throws and exception if not.
    * @param matrix_a - First matrix to check dimnesions of
    * @param matrix_b - Second matrix to check dimnesions of
    * @return
    * 	NONE, throws an exception if Dimensions are not equal.
    */
    template <class T>
    void checkDimensions(const Matrix<T> matrix_a, const Matrix<T> matrix_b)
    {
        Dimensions dim_a(matrix_a.height(), matrix_a.width());
        Dimensions dim_b(matrix_b.height(), matrix_b.width());

        if (dim_a != dim_b)
        {
            throw typename Matrix<T>::DimensionMismatch(dim_a, dim_b);
        }
    }
    /**
    * operator+(): creates a new matrix with the current element value plus the num specified.
    * Uses the operator+ of Matrices.
    * @param value - The T value to add
    * @param matrix_a - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    template <class T>
    mtm::Matrix<T> operator+(const T value, const Matrix<T> &matrix_a)
    {
        return matrix_a + value;
    }
    /**
    * operator+(): creates a new matrix with the current element value of matrix_a plus
    * the current element value of matrix_b.
    *
    * @param matrix_a - The matrix to take the values from
    * @param matrix_b - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix with opertor +
    * ASSUMPTIONS: T has an operator+ definition
    */
    template <class T>
    Matrix<T> operator+(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) // Outside class to support symetric +
    {
        checkDimensions(matrix_a, matrix_b);
        Matrix<T> new_matrix(matrix_a);

        int max_height = matrix_a.height();
        int max_width = matrix_a.width();
        for (int i = 0; i < max_height; i++)
        {
            for (int j = 0; j < max_width; j++)
            {
                new_matrix(i, j) = new_matrix(i, j) + matrix_b(i, j); // assuming + operator exists on T
            }
        }
        return new_matrix;
    }
    /**
    * operator-(): creates a new matrix with the current element value of matrix_a
    * minus the current element value of matrix_b.
    *
    * @param matrix_a - The matrix to take the values from
    * @param matrix_b - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix with operator- on them
    */
    template <class T>
    Matrix<T> operator-(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) // Outside class to support symetric -
    {

        Matrix<T> new_matrix(matrix_a);
        new_matrix = new_matrix + (-matrix_b);
        return new_matrix;
    }
    /**
    * checkBooleanMatrix: checks boolean value of T values in matrix, helper function to All and Any
    * @return
    * 	ENUM value describing whether Any/All of the values are true:
    *    ALL_TRUE = all T value are true when converted
    *    TRUE_EXISTS = at least one T value is true when converted
    *    ALL_FALSE = all values are not true when converted
    * ASSUMPTIONS: T has a conversion to boolean
    */
    template <class T>
    MATRIX_BOOLEAN_STATUS checkBooleanMatrix(const Matrix<T> &matrix)
    {
        int number_of_trues = 0;
        int max_height = matrix.height();
        int max_width = matrix.width();
        for (int i = 0; i < max_height; i++)
        {
            for (int j = 0; j < max_width; j++)
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
    * all: checks if all the the matrix's values are true when converting T to boolean
    * @return
    * 	True if all the the matrix's values are true when converting T to boolean
    *   False otherwise
    * ASSUMPTIONS: T has a conversion to boolean
    */
    template <class T>
    bool all(const Matrix<T> &matrix)
    {
        return checkBooleanMatrix(matrix) == ALL_TRUE;
    }
    /**
    * any: checks if at least one of the matrix's values is TRUE when converting T type to bool.
    * @return
    * 	True if at least one of the matrix's values is TRUE when converting T type to bool.
    *   False otherwise
    * ASSUMPTIONS: T has a conversion to boolean
    */
    template <class T>
    bool any(const Matrix<T> &matrix)
    {
        return checkBooleanMatrix(matrix) == TRUE_EXISTS;
    }

} // namespace mtm

#endif //MATRIX_H
