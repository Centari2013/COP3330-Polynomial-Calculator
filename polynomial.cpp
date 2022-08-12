// Zaria Burton  zb19e  Sec. 1
#include "polynomial.h"
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <vector>

Polynomial::Polynomial()
{
    clear();
}

Polynomial::Polynomial(int c)
{
    variable = 'x';
    coefficients.resize(MAX_DEGREE + 1);
    for (int i = MAX_DEGREE; i >= 0; --i) //starts at end of vector
    {
        coefficients[i] = c;
        --c;
    }
    setDegree();


}

void Polynomial::clear()
{
    degree = -1;
    variable = 'x';
    coefficients.resize(MAX_DEGREE + 1);
    for (int i = MAX_DEGREE; i >= 0; --i) //starts at end of vector
    {
        coefficients[i] = 0;
    }
}

int Polynomial::evaluate(int x)
{
    int total = 0; //adds total result
    for (int i = 0; i < coefficients.size(); i++) //starts at beginning of vector
    {
        if (i < coefficients.size() - 1)
        {
            total += (coefficients[i] * int(pow(x, coefficients.size() - i - 1)));
        }
        else
        {
            total += coefficients[i];
        }

    }

    return total;
}

int Polynomial::getCoefficient(int k)
{
    if (k >= 0 && k <= MAX_DEGREE)
    {
        return (coefficients[abs(k - MAX_DEGREE)]);
    }
    else
    {
        return 0;
    }
}

int Polynomial::getDegree()
{
    return degree;
}

bool Polynomial::setCoefficient(int k, int c)// k = exponent of coefficient and c = replacement coefficient
{
    if (k >= 0 && k <= MAX_DEGREE)
    {
        coefficients[abs(k - MAX_DEGREE)] = c;
        return true;
    }
    else
    {
        return false;
    }
}

bool Polynomial::setLetter(char var)
{
    if (int(var) >= 65 && int(var) <= 97)
    {
        variable = tolower(int(var));
        return true;
    }
    else
    {
        return false;
    }
}

void Polynomial::setDegree()
{
    if (coefficients[0] == 0)
    {
        int j = 0;
        for (int i = 0; i < coefficients.size(); i++)
        {
            if (coefficients[i] == 0)
            {
                j++;
            }
            else
            {
                break;
            }
        }
        degree = MAX_DEGREE - j;
    }
    else
    {
        degree = MAX_DEGREE;
    }
}

std::ostream &operator<< (std::ostream &func, const Polynomial &p)
{
    if (p.degree != -1)
    {
        for (int i = 0; i < p.coefficients.size(); i++)
        {
            if (p.coefficients[i] != 0) //doesn't print 0s
            {
                if (p.coefficients[i] < 0) //negative numbers
                {
                    if (i != p.coefficients.size() - 1 && i != p.coefficients.size() - 2)
                    {
                        if (p.coefficients[i] != -1)
                        {
                            func << " - " << abs(p.coefficients[i]) << p.variable << "^" << (p.coefficients.size() - i - 1);
                        }
                        else
                        {
                            func << " - " << p.variable << "^" << (p.coefficients.size() - i - 1);
                        }
                    }
                    else if (i == p.coefficients.size() - 2)
                    {
                        func << " - " << abs(p.coefficients[i]) << p.variable;
                    }
                    else
                    {
                        func << " - " << abs(p.coefficients[i]);
                    }
                }
                else if (p.coefficients[i] > 0) //positive numbers
                {
                    if (i != p.coefficients.size() - 1 && i != p.coefficients.size() - 2 && i != 0)
                    {
                        if (p.coefficients[i] != 1)
                        {
                            func << " + " << p.coefficients[i] << p.variable << "^" << (p.coefficients.size() - i - 1);
                        }
                        else
                        {
                            func << " + " << p.variable << "^" << (p.coefficients.size() - i - 1);
                        }
                    }
                    else if (i == 0)
                    {
                        func << p.coefficients[i] << p.variable << "^" << (p.coefficients.size() - i - 1);
                    }
                    else if (i == p.coefficients.size() - 2)
                    {
                        func << " + " << p.coefficients[i] << p.variable;
                    }
                    else
                    {
                        func << " + " << p.coefficients[i];
                    }
                }

            }

        }
    }
    else
    {
        func << "Polynomial of degree -1";
    }
    return func;

}

