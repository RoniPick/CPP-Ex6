#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

namespace zich{
    class Matrix{
    private:
        size_t rows, cols;
        vector<vector<double>> matrix;

    public:
    //counstructors
        Matrix(vector<double> &matrix, size_t rows, size_t cols);
        ~Matrix();
        Matrix(size_t rows, size_t cols);
        Matrix(const Matrix &mat);

        // + operations
        Matrix operator++(int);
        Matrix operator++();
        friend Matrix operator+(Matrix &mat);
        friend Matrix operator+(const Matrix &mat1, const Matrix &mat2);
        Matrix operator+=(Matrix &mat);
        friend Matrix operator+=(Matrix &mat, const int scalar);

        // - operartions
        Matrix operator--(int);
        Matrix operator--();
        friend Matrix operator-(const Matrix &mat1, const Matrix &mat2);
        friend Matrix operator-(Matrix &mat);
        Matrix operator-=(Matrix &mat);
        friend Matrix operator-=(Matrix &mat, const int scalar);
        friend Matrix operator-(const Matrix &mat);

        // * operations
        friend Matrix operator*=(Matrix &mat, const int scalar);
        friend Matrix operator*(const Matrix &mat1, const Matrix &mat2);
        friend Matrix operator*(const double scalar, const Matrix &mat);
        friend Matrix operator*(const Matrix &mat, const double scalar);

        //help function
        friend bool sameSize(const Matrix &mat1, const Matrix &mat2);

        //compering operations
        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        friend bool operator!=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>(const Matrix &mat1, const Matrix &mat2);

        //input output operations
        friend istream& operator>>(istream &in, const Matrix &mat);
        friend ostream& operator<<(ostream &out, const Matrix &mat);

    };
    
    

}
