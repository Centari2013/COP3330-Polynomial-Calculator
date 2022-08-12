// Zaria Burton  zb19e  Sec. 1
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>
#include <string>

const int MAX_DEGREE = 10;

class Polynomial
{

private:
    int degree;
    std::string variable;
    std::vector<int> coefficients;

    void setDegree();

    friend std::ostream &operator<< (std::ostream &func, const Polynomial &p);
    friend std::istream &operator>> (std::istream &func, Polynomial &p);

    friend bool operator< (const Polynomial &p, const Polynomial &q);
    friend bool operator> (const Polynomial &p, const Polynomial &q);
    friend bool operator<= (const Polynomial &p, const Polynomial &q);
    friend bool operator>= (const Polynomial &p, const Polynomial &q);
    friend bool operator== (const Polynomial &p, const Polynomial &q);
    friend bool operator!= (const Polynomial &p, const Polynomial &q);

    friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
    friend Polynomial operator-(const Polynomial &p, const Polynomial &q);
    friend Polynomial operator*(const Polynomial &p, const Polynomial &q);

public:
    Polynomial();
    explicit Polynomial(int c);
    void clear();
    int evaluate(int x = 0);
    int getCoefficient(int k);
    int getDegree();
    bool setCoefficient(int k, int c = 0);
    bool setLetter(char var);



};


#endif

