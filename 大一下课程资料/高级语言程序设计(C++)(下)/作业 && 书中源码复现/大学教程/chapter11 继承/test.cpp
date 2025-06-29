#include <iostream>
#include <iomanip>
#include "Employee.h"
#include "Employeee.cpp"

using namespace std;

int main ()
{
    CommissionEmployee commissionEmployee(
        "Sue", "Jones", "222-22-2222", 10000, 0.06
    );
    CommissionEmployee *commissionEmployeePtr = nullptr;

    BasePlusCommissionEmployee basePlusCommissionEmployee(
        "Bob", "Lewis", "333-33-3333", 5000, 0.04, 300
    );

    BasePlusCommissionEmployee *basePlusCommissionEmployeePtr = nullptr;

    cout << fixed << setprecision( 2 );

    cout << "Print base-class and derived-class objects:\n\n";

    commissionEmployee.print();

    cout << "\n\n";
    basePlusCommissionEmployee.print();

    commissionEmployeePtr = &commissionEmployee;

    cout << "\n\n\nCalling print with base class pointer to \nbase-class"
    <<"object invokes base-class print function（用指向基类的基类指针调用基类函数）:\n\n";
    commissionEmployeePtr->print();

    basePlusCommissionEmployeePtr = &basePlusCommissionEmployee;
    cout << "\n\n\nCalling print with derived-class pointer to "
    << "\nderived-class object invokes derived-class"
    << " Print function（用指向子类的子类指针调用子类函数） :\n\n";
    basePlusCommissionEmployeePtr->print();

    commissionEmployeePtr = &basePlusCommissionEmployee;
    cout << "\n\n\n用指向子类对象的基类指针调用基类的print函数去打印子类信息\n";
    commissionEmployeePtr -> print();
    cout << endl;
}