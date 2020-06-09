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
        /**
        * IntMatrix::&operator=(): assignment operator, assigns the given matrix to this
        *
        * @param matrix - The matrix to copy to this
        * @return
        * 	returns reference to the new copied matrix
        */
        IntMatrix &operator=(const IntMatrix &matrix); // Assignment operator
        /**
        * IntMatrix::&operator__(): execute the logical operation for every element in the matrix and creates a new matrix
        * in the same size. if the logical operation of the element was true then the element in the new_matrix is 1, otherwise the element is 0.
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

        int& operator()(const int row, const int column);
        const int& operator()(const int row, const int column) const;
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
        IntMatrix transpose() const;     

        static IntMatrix Identity(const int size);

        class iterator;
        /**
        * IntMatrix::begin/end(): creates an iterator for the given matrix and retets it to be the begin/end of the matrix
        *
        * @return
        * 	returns the new iterator
        */
        iterator begin();
        iterator end();

        /**
         * same as the end and begin, the difference is that the return iterator is constant and the matrix is constant
         */
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
        /**
        * iretaror::operator++(): promotes the iterator index by 1. 
        *
        * @return
        *  --The prefix increment returns the value of a variable after it has been incremented.
        *  --The postfix increment returns the value of a variable before it has been incremented. 
        */
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
    
    /**
    * operator+(): creates a new matrix with the current element value plus the num specified.
    *
    * @param num - The number to add to the exsisting value
    * @param mat1 - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    IntMatrix operator+(const int num, const IntMatrix & mat1) ;
    
    /**
    * operator+(): creates a new matrix with the current element value of mat1 plus the current element value of mat2.
    *
    * @param mat1 - The matrix to take the values from
    * @param mat2 - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    IntMatrix operator+(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric +
    
    /**
    * operator-(): creates a new matrix with the current element value of mat1 minus the current element value of mat2.
    *
    * @param mat1 - The matrix to take the values from
    * @param mat2 - The matrix to take the values from
    * @return
    * 	returns a copy of the new matrix
    */
    IntMatrix operator-(const IntMatrix & mat1, const IntMatrix & mat2); // Outside class to support symetric - 
    
    /**
    * all: checks if all the the matrix's values are different from 0
    * @return
    * 	True if all the the matrix's values are different from 0.
    *   False otherwise
    */
    bool all(const IntMatrix & mat);
    /**
    * any: checks if at least one of the matrix's values are different from 0.
    * @return
    * 	True if at least one of the matrix's values are different from 0.
    *   False otherwise
    */
    bool any(const IntMatrix & mat); 

   

} // namespace mtm

#endif //INT_MATRIX_H
