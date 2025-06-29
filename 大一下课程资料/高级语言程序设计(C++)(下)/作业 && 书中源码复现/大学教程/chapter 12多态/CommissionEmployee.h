#ifndef COMMISSIONEMPLOYEE_H
#define COMMISSIONEMPLOYEE_H

#include <iostream>
#include "Employee.h"

class CommissionEmployee: public Employee
{
public:
    CommissionEmployee( const string &, const string &, const string &, double = 0.0, double = 0.0 );
    virtual ~CommissionEmployee(){};

    void setCommissionRate( double );
    double getCommissionRate( ) const;

    void setGrossSales( double );
    double getGrossSales() const;

    //包含关键字，重载虚函数
    virtual double earnings() const override;
    virtual void print() const override;

private:
    double grossSales;
    double commissionRate;
} ;
#endif