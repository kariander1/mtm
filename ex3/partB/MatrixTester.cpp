#include <string>
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "../partA/IntMatrix.h"
#include "Auxiliaries.h"
using mtm::Dimensions;
using mtm::IntMatrix;
using mtm::Matrix;
using std::cin;
using std::cout;
using std::endl;
class Square
{
public:
    int operator()(int val)
    {
        return val * val;
    }
};
template <class T>
class Non
{
public:
    T operator()(T val)
    {
        return -val;
    }
};

template <class T>
class NullFunctor
{
public:
    T operator()(T val)
    {
        return val;
    }
};


class NullClass
{

private:
    int val=0;
public:
    NullClass(/* args */) = default;
    ~NullClass() = default;
    NullClass &operator=(const NullClass &it) = default;
    NullClass &operator=(NullClass &it) = default;
    NullClass(const NullClass &matrix) = default;
    NullClass(NullClass &matrix) = default;
    bool operator<(const NullClass &value) const
    {
       return val<value.val;
    }
        NullClass operator+=(const NullClass &value) const
    {
        return NullClass();
    }
    bool operator==(const NullClass &value) const
    {
        return val==value.val;
    }
    NullClass operator-() const{
        return NullClass();
    }
    operator bool() const
    {
        return true;
    }
};
   NullClass operator+(const NullClass &matrix_a, const NullClass &matrix_b)
   {
       return NullClass();
   }
       std::ostream &operator<<(std::ostream &os, const NullClass &matrix)
    {
        return os;
    }
int main()
{
    
    cout << "Matrix Tester V1.0 C Shelly Francis & Shai Yehezkel" << endl;


    Dimensions dim(2, 3);
    Matrix<IntMatrix> mat_of_mats(dim);
    
    dim = Dimensions(2, 2);
    Matrix<IntMatrix>::iterator it = mat_of_mats.begin();
    int count = 0;
    for (; it != mat_of_mats.end(); ++it, ++count)
    {
        *it = IntMatrix(dim, count);
    }
    cout << mat_of_mats;
    mat_of_mats(1, 2) = 1 + mat_of_mats(1, 2) + 1 + (-IntMatrix(dim, 8));
    cout << mat_of_mats(1, 2);

    Matrix<IntMatrix> neg_mats = mat_of_mats.apply(Non<IntMatrix>());
    cout << neg_mats;
    mat_of_mats = neg_mats;

    Matrix<bool> new_matrix(dim, 5);
    Matrix<NullClass> nulls_matrix(dim);
    Matrix<NullClass> nulls_matrix_copy = nulls_matrix;
    nulls_matrix = nulls_matrix_copy;
    nulls_matrix_copy < NullClass();
    nulls_matrix_copy > NullClass();
    nulls_matrix_copy <= NullClass();
    nulls_matrix_copy == NullClass();
    nulls_matrix_copy != NullClass();
    nulls_matrix_copy >= NullClass();
    nulls_matrix_copy + nulls_matrix_copy;
    -nulls_matrix_copy;
    nulls_matrix_copy+NullClass();
    nulls_matrix_copy+=NullClass();
    nulls_matrix_copy(0,0);
    nulls_matrix_copy.height();
    nulls_matrix_copy.size();
    nulls_matrix_copy.width();
    nulls_matrix_copy.transpose();
     //Matrix<int> mat_2 = Matrix<int>::Diagonal(2,-1);
    nulls_matrix_copy = Matrix<NullClass>::Diagonal(2,NullClass());
    nulls_matrix_copy.apply(NullFunctor<NullClass>());
    Matrix<NullClass>::iterator null_class_it = nulls_matrix_copy.begin();
    for (; null_class_it != nulls_matrix_copy.end(); ++null_class_it)
    {
        *null_class_it = NullClass();
    }
    const  Matrix<NullClass> null_mat =nulls_matrix_copy;
    Matrix<NullClass>::const_iterator null_class_it_con = null_mat.begin();
    for (; null_class_it_con != null_mat.end(); ++null_class_it_con)
    {
        cout << *null_class_it_con;
    }
    cout << nulls_matrix_copy;

     (nulls_matrix_copy+=NullClass())+=NullClass();


    const Matrix<NullClass> const_mats(dim);
    Matrix<NullClass> const_mats_copy = const_mats;
    const_mats_copy = nulls_matrix_copy;
    const_mats_copy < NullClass();
    const_mats_copy > NullClass();
    const_mats_copy <= NullClass();
    const_mats_copy == NullClass();
    const_mats_copy != NullClass();
    const_mats_copy >= NullClass();
    -const_mats_copy;
    const_mats_copy+const_mats_copy;
    const_mats_copy+NullClass();
    const_mats_copy+=NullClass();
    const_mats_copy(0,0);
    const_mats_copy.height();
    const_mats_copy.size();
    const_mats_copy.width();
    const_mats_copy.transpose();
     //Matrix<int> mat_2 = Matrix<int>::Diagonal(2,-1);
    const_mats_copy = Matrix<NullClass>::Diagonal(2,NullClass());
    const_mats_copy.apply(NullFunctor<NullClass>());

    cout << const_mats_copy;



    Dimensions dim_1(2,3);
    Dimensions dim_2(-2,3);
    Dimensions dim_3(3,2);
    NullClass placeholder = NullClass();
    try{
        const Matrix<NullClass> mat_1(dim_2,placeholder);
    } catch(Matrix<NullClass>::IllegalInitialization& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        Matrix<NullClass> mat_1(dim_1,placeholder);
        const Matrix<NullClass> mat_2((mat_1+NullClass()+mat_1));
        const Matrix<NullClass> mat_3(mat_1.transpose());
        std::cout<<mat_2;
        Matrix<NullClass> mat_4=mat_1+mat_3;
    } catch(Matrix<NullClass>::DimensionMismatch& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        const Matrix<NullClass> mat_1 = Matrix<NullClass>::Diagonal(2,placeholder);
        Matrix<NullClass> mat_2 = Matrix<NullClass>::Diagonal(2,placeholder);
        std::cout<<any(mat_1)<<" "<<any(mat_1-mat_2)<<" "<<all(mat_1+mat_2+placeholder)<<std::endl;
        std::cout<<(-mat_2)(1,1)<<(-mat_2)(2,2)<<std::endl;
    } catch(Matrix<NullClass>::AccessIllegalElement& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        Matrix<NullClass> mat_1(dim_1);
        Matrix<NullClass>::iterator it=mat_1.begin();
        for(;it!=mat_1.end();++it){
            *it=placeholder;
        }
        std::cout<<(mat_1>=placeholder);
        it++;
        std::cout<<(mat_1==placeholder);
        std::cout << "______________ shelly tests ______________" << std::endl;
        std::cout<<(mat_1) <<std::endl;
        std::cout<<(mat_1!=placeholder) <<std::endl;
        std::cout<<(mat_1<placeholder) <<std::endl;
        std::cout<<(mat_1>placeholder) <<std::endl;
        std::cout<<(mat_1<=placeholder) <<std::endl;
        *it;
    } catch(Matrix<NullClass>::AccessIllegalElement& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        const Matrix<NullClass> mat_1(dim_1,placeholder);
        const Matrix<NullClass> mat_2=mat_1.apply(NullFunctor<NullClass>());
        std::cout<<mat_1;
        std::cout<<mat_2(1,2)<<std::endl;
        Matrix<NullClass>::const_iterator it = mat_2.end();
        std::cout<<*it;
    } catch(Matrix<NullClass>::AccessIllegalElement& e){
        std::cout<<e.what()<<std::endl;
    }
}