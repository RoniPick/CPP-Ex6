#include "doctest.h"
#include "Matrix.hpp"

using namespace zich;
using namespace std;


TEST_CASE("Good input"){
    //operator ==
    vector<double> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<double> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix mat1(vec1, 3, 3);
    Matrix mat2(vec2, 3, 3);
    CHECK(mat1 == mat2);

    //operator !=
    vector<double> vec3 = {1, 2, 3, 4, 5, 7, 6, 8, 9};
    Matrix mat3(vec3, 3, 3);
    CHECK(mat1 != mat3);

    //operator == and *
    vector<double> vec4 = {1, 0, 0, 0, 1, 0};
    vector<double> vec5 = {3, 0, 0, 0, 3, 0};
    Matrix mat4(vec4, 3, 2);
    Matrix mat5(vec5, 3, 2);
    CHECK((3*mat4) == mat5);
    CHECK((mat5*1) == mat5);

    //operator == and + 
    vector<double> vec6 = {5, 4, 3, 2, 1, 0, -1, -2, -3};
    vector<double> vec7 = {6, 6, 6, 6, 6, 6, 6, 6, 6};
    Matrix mat6(vec6, 3, 3);
    Matrix mat7(vec7, 3, 3);
    CHECK(mat6+mat1 == mat7); //mat1 = 45, mat6 = 9, mat7 = 54

    //operator < and >
    vector<double> vec8 = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    Matrix mat8(vec8, 3, 3);
    CHECK(mat1 < mat8);  //mat1 = 45, mat8 = 54
    CHECK(mat4 < mat5); // mat4 = 2, mat5 = 6
    CHECK(mat8 > mat6); // mat8 = 54, mat6 = 9
    CHECK(mat7 > mat1); // mat7 = 54, mat5 = 45

    //operator >= and <=
    CHECK(mat7 <= mat8); // mat7 = 54, mat8 = 54
    CHECK(mat7 >= mat8); // mat7 = 54, mat8 = 54
    CHECK(mat1 <= mat2); // mat7 = 45, mat8 = 45
    CHECK(mat1 >= mat2); // mat7 = 45, mat8 = 45

    //operator ++ and --(before and after the matrix)
    vector<double> vec9 = {1, 0, 0, 1};
    vector<double> vec10 = {2, 1, 1, 2};
    vector<double> vec11 = {1, 0, 0, 1};
    Matrix mat9(vec9, 2, 2);
    Matrix mat10(vec10, 2, 2);
    Matrix mat11(vec11, 2, 2);
    ++mat9;
    CHECK(mat9 == mat10); //returning the matrix after adding 1
    --mat9;
    CHECK(mat9 == mat11); //returning the matrix after removing 1

    vector<double> vec12 = {7, 7, 7, 7, 7, 7, 7, 7, 7};
    vector<double> vec13 = {6, 6, 6, 6, 6, 6, 6, 6, 6};
    Matrix mat12(vec12, 3, 3);
    Matrix mat13(vec13, 3, 3);
    // mat7 = {6, 6, 6, 6, 6, 6, 6, 6, 6};
    CHECK(mat13 == mat7); //returning the matrix before adding 1
    mat13++;
    CHECK(mat13 == mat12); //the matrix after adding 1 in the prev test
    mat13--;
    CHECK(mat13 == mat7); //the matrix after removing 1 in the prev test

    //operator += and -=
    vector<double> vec14 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> vec15 = {5, 4, 4, 4, 5, 4, 4, 4, 5};
    vector<double> vec16 = {4, 3, 3, 3, 4, 3, 3, 3, 4};
    vector<double> vec17 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix mat14(vec14, 3, 3);
    Matrix mat15(vec15, 3, 3);   
    Matrix mat16(vec16, 3, 3);
    Matrix mat17(vec17, 3, 3);
    vector<double> vt1 = {4, 4, 4, 4, 4, 4, 4, 4, 4};
    vector<double> vt2 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    vector<double> vt3 = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    Matrix mt1(vt1, 3, 3);   
    Matrix mt2(vt2, 3, 3);
    Matrix mt3(vt3, 3, 3);
    mat14+=mt1;
    CHECK(mat14 == mat15);
    mat14-=mt2;
    CHECK(mat14 == mat16);
    mat14-=mt3;
    CHECK(mat14 == mat17);

    //operator *=
    vector<double> vec18 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    vector<double> vec19 = {7, 7, 7, 7, 7, 7, 7, 7, 7};
    vector<double> vec20 = {-7, -7, -7, -7, -7, -7, -7, -7, -7};
    Matrix mat18(vec18, 3, 3);
    Matrix mat19(vec19, 3, 3);
    Matrix mat20(vec20, 3, 3);
    mat18*=7;
    CHECK(mat18 == mat19);
    mat18*=-1;
    CHECK(mat18 == mat20);

    // matrix mult
    vector<double> vec21 = {3, -1, 0, 1, 1, 0, 0, 3, 3};
    vector<double> vec22 = {20, 1, 0};
    Matrix mat21(vec21, 3, 3);
    Matrix mat22(vec22, 3, 1);
    vector<double> vec23 = {59, 21, 3};
    Matrix mat23(vec23, 3, 1);
    Matrix ans(3, 1);
    ans = mat21*mat22;
    CHECK(ans == mat23);

    // unari operators
    vector<double> vec24 = {7, 7, 7, 7, 7, 7, 7, 7, 7};
    vector<double> vec25 = {7, 7, 7, 7, 7, 7, 7, 7, 7};
    vector<double> vec26 = {-7, -7, -7, -7, -7, -7, -7, -7, -7};
    Matrix mat24(vec24, 3, 3);
    Matrix mat25(vec25, 3, 3);
    Matrix mat26(vec26, 3, 3);
    +mat24;
    CHECK(mat24==mat25);
    -mat25;
    CHECK(mat25==mat26);
}


