#include <iostream>
using namespace std;

class Count
{
    friend void setX( Count &, int);
public:
    Count() : x(0) {};

    void print() const
    {
        cout << x << endl;
    }
private:
    int x ;

};

//function setX can modify private data of Count 
//因为其是Count类的友元函数

void setX( Count &c, int val )
//传入了一个Count类对象的引用以及一个int值
{
    c.x = val;
}

int main()
{
    Count counter;
    setX( counter, 8 );
    
    cout << "counter.x after call to setX friend function: ";
    counter.print();
}