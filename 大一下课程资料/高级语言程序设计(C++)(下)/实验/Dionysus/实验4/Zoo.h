#pragma once
#include <random>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

//Money类
class Money
{
private:
    int dollar;
    int cent;

public:
    //构造与析构函数
    Money();
    Money(int dl = 0, int ct = 0);

    //重载Money类运算符
    friend std::ostream& operator<<(std::ostream& os, const Money&);
    friend std::istream& operator>>(std::istream& is, const Money&);
    Money& operator+(const Money&);
    Money& operator-(const Money&);
    Money& operator=(const Money&);
    Money& operator-=(const Money&);
    Money& operator+=(const Money&);
    //set美元美分两个数据成员
    void setDollar(int);
    void setCent(int);
    int getDollar();
    int getCent();
    void in_decreaseMoney(int, int);
    void in_decreaseMoney(Money);
};
//Food类
class Food
{
public:
    Food() :price(0), amount(0), fullValue(1) {}
    Food(int pc = 0, int am = 0);
    ~Food() {};

    void setPrice(int);
    int getPrice();
    void setAmount(int);
    int getAmount();
    void in_decreaseAmount(int);
    void clear();
private:
    int amount;
    int price;//其实这两项应该算是市场属性而非食物本身属性，不过在这里开发将就用
    int fullValue;//饱腹值
};

class Peanut :public Food
{
public:
    Peanut(int pc = 0, int am = 0) :Food(pc, am) {}
};
class Carrot :public Food
{
public:
    Carrot(int pc = 0, int am = 0) :Food(pc, am) {}
};
class Banana :public Food
{
public:
    Banana(int pc = 0, int am = 0) :Food(pc, am) {}
};

//Animal类
class Animal
{
private:
    int foodCapacity;
    int eatenFood;
public:
    //构造和析构函数
    Animal();
    Animal(int);//设置食量的接口
    ~Animal() {}
    //功能函数
    void eat(int);//进食，吃什么，吃多少;用于处理不同食物饱腹感不同的状况
    bool Full();//判断吃饱没有

    //数据成员操作函数
    void setFoodCapacity(int);
    int getFoodCapacity();
    void setEatenFood(int);
    int getEatenFood();
};

//Elephant类
class Elephant : public Animal
{
private:
    double trunkLength;
public:
    Elephant() :Animal(750) {}
    ~Elephant() {}
};

//monkey类
class Monkey : public Animal
{
private:
    double armLength;
public:
    Monkey() :Animal(300) {}
    ~Monkey() {}
};

//giraffe类
class Giraffe :public Animal
{
private:
    double neckLength;
public:
    Giraffe() :Animal(500) {}
    ~Giraffe() {}
};
class Enclosure
{
private:
    int dirtyLevel;
    bool openStatus;
    int closeTimes;
    int maxDirty;
public:
    Enclosure();
    ~Enclosure() {}

    //数据成员操作函数
    bool returnOpenStatus();
    //void helpIncrementDirtAndClose(int); //不能顺便关掉，要等一天结束后
    void helpIncrementDirt(int);
    void setDirtyLevel(int);
    int getDirtyLevel();
    int getMaxDirty();
    int getCloseTimes() { return this->closeTimes; }
    
    void setMaxDirty(int);
    //此处想写一个通用的返回动物成员的指针，如何实现呢

    //功能函数
    void closeEnclosure();
    void openEnclosure();
    void clearDirt();
    void incrementCloseTimes(int);
};

//定义不同动物的围栏
//其实分级后可以实现一个围栏里面根据实际情况有多个动物
class MonkeyEnclosure : public Enclosure
{
private:
    Monkey monkey;
public:
    MonkeyEnclosure() {};
    ~MonkeyEnclosure() {};
    Monkey& getMonkey() { return monkey; }
};

class GiraffeEnclosure : public Enclosure
{
private:
    Giraffe giraffe;
public:
    GiraffeEnclosure() {};
    ~GiraffeEnclosure() {};
    Giraffe& getGiraffe() { return giraffe; }
};

class ElephantEnclosure : public Enclosure
{
private:
    Elephant elephant;
public:
    ElephantEnclosure() {};
    ~ElephantEnclosure() {};
    Elephant& getElephant() { return elephant; }
};
class Person
{
public:
    Person(string a , int age) { Name = a; Age = age;}
    Person(){Name = " "; Age = " ";}
    ~Person() {};//注意，基类和派生类的构造函数要各自声明，但派生类可调用基类构造函数

    string getName(){return Name;}
private:
    string Name;
    string Age;
};

