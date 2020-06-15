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

        class MatrixError;
        // Helper Functions
        int calcMatSize(const mtm::Dimensions &dim) const;
        void copyMatrixValues(const Matrix &matrix);
        void copyMatrixValues(const T &init_value);

        // For negating all boolean values
        class BooleanNot;
        
        class Negative;
        
    public:
        Matrix(mtm::Dimensions dimensions, T init_value = T()) : array(new T[calcMatSize(dimensions)]), // New will throw bad_alloc if allocation failed
                                                                 dim(dimensions)
        {

            copyMatrixValues(init_value);
        }
        Matrix(const Matrix &matrix) : array(new T[calcMatSize(matrix.dim)]), // Copy constructor
                                       dim(matrix.dim)
        {
            copyMatrixValues(matrix);
        }
        ~Matrix()
        { //Destructor
            delete[] array;
        }

        Matrix& operator=(const Matrix &matrix);

        Matrix<bool> operator<(const T &value) const;
        
        Matrix<bool> operator<=(const T &value) const;
        
        Matrix<bool> operator>(const T &value) const;
        
        Matrix<bool> operator>=(const T &value) const;
        
        Matrix<bool> operator==(const T &value) const;
        
        Matrix<bool> operator!=(const T &value) const;
        
        Matrix operator-() const;
        
        Matrix &operator+=(const T init_value);
        
        Matrix operator+(const T init_value) const;
        
        T &operator()(const int &row, const int &column);
        
        const T operator()(const int &row, const int &column) const;
        
        friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix);
        
        int height() const;

        int width() const;

        int size() const;

        Matrix transpose() const;
        
        static Matrix Diagonal(const int size, const T init_value);
        
        template <class ApplyFunctor>
        Matrix apply(ApplyFunctor functor) const;

        class iterator;
        iterator begin()
        {
            return iterator(this, 0);
        }
        iterator end()
        {
            return iterator(this, this->size());
        }

        class const_iterator;
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
    template <class T>
    int Matrix<T>::calcMatSize(const mtm::Dimensions &dim) const
    {
        if (dim.getCol() < 0 || dim.getRow() < 0)
            throw IllegalInitialization();
        return dim.getCol() * dim.getRow();
    }

    template <class T>
    void Matrix<T>::copyMatrixValues(const Matrix &matrix)
    {
        int max_size = size();
        for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
        {
            array[i] = matrix.array[i]; //Or maybe should use iterator?
        }
    }

    template <class T>
    void Matrix<T>::copyMatrixValues(const T &init_value)
    {
        int max_size = size();
        for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
        {
            array[i] = init_value; //Or maybe should use iterator?
        }
    }

    //*************** helper classes ************
    class BooleanNot
        {
        public:
            bool operator()(bool val)
            {
                return !val;
            }
        };
    template<class T>
    class Matrix<T>::Negative
        {
        public:
            T operator()(T val)
            {
                return -val;
            }
        };
    
    template<class T>
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
    template<class T>
    const T Matrix<T>::operator()(const int &row, const int &column) const
        {
            Matrix temp = *this;
            return temp(row, column);
        }

    template<class T>
    T& Matrix<T>::operator()(const int &row, const int &column)
        {
            const int shifted_index = row * width() + column;
            if (row < 0 || column < 0 || shifted_index >= size())
                throw AccessIllegalElement();

            return array[shifted_index];
        }

    template<class T>
    Matrix<T> Matrix<T>::operator+(const T init_value) const
        {
            int matrix_columns = width();
            int matrix_rows = height();
            Dimensions d(matrix_rows, matrix_columns);
            Matrix init_matrix(d, init_value);
            return *this + init_matrix;
        }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const T init_value)
        {
            *this = *this + init_value;
            return *this;
        }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const
        {

            return apply(Negative());
        }

    template<class T>
    Matrix<bool> Matrix<T>::operator!=(const T &value) const
        {
            return ((*this) == value).apply(BooleanNot());
        }

    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T> &matrix) // Assignment operator
        {
            dim = matrix.dim;
            T *temp_array = new T[size()]; // Will throw bad_alloc if allocation failed.

            delete[] array; // If reached here, then allocation was successful
            array = temp_array;

            copyMatrixValues(matrix);

            return *this;
        }

    template<class T>
    Matrix<bool> Matrix<T>::operator<(const T &value) const
        {
            Matrix<bool> new_matrix(dim);
            int max_height = height();
            int max_width = width();
            for (int i = 0; i < max_height; i++)
            {
                for (int j = 0; j < max_width; j++)
                {
                    (new_matrix(i, j)) = ((*this)(i, j) < value);
                }
            }
            return new_matrix;
        }

    template<class T>
    Matrix<bool> Matrix<T>::operator<=(const T &value) const
        {
            return (((*this) == value) + ((*this) < value));
        }

    template<class T>
    Matrix<bool> Matrix<T>::operator>(const T &value) const
        {
            return ((*this) < value).apply(BooleanNot());
        }

    template<class T>
    Matrix<bool> Matrix<T>::operator>=(const T &value) const
        {

            return ((*this) > value) + ((*this) == value);
        }

    template<class T>
    Matrix<bool> Matrix<T>::operator==(const T &value) const
        {

            Matrix<bool> new_matrix(dim, value);
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
    
    //*********** class functions **************
    
    template<class T>
    Matrix<T> Matrix<T>::Diagonal(const int size, const T init_value)
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

    template<class T>
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

    template<class T>
    std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix)
        { // should we add const th the declerastion?
            const_iterator begin = matrix.begin();
            const_iterator end = matrix.end();
            int width = matrix.width();
            return mtm::printMatrix(os, begin, end, width);
        }
    
    template<class T>
    int Matrix<T>::height() const
        {
            return dim.getRow();
        }

    template<class T>    
    int Matrix<T>::width() const
        {
            return dim.getCol();
        }

    template<class T>    
    int Matrix<T>::size() const
        {
            return dim.getCol() * dim.getRow();
        }
    
    template <class T>
    class Matrix<T>::MatrixError
    {
    protected:
        const std::string error_prefix;

    public:
        MatrixError(std::string des = "Mtm matrix error: ") : error_prefix(des)
        {
        }
    };
    template <class T>
    class Matrix<T>::AccessIllegalElement
    {
    private:
        const std::string description;

    public:
        const std::string what() const
        {
            return "Mtm matrix error: An attempt to access an illegal element";
        }
    };
    template <class T>
    class Matrix<T>::IllegalInitialization
    {
    private:
    public:
        const std::string what() const
        {
            return "Mtm matrix error: Illegal initialization values";
        }
    };
    template <class T>
    class Matrix<T>::DimensionMismatch
    {
    private:
        const Dimensions dim_a;
        const Dimensions dim_b;

    public:
        DimensionMismatch(const Dimensions dim_a, const Dimensions dim_b)
            : dim_a(dim_a), dim_b(dim_b)
        {
        }

        const std::string what() const
        {
            return "Mtm matrix error: Dimensions mismatch: " + dim_a.toString() + " " + dim_b.toString(); // to_string works?
        }
    };
    template <class T>
    class Matrix<T>::iterator
    {

        Matrix<T> *matrix; // pointer to matrix
        int max_index;
        int index; // index indicating postion in matrix
        iterator(Matrix *matrix, int index) : matrix(matrix), index(index), max_index(matrix->size())
        {
        }

        friend class Matrix<T>; // For enabling accessing private fields of Matrix

    public:
        iterator(const iterator &it) = default;            // Copy constructor
        iterator &operator=(const iterator &it) = default; // Assingment operator
        ~iterator() = default;                             // D'tor
        T &operator*() const
        {
            if (index >= max_index) // Index cannot go negative
            {
                throw Matrix::AccessIllegalElement();
            }
            return matrix->array[index];
        }
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

        bool operator==(const iterator &it) const
        {
            return index == it.index;
        }
        bool operator!=(const iterator &it) const
        {
            return !(*this == it);
        }
    };

    template <class T>
    class Matrix<T>::const_iterator
    {
        const Matrix<T> *matrix; // Const version of int matrix
        int max_index;
        int index;

        const_iterator(const Matrix<T> *matrix, int index) : matrix(matrix), index(index), max_index(matrix->size())
        {
        }
        friend class Matrix<T>;

    public:
        const_iterator(const const_iterator &it) = default;            // Copy constructor
        const_iterator &operator=(const const_iterator &it) = default; // Assingment operator
        ~const_iterator() = default;                                   // D'tor
        const T &operator*() const                                     // Returns a const int
        {
            if (index >= max_index)
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
    template <class T>
    void checkDimensions(const Matrix<T> matrix_a, const Matrix<T> matrix_b)
    {
        int matrix_a_rows = matrix_a.height();
        int matrix_a_columns = matrix_a.width();
        int matrix_b_rows = matrix_b.height();
        int matrix_b_columns = matrix_b.width();
        if (matrix_a_rows != matrix_b_rows || matrix_a_columns != matrix_b_columns)
        {
            throw typename Matrix<T>::DimensionMismatch(Dimensions(matrix_a_rows, matrix_a_columns), Dimensions(matrix_b_rows, matrix_b_columns));
        }
    }
    template <class T>
    mtm::Matrix<T> operator+(const int num, const Matrix<T> &matrix_a)
    {
        return matrix_a + num;
    }
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
                new_matrix(i, j) += matrix_b(i, j); // assuming += operator exists
            }
        }
        return new_matrix;
    }
    template <class T>
    Matrix<T> operator-(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) // Outside class to support symetric -
    {

        Matrix<T> new_matrix(matrix_a);
        new_matrix = new_matrix + (-matrix_b); // Ok when operator + will be implemented
        return new_matrix;
    }
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
    template <class T>
    bool all(const Matrix<T> &matrix)
    {
        return checkBooleanMatrix(matrix) == ALL_TRUE;
    }
    template <class T>
    bool any(const Matrix<T> &matrix)
    {
        return checkBooleanMatrix(matrix) == TRUE_EXISTS;
    }

} // namespace mtm

#endif //INT_MATRIX_H
