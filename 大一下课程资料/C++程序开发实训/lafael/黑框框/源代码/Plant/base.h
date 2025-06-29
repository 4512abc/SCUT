#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "map.h"
using namespace std;
#ifndef BASE_H
#define BASE_H
class base :public map
{
public:
    base();
    ~base();
    virtual void work();
private:
};
#endif
