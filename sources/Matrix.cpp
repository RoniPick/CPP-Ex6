#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include <sstream>
#include <fstream>
using namespace std;

/*
an help function in order to split the given string in the >> operator into rows string,
spliting when we see ", ", then we have a new row
*/
vector<string> tokenize(const string &s, const string &del = ", "){
    vector<string> ans;

    size_t start = 0;
    size_t end = s.find(del);
    while (end != -1) {
        ans.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    ans.push_back(s.substr(start, end - start));

    return ans;
}

namespace zich{

    //constructor - reciving vector, rows and cols number
    Matrix::Matrix(const vector<double> &matrix, int rows, int cols){
        if(rows<=0 || cols<=0){
            throw invalid_argument("Invalid input");
        }

        if(matrix.empty()){
            throw invalid_argument("Invalid input");
        }

        if(matrix.size() != (rows*cols)){
            throw invalid_argument("Wrong input, n*m is not even to the matrix size");
        }
        this->rows = (size_t)rows;
        this->cols = (size_t)cols;

        this->matrix.resize((size_t)rows);

        for (size_t i = 0; i < rows; i++) {
            this->matrix[i].resize((size_t)cols);
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
    Matrix::Matrix(int rows, int cols){
        if(rows<=0 || cols<=0){
            throw invalid_argument("Invalid input");
        }

        this->rows = (size_t)rows;
        this->cols = (size_t)cols;

        this->matrix.resize((size_t)rows);

        for (size_t i = 0; i < rows; i++) {
            this->matrix[i].resize((size_t)cols);
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

        vector<vector<double>> m(rows, vector<double>(cols, 0.0));

        for (size_t i = 0; i < this->rows; i++){
            for (size_t j = 0; j < this->cols; j++){
                m[i][j] = mat.matrix[i][j];
            } 
        }
         this->matrix = m;
        
    }

    Matrix::~Matrix(){

    }

    //adding before the matrix returned, the adding operation is on the main matrix
    Matrix& Matrix::operator++(){
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]++;
            }
        }

        return *this;
    }

    /*
    adding after the matrix returned, the adding operation is on the main matrix but 
    the returned matrix is a copy matrix with the values of the main matrix before the adding
    */
    Matrix Matrix::operator++(int){
        Matrix m(*this);
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]++;
            }
        }

        return m;
    }

    /*
    removing after the matrix returned, the removing operation is on the main matrix but 
    the returned matrix is a copy matrix with the values of the main matrix before the removing
    */
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
    Matrix& Matrix::operator--(){
        for(size_t i=0; i<this->rows; i++){
            for(size_t j=0; j<this->cols; j++){
                this->matrix[i][j]--;
            }
        }

        return *this;
    }

    //function that checking if the matrixs are the same size in order to do the operations
    bool sameSize(const Matrix &mat1, const Matrix &mat2){
        return (mat1.cols == mat2.cols && mat1.rows == mat2.rows);
    }

    /*
    in this function we operating each value in both matrixs and adding to the new matrix 
    the value in the same location in the first plus the second matrix
    */
    Matrix operator+(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }
        size_t row = mat1.rows;
        size_t col = mat1.cols;
        Matrix m(row, col);
        for(size_t i=0; i<m.rows; i++){
            for(size_t j=0; j<m.cols; j++){
                m.matrix[i][j] = mat1.matrix[i][j] + mat2.matrix[i][j];
            }
        }
        return m;
    }

    /*
    in this function we operating each value in both matrixs and adding to the new matrix 
    the value in the same location in the first - the second matrix
    */
    Matrix operator-(const Matrix &mat1, const Matrix &mat2){
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
    in this function we creating a new matrix from the current matrix, as it is, unary + 
    */
    Matrix Matrix::operator+(){
         vector<double> vec;
         size_t k=0;
         for(size_t i=0; i<this->rows; i++){
             for(size_t j=0; j<this->cols; j++){
                 vec.push_back(this->matrix[i][j]);
             }
         }
         
         return Matrix(vec,this->rows,this->cols);
    }

    /*
    in this function we creating a new matrix from the current matrix and mult it by -1 
    */
    Matrix Matrix::operator-(){
     vector<double> vec;
         size_t k=0;
         for(size_t i=0; i<this->rows; i++){
             for(size_t j=0; j<this->cols; j++){
                 vec.push_back(-this->matrix[i][j]);
             }
         }
         
         return Matrix(vec,this->rows,this->cols);
    }

    /*
    in this function we operating 2 for loops, each value we copy from the given matix
    into the origin matrix, at the end we will return the origin matrix 
    with the given matrix values
    */
    Matrix& Matrix::operator=(const Matrix& mat){
        this->matrix.clear();
        this->matrix.resize(mat.rows);
        for(size_t i=0; i<mat.rows; i++){
            matrix[i].resize(mat.cols);
            for(size_t j=0; j<mat.cols; j++){
                this->matrix[i][j] = 0;
            }
        }

        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                this->matrix[i][j] = mat.matrix[i][j];
            }    
        }
        return *this;
    }
   
    /*
    in this function we operating each value in both matrixs and adding to the main matrix the
    value in the same location in the given materix
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
    in this function we operating each value in the given matrix and adding to each value 
    the scalar value 
    */
    Matrix operator+=(Matrix &mat, const int scalar){
        //adding to the main matrix the values of the given scalar
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] += scalar;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in the given matrix and removing to each value
    the scalar value 
    */
    Matrix operator-=(Matrix &mat, const int scalar){
        //adding to the main matrix the values of the given scalar
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] -= scalar;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in both matrixs and removing from the main matrix 
    the value in the same location in the given matrix
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
    in this function we operating each value in the given matrix and multing each value with
    the scalar value 
    */
    Matrix operator*=(Matrix &mat, const int scalar){
        //adding to the main matrix the values of the given scalar
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                mat.matrix[i][j] *= scalar;
            }
        }
        return mat;
    }

    /*
    in this function we operating each value in both matrixs and compering if they are equals, 
    if the are not equels the nested for loop will return false during the loop, if we didn't
    entered the if condition which mean that both of the matrix are even - we will return true
    */
    bool operator==(const Matrix &mat1, const Matrix &mat2){
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
    in this function we use the == operator and return the not value, we check if each value
    in both matix are even, if the matrixs are even the == operator will return true and we 
    will return false, alse the operator will return false(not even) and we will return true
    */
    bool operator!=(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(!sameSize(mat1,mat2)){
            throw invalid_argument("Matrixs are not in the same size");
        }

        return !(mat1==mat2);
    }

    /*
    in this function we operating each value in both matrixs and adding each value of each 
    matrix to a counter that we created for it, count1 calculate mat1 values and count1
    calculate mat1 values, after we calculate the values of the two matrixs we will 
    check - if count1 is bigger then count2 we will return true, else false 
    */
    bool operator>(const Matrix &mat1, const Matrix &mat2){
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
    in this function we operating each value in both matrixs and adding each value of each 
    matrix to a counter that we created for it, count1 calculate mat1 values and count1 
    calculate mat1 values, after we calculate the values of the two matrixs we will 
    check - if count1 is bigger then or equals to count2 we will return true, else false 
    */
    bool operator>=(const Matrix &mat1, const Matrix &mat2){
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
    in this function we operating each value in both matrixs and adding each value of each
    matrix to a counter that we created for it, count1 calculate mat1 values and count1 
    calculate mat1 values, after we calculate the values of the two matrixs we will 
    check - if count1 is smaller then count2 we will return true, else false 
    */
    bool operator<(const Matrix &mat1, const Matrix &mat2){
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
    in this function we operating each value in both matrixs and adding each value of each 
    matrix to a counter that we created for it, count1 calculate mat1 values and count1 
    calculate mat1 values, after we calculate the values of the two matrixs we will 
    check - if count1 is smaller then or equals to count2 we will return true, else false 
    */
    bool operator<=(const Matrix &mat1, const Matrix &mat2){
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
    in this function we operating 3 for loops, mult the matrixs values and adding it to a sum,
    after multing row and col we add it to the current location in the new matrix , at the
     end we will return the new matrix
    */
    Matrix operator*(const Matrix &mat1, const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(mat1.cols != mat2.rows){
            throw invalid_argument("Matrixs could not be multiplyed");
        }

        Matrix m(mat1.rows, mat2.cols);

        for(size_t i=0; i<mat1.rows; i++){
            for(size_t j=0; j<mat2.cols; j++){
                m.matrix[i][j] = 0;
                for(size_t k=0; k<mat2.rows; k++){
                    m.matrix[i][j] += mat1.matrix[i][k] * mat2.matrix[k][j];
                }
            }    
        }
        return m;
    }

    /*
    in this function we create an help matrix, mult the given matrixs values and adding 
    it to this help matrix, after multing the matrixs we copy the new matrix
    to the first matrix and return it (this)
    */
    Matrix Matrix::operator*=(const Matrix &mat2){
        //checking if the matrixs are in the same size
        if(this->cols != mat2.rows){
            throw invalid_argument("Matrixs could not be multiplyed");
        }
        Matrix m = (*this)*mat2;
        *this = m;
        return *this;
    }

    /*
    in this function we operating each value in the given matrixs and multing the value in 
    the current location in the given materix by the scalar value, we will use this function
     is we reciving the scalar first
    */
    Matrix operator*(const double scalar, const Matrix &mat){
        Matrix m(mat.rows, mat.cols);
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                m.matrix[i][j] = mat.matrix[i][j] * scalar;
            }
        }
        return m;
    }

    /*
    in this function we operating each value in the given matrixs and multing the value in 
    the current location in the given materix by the scalar value, we will use this function 
    is we reciving the matrix first
    */
    Matrix operator*(const Matrix &mat, const double scalar){
        Matrix m(mat.rows, mat.cols);
        for(size_t i=0; i<mat.rows; i++){
            for(size_t j=0; j<mat.cols; j++){
                m.matrix[i][j] = mat.matrix[i][j] * scalar;
            }
        }
        return m;
    }

    istream& operator>>(istream &in, Matrix &mat){
        // [a b c], [a b c], [a b c]
        string ans;
        string temp;
        //adding the given stream into a string
        while(getline(in, temp)){
            ans += temp;
        }
        if(ans[0]!='[' || ans[ans.length()-1]!=']'){
            throw invalid_argument("Invalid input");
        }

        //check if the input is valid
        for(size_t i=0; i<ans.length()-1; i++){
             // [], []
            if(ans[i] == ',' && ans[i+1] != ' '){
                throw invalid_argument("Invalid input");
            }
            // [ ]
            if(ans[i] == '[' && ans[i+1] == ' '){
                throw invalid_argument("Invalid input");
            }
            // '   '
            if(ans[i] == ' ' && ans[i+1] == ' '){
                throw invalid_argument("Invalid input");
            }
            // , []
            if(i>=1 && ans[i-1] == ',' && ans[i] == ' ' && ans[i+1] != '['){
                throw invalid_argument("Invalid input");
            }
            // ],  
            if(ans[i] == ']' && ans[i+1]!= ',' && i<ans.length()-2){
                throw invalid_argument("Invalid input");
            }
        }
        
        size_t col=0;
        size_t row=0;

        vector<string> token = tokenize(ans);
        row = token.size();

        vector<double> vec;

        for(size_t i=0; i<token.size(); i++){
            vector<string> cur = tokenize(token[i].substr(1, token[i].length()-1)," ");
            col = cur.size();
            for(size_t j=0; j<cur.size(); j++){
                vec.push_back(stod(cur[j]));
            }
        }

        mat = Matrix(vec, row, col);
        return in;
        }


    ostream& operator<<(ostream &out, const Matrix &mat){
          for(size_t i=0; i< mat.rows; i++){
              out << '[';
            for(size_t j=0; j<mat.cols; j++){
                out << mat.matrix[i][j];
                if(j!=mat.cols-1){
                    out << ' ';
                }
                else{
                    out << ']';
                }
                
            }
            // if it is not the last row - we want /n
            if(i!=mat.rows-1){
                out << endl;
            }
            
        }
        return out;
        }
    }
