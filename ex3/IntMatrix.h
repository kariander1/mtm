#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
namespace mtm {
    class IntMatrix {
    private:
        int* array;
        mtm::Dimensions dim;

        // Helper Functions
        int calcMatSize(const mtm::Dimensions& dim) const;
        void copyMatrixValues(const IntMatrix& matrix);
        void copyMatrixValues(const int& init_value);

    public:
        IntMatrix(mtm::Dimensions dimensions,int init_number=0);
        IntMatrix(const IntMatrix &);                            // Copy constructor
        ~IntMatrix();                                            //Destructor
        IntMatrix &operator=(const IntMatrix &matrix);
        IntMatrix operator<(const int &num) const;
        IntMatrix operator<=(const int &num) const;
        IntMatrix operator>(const int &num) const;
        IntMatrix operator>=(const int &num) const;
        IntMatrix operator==(const int &num) const;
        IntMatrix operator!=(const int &num) const;

        int height() const;
        int width() const;
        int size() const;

        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);
    };

    IntMatrix operator+(const IntMatrix &, const IntMatrix &); // Outside class to support symetric +
    IntMatrix operator-(const IntMatrix &, const IntMatrix &); // Outside class to support symetric +

    std::ostream &operator<<(std::ostream &os, const IntMatrix &mat) // Friend functions are in .h files?
    {

        os << mtm::printMatrix(mat.array, mat.dim);
        return os;
    }
} // namespace mtm

#endif //INT_MATRIX_H
