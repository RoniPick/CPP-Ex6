#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include <sstream>
#include <fstream>
using namespace std;

namespace zich{

    //constructor - reciving vector, rows and cols number
    Matrix::Matrix(vector<double> &matrix, size_t rows, size_t cols){
        if(rows<=0 || cols<=0){
            throw invalid_argument("Invalid input");
        }

        if(matrix.empty()){
            throw invalid_argument("Invalid input");
        }

        if(matrix.size() != (rows*cols)){
            throw invalid_argument("Wrong input, n*m is not even to the matrix size");
        }
        this->rows = rows;
        this->cols = cols;

        for (size_t i = 0; i < rows; i++) {
            this->matrix[i].resize(cols);
        }

        size_t cur=0;
        for(size_t i=0; i<rows; i++){
            for(size_t j=0; j<cols; j++){
                this->matrix[i][j] = matrix[cur];
                cur++;
            }
        }
        
    }

    //constructor - reciving only rows and cols number, for the metrix that i return in the functions 
    Matrix::Matrix(size_t rows, size_t cols){
        if(rows<=0 || cols<=0){
            throw invalid_argument("Invalid input");
        }

        this->rows = rows;
        this->cols = cols;

        for (size_t i = 0; i < rows; i++) {
            this->matrix[i].resize(cols);
        }

        for(size_t i=0; i<rows; i++){
            for(size_t j=0; j<cols; j++){
                this->matrix[i][j] = 0;
            }
        }
        
    }

    //copy constructor - reciving a pointer to the matrix
    Matrix::Matrix(const Matrix &mat){
        this->rows=mat.rows;
        this->cols=mat.cols;
        for (size_t i = 0; i < this->rows; i++){
            vector<double> r;
            for (size_t j = 0; j < this->cols; j++){
                r.push_back(mat.matrix[i][j]);
            }
            this->matrix.push_back(r); 
        }
        
    }

