#include <string>
#include "date.h"

//Employee类定义展示了“组成”的概念

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
public:
    Employee( const std::string &, const std::string &,
            const Date &, const Date &);
    void print() const;
    ~Employee();//满足确定析构命令执行的需要
private:
    std::string firstName;
    std::string lastName;
    const Date birthDate;
    const Date hireDate;
};

#endif