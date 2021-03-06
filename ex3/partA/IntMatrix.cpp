#include <string>
#include <iostream>
#include "IntMatrix.h"
#include "Auxiliaries.h"

namespace mtm
{
    const int IDENTITIY = 1;

    IntMatrix::IntMatrix(Dimensions dimensions, int init_number) 
        : array(new int[calcMatSize(dimensions)]), dim(dimensions)
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
            new_identity.array[i] = IDENTITIY; //put "1" in the diagonal
        }
        return new_identity;
    }
    IntMatrix::IntMatrix(const IntMatrix &matrix) : array(new int[calcMatSize(matrix.dim)]),
                                                    dim(matrix.dim)
    {
        copyMatrixValues(array,matrix);
    }

    IntMatrix::~IntMatrix()
    {
        delete[] array;
    }
    IntMatrix operator+(const IntMatrix &matrix_a, const IntMatrix &matrix_b)
    {
        IntMatrix new_matrix(matrix_a);
        int max_height = matrix_a.height();
        int max_width = matrix_a.width();
        for (int i = 0; i < max_height; i++)
        {
            for (int j = 0; j < max_width; j++)
            {
                new_matrix(i, j) += matrix_b(i, j);
            }
        }
        return new_matrix;
    }
    IntMatrix operator-(const IntMatrix &matrix_a, const IntMatrix &matrix_b)
    {
        IntMatrix new_matrix(matrix_a);
        new_matrix = new_matrix + (-matrix_b); // Using unary operator
        return new_matrix;
    }
    IntMatrix &IntMatrix::operator=(const IntMatrix &matrix)
    {
        dim = matrix.dim;
        int *temp_array = new int[size()]; // Will throw bad_alloc if allocation failed.
        copyMatrixValues(temp_array,matrix);
        delete[] array; // If reached here, then allocation and transfer was successful
        array = temp_array;

        return *this;

        
    }

    IntMatrix IntMatrix::operator<(const int &num) const
    {
        IntMatrix new_matrix(dim, 0);
        int max_size =size();
        for (int i = 0; i < max_size; i++)
        {
            (new_matrix.array[i] = array[i] < num ? 1 : 0);
        }
        return new_matrix;
    }
    IntMatrix IntMatrix::operator>(const int &num) const
    {
        return (-(*this)) < (-num);
    }
    IntMatrix IntMatrix::operator>=(const int &num) const
    {
        return (-(*this)) <= (-num);
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

    void IntMatrix::copyMatrixValues(int* array,const IntMatrix &matrix)
    {
        int max_size = matrix.size();
        for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
        {
            array[i] = matrix.array[i];
        }
    }
    void IntMatrix::copyMatrixValues(const int &init_value)
    {
        int max_size = size();
        for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
        {
            array[i] = init_value;
        }
    }
    int IntMatrix::calcMatSize(const Dimensions &dim)
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
    int &IntMatrix::operator()(const int& row, const int& column)
    {
        return array[row * width() + column];
    }
    const int IntMatrix::operator()(const int& row, const int& column) const
    {
        IntMatrix temp = *this;
        return temp(row,column);
    }

    MATRIX_STATUS checkMatrix(const IntMatrix &matrix)
    {
        int number_of_ones = 0;
        int max_height = matrix.height();
        int max_width = matrix.width();
        for (int i = 0; i < max_height; i++)
        {
            for (int j = 0; j <max_width; j++)
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
        return checkMatrix(compare_matrix) == ALL_ONES;

    }
    bool any(const IntMatrix &matrix)
    {
        IntMatrix compare_matrix = matrix != 0;
        MATRIX_STATUS matrix_status =checkMatrix(compare_matrix);
        return  (matrix_status == ALL_ONES || matrix_status == ONE_EXISTS);
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
    // **************************************************** ITERATOR CLASS************************
    IntMatrix::iterator::iterator(IntMatrix *matrix_a, int index) : matrix(matrix_a),
                                                                    index(index){}
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
    // **************************************************** ITERATOR CLASS*************************
    // **************************************************** CONST ITERATOR CLASS*******************
    IntMatrix::const_iterator::const_iterator(const IntMatrix *matrix_a, int index) : matrix(matrix_a),
                                                                                      index(index){}
    bool IntMatrix::const_iterator::operator==(const const_iterator &it) const
    {
        return index == it.index;
    }

    bool IntMatrix::const_iterator::operator!=(const const_iterator &it) const
    {
        return !(*this == it);
    }
    const int &IntMatrix::const_iterator::operator*() const
    {
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
    // **************************************************** CONST ITERATOR CLASS*******************

} // namespace mtm