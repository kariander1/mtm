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
        *   Constructors and Destructors:
        * 
        *   IntMatrix(mtm::Dimensions dimensions,int init_number=0):
        * 
        *   Default constructor, with given dimensions, enables to init the matrix values or default them to 0.
        *   @param dimensions - Dimensions to init the matrix
        *   @param init_number - Init value for matrix values
        *   @return
        * 	instance of a intMatrix
        * 
        *   IntMatrix(const IntMatrix &)
        * 
        *   Copy constructor, given a mtrix, this constructor copies all values by value to a new copy of matrix
        *   @param dimensions - Dimensions to init the matrix
        *   @param init_number - Init value for matrix values
        *   @return
        * 	instance of a intMatrix
        *  ~IntMatrix()
        *    and replace the old value for the new value (frees the old value)
        *
        *   ~IntMatrix()
        * 
        *   Destructor. Deletes allocated area.
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
        int& operator()(const int row, const int column);
        const int& operator()(const int row, const int column) const;

        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);


        int height() const;
        int width() const;
        int size() const;



        /**
        *   IntMatrix transpose()
        * 
        *   Transposes the matrix and switches position of values according to mathematical transpose operator.
        * 
        *   @return
        * 	Returns a COPY of the transposed matrix. does not change original matrix.
        */
        IntMatrix transpose() const;     
        /**
        *    static IntMatrix Identity
        * 
        *   Returns an identity cubic matrix defined by the size arguemnet
        * 
        *   @param size - size for dimensions of matrix. [ size X size ]
        *   @return
        * 	Returns a COPY of the transposed matrix. does not change original matrix.
        */
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

        IntMatrix *matrix; // pointer to matrix
        int index; // index indicating postion in matrix
        /**
        *    Default constructor
        * 
        *   Default constructor, initializing iterator attributes.
        * 
        *   @return
        * 	Reference the value at the current index
        */
        iterator(IntMatrix *matrix, int index);
   
        friend class IntMatrix; // For enabling accessing private fields of IntMatrix

    public:
        iterator(const iterator & it) = default; // Copy constructor
        iterator& operator=(const iterator & it) = default; // Assingment operator
        ~iterator() = default; // D'tor
        /**
        *    operator*()
        * 
        *   Returns by reference the value at the current index
        * 
        *   @return
        * 	Reference the value at the current index
        */
        int &operator*() const;
        iterator &operator++(); // Prefix
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
    /**
    *    Class const_iterator
    *   same as iterator, inly differences is in handling a const matrix.
    *   Differences in decalrations are in:
    * 
    *   Const IntMatrix *matrix
    *   const_iterator(const IntMatrix *matrix, int index);     
    *   const int &operator*() const;
    */
    class IntMatrix::const_iterator
    {
        const IntMatrix *matrix; // Const version of int matrix
        int index;
        const_iterator(const IntMatrix *matrix, int index); // Arguement is const for intMatrix
        friend class IntMatrix;

    public:
        const int &operator*() const; // Returns a const int
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