std::istream &operator>> (std::istream &func, Polynomial &p)
{
    char v;
    char delimiter;

    func >> v >> delimiter;

    if (int(v) <= 97 && int(v) >= 65)
    {

        char delimiter2 = ',';

        std::string Poly;

        func >> Poly;

        p.variable = Poly.substr(0, Poly.find(delimiter));
        Poly.erase(0, Poly.find(delimiter) + 1);

        for (int i = p.coefficients.size() - 1; i == 0; i--)
        {
            p.coefficients[i] = std::stoi(Poly.substr(0, Poly.find(delimiter2)));
            Poly.erase(0, Poly.find(delimiter2) + 1);
        }

        p.setDegree();

    }
    else
    {
       p.clear();
    }

    return func;
}

bool operator< (const Polynomial &p, const Polynomial &q)
{
    //coefficient sums
    int psum = 0;
    int qsum = 0;

    if (p.degree < q.degree)
    {
        return true;
    }
    else if (p.degree == q.degree)
    {
        for (int i = 0; i < p.coefficients.size(); i++)
        {
            psum += p.coefficients[i];
            qsum += q.coefficients[i];
        }

        return psum < qsum;
    }
    else
    {
        return false;
    }
}

bool operator> (const Polynomial &p, const Polynomial &q)
{
    //coefficient sums
    int psum = 0;
    int qsum = 0;

    if (p.degree > q.degree)
    {
        return true;
    }
    else if (p.degree == q.degree)
    {
        for (int i = 0; i < p.coefficients.size(); i++)
        {
            psum += p.coefficients[i];
            qsum += q.coefficients[i];
        }

        return psum > qsum;
    }
    else
    {
        return false;
    }
}

bool operator== (const Polynomial &p, const Polynomial &q)
{
    int j = 0;

    if (p.degree == q.degree)
    {
        return (p.coefficients == q.coefficients);
    }
    else
    {
        return false;
    }
}

bool operator<= (const Polynomial &p, const Polynomial &q)
{
    if (p < q)
    {
        return true;
    }
    else return p == q;

}

bool operator>= (const Polynomial &p, const Polynomial &q)
{
    if (p > q)
    {
        return true;
    }
    else return p == q;
}

bool operator!= (const Polynomial &p, const Polynomial &q)
{
    return !(p == q);
}

Polynomial operator+(const Polynomial &p, const Polynomial &q)
{
    Polynomial P;
    P.variable = p.variable;
    for (int i = 0; i < p.coefficients.size(); i++)
    {
        P.coefficients[i] = p.coefficients[i] + q.coefficients[i];
    }
    P.setDegree();

    return P;
}

Polynomial operator-(const Polynomial &p, const Polynomial &q)
{
    Polynomial P;
    P.variable = p.variable;
    for (int i = 0; i < p.coefficients.size(); i++)
    {
        P.coefficients[i] = p.coefficients[i] - q.coefficients[i];
    }
    P.setDegree();

    return P;
}

Polynomial operator*(const Polynomial &p, const Polynomial &q)
{
    Polynomial P;
    P.variable = p.variable;

    for (int i = 0; i < p.coefficients.size(); i++)
    {
        for (int j = 0; j < q.coefficients.size(); j++)
        {
            if ((i + j) >= 0 && (i + j) < P.coefficients.size())
            {
                P.coefficients[i + j] += p.coefficients[i] * q.coefficients[j];
            }
        }

    }

    P.setDegree();

    return P;
}


