#include "Matrix.h"
#include "Matrix.cpp"
#include <iostream>
using namespace std;

int main()
{
    cout << "test default constructor" << endl;
    Matrix  m1;
    cout <<"m1 = \n" << m1 << endl;
    cout << "test constructor with parameters " << endl;
    Matrix m2(3, 2, 1, 4);
    cout << "m2 = \n" <<m2 << endl;
    cout << "test copy constructor" << endl;
    Matrix m3(m2);
    cout << "m3(m2) = \n" << m3 << endl;
    cout << "test assignment operator m1 = m2;" << endl;
    m1 = m2;
    cout << "m1 = \n" <<m1 << endl;
    cout << "test operator +" << endl;
    cout << "m1 + m2 = \n"<<m1 + m2 << endl;
    cout << "test operator *" << endl;
    cout << "m1 * m2 = \n"<<m1 * m2 << endl;
    cout << "test operator * with scalar" << endl;
    cout << "m1 * 2 = \n"<<m1 * 2 << endl;
    cout << "test operator -" << endl;
    cout << "m1 - m2 = \n"<<m1 - m2 << endl;
    cout << "test operator ==" << endl;
    cout << "m1 == m2 ? \n" << endl;
    if (m1 == m2) 
        cout << "m1 == m2" << endl;
    else 
        cout << "m1 != m2" << endl;

    cout << "test operator !=" << endl;
    cout << "m1 != m2 ? \n" << endl;
    if (m1 != m2)  
        cout << "m1 != m2" << endl;
    else  
        cout << "m1 == m2" << endl;
    return 0;
}