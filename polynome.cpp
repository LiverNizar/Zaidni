#include <ostream>
#include <vector>

template <typename T>
class Polynome{
    private:
        std::vector<T> coefficient;
        int degre;
        void _extendToZeros(int n){
            coefficient.resize(n+1, T{});
        }
    public:
        Polynome(int n): degre(n), coefficient(n + 1, T{}){}
        int Degre(){return degre;};
        void setValue(int n, T coef){
            coefficient[n] = coef;
        }
        T getValue(int n) const {
            return coefficient[n];
        }

        // printing polynome !!Its all '+' it should check if the sign of the coefficient
        friend std::ostream& operator<<(std::ostream& os, const Polynome<T>& polynome){
            os << polynome.getValue(0);
            for (int i = 1; i <= polynome.degre; i++){
                if (polynome.getValue(i) == 1){
                    os << " + X^" << i;
                }
                else{
                    os << " + " << polynome.getValue(i) << "X^" << i;
                }
            }
            return os;
        }

        // operations
        void operator+=(Polynome p2){
            if (degre >= p2.degre){
                p2._extendToZeros(degre);
            }
            else{
                this->_extendToZeros(p2.degre);
                degre = p2.degre;
            }
            for (int i = 0; i <= degre; i++){
                coefficient[i] += p2.coefficient[i];
            }
        }
        void operator*=(Polynome p2){
            *this = *this * p2;
        }
        template <typename U>
        void operator*=(U lambda){
            *this = lambda * *this;
        }
        friend Polynome<T> operator+(Polynome<T> p1, Polynome<T> p2){
            p1 += p2;
            return p1;
        }
        friend Polynome<T> operator*(Polynome<T> p1, Polynome<T> p2){
            int n = p1.degre + p2.degre;
            p1._extendToZeros(n);
            p2._extendToZeros(n);
            T temp{};
            Polynome<T> m(n);
            for (int i = 0; i <= n; i++){
                temp = {};
                for (int k = 0; k <= i; k++){
                    temp += p1.coefficient[k] * p2.coefficient[i - k];
                }
                m.coefficient[i] = temp;
            }
            return m;
        }
        template <typename U>
        friend Polynome<T> operator*(U lambda, Polynome<T> p){
            Polynome p_new(p.degre);
            if (lambda == U{}){
                p_new.degre = 0;
                p_new._extendToZeros(1);
                p_new.coefficient[0] = U{};
            }
            else{
                for (int i = 0; i <= p.degre; i++){
                    p_new.coefficient[i] = p.coefficient[i] * lambda;
                }
            }
            return p_new;
        }
        template <typename U>
        friend Polynome<T> operator*(Polynome<T> p, U lambda){
            Polynome p_new(p.degre);
            if (lambda == U{}){
                p_new.degre = 0;
                p_new._extendToZeros(1);
                p_new.coefficient[0] = U{};
            }
            else{
                for (int i = 0; i <= p.degre; i++){
                    p_new.coefficient[i] = p.coefficient[i] * lambda;
                }
            }
            return p_new;
         }
        // casting from a type to a polynome;

};
