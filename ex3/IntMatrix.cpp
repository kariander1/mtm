#include <string>
#include <iostream>
#include "IntMatrix.h"
#include "Auxiliaries.h"


namespace mtm
{
    const int IDENTITIY = 1;
    enum MATRIX_STATUS {ALL_ONES = -1, ONE_EXISTS, ALL_ZEROS};
    /**
    * checkMatrix: checks matrix with special properties for "any" and "all" functions
    * 
    *
    * @param matrix - The matrix to check the properites on
    * @return
    * 	enumerable value of MATRIX_STATUS, whether atrix contatins all ones, all zeroes, and if at least one.
    */
    static MATRIX_STATUS checkMatrix(const IntMatrix& matrix);

    IntMatrix::IntMatrix(Dimensions dimensions, int init_number) : array(new int[calcMatSize(dimensions)]), dim(dimensions)
    {

        copyMatrixValues(init_number);
    }

    IntMatrix IntMatrix::Identity(int size)
    {
        Dimensions dims(size, size);
        IntMatrix new_identity(dims, 0); // initiate the matrix to all zeros
        int matrix_size = new_identity.size();

        for (int i = 0; i < matrix_size; i += size + 1)
        {
            new_identity.array[i] = IDENTITIY; //add "1" in the diagonal
        }
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
    IntMatrix operator+(const IntMatrix &matrix_a, const IntMatrix &matrix_b)
    {
        IntMatrix new_matrix(matrix_a);
        for (int i = 0; i < matrix_a.height(); i++)
        {
            for (int j = 0; j < matrix_a.width(); j++)
            {
                new_matrix(i, j) += matrix_b(i, j);
            }
        }
        return new_matrix;
    }
    IntMatrix operator-(const IntMatrix &matrix_a, const IntMatrix &matrix_b)
    {
        IntMatrix new_matrix(matrix_a);
        new_matrix = new_matrix + (-matrix_b); // Will be ok with unary operator
        return new_matrix;
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

    IntMatrix IntMatrix::operator<(const int &num) const
    {
        IntMatrix new_matrix(dim, 0);
        for (int i = 0; i < size(); i++)
        {
            (new_matrix.array[i] = array[i] < num ? 1 : 0);
        }
        return new_matrix;
    }
    IntMatrix IntMatrix::operator>(const int &num) const
    {
        return (*this) < (-num);
    }
    IntMatrix IntMatrix::operator>=(const int &num) const
    {
        return (*this) <= (-num);
    }
    IntMatrix IntMatrix::operator<=(const int &num) const
    {
        return (*this) < (num + 1);
    }
    IntMatrix IntMatrix::operator==(const int &num) const
    {
        return (*this >= (num)) - (*this > (num)); // >= (minus operator) >
    }

    IntMatrix IntMatrix::operator!=(const int &num) const
    {
        IntMatrix all_diff_matrix(dim, 1);
        return (all_diff_matrix - ((*this) == num));
    }

    void IntMatrix::copyMatrixValues(const IntMatrix &matrix)
    {
        for (int i = 0; i < size(); i++) //size is the amount of elements in *this
        {
            array[i] = matrix.array[i]; //Or maybe should use iterator?
        }
    }
    void IntMatrix::copyMatrixValues(const int &init_value)
    {
        for (int i = 0; i < size(); i++) //size is the amount of elements in *this
        {
            array[i] = init_value; //Or maybe should use iterator?
        }
    }
    int IntMatrix::calcMatSize(const Dimensions &dim) const
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
        Dimensions new_dim(column, row);
        IntMatrix transpose_matrix(new_dim, 0); //create new matrix for transposed values

        int old_size = size();
        for (int i = 0; i < old_size; i++)
        {
            transpose_matrix.array[(i / column) + (i % column) * row] = array[i]; // calculate the new position
        }

        return transpose_matrix;
    }
    IntMatrix IntMatrix::operator-() const
    {
        IntMatrix decrease_matrix(dim);
        int matrix_size = size();
        for (int i = 0; i < matrix_size; i++)
        {
            decrease_matrix.array[i] = -array[i]; // set every element to -element
        }
        return decrease_matrix;
    }

    IntMatrix &IntMatrix::operator+=(const int num)
    {
        *this = *this + num;
        return *this;
    }
    int &IntMatrix::operator()(const int row, const int column)
    {
        return array[row * width() + column];
    }
    const int &IntMatrix::operator()(const int row, const int column) const
    {
        return array[row * width() + column];
    }

    MATRIX_STATUS checkMatrix(const IntMatrix& matrix)
    {
        int number_of_ones = 0;
        for (int i = 0; i < matrix.height(); i++)
        {
            for (int j = 0; j < matrix.width(); j++)
            {
                if (matrix(i, j) == 1)
                {
                    number_of_ones += 1;
                }
            }
        }

        if (number_of_ones == matrix.size())
        {
            return ALL_ONES;
        }

        return number_of_ones > 0 ? ONE_EXISTS : ALL_ZEROS;
    }

    bool all(const IntMatrix &matrix)
    {
        IntMatrix compare_matrix = matrix != 0;
        if (checkMatrix(compare_matrix) == ALL_ONES)
        {
            return true;
        }
        return false;
    }
    bool any(const IntMatrix &matrix)
    {
        IntMatrix compare_matrix = matrix != 0;
        if (checkMatrix(compare_matrix) != ALL_ZEROS)
        {
            return true;
        }
        return false;
    }
    std::ostream &operator<<(std::ostream &os, const IntMatrix &matrix)
    {

        os << mtm::printMatrix(matrix.array, matrix.dim);
        return os;
    }

    IntMatrix IntMatrix::operator+(const int num) const
    {
        int matrix_columns = width();
        int matrix_rows = height();
        Dimensions d(matrix_rows, matrix_columns);
        IntMatrix num_matrix(d, num);
        return *this + num_matrix;
    }
    IntMatrix operator+(const int num, const IntMatrix &matrix_a)
    {
        return matrix_a + num;
    }
    // **************************************************** ITERATOR CLASS******************************************************
    IntMatrix::iterator::iterator(IntMatrix *matrix_a, int index) : matrix(matrix_a),
                                                                     index(index)
    {
    }

    bool IntMatrix::iterator::operator==(const iterator &it) const
    {
        return index == it.index;
    }

    bool IntMatrix::iterator::operator!=(const iterator &it) const
    {
        return !(*this == it);
    }
    int &IntMatrix::iterator::operator*() const
    {
        return matrix->array[index];
    }
    IntMatrix::iterator &IntMatrix::iterator::operator++()
    {
        ++index;
        return *this;
    }
    IntMatrix::iterator IntMatrix::iterator::operator++(int)
    {
        iterator result = *this;
        ++*this;
        return result;
    }
    IntMatrix::iterator IntMatrix::begin()
    {
        return iterator(this, 0);
    }
    IntMatrix::iterator IntMatrix::end() 
    {
        return iterator(this, this->size());
    } 
 // **************************************************** ITERATOR CLASS*********************************************************
 // **************************************************** CONST ITERATOR CLASS***************************************************
    IntMatrix::const_iterator::const_iterator(const IntMatrix *matrix_a, int index) : matrix(matrix_a),
                                                                     index(index)
    {
        
    }
    bool IntMatrix::const_iterator::operator==(const const_iterator &it) const
    {
        //return iterator(*this)==iterator(it);
        return index ==it.index;
    }

    bool IntMatrix::const_iterator::operator!=(const const_iterator &it) const
    {
        return !(*this == it);
    }
    const int &IntMatrix::const_iterator::operator*() const
    {
        //return *(iterator(*this));
        return matrix->array[index];
    }
    IntMatrix::const_iterator &IntMatrix::const_iterator::operator++()
    {        
        ++index;
        return *this;
    }
    IntMatrix::const_iterator IntMatrix::const_iterator::operator++(int)
    {
        const_iterator result = *this;
        ++*this;
        return result;
    }
    IntMatrix::const_iterator IntMatrix::begin() const
    {
        return const_iterator(this, 0);
    }
    IntMatrix::const_iterator IntMatrix::end() const 
    {
        return const_iterator(this, this->size());
    } 
// **************************************************** CONST ITERATOR CLASS****************************************************
  
} // namespace mtm