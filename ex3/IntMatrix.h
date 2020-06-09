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
        /**
        * IntMatrix: creates a copy of the given new value - in order to save inside the node
        *    and replace the old value for the new value (frees the old value)
        *
        * @param old_val - The old value addres - if we want to replace an exsisting value , if this is a new value then old val is null
        * @param new_val - the address of the new value to put inside the node (value od key)
        * @return
        * 	true - if allocation succeeded 
        *   false - ifallocation failed 
        */
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

        class iterator;
        iterator begin();
        iterator end();

        
        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const;

        
    };
    class IntMatrix::iterator
    {
        IntMatrix *matrix;
        int index;
        iterator(IntMatrix *matrix, int index);
   
        friend class IntMatrix;

    public:
        int &operator*() const;
        iterator &operator++(); // Prefix
        iterator operator++(int); // Postfix
        bool operator==(const iterator &it) const;
        bool operator!=(const iterator &it) const;
        iterator(const iterator & it) = default; // Copy constructor
        iterator& operator=(const iterator & it) = default; // Assingment operator
        ~iterator() = default; // D'tor
       
        
    }; 
    class IntMatrix::const_iterator
    {
        const IntMatrix *matrix;
        int index;
        const_iterator(const IntMatrix *matrix, int index);      
        friend class IntMatrix;

    public:
        const int &operator*() const;
        const_iterator &operator++(); // Prefix
        const_iterator operator++(int); // Postfix
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
        const_iterator(const const_iterator & it) = default; // Copy constructor
        const_iterator& operator=(const const_iterator & it) = default; // Assingment operator
        ~const_iterator() = default; // D'tor
      
        
    }; 
    IntMatrix operator+(const int num, const IntMatrix & mat1) ;
    IntMatrix operator+(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric +
    IntMatrix operator-(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric - 
    bool all(const IntMatrix & mat);
    bool any(const IntMatrix & mat); 

   

} // namespace mtm

#endif //INT_MATRIX_H