TEST_CASE("Bad input and wrong checks"){

    //compering that will fail:
    vector<double> v1 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> v2 = {1, 0, 0, 0, 2, 0, 0, 0, 1};
    Matrix m1(v1, 3, 3);
    Matrix m2(v2, 3, 3);
    CHECK_FALSE(m1 == m2);

    vector<double> v3 = {4, 0, 0, 0, 4, 0, 0, 0, 4};
    Matrix m3(v3, 3, 3);
    CHECK_FALSE(m1 == m3); // m1 = 3, m3 = 12
    CHECK_FALSE(m1 >= m3);
    CHECK_FALSE(m1*2 == m3);

    //v3 size is 3*3, the given size is 2*3
    CHECK_THROWS(Matrix m4(v3, 2, 3));

    //v3 size is 3*3, the given size is 3*0
    CHECK_THROWS(Matrix m5(v3, 3, 0));

    vector<double> v4 = {1, 0, 0, 1};
    Matrix m6(v4, 2, 2);

    // the size of m1 is not equal to the size of m6, any of this function will fail (because m1:3*3 and m6:2*2) :
    CHECK_THROWS(if(m6 == m1){}); 
    CHECK_THROWS(if(m6 != m1){}); 
    CHECK_THROWS(if(m6 <= m1){});
    CHECK_THROWS(if(m6 < m1){});
    CHECK_THROWS(if(m6 > m1){});
    CHECK_THROWS(if(m6 >= m1){});
    CHECK_THROWS(m6 + m1);
    CHECK_THROWS(m6 * m1);
    CHECK_THROWS(m6 - m1);

    //adding 1 after the compering
    vector<double> v5 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> v6 = {2, 1, 1, 1, 2, 1, 1, 1, 2};
    Matrix m7(v5, 3, 3);
    Matrix m8(v6, 3, 3);
    CHECK_FALSE(m7 == m8); 
    m7++;
    CHECK(m7 == m8); 



}