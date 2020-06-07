#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
namespace mtm {
    class IntMatrix {
    private:
        //Private fields
        int* array;
        mtm::Dimensions dim;

        // Helper Functions
        int calcMatSize(const mtm::Dimensions& dim) const;
        void copyMatrixValues(const IntMatrix& matrix);
        void copyMatrixValues(const int& init_value);

    public:

        // C'tor + D'tor
        IntMatrix(mtm::Dimensions dimensions,int init_number=0);
        IntMatrix(const IntMatrix &);                            // Copy constructor
        ~IntMatrix();                                            //Destructor

        // Operators
        IntMatrix &operator=(const IntMatrix &matrix); // Assignment operator
        IntMatrix operator<(const int &num) const;
        IntMatrix operator<=(const int &num) const;
        IntMatrix operator>(const int &num) const;
        IntMatrix operator>=(const int &num) const;
        IntMatrix operator==(const int &num) const;
        IntMatrix operator!=(const int &num) const;
        IntMatrix operator-() const;
        IntMatrix& operator+=(const int num);
        IntMatrix operator+(const int num) const;
        int& operator()(const int row, const int column);
        const int& operator()(const int row, const int column) const;
        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);


        int height() const;
        int width() const;
        int size() const;
        IntMatrix transpose() const;     

        static IntMatrix Identity(const int size);

        class Iterator;
    };
    class IntMatrix::Iterator // Copied
    {
        const IntMatrix *set;
        int index;
        Iterator(const IntMatrix *set, int index);
        friend class IntMatrix;

    public:
        const int &operator*() const;
        Iterator &operator++();
        Iterator operator++(int);
        bool operator==(const Iterator &it) const;
        bool operator!=(const Iterator &it) const;
        Iterator(const Iterator &) = default;
        Iterator &operator=(const Iterator &) = default;
    }; // Copied

    enum MATRIX_STATUS {ALL_ONES = -1, ONE_EXSISTS, ALL_ZEROS};
    static MATRIX_STATUS checkMatrix(const IntMatrix& mat);

    IntMatrix operator+(const int num, const IntMatrix & mat1) ;
    IntMatrix operator+(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric +
    IntMatrix operator-(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric - 
    bool all(const IntMatrix & mat);
    bool any(const IntMatrix & mat); 
  

} // namespace mtm

#endif //INT_MATRIX_H
