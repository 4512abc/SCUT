using namespace std;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
public:
    Employee( const string &, const string &, const string & );
    virtual ~Employee(){ }

    void setFirstName( const string & );
    string getFirstName( ) const;

    void setLastName( const string & );
    string getLastName( ) const;

    void setSocialSecurityNumber( const string & );
    string getSocialSecurityNumber ( ) const;

    //纯虚函数，让Employee类成为抽象基类
    virtual double earnings( ) const = 0;//pure virtual 
    virtual void print() const; // virtual

private:
    string firstName;
    string lastName;
    string socialSecurityNumber;

};

#endif