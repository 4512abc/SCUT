#include <iostream>
#include <stdexcept>
using namespace std;

#ifndef COMMISIONEMPLOYEE
#define COMMISIONEMPLOYEE

class CommissionEmployee
{
public:
    CommissionEmployee( const string &, const string &,
        const string &, double = 0.0, double = 0.0);

    //初始化所用到的set函数以及get函数得到数据成员
    void setFirstName( const string & );
    string getFirstName() const;
    
    void setLastName( const string & );
    string getLastName() const;

    void setSocialSecurityNumber( const string & );
    string getSocialSecurityNumber() const;

    void setGrossSales( double );
    double getGrossSales( ) const;

    void setCommissionRate( double );
    double getCommisionRate( ) const;

    double earnings() const;
    void print() const;

private:
    string FirstName;
    string LastName;
    string SocialSecurityNumber;
    double grossSales;
    double commissionRate;

};
#endif

#ifndef BASEPLUS_H
#define BASEPLUS_H
class BasePlusCommissionEmployee : public CommissionEmployee
{
public:
    BasePlusCommissionEmployee( const string &, const string &, const string &,
            double = 0.0, double = 0.0, double = 0.0 );
    void setBaseSalary( double );
    double getBaseSalary( ) const;
    double earnings( ) const;
    void print() const;
private:
    double baseSalary ;
};
#endif

