
#include<iostream>

using namespace std;
#ifndef EMPLOYEE_H
#define EMPLOYEE_H


class Employee {
public:
    Employee(const std::string&, const std::string&);
~Employee();Employee& getFirstName();
Employee& getLastName();
    static unsigned int getCount();
private:
std::string FirstName;
std::string LastName;
static unsigned int count;
};

#endif




unsigned int Employee::count = 0;
unsigned int Employee::getCount() {
	return count;
}
Employee::Employee(const string& first, const string& last)
	:FirstName(first), LastName(last) {
	++count;
	cout << FirstName << LastName << endl;
}
Employee::~Employee() {
	cout << FirstName << LastName << endl;
	--count;
}
Employee& Employee::getFirstName() {
	cout << FirstName;
	return *this;
}
Employee& Employee::getLastName() {
	cout << LastName<<endl;
	return *this;
}


using namespace std;
int main() {
	{
		cout<<Employee::getCount()<<endl;
		Employee e1("Sarah", "Chen");
		Employee e2("Tan", "Yi");
		e1.getFirstName().getLastName();
		e2.getFirstName().getLastName();
		cout << Employee::getCount() << endl;
	}
	cout << Employee::getCount() << endl;
	return 0;
}