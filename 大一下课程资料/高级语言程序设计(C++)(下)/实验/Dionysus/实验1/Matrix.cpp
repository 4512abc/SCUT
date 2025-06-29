#include "Matrix.h"

// Default constructor initializer
Matrix::Matrix() : a(1), b(0), c(0), d(1) {}
Matrix::Matrix(double x1, double x2, double x3, double x4) : a(x1), b(x2), c(x3), d(x4){}

std::istream& operator>>(std::istream& in, Matrix& M) {
    return in >> M.a >> M.b >> M.c >> M.d;
}
std::ostream& operator<<(std::ostream& out, const Matrix& M) {
    return out << "[ " << M.a << " " << M.b << " ]\n[ " << M.c << " " << M.d << " ]";
}

Matrix Matrix::operator+(const Matrix& other) const 
{
    return Matrix(a + other.a, b + other.b, c + other.c, d + other.d);
}

Matrix Matrix::operator-(const Matrix& other) const 
{
    return Matrix(a - other.a, b - other.b, c - other.c, d - other.d);
}

Matrix Matrix::operator*(const Matrix& other) const 
{
    return Matrix
    (
        a * other.a + b * other.c,
        a * other.b + b * other.d,
        c * other.a + d * other.c,
        c * other.b + d * other.d
    );
}

Matrix& Matrix::operator+=(const Matrix& other) 
{
    a += other.a;
    b += other.b;
    c += other.c;
    d += other.d;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) 
{
    a -= other.a;
    b -= other.b;
    c -= other.c;
    d -= other.d;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) 
{
    a = a * other.a + b * other.c;
    b = a * other.b + b * other.d;
    c = c * other.a + d * other.c;
    d = c * other.b + d * other.d;
    return *this;
}

// Scalar multiplication operator
Matrix Matrix::operator*(double scalar) const 
{
    return Matrix(a * scalar, b * scalar, c * scalar, d * scalar);
}

// Equality and inequality operators for matrix comparison
bool Matrix::operator==(const Matrix& other) const {
    return a == other.a && b == other.b && c == other.c && d == other.d;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}