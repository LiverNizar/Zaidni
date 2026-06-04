#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class Matrix{
    private:
        int size;
        std::vector<std::vector<T> > coefficients;

    public:
        Matrix(int n): size(n), coefficients(n, std::vector<T>(n, {})) {}
        int Size(){return size;}
        void setValue(int row, int column, T value){
            coefficients[row - 1][column - 1] = value;
        }
        T getValue(int row, int column){
            return coefficients[row - 1][column - 1];
        }
        void display(){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    std::cout << coefficients[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
        void setAllValues(){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    std::cin >> coefficients[i][j];
                }
            }
            std::cout << "\n";
        }

        // operators
        void operator+=(Matrix m2){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    coefficients[i][j] += m2.coefficients[i][j];
                }
            }
        }
        void operator*=(const Matrix m2) {
                *this = *this * m2;
        }
        template <typename U>
        void operator*=(U lambda){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    coefficients[i][j] *= lambda;
                }
            }
        }
        friend Matrix<T> operator+(Matrix<T> m1, Matrix<T> m2){
            m1 += m2;
            return m1;
        }
        friend Matrix<T> operator*(Matrix<T> m1, Matrix<T> m2){
            Matrix m3(m1.Size());
            T temp;
            for (int i = 1; i <= m1.Size(); i++){
                for (int j = 1; j <= m1.Size(); j++){
                    temp = {};
                    for (int k = 1; k <= m1.Size(); k++){
                        temp += m1.getValue(i, k) * m2.getValue(k, j);
                    }
                    m3.setValue(i, j, temp);
                }
            }
            return m3;
        }
        template <typename U>
        friend Matrix<T> operator*(U lambda, Matrix<T> m){
            m *= lambda;
            return m;
        }

        // Determinant
        T determinant(){
            if (size == 1){
                return coefficients[0][0];
            }
            else if (size == 2){
                return coefficients[0][0] * coefficients[1][1] - coefficients[0][1] * coefficients[1][0];
            }
            else{
                T det = {};
                for (int i = 0; i < size; i++){
                    Matrix temp(size - 1);
                    for (int j = 0; j < size - 1; j++){
                        for (int k = 0; k < size - 1; k++){
                            if (k < i){
                                temp.coefficients[j][k] = coefficients[j+1][k];
                            }
                            else{
                                temp.coefficients[j][k] = coefficients[j+1][k+1];
                            }
                        }
                    det += std::pow(-1, i) * coefficients[0][i] * temp.determinant();
                    }
                }
                return det;
            }
        }
};
