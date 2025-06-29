#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
public:

    Matrix();
    Matrix(double a, double b, double c, double d);

    friend std::istream& operator>>(std::istream& in, Matrix& M);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& M);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    Matrix operator*(double scalar) const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

private:
    double a, b, c, d; 
};

#endif 