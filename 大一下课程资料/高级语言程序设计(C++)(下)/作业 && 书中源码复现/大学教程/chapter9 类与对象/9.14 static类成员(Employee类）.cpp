#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include<string>

class Employee
{
public:
    Employee( const std::string &, const std::string & );
   ~Employee();
   std::string getFirstName() const;
   std::string getLastName() const;

   static unsigned int getCount() ;//不能加const

private:
    std::string firstName;
    std::string lastName;

    static unsigned int count;
};

#endif

#include <iostream>
using namespace std;

unsigned int Employee::count = 0;

unsigned int Employee::getCount()
{
    return count;
}

Employee::Employee( const string& first, const string& last)
: firstName(first),lastName(last)
{
    ++count;
    cout << "Employee constructor for "<< firstName
    << " " << lastName << " called" << endl;
}
Employee::~Employee()
{
    count--;
    cout << "Employee destructor for " << firstName
    << ' ' << lastName << " called" << endl;
}

string Employee::getFirstName() const
{
    return firstName;
}
string Employee::getLastName() const
{
    return lastName;
}

int main()
{
    cout << "Number of employees before instantiation of "
    << "any object is " << Employee::getCount() << endl;
    //使用类名访问static数据

    //在以下的作用域里构造和析构
    {
        Employee e1( "WenTao", "Yuan");
        Employee e2( "TaiXi", "Rao");
        
        cout << "目前有" << Employee::getCount() << "个员工\n" ;

    }//end nested scope, no Employee object remains

    cout << " 主函数中还有" << Employee::getCount() << "名员工\n" << endl;  
}