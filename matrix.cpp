#include <iostream>
#include <vector>

class Matrix;
Matrix operator*(Matrix m1, Matrix m2);

class Matrix{
    private:
        int size;
        std::vector<std::vector<double> > coefficients;

    public:
        Matrix(int n): size(n), coefficients(n, std::vector<double>(n, 0.0)) {}
        int Size(){return size;}
        void setValue(int row, int column, double value){
            coefficients[row - 1][column - 1] = value;
        }
        double getValue(int row, int column){
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
        }
        // operators
        void operator+=(Matrix m2){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    coefficients[i][j] += m2.coefficients[i][j];
                }
            }
        }
        Matrix& operator*=(const Matrix& m2) {
                *this = *this * m2;
                return *this;
        }
};

Matrix operator+(Matrix m1, Matrix m2){
    m1 += m2;
    return m1;
}

Matrix operator*(Matrix m1, Matrix m2){
    Matrix m3(m1.Size());
    double temp;
    for (int i = 1; i <= m1.Size(); i++){
        for (int j = 1; j <= m1.Size(); j++){
            temp = 0;
            for (int k = 1; k <= m1.Size(); k++){
                temp += m1.getValue(i, k) * m2.getValue(k, j);
            }
            m3.setValue(i, j, temp);
        }
    }
    return m3;
}

int main(void){
    Matrix identite(3), bra(3);
    identite.setAllValues();
    identite.display();
    std::cout << "\n";
    bra.setAllValues();
    bra.display();
    std::cout << "\n";
    std::cout << "no pb\n";
    bra *= identite;
    bra.display();
}