    //adding before the matrix returned, the adding operation is on the main matrix
    Matrix Matrix::operator++(){
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]++;
            }
        }

        return *this;
    }

    //adding after the matrix returned, the adding operation is on the main matrix but 
    //the returned matrix is a copy matrix with the values of the main matrix before the adding
    Matrix Matrix::operator++(int){
        Matrix m(*this);
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]++;
            }
        }

        return m;
    }

    //removing after the matrix returned, the removing operation is on the main matrix but 
    //the returned matrix is a copy matrix with the values of the main matrix before the removing
    Matrix Matrix::operator--(int){
        Matrix m(*this);
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]--;
            }
        }

        return m;
    }

    //removing before the matrix returned, the removing operation is on the main matrix
    Matrix Matrix::operator--(){
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]--;
            }
        }

        return *this;
    }

    //function that checking if the matrixs are the same size in order to do the operations
    bool sameSize(const Matrix &mat1, const Matrix &mat2){
        return (mat1.cols != mat2.cols || mat1.rows != mat2.rows);
    }

    /*
    in this function we operating each value in both matrixs and adding to the first matrix the value in the
    same location in the second materix
    */
    Matrix zich::operator+(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        size_t r = mat1.rows;
        size_t c = mat1.cols;
        Matrix m(r, c);
        for(size_t i=0; i<m.rows; i++){
            for(size_t j=0; j<m.cols; j++){
                m.matrix[i][j] = mat1.matrix[i][j] + mat2.matrix[i][j];
            }
        }
        return m;
    }

    /*
    in this function we operating each value in both matrixs and removing from the first matrix the value in the
    same location in the second materix
    */
    Matrix zich::operator-(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }

        Matrix m(mat1.rows, mat1.cols);
        for(size_t i=0; i<m.rows; i++){
            for(size_t j=0; j<m.cols; j++){
                m.matrix[i][j] = mat1.matrix[i][j] - mat2.matrix[i][j];
            }
        }
        return m;
    }

    /*
    in this function we operating each value in the given matrix and multing to each value by 1 
    */
    Matrix zich::operator+(Matrix &mat){
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] *= 1;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in the given matrix and multing to each value by -1 
    */
    Matrix zich::operator+(Matrix &mat){
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] *= (-1);
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in both matrixs and adding to the main matrix the value in the
    same location in the given materix
    */
    Matrix Matrix::operator+=(Matrix &mat){
        //checking if the matrixs are in the same size
        if(!sameSize(*this, mat)){
            throw invalid_argument("Matrixs are not in the same size");
        }

        //adding to the main matrix the values of the given matrix
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j] += mat.matrix[i][j];
            }
        }
        return *this;
    }

    /*
    in this function we operating each value in the given matrix and adding to each value the scalar value 
    */
    Matrix zich::operator+=(Matrix &mat, const int scalar){
        //adding to the main matrix the values of the given scalar
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] += scalar;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in the given matrix and removing to each value the scalar value 
    */
    Matrix zich::operator-=(Matrix &mat, const int scalar){
        //adding to the main matrix the values of the given scalar
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] -= scalar;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in both matrixs and removing from the main matrix the value in the
    same location in the given materix
    */
    Matrix Matrix::operator-=(Matrix &mat){
        //checking if the matrixs are in the same size
        if(!sameSize(*this, mat)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        
        //removing from the main matrix the values of the given matrix
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j] -= mat.matrix[i][j];
            }
        }
        return *this;
    }

    /*
    in this function we operating each value in the given matrix and multing to each value the scalar value 
    */
    Matrix zich::operator*=(Matrix &mat, const int scalar){
        //adding to the main matrix the values of the given scalar
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] *= scalar;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in both matrixs and compering if they are equals, if the are not equels
    the nested for loop will return false during the loop, if we didn't entered the if condition witch mean that 
    both of the matrix are even - we will return true
    */
    bool zich::operator==(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }

        for(size_t i=0; i<mat1.rows; i++){
            for (size_t j = 0; j < mat2.cols; j++){
                if(mat1.matrix[i][j] != mat2.matrix[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    /*
    in this function we operating each value in both matrixs and compering if they are equals, I created
    a counter that will count how many values from the matrixs are even, if the are equels we will add 1 to the 
    counter, then we have an if condition witch check if the number of even numbers in the matrixs is equal
    to the size of the matrix, if it is equals it means that the matrixs are equals - we will return false,
    else if the counter is smaller we will return true 
    */
    bool zich::operator!=(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }

        size_t count = 0;
        for(size_t i=0; i<mat1.rows; i++){
            for (size_t j = 0; j < mat2.cols; j++){
                if(mat1.matrix[i][j] == mat2.matrix[i][j]){
                    count++;
                }
            }
        }
        return count == (mat1.cols*mat2.rows);
    }

    /*
    in this function we operating each value in both matrixs and adding each value of each matrix to a counter that
    we created for it, count1 calculate mat1 values and count1 calculate mat1 values, 
    after we calculate the values of the two matrixs we will check - if count1 is bigger then count2 we will 
    return true, else false 
    */
    bool zich::operator>(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        size_t count1 = 0;
        size_t count2 = 0;
        for(size_t i=0; i<mat1.rows; i++){
            for (size_t j=0; j<mat1.cols; j++){
                count1 += mat1.matrix[i][j];
                count2 += mat2.matrix[i][j];
            }
        }
        return count1 > count2;
    }

    /*
    in this function we operating each value in both matrixs and adding each value of each matrix to a counter that
    we created for it, count1 calculate mat1 values and count1 calculate mat1 values, 
    after we calculate the values of the two matrixs we will check - if count1 is bigger then or equals to count2 we
    will return true, else false 
    */
    bool zich::operator>=(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        size_t count1 = 0;
        size_t count2 = 0;
        for(size_t i=0; i<mat1.rows; i++){
            for (size_t j=0; j<mat1.cols; j++){
                count1 += mat1.matrix[i][j];
                count2 += mat2.matrix[i][j];
            }
        }
        return count1 >= count2;
    }

    /*
    in this function we operating each value in both matrixs and adding each value of each matrix to a counter that
    we created for it, count1 calculate mat1 values and count1 calculate mat1 values, 
    after we calculate the values of the two matrixs we will check - if count1 is smaller then count2 we
    will return true, else false 
    */
    bool zich::operator<(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        size_t count1 = 0;
        size_t count2 = 0;
        for(size_t i=0; i<mat1.rows; i++){
            for (size_t j=0; j<mat1.cols; j++){
                count1 += mat1.matrix[i][j];
                count2 += mat2.matrix[i][j];
            }
        }
        return count1 < count2;
    }

    /*
    in this function we operating each value in both matrixs and adding each value of each matrix to a counter that
    we created for it, count1 calculate mat1 values and count1 calculate mat1 values, 
    after we calculate the values of the two matrixs we will check - if count1 is smaller then or equals to count2 we
    will return true, else false 
    */
    bool zich::operator<=(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        size_t count1 = 0;
        size_t count2 = 0;
        for(size_t i=0; i<mat1.rows; i++){
            for (size_t j=0; j<mat1.cols; j++){
                count1 += mat1.matrix[i][j];
                count2 += mat2.matrix[i][j];
            }
        }
        return count1 <= count2;
    }

    /*
    in this function we operating 3 for loops, mult the matrixs values and adding it to a sum, after multing
    row and col we add it to the current location in the new matrix , at the end we will return the new natrix
    */
    Matrix zich::operator*(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(mat1.cols != mat2.rows){
            throw invalid_argument("Matrixs could not be multiplyed");
        }

        Matrix m(mat1.rows, mat2.cols);
        int sum = 0;
        for(size_t i=0; i<mat1.rows; i++){
            for(size_t j=0; j<mat2.cols; j++){
                for(size_t k=0; k<mat2.rows; k++){
                    sum += (int)(mat1.matrix[i][k] * mat2.matrix[k][j]);
                }
                m.matrix[i][j] = sum;
                sum = 0;
            }    
        }
        return m;
    }

    /*
    in this function we operating each value in the given matrixs and multing the value in the current location
    in the given materix by the scalar value, we will use this function is we reciving the scalar first
    */
    Matrix zich::operator*(const double scalar, const Matrix &mat){
        Matrix m(mat.rows, mat.cols);
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                m.matrix[i][j] = mat.matrix[i][j] * scalar;
            }
        }
        return m;
    }

    /*
    in this function we operating each value in the given matrixs and multing the value in the current location
    in the given materix by the scalar value, we will use this function is we reciving the matrix first
    */
    Matrix zich::operator*(const Matrix &mat, const double scalar){
        Matrix m(mat.rows, mat.cols);
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                m.matrix[i][j] = mat.matrix[i][j] * scalar;
            }
        }
        return m;
    }

    istream& operator>>(istream &in, const Matrix &mat){
        return in;
        }

    ostream& operator<<(ostream &out, const Matrix &mat){
        return out;
        }
    }