class ZooKeeper : public Person
{
public:
    //构造和析构函数
    ZooKeeper() :workDays(0), Person("YuanWentao", 19) {}
    ~ZooKeeper() {}
    //数据成员函数
    int getWorkDays() { return workDays; }
    //功能函数
    void checkAndCloseMonkeyEnclosure(MonkeyEnclosure&);
    void checkAndCloseGiraffeEnclosure(GiraffeEnclosure&);
    void checkAndCloseElephantEnclosure(ElephantEnclosure&);
    void working();
    bool returnWorkingStatus();
    void cleaningMonkeyEnclosure(MonkeyEnclosure&);
    void cleaningGiraffeEnclosure(GiraffeEnclosure&);
    void cleaningElephantEnclosure(ElephantEnclosure&);

    void helpIncrementWorkDay(int);
    void resetStatus(){workingStatus = 0;}
private:
    int workDays;
    bool workingStatus;//一个状态位参数，判断其有没有在打扫，仅仅是打扫的这份工作
};

class FoodSeller : public Person
{
private:
    Money moneyOwned;
    Peanut peanuts;
    Carrot carrots;
    Banana bananas;
    int kindsOfFood = 3;
    bool sellStatus;//判断是否卖完
public:
    FoodSeller(); 
    //另一种自定义价格数量的构造函数
    FoodSeller(int, int, int, int, int, int);
    ~FoodSeller() {}

    Money getMoneyOwned();
    void in_decreaseMoney(int, int);
    int getKindsOfFood();
    //提供接口扣货
    Peanut& getPeanut() { return this->peanuts; }
    Carrot& getCarrot() { return this->carrots; }
    Banana& getBanana() { return this->bananas; }
    //功能函数
    void sellFood(Food&, int);//利用多态实现,卖什么，卖了多少
    bool returnSellStatus();
};

//Visitor类
class Visitor :public Person
{
private:
    string passID; //只创建成员，在大人和小孩中有不同的格式
public:
    Visitor():Person(" ", 0) {}
    ~Visitor() {}

    virtual void initializeID();
    void setPassID(string);
    string& getPassIDReference();
};


//Child类
class Child : public Visitor
{
private:
    Peanut peanuts;
    Carrot carrots;
    Banana bananas;
public:
    //构造和析构函数
    Child();
    ~Child() {}
    //三种版本的喂食函数，两个参数，喂谁、喂多少
    void feed(MonkeyEnclosure&, int);
    void feed(GiraffeEnclosure&, int);
    void feed(ElephantEnclosure&, int);

    virtual void initializeID() override;

    Peanut& invokePeanuts();
    Carrot& invokeCarrots();
    Banana& invokeBananas();
};

//Adult类
class Adult : public Visitor
{
public:
    //构造与析构函数
    Adult();
    ~Adult() {}
    //行为成员函数
    void buyZooTicket();
    void buyFood(FoodSeller&);//传入一个销售商，合理
    void distributeFood();

    //数据成员操作成员函数
    Money getMoneyOwned(){return moneyOwned;}
    Peanut& getPeanutOwned(){return peanutsOwned;}
    //children相关
    void generateChildren();
    int getChildrenNumber();

    void setMoneyRandomly();
    void setMoney(int, int);

    virtual void initializeID() override;

    //想要返回数据成员Children vector引用的函数
    vector <Child>& getChildren();

private:
    Money moneyOwned;
    vector <Child> children;
    int childrenNumber = 0;
    Peanut peanutsOwned;
    Carrot carrotsOwned;
    Banana bananasOwned;
};
//Zoo类
class Zoo
{

private:
    //类对象成员
    FoodSeller foodSeller;
    ZooKeeper zooKeeper;
    ElephantEnclosure elephantEnclosure;
    MonkeyEnclosure monkeyEnclosure[3];
    GiraffeEnclosure giraffeEnclosure[2];
    vector<Adult>adults;
    vector < Enclosure > EnclosureToClean;
    int adultsNumber;
    //其他
    int runningDay;
    bool openStats;
    int closingEnclosureAmount;
    int historicVisitorAmount;
public:
    //功能函数
    int simulateOneDay();
    void simulateAllProcess();

    //数据成员函数
    ElephantEnclosure& getElephantEnclosure(){return elephantEnclosure;}
    FoodSeller& getFoodSeller(){return foodSeller;}
    Adult getAdult(int a){return adults[a];}
    ZooKeeper& getZooKeeper(){return zooKeeper;}
    int getAdultsNumber();
    int getHistoricVisitorAmount(){return historicVisitorAmount;}
    void setAdultsNumber(int);
    void openZoo();
    void closeZoo() { openStats = false; }
    void increaseVisitorAmount(int);
    bool returnOpenStats() { return openStats; }
    int getRunningDays() { return this->runningDay; }
    //功能函数
    void generateAdults();
    //构造函数
    Zoo();
};
