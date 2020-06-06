#include <string>
#include <iostream>
#include "IntMatrix.h"
#include "Auxiliaries.h"
#include "Auxiliaries.cpp" //REMOVE BEFORE FLIGHT!!!!!!!!!
using mtm::Dimensions;
using mtm::IntMatrix;
using std::cout;
using std::cin;
using std::endl;

#define MAX_MATRICES 1000
IntMatrix matrices[MAX_MATRICES];
int current_matrix_num =0;

void printMatrixIterator(IntMatrix mat)
{
    /*
    IntMatrix::iterator it_begin = mat.begin(); // it_begin is a new iterator pointing to first element
    // (mat_3[0][0], which is equal to 1)
    IntMatrix::iterator it_end = mat.end(); 
    int width = mat.width();
    int count=0;
    while (it_begin!=it_end)
    {
        cout << *it_begin << " ";
        it_begin++;
        count++;
        if(count == width)
        {
            count << std::endl;
        }
    }
    count << std::endl;
    */
}
void CreateMatrix()
{
     cout << "Which matrix would you like to remove? [" <<0<<"-"<<current_matrix_num<<"] " ;
    int matrix_num =0;
    cin >> matrix_num;
    matrices[matrix_num] = matrices[current_matrix_num];
    current_matrix_num--;
    
}

void CreateMatrix()
{
    cout << "How many matrices would you like to create? " ;
    int num_of_matrices =0;
    cin >> num_of_matrices;
    for (int i = 0; i < num_of_matrices; i++)
    {
        int rows=0,columns=0, def_val=0;
         cout << "Enter matrix N."  << i <<" rows: ";
         cin >> rows;
         cout << "Enter matrix N."  << i <<" columns: ";
         cin >> columns;
         cout << "Enter initial values: "  << i;
        cin >> def_val;
         Dimensions d(rows,columns);
         IntMatrix mat(d); // No usage
         IntMatrix mat(d,def_val);

        matrices[current_matrix_num] = mat;
        current_matrix_num++;
        cout << "Created matrix "  << i;
    }
    
}
void RunTestCases()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
                Dimensions d(0,0);
    IntMatrix mat(d);
    IntMatrix mat(d,1);
    mat = mat+mat;
    mat = mat-mat;
    mat = mat + 0;
    mat = mat += 0;
    mat = 0 + mat;
    mat.transpose();
        }
        
    }
    


}
int main(){
    cout << "Int Matrix Tester V1.0 C Shai Yehezkel" << endl;
    cout << "What woud you like to do?" << endl;
    
}