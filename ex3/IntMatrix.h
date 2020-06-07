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
        IntMatrix operator-() const;
        IntMatrix& operator+=(const int num);
        int& operator()(const int row, const int column);
        const int& operator()(const int row, const int column) const;

        int height() const;
        int width() const;
        int size() const;
        IntMatrix transpose() const;
        

        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);
        IntMatrix operator+(const int num) const;
        static IntMatrix Identity(const int size);  
        static MATRIX_STATUS checkMatrix(const IntMatrix& mat);
    };

    IntMatrix operator+(const int num, const IntMatrix & mat1) ;
    IntMatrix operator+(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric +
    IntMatrix operator-(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric - 
    bool all(const IntMatrix & mat);
    bool any(const IntMatrix & mat); 
  

} // namespace mtm

#endif //INT_MATRIX_H
