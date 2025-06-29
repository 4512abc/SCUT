#include <iostream>
#include <iomanip>
#include <vector>

#include "Employee.h"
#include "Employee.cpp"
#include "SalariedEmployee.h"
#include "SalariedEmployee.cpp"
#include "CommissionEmployee.h"
#include "CommissionEmployee.cpp"
#include "BasePlusCommissionEmployee.h"
#include "BasePlusCommissionEmployee.cpp"

using namespace std;

void virtualViaPointer( const Employee * const);
void virtualViaReference( const Employee &);

int main()
{
    cout << fixed << setprecision(2);

    SalariedEmployee salariedEmployee(
    "Hangzi", "Qiu", "111-11-1111", 800);
    CommissionEmployee commissionEmployee(
    "Taozi", "Yuan", "222-22-2222", 5000, 0.04);
    BasePlusCommissionEmployee basePlusCommissionEmployee(
    "Zituo", "Ren", "333-33-3333", 5000, 0.04, 10000);

    cout << "Employees processed individually using static binding:\n\n";

    //输出每个对象的信息
    salariedEmployee.print();
    cout << "\nearned $" << salariedEmployee.earnings() << "\n\n";
    commissionEmployee.print();
    cout << "\nearned $" << commissionEmployee.earnings() <<"\n\n";
    basePlusCommissionEmployee.print();
    cout << "\nearned $" << basePlusCommissionEmployee.earnings() << "\n\n";

    //创建含有三个Employee基类类型指针的向量
    vector< Employee *>employees( 3 );
    //用不同的地址初始化向量
    employees[ 0 ] = &salariedEmployee;
    employees[ 1 ] = &commissionEmployee;
    employees[ 2 ] = &basePlusCommissionEmployee;

    cout << "Employees processed polymorphically via dynamic binding:  \n\n";
    //通过动态绑定，Employees数组实现了多态

    cout << "Virtual function calls made off base-class pointers:\n\n";
    //通过基类指针调用虚函数
    for ( const Employee *employeePtr : employees )
        virtualViaPointer( employeePtr );

    //利用遍历输出每个员工的信息
    //工资通过动态绑定实现

    cout << "Virtual function calls made off base-class references:\n\n";
    //通过基类引用去调用虚函数
    for ( const Employee *employeePtr : employees )
        virtualViaReference( *employeePtr );
}//结束main函数

//利用动态绑定指针调用虚函数
void virtualViaPointer( const Employee * const baseClassPtr )
{
    baseClassPtr->print();
    cout <<"\nearned $" << baseClassPtr->earnings() << "\n\n";
}
//通过引用调用虚函数
void virtualViaReference( const Employee &baseClassRef )
{
    baseClassRef.print();
    cout << "\nearned $" << baseClassRef.earnings() << "\n\n";
}
