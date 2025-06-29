#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "map.h"
using namespace std;
#ifndef STORAGE_H
#define STORAGE_H
class storage :public map
{
public:
    storage();
    ~storage();
    virtual void work();
private:
};
#endif
