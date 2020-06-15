
#include <string>
#include <iostream>
#include "Auxiliaries.h"
#include "Matrix.h"

namespace mtm
{
    // ********* Helper functions **********
    template<class T>
    int Matrix<T>::calcMatSize(const mtm::Dimensions &dim) const
        {
            if (dim.getCol() < 0 || dim.getRow() < 0)
                throw IllegalInitialization();
            return dim.getCol() * dim.getRow();
        }
    
    template<class T>
    void Matrix<T>::copyMatrixValues(const Matrix &matrix)
        {
            int max_size = size();
            for (int i = 0; i < max_size; i++) //size is the amount of elements in *this
            {
                array[i] = matrix.array[i]; //Or maybe should use iterator?
            }
        }

    template<class T>
    void Matrix<T>::copyMatrixValues(const T &init_value)
        {
             int max_size = size();
            for (int i = 0; i <max_size; i++) //size is the amount of elements in *this
            {
                array[i] = init_value; //Or maybe should use iterator?
            }
        }
}