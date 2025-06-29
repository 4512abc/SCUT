using namespace std;

#ifndef SALARIED_H
#define SALARIED_H

#include "Employee.h"

class SalariedEmployee : public Employee
{
public:
    SalariedEmployee( const string &, const string &, const string &,
                    double = 0.0  );
    virtual ~SalariedEmployee( ) { };

    void setWeeklySalary( double );
    double getWeeklySalary() const;

    //重写earnings和print函数，加上override关键字
    virtual double earnings() const override;
    virtual void print() const override;

private:
    double weeklySalary;
};
#endif