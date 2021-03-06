#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"
namespace mtm {

     // Status for the all/any function to determine exact result
    enum MATRIX_STATUS
    {
        ALL_ZEROS = -1,        
        ONE_EXISTS,
        ALL_ONES
    };
  
    class IntMatrix {
    private:
        //Private fields
        int* array;
        mtm::Dimensions dim;

        // Helper Functions
          /**
        * checkMatrix: checks matrix with special properties for "any" and "all" functions
        * 
        *
        * @param matrix - The matrix to check the properites on
        * @return
        * 	enumerable value of MATRIX_STATUS, whether atrix contatins all ones, all zeroes, and if at least one.
        * NOTE: this function is declared here since return type is enum MATRIX_STATUS which
        * we didn't want to include in header file, so that the interface won't export MATRIX_STATUS
        * to users.
        */
        static MATRIX_STATUS checkMatrix(const IntMatrix &matrix);

    
        /**
        * IntMatrix::calcMatSize: gets the size of the matrix (rows*columns). 
        * @param dim - The dimentions of the matrix
        * @return
        * 	returns the size of the matrix (rows*columns) .
        */
        static int calcMatSize(const mtm::Dimensions& dim);
        /**
        * IntMatrix::copyMatrixValues: copys all the values from the given matrix
        * to the "this" matrix. 
        * @param matrix - The matrix to copy its values
        * @param array - Array to copy the values to
        * @return
        * 	Nothing.
        */
        static void copyMatrixValues(int* array,const IntMatrix& matrix);
        /**
        * IntMatrix::copyMatrixValues: sets all the values of the "this" matrix 
        * to the init_number.
        * @param init_value - The value to initiate the matrix with
        * @return
        * 	Nothing.
        */
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
        /**
        * IntMatrix::&operator=(): assignment operator, assigns the given matrix to this
        *
        * @param matrix - The matrix to copy to this
        * @return
        * 	returns reference to the new copied matrix
        */
        IntMatrix &operator=(const IntMatrix &matrix); // Assignment operator
        /**
        * IntMatrix::&operator__(): execute the logical operation for every element in the matrix and creates 
        * a new matrix in the same size. if the logical operation of the element was true then the element in
        * the new_matrix is 1, otherwise the element is 0.
        *
        * @param num - The number to compare to
        * @return
        * 	returns the new matrix with zeros and ones according to the output of the logic operation.
        */
        IntMatrix operator<(const int &num) const;
        IntMatrix operator<=(const int &num) const;
        IntMatrix operator>(const int &num) const;
        IntMatrix operator>=(const int &num) const;
        IntMatrix operator==(const int &num) const;
        IntMatrix operator!=(const int &num) const;
        /**
        * IntMatrix::&operator-(): creates a new matrix where each value is the negative of the current value.
        *
        * @return
        * 	returns the new matrix with negative values.
        */
        IntMatrix operator-() const;
        /**
        * IntMatrix::&operator+=(): adds to each element in the exsisting matrix the num specified.
      
        *
        * @param num - The number to add to the exsisting value
        * @return
        * 	returns a reference to the modified matrix
        */
        IntMatrix& operator+=(const int num);
        /**
        * IntMatrix::&operator+(): creates a new matrix with the current element value plus the num specified.
      
        *
        * @param num - The number to add to the exsisting value
        * @return
        * 	returns a copy of the new matrix
        */
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
        int& operator()(const int& row, const int& column);
        const int operator()(const int& row, const int& column) const;
        /**
        * IntMatrix::&operator<<(): Prints the given matrix.
        * @return
        * 	None
        */
        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);

        /**
        * IntMatrix::height/width/size(): calculates the height/width/size of the given matrix
        *
        * @return
        * 	returns the height/width/size of the given matrix
        */
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
        * 	Returns a new matrix with diagonal values
        */
        static IntMatrix Identity(const int size);

        class iterator;
        /**
        * IntMatrix::begin/end(): creates an iterator for the given matrix and retets it 
        * to be the begin/end of the matrix
        *
        * @return
        * 	returns the new iterator
        */
        iterator begin();
        iterator end();

        /*
         * same as the end and begin, the difference is that the return iterator 
         * is constant and the matrix is constant
         */
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
        /**
        * iterator::operator++(): promotes the iterator index by 1. 
        *
        * @return
        *  --The prefix increment returns the value of a variable after it has been incremented.
        *  --The postfix increment returns the value of a variable before it has been incremented. 
        */
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
    *   same as iterator, only differences is in handling a const matrix.
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
    
    /**
    * operator+(): creates a new matrix with the current element value plus the num specified.
    *
    * @param num - The number to add to the existing value
    * @param matrix_a - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    IntMatrix operator+(const int num, const IntMatrix & matrix_a) ;
    
    /**
    * operator+(): creates a new matrix with the current element value of matrix_a plus
    * the current element value of matrix_b.
    *
    * @param matrix_a - The matrix to take the values from
    * @param matrix_b - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    IntMatrix operator+(const IntMatrix & matrix_a, const IntMatrix & matrix_b); // Outside class to support symetric +
    
    /**
    * operator-(): creates a new matrix with the current element value of matrix_a
    * minus the current element value of matrix_b.
    *
    * @param matrix_a - The matrix to take the values from
    * @param matrix_b - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    IntMatrix operator-(const IntMatrix & matrix_a, const IntMatrix & matrix_b); // Outside class to support symetric - 
    
    /**
    * all: checks if all the the matrix's values are different from 0
    * @return
    * 	True if all the the matrix's values are different from 0.
    *   False otherwise
    */
    bool all(const IntMatrix & matrix);
    /**
    * any: checks if at least one of the matrix's values are different from 0.
    * @return
    * 	True if at least one of the matrix's values are different from 0.
    *   False otherwise
    */
    bool any(const IntMatrix & matrix); 

   

} // namespace mtm

#endif //INT_MATRIX_H
