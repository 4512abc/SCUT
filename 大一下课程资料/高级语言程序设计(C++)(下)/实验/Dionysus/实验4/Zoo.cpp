#include <random>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <string>

#include "Zoo.h"
using namespace std;
Food::Food(int pc, int am) :price(pc), amount(am)
{}//此处必须用初始化列表进行构造，否则派生类无法继承
int Food::getPrice()
{
    return price;
}

int Food::getAmount()
{
    return amount;
}

void Food::setAmount(int am)
{
    if (am >= 0)
        amount = am;
    else throw invalid_argument("amount must >= 0");
}

void Food::setPrice(int pc)
{
    if (pc >= 0)
        price = pc;
    else
        throw invalid_argument("price must >= 0");
}
void Food::in_decreaseAmount(int delta)
{
    //这里只用于修改，判断函数在FoodSeller中自行写
    if (amount + delta < 0)
        amount = 0;
    else amount = amount + delta;
}
void Food::clear()
{
    this->amount = 0;
}

Money::Money()
{
    dollar = 0;
    cent = 0;
}
//含有两个参数初始化money对象的构造函数
Money::Money(int dl, int ct)
{
    if (dl >= 0 && ct >= 0)
    {
        dollar = dl + (ct / 100);

        cent = ct % 100;
    }
    //钱在该系统中均假定为正数
    else
        throw invalid_argument("input must be >= 0");
}

//重载运算符
std::ostream& operator<<(std::ostream& os, const Money& money)
{
    os << money.dollar << '$' << ' ' <<money.cent <<"cent";
    return os;
}
istream& operator>>(istream& is, const Money& money)
{
    is >> money.dollar >> money.cent;
    return is;
}
Money& Money::operator+(const Money& other)
{
    dollar += other.dollar;
    cent += other.cent;
    if (cent >= 100)
    {
        int a = cent / 100;
        cent = cent % 100;
        dollar += a;
    }
    return *this;
}
Money& Money::operator-(const Money& other)
{
    this->dollar -= other.dollar;
    this->cent -= other.cent;
    if (cent <= -100)
    {
        int a = (-cent) / 100;
        cent = -((-cent) % 100);
        dollar -= a;
    }
    return *this;
}
Money& Money::operator=(const Money& other)
{
    this->dollar = other.dollar;
    this->cent = other.cent;
    return *this;
}
Money& Money::operator-=(const Money& other)
{
    *this = *this - other;
    return *this;
}
Money& Money::operator+=(const Money& other)
{
    *this = *this + other;
    return *this;
}

//数据成员操作函数
void Money::setCent(int a)
{
    cent = a;
}
void Money::setDollar(int a)
{
    dollar = a;
}
int Money::getCent()
{
    return cent;
}
int Money::getDollar()
{
    return dollar;
}
void Money::in_decreaseMoney(int dl, int ct)
{
    Money increase(dl, ct);
    *this += increase;
}
void Money::in_decreaseMoney(Money delta)
{
    *this += delta;
}

//构造析构函数
Animal::Animal() : foodCapacity(0) {}
Animal::Animal(int fc)
{
    if (fc >= 0)
        foodCapacity = fc;
    else
        throw invalid_argument("foodCapacity must be >= 0");
}
//数据成员函数
void Animal::setFoodCapacity(int fc)
{
    foodCapacity = fc;
}
int Animal::getFoodCapacity()
{
    return foodCapacity;
}

//功能函数
bool Animal::Full()
{
    if (eatenFood >= foodCapacity)
        return true;
    else return false;
}
void Animal::eat(int a)
{
    eatenFood += a;
}
int Animal::getEatenFood()
{
    return eatenFood;
}
void Animal::setEatenFood(int eatAmount)
{
    this->eatenFood = eatAmount;
}

Enclosure::Enclosure()
{
    this->openStatus = 0;
    this->dirtyLevel = 0;
    maxDirty = 2000;
    this->closeTimes = 0;
}
void Enclosure::setDirtyLevel(int Dl)
{
    dirtyLevel = Dl;
}

void Enclosure::clearDirt()
{
    setDirtyLevel(0);
}
void Enclosure::closeEnclosure()
{
    this->openStatus = 0;
    this->closeTimes++;
}
int Enclosure::getDirtyLevel()
{
    return this->dirtyLevel;
}
int Enclosure::getMaxDirty()
{
    return maxDirty;
}
bool Enclosure::returnOpenStatus()
{
    return this->openStatus;
}
void Enclosure::setMaxDirty(int maxDL)
{
    this->maxDirty = maxDL;
}
void Enclosure::openEnclosure()
{
    openStatus = true;
}
//关闭函数单独写，且在Zookeeper中

// void Enclosure::helpIncrementDirtAndClose( int FoodAmount )
// {
//     if( FoodAmount > this->getMaxDirty() - this->getDirtyLevel() )
//     {
//         setDirtyLevel( this->getMaxDirty() );
//         this->closeEnclosure();
//     }
//     else this->dirtyLevel += FoodAmount;
// }
void Enclosure::helpIncrementDirt(int DT)
{
    this->dirtyLevel += DT;
}
void Enclosure::incrementCloseTimes(int a)
{
    closeTimes += a;
}
//Zookeeper类

void ZooKeeper::checkAndCloseMonkeyEnclosure(MonkeyEnclosure& enclosure)
{
    if (enclosure.getDirtyLevel() >= enclosure.getMaxDirty())
    {
        enclosure.closeEnclosure();
    }
}
void ZooKeeper::checkAndCloseElephantEnclosure(ElephantEnclosure& enclosure)
{
    if (enclosure.getDirtyLevel() >= enclosure.getMaxDirty())
    {
        enclosure.closeEnclosure();
    }
}
void ZooKeeper::checkAndCloseGiraffeEnclosure(GiraffeEnclosure& enclosure)
{
    if (enclosure.getDirtyLevel() >= enclosure.getMaxDirty())
    {
        enclosure.closeEnclosure();
    }
}
void ZooKeeper::working()
{
    if (!this->returnWorkingStatus())
    {
        this->workingStatus = true;//调整工作状态，但是要判断先前是否在工作
        this->helpIncrementWorkDay(1);
    }
}
void ZooKeeper::cleaningMonkeyEnclosure(MonkeyEnclosure& enclosure)
{
    this->workingStatus = 1;
    enclosure.clearDirt();
    enclosure.openEnclosure();
    workDays ++;
}
void ZooKeeper::cleaningGiraffeEnclosure(GiraffeEnclosure& enclosure)
{
    this->workingStatus = 1;
    enclosure.clearDirt();
    enclosure.openEnclosure();
    workDays ++;
}
void ZooKeeper::cleaningElephantEnclosure(ElephantEnclosure& enclosure)
{
    this->workingStatus = 1;
    enclosure.clearDirt();
    enclosure.openEnclosure();
    workDays ++;
}

bool ZooKeeper::returnWorkingStatus()
{
    return workingStatus;
}
void ZooKeeper::helpIncrementWorkDay(int a)
{
    workDays += a;
}
//FoodSeller类

FoodSeller::FoodSeller() :moneyOwned(0, 0), Person("Dionysus", 19)
{
    peanuts.setAmount(10000);
    peanuts.setPrice(20);
    carrots.setPrice(30);
    carrots.setAmount(7000);
    bananas.setAmount(4000);
    bananas.setPrice(50);
}
FoodSeller::FoodSeller(int pnAmount, int pnPrice, int ctAmount, int ctPrice, int bnAmount, int bnPrice) : moneyOwned(0, 0),Person(" ", 0)
{
    peanuts.setAmount(pnAmount);
    peanuts.setPrice(pnPrice);
    carrots.setPrice(ctAmount);
    carrots.setAmount(ctPrice);
    bananas.setAmount(bnAmount);
    bananas.setPrice(bnPrice);
}
int FoodSeller::getKindsOfFood()
{
    return kindsOfFood;
}
Money FoodSeller::getMoneyOwned()
{
    return moneyOwned;
}
void FoodSeller::in_decreaseMoney(int dl, int ct)
{
    Money delta(dl, ct);
    moneyOwned += delta;
}
void FoodSeller::sellFood(Food& food, int a)
{
    food.in_decreaseAmount(-a);//减货
    this->in_decreaseMoney(0, food.getPrice() * a);//加钱
}
bool FoodSeller::returnSellStatus()
{
    return sellStatus;
}

//Visitor类

void Visitor::setPassID(string s)
{
    passID = s;
}
string& Visitor::getPassIDReference()
{
    return passID;
}
void Visitor::initializeID()
{
    passID = "D000000N";
}

//Adult类
Adult::Adult() :moneyOwned(0, 0)
{
    initializeID();
    setMoneyRandomly();
    generateChildren();
}

void Adult::setMoneyRandomly()
{
    srand(time(0));
    int dl = rand() % 11 +10;
    moneyOwned.setDollar(dl);
}

void Adult::setMoney(int a, int b)
{
    moneyOwned.setDollar(a);
    moneyOwned.setCent(b);
}

//优化一下，免去了复制的消耗

//void Adult::generateChildren()//在该函数中只产生了孩子的天数ID，序号ID没有产生
//{
//    std::default_random_engine e;
//    std::uniform_int_distribution<int> u(1, 3);
//    childrenNumber = u(e);
//    children.resize(childrenNumber);
//    Child childrenCopy[3];
//    for (int i = 0; i <= childrenNumber; i++)
//    {
//        string accessNumber = to_string(i);
//        for (int j = 0; (3 - j > 0); j++)
//        {
//            childrenCopy[i].getPassIDReference()[3 - j] = this->getPassIDReference()[3 - j];
//        }
//    }
//    for (int i = 0; i <= childrenNumber; i++)
//    {
//        children.push_back(childrenCopy[i]);
//    }
//}
void Adult::generateChildren() // 在该函数中只产生了孩子的天数ID，序号ID没有产生
{
    srand(time(0));
    
    childrenNumber = rand() % 3 + 1;
    children.resize(childrenNumber);
    // for (int i = 0; i < childrenNumber; i++)
    // {
    //     string accessNumber = to_string(i + 1);
    //     string childID = this->getPassIDReference().substr(0, 3) + accessNumber;

    //     children[i].setPassID(childID);
    // }
}


void Adult::initializeID()
{
    setPassID("D000000A");
}

int Adult::getChildrenNumber()
{
    return childrenNumber;
}


void Adult::buyZooTicket()
{
    Money buyTicket(1,40 * childrenNumber);
    this->moneyOwned = moneyOwned - buyTicket;
}
//重写一下buyFood函数咯，处理方法不能对应上销售商货物实时状态
void Adult::buyFood(FoodSeller& foodseller) //在运营状态中检查是否买完，便于退出程序
{   
    // //第一遍检查，发现居然没给销售商扣货.....
    // //将手中的钱全部转化为美分形式
    long moneyInCent = (moneyOwned.getDollar() * 100 + moneyOwned.getCent());
    //先算平均数，后续再加权
    // int foodGroupNumber = moneyInCent / (foodseller.getCarrot().getPrice()
    //                                     +foodseller.getBanana().getPrice()
    //                                     +foodseller.getPeanut().getPrice()
                                        // );
    //公式为：比例A = pb * pc /( pa * pb + pb * pc + pc * pa) 
    int carrotsNumber = moneyInCent / 90 ;
    int peanutsNumber = moneyInCent / 60 ;
    int bananasNumber = moneyInCent / 150 ;
    // //按照价钱加权平均购买，还是错误，再次改进方法
    // int singlePricePlusTogether = foodseller.getBanana().getPrice() + foodseller.getCarrot().getPrice() + foodseller.getPeanut().getPrice();
    // int buyPeanutsMoney = moneyInCent * foodseller.getPeanut().getPrice() / singlePricePlusTogether;
    // int carrotsNumber = moneyInCent * foodseller.getCarrot().getPrice() / singlePricePlusTogether;
    // int buyBananasMoney = moneyInCent * foodseller.getBanana().getPrice() / singlePricePlusTogether;
    int moneyRemained = moneyInCent - bananasNumber * foodseller.getBanana().getPrice() - peanutsNumber * foodseller.getPeanut().getPrice() - carrotsNumber * foodseller.getCarrot().getPrice(); // By calculating
    //第二遍检查，还是没有实现平均，计算改进方法，公式为：AmountA = 
    
    //以此去购买售货商的货物，买目前实际的货物量
    if (peanutsNumber >= foodseller.getPeanut().getAmount()) //买的量大于目前所能出售的量
    {
        foodseller.in_decreaseMoney(0, foodseller.getPeanut().getPrice() * foodseller.getPeanut().getPrice());//给钱
        this->peanutsOwned.in_decreaseAmount(foodseller.getPeanut().getAmount());//给货
        moneyRemained += ( peanutsNumber - foodseller.getPeanut().getAmount() ) * foodseller.getPeanut().getPrice();//剩的钱
        foodseller.getPeanut().setAmount(0);//扣货
    }
    else
    {
        foodseller.in_decreaseMoney(0, peanutsNumber * foodseller.getPeanut().getPrice());//给钱
        this->peanutsOwned.in_decreaseAmount(peanutsNumber);//给货
        foodseller.getPeanut().in_decreaseAmount( -peanutsNumber);//扣货
    }

    if (carrotsNumber >= foodseller.getCarrot().getAmount())
    {
        foodseller.in_decreaseMoney(0, foodseller.getCarrot().getPrice() * foodseller.getCarrot().getAmount());
        this->carrotsOwned.in_decreaseAmount(foodseller.getCarrot().getAmount());
        moneyRemained += ( carrotsNumber - foodseller.getCarrot().getAmount() )* foodseller.getPeanut().getPrice();
        foodseller.getCarrot().setAmount(0);
    }
    else
    {
        foodseller.in_decreaseMoney(0, carrotsNumber * foodseller.getCarrot().getPrice());
        this->carrotsOwned.in_decreaseAmount(carrotsNumber);
        foodseller.getCarrot().in_decreaseAmount( -carrotsNumber );
    }

    if ( bananasNumber >= foodseller.getBanana().getAmount()) //用于买的钱大于目前所能出售的量
    {
        foodseller.in_decreaseMoney(0, foodseller.getBanana().getAmount() * foodseller.getBanana().getPrice());
        this->bananasOwned.in_decreaseAmount(foodseller.getBanana().getAmount());
        moneyRemained += ( bananasNumber - foodseller.getBanana().getAmount()) * foodseller.getBanana().getPrice();
        foodseller.getBanana().setAmount(0);
    }
    else
    {
        foodseller.in_decreaseMoney(0, bananasNumber * foodseller.getBanana().getPrice());
        this->bananasOwned.in_decreaseAmount( bananasNumber );
        foodseller.getBanana().in_decreaseAmount( -bananasNumber );
    }

    //简单处理一下，剩下的钱全部去买胡罗卜，平均一下比例，题目所给的是：数目 10 ：7 ：4 ； 价钱 2：3：5，那么肯定胡萝卜在不处理的情况下最不可能卖完，不再作剩余钱的处理，在模拟中只多出一个Adult成员的一些美分，无所谓
    if (moneyRemained > foodseller.getCarrot().getAmount() * foodseller.getCarrot().getPrice())
    {
        foodseller.in_decreaseMoney(0, foodseller.getCarrot().getAmount() * foodseller.getCarrot().getPrice());//给钱
        this->carrotsOwned.in_decreaseAmount(foodseller.getCarrot().getAmount());//给货
        moneyRemained -= foodseller.getCarrot().getAmount() * foodseller.getPeanut().getPrice();
        foodseller.getCarrot().setAmount(0);
    }
    else
    {
        foodseller.in_decreaseMoney(0, moneyRemained);
        this->carrotsOwned.in_decreaseAmount( ( moneyRemained / foodseller.getCarrot().getPrice()) );
        foodseller.getCarrot().in_decreaseAmount( -(moneyRemained / foodseller.getCarrot().getPrice()) );
    }
    this->moneyOwned.setDollar(0);
}

void Adult::distributeFood()
{
    //两种方法，先按组数分，剩下的都给1 ; 或者每个食物先平均，然后分出去
    //选择方2,复杂度来说都是线性，还好
    //然后多出来的给剩下的孩子吧；
    int bananaGroup = bananasOwned.getAmount() / getChildrenNumber();
    int carrotsGroup = carrotsOwned.getAmount() / getChildrenNumber();
    int peanutsGroup = peanutsOwned.getAmount() / getChildrenNumber();
    //循环，平均分
    for (int i = 0; i < getChildrenNumber(); i++)
    {
        //我的类的类不是我的类。。。要怎么跨类调用私有成员
        //此处是Adult->Children->Food的数据成员，已经无法调用Children对象的类成员了，看下能不能提供类的接口

        //yeahhhhh，再写一个成员函数返回引用即可
        children[i].invokePeanuts().setAmount(peanutsGroup);
        children[i].invokeCarrots().setAmount(carrotsGroup);
        children[i].invokeBananas().setAmount(bananaGroup);
    }
    //分剩下的给最后一个孩子,似乎只分了最后一个孩子，对的对的，有时候只有一个孩子，搞错了
    this->children[this->getChildrenNumber() - 1].invokePeanuts().in_decreaseAmount(bananasOwned.getAmount() % getChildrenNumber());
    this->children[this->getChildrenNumber() - 1].invokeCarrots().in_decreaseAmount(carrotsOwned.getAmount() % getChildrenNumber());
    this->children[this->getChildrenNumber() - 1].invokeBananas().in_decreaseAmount(bananasOwned.getAmount() % getChildrenNumber());
    //清空大人有的，写一个clear函数吧，放在食物类
    bananasOwned.clear();
    carrotsOwned.clear();
    peanutsOwned.clear();
}

vector <Child>& Adult::getChildren() //返回孩子列表
{
    return children;
}

//Child类
Child::Child()
{
    initializeID();
}
//数据成员操作函数
void Child::initializeID()
{
    setPassID("D000000C");
}

Peanut& Child::invokePeanuts()
{
    return peanuts;
}
Carrot& Child::invokeCarrots()
{
    return carrots;
}
Banana& Child::invokeBananas()
{
    return bananas;
}

//行为函数

/*此处喂养的参数设置为围栏对象，要反馈一下其脏度，通过围栏喂，合理
不过在test函数中要通过zoo对象多层访问，用点运算符
Child和Keeper各自与围栏挂钩，不相干，对应的操作都是围栏对象
三个参数，对象，种类，量(修改为一个，量和种类都可以在Child成员里找到)
也罢，就简单的
*/
void Child::feed(MonkeyEnclosure& monkeyEnclosure, int wantFeed)
{
    int ActuallyFeed = 0;
    //喂食前判断动物饱了没有、围栏关了没有，判断函数写在动物类和围栏类里
    if (monkeyEnclosure.returnOpenStatus())
    {
        if (wantFeed >= monkeyEnclosure.getMonkey().getFoodCapacity() - monkeyEnclosure.getMonkey().getEatenFood())
            ActuallyFeed = monkeyEnclosure.getMonkey().getFoodCapacity() - monkeyEnclosure.getMonkey().getEatenFood();
        else ActuallyFeed = wantFeed;
        bananas.in_decreaseAmount(-ActuallyFeed);//减掉孩子手上的
        monkeyEnclosure.getMonkey().eat(ActuallyFeed);//喂给对象
        monkeyEnclosure.helpIncrementDirt(ActuallyFeed);//增加围栏的脏度
    }
}
void Child::feed(GiraffeEnclosure& giraffeEnclosure, int wantFeed)
{
    int ActuallyFeed = 0;
    if (giraffeEnclosure.returnOpenStatus())
    {
        if (wantFeed >= giraffeEnclosure.getGiraffe().getFoodCapacity() - giraffeEnclosure.getGiraffe().getEatenFood())
            ActuallyFeed = giraffeEnclosure.getGiraffe().getFoodCapacity() - giraffeEnclosure.getGiraffe().getEatenFood();
        else ActuallyFeed = wantFeed;
        carrots.in_decreaseAmount(-ActuallyFeed);
        giraffeEnclosure.getGiraffe().eat(ActuallyFeed);
        giraffeEnclosure.helpIncrementDirt(ActuallyFeed);
    }
}
void Child::feed(ElephantEnclosure& elephantEnclosure, int wantFeed)
{
    int ActuallyFeed = 0;
    if (elephantEnclosure.returnOpenStatus())
    {
        if (wantFeed >= elephantEnclosure.getElephant().getFoodCapacity() - elephantEnclosure.getElephant().getEatenFood())
        {
            ActuallyFeed = elephantEnclosure.getElephant().getFoodCapacity() - elephantEnclosure.getElephant().getEatenFood();
        }
        else ActuallyFeed = wantFeed;
        this->peanuts.in_decreaseAmount(-ActuallyFeed);
        elephantEnclosure.getElephant().eat(ActuallyFeed);
        elephantEnclosure.helpIncrementDirt(ActuallyFeed);
    }
}
//构造函数
Zoo::Zoo() : runningDay(0), adultsNumber(0), openStats(0), historicVisitorAmount(0),closingEnclosureAmount(0) 
    { 
    EnclosureToClean.resize(7);    
    for(int i = 0; i < 3;i++)
    {
        this->monkeyEnclosure[i].openEnclosure();
    }
    for(int i = 0; i < 2; i++)
    {
        this->giraffeEnclosure[i].openEnclosure();
    }
    this->elephantEnclosure.openEnclosure(); 
    }
//运营函数
int Zoo::simulateOneDay() //用int作为返回值，进行一个菜单选择，记录状态，是否继续运营
{
    //一天重新开始时需要处理的数据
    this->openZoo();
    this->runningDay++;
    int today_bananas = foodSeller.getBanana().getAmount();
    int today_carrots = foodSeller.getCarrot().getAmount();
    int today_peanuts = foodSeller.getPeanut().getAmount();
    Money today_money = foodSeller.getMoneyOwned();
    cout << "==============\n";
    cout << "\nContinue to run !\n Day" << runningDay << ": \n";
    this->setAdultsNumber(0);
    this->zooKeeper.resetStatus();
    cout << "zooKeeper " << this->zooKeeper.getName() << " is energetic!\n===========\n\n";
    // this->EnclosureToClean.clear();
    //重新设置各类动物的EatenFood
    for (int i = 0; i < 3; i++)
    {
        this->monkeyEnclosure[i].getMonkey().setEatenFood(0);
    }
    for (int i = 0; i < 2; i++)
    {
        this->giraffeEnclosure[i].getGiraffe().setEatenFood(0);
    }
    this->elephantEnclosure.getElephant().setEatenFood(0);

    Zoo::generateAdults();//设置了清空先前Adult的vector,同时生成adult
    cout << "There " << getAdultsNumber() << " adults bring their kids to the zoo.\n===========" << endl;
    //买票、买食物、分配食物、喂动物
    for (int i = 0; i < this->getAdultsNumber(); i++)
    {
        adults.at(i).buyZooTicket();//正常
        //买食物前记录一下状态，即可，当食物为0时Adult不会再进行购买
        if (this->foodSeller.getBanana().getAmount() == 0 || this->foodSeller.getCarrot().getAmount() == 0 || this->foodSeller.getPeanut().getAmount() == 0) break;
        adults.at(i).buyFood(this->foodSeller);//已经优化，帅！
        //调试这一块的时候，食物发过去了，但是发之前每个adult的食物都是0不知道为什么
        // cout << "An adult bought a ticket and food.Left money" << adults.at(0).getMoneyOwned() << endl;
        // cout << "before distribute adult has " << adults.at(0).getPeanutOwned().getAmount() << " peanuts" << endl;
        adults.at(i).distributeFood();
        // cout << "======================" << adults.at(i).getChildren().at(0).invokeBananas().getAmount() << endl;
        
        //喂食物
        for (int j = 0; j < this->adults.at(i).getChildrenNumber(); j++)
        {
           
            //判断能否喂食，需要在每个小孩喂食前进行判断，故没有选择初始化一些记录的数据在for外部
            //此处判断能够喂食的栅栏，不需要，每个小孩的feed函数可以判断

            //以下所有都考虑为固定数组，不进行优化了
            //喂猴子
            for (int k = 0; k < 3; k++)
            {
                this->adults.at(i).getChildren()[j].feed(this->monkeyEnclosure[k], this->adults.at(i).getChildren().at(j).invokeBananas().getAmount() / (3 - k));//实现了较好的分配，比例随个数变化
            }
            //喂鹿
            for (int k = 0; k < 2; k++)
                this->adults.at(i).getChildren()[j].feed(this->giraffeEnclosure[k], this->adults.at(i).getChildren().operator[](j).invokeCarrots().getAmount() / (2 - k));
            //喂大象
            this->adults.at(i).getChildren()[j].feed(this->getElephantEnclosure(), this->adults.at(i).getChildren().at(j).invokePeanuts().getAmount());
        }
    }
        cout << "Harvest full! Today has solden " << today_bananas - foodSeller.getBanana().getAmount() << " bananas." << ' '
                                                 << today_carrots - foodSeller.getCarrot().getAmount() << " carrots." << ' '
                                                 << today_peanuts - foodSeller.getPeanut().getAmount() << " peanuts." << endl;
        cout << "Today our zoo has earned " << foodSeller.getMoneyOwned() - today_money << "\n==========="<<endl;
        cout << "Enclosure's dirty level has increased, now:\n";
        for(int i = 0; i < 3; i++)
        cout << "monkey enclosure " << i << ": " << monkeyEnclosure[i].getDirtyLevel() << endl;
        for(int i = 0; i < 2; i++)
        cout << "giraffe enclosure " << i << ": " << giraffeEnclosure[i].getDirtyLevel() << endl;
        cout << "elephant enclosure: " << elephantEnclosure.getDirtyLevel() << endl;
    //保存游客数量到Zoo数据成员中
    int kidsNumber = 0;//计算小孩
    for (int i = 0; i < this->getAdultsNumber(); i++)
    {
        kidsNumber += this->adults.at(i).getChildrenNumber();
    }
    int todayVisitor = this->getAdultsNumber() + kidsNumber;
    this->increaseVisitorAmount(todayVisitor);
    cout << "============\n";
    cout << "Congratulation! Today there are " << getAdultsNumber() + kidsNumber << " visitors\n\n";

    cout << "Zookeeper " << zooKeeper.getName() << " starts to clean the enclosure" << endl;
    //打扫围栏并重新开启
    for(int i = 0; i < 3; i++)
    {
        if(!monkeyEnclosure[i].returnOpenStatus() && !zooKeeper.returnWorkingStatus())
        {
            zooKeeper.cleaningMonkeyEnclosure(monkeyEnclosure[i]);
            closingEnclosureAmount --;
            cout << "Laborious! Monkey enclosure" << i << "has been cleaned\n";
        }
    }
    for(int i = 0 ; i < 2; i++ )
    {
        if( !giraffeEnclosure[i].returnOpenStatus() && !zooKeeper.returnWorkingStatus())
        {
            zooKeeper.cleaningGiraffeEnclosure(giraffeEnclosure[i]);
            closingEnclosureAmount --;
            cout << "Laborious! Giraffe enclosure" << i << "has been cleaned\n";
        }
    }
    if(!elephantEnclosure.returnOpenStatus() && !zooKeeper.returnWorkingStatus())
    {
        zooKeeper.cleaningElephantEnclosure(elephantEnclosure);
        closingEnclosureAmount --;
        cout << "Laborious Taoshen! Elephant enclosure" << "has been cleaned\n" ;
    }
    //ZooKeeper检查、关闭围栏，已关闭的不用检查，顺序打扫就行
    //int closedAmount = 0; // 加入需要清理的围栏向量后不再需要该参数,但是不知道vector如何扩容，不过size函数是返回元素个数，可行
    //检查猴子，鹿，大象
    cout << "Zookeeper " << zooKeeper.getName() << " is checking enclosures\n" ;
    for (int i = 0; i < 3; i++)
    {
        if(monkeyEnclosure[i].returnOpenStatus())
        {
            this->zooKeeper.checkAndCloseMonkeyEnclosure(monkeyEnclosure[i]);
            if(!monkeyEnclosure[i].returnOpenStatus()) cout << "Monkey Enclosure " << i << " is closed." << endl,closingEnclosureAmount ++;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if(giraffeEnclosure[i].returnOpenStatus())
        {
            this->zooKeeper.checkAndCloseGiraffeEnclosure(giraffeEnclosure[i]);
            if(!giraffeEnclosure[i].returnOpenStatus()) cout << "Giraffe Enclosure " << i << " is closed" << endl,closingEnclosureAmount ++;

        }
    }

    if(elephantEnclosure.returnOpenStatus())
    {
        this->zooKeeper.checkAndCloseElephantEnclosure(elephantEnclosure);
        if(!elephantEnclosure.returnOpenStatus()) cout << "ElephantEnclosure is closed" << endl, closingEnclosureAmount ++;

    }
    
    cout << "closingEnclosureAmount: " << closingEnclosureAmount << endl;

    //检查foodseller食物卖完没有
    if (foodSeller.getBanana().getAmount() == 0) return 5;
    if (foodSeller.getCarrot().getAmount() == 0) return 4;
    if (foodSeller.getPeanut().getAmount() == 0) return 3;

    this->closeZoo();
    _sleep(1000);
    cout << "==============\n";
    return 0;//一切正常，返回0继续运营

}

void Zoo::simulateAllProcess()
{
    int a = 0;//状态码，正常运营
    while (!a)
    {
        a = simulateOneDay();
    }
    cout << "=====================\n";
    switch (a)
    {
    case 1:
        cout << "\n\nZoo closed, because  zookeeper can't clean so many enclosure";
        break;
    case 2:
        cout << "\n\nZoo closed, because zookeeper had worked so many times(over 10)";
        break;
    case 3:
        cout << "\n\nZoo closed, because foodseller's peanuts had solden out";
        break;
    case 4:
        cout << "\n\nZoo closed, because foodseller's carrots had solden out";
        break;
    case 5:
        cout << "\n\nZoo closed, because foodseller's bananas had solden out";
        break;
    default:
        cout << "\n\nZoo closed because of other reasons";
    }
    //信息展示
    cout << "\n\ninformation of zoo:  \nZoo openDays: " << this->runningDay
        << "\nZoo's historical visitor amount: " << this->historicVisitorAmount
        << "\n\nThe money that foodseller earned: " << this->foodSeller.getMoneyOwned()
        << "\nThe food that foodseller left: \n" ;
    cout<< "banana: "<<this->foodSeller.getBanana().getAmount() << endl << "peanut: "<<this->foodSeller.getPeanut().getAmount() << endl << "carrot: "<<this->foodSeller.getCarrot().getAmount() << endl;
    cout<< "\nThe days that zookeeper " << this->zooKeeper.getName() << " worked: " << this->zooKeeper.getWorkDays()
        << "\n\nThe times that every kind of enclosure closed: ";
    int monkeyEnclosureClosedTimes = 0;
    int giraffeEnclousreClosedTimes = 0;
    for (int i = 0; i < 3; i++)
        monkeyEnclosureClosedTimes += this->monkeyEnclosure[i].getCloseTimes();
    for (int i = 0; i < 2; i++)
        giraffeEnclousreClosedTimes += this->giraffeEnclosure[i].getCloseTimes();

    cout << "\nMonkeyEnclousre: " << monkeyEnclosureClosedTimes
        << "\nGiraffeEnclosure: " << giraffeEnclousreClosedTimes
        << "\nElephantEnclosure: " << elephantEnclosure.getCloseTimes();
}

//数据成员操作函数
// void Zoo::generateAdults()
// {
// 	//随机产生成年游客，用固定数组接受，随后复制到了Zoo类的动态成员中
// 	std::default_random_engine e;
// 	std::uniform_int_distribution<int> u(20, 40);
// 	e.seed(time(0));
// 	adultsNumber = u(e);
// 	Adult adults1[40];
// 	for (int i = 0; i < adultsNumber; i++)
// 	{
// 		string day = to_string(runningDay);
// 		string accessNumber = to_string(i);
// 		for (int j = 0; ((3 - j > 0) && (day.size() - 1 - j) >= 0); j++)
// 		{
// 			adults.operator[](i).getPassIDReference()[3 - j] = day[day.size() - 1 - j];
// 		}
// 		for (int j = 0; ((6 - j > 3) && (accessNumber.size() - 1 - j >= 0)); j++)
// 		{
// 			adults.operator[](i).getPassIDReference()[6 - j] = accessNumber[accessNumber.size() - 1 - j];
// 		}
// 	}
// 	//加入到动态数组中进行维护
// 	adults.clear();
// 	for (int i = 0; i < adultsNumber; i++)
// 	{
// 		adults.push_back(adults1[i]);
// 	}
// }
void Zoo::generateAdults()
{
    adults.clear();
    srand(time(0));

    this->adultsNumber = rand()%21 + 20;
    adults.resize( adultsNumber );
    for (int i = 0; i < adultsNumber; i++)
    {
        //    string day = to_string( this -> runningDay );
        //    string accessNumber = to_string(i + 1);

        //    string adultID = "D" + day.substr(day.size() - 3) + accessNumber;

        //    adults.at(i).setPassID(adultID);
        adults.at(i).generateChildren();
    }
}

//已经优化，删去下列函数

//void Zoo::generateChildrenID()
//{
//	int Sequence = 0;
//	for (int i = 0; i < this->getAdultsNumber(); i++)//遍历Adult
//	{
//		for (int j = 0; j < this->adults->operator[](i).getChildrenNumber(); j++)//遍历Child
//		{
//			Sequence += j;
//			string childID = to_string(Sequence);
//			for (int k = 0; (6 - k > 3) || (childID.size() - 1 - k); k++)//遍历并设置后三位ID
//			{
//				this->adults->operator[](i).getChildren().operator[](j).getPassIDReference()[6 - j] = childID[childID.size() - 1 - k];
//			}
//		}
//	}
//}


int Zoo::getAdultsNumber()
{
    return adultsNumber;
}

void Zoo::setAdultsNumber(int a)
{
    if (a >= 0)
        adultsNumber = a;
    else
        throw invalid_argument("Adults number must be >= 0");
}

//辅助函数

//将数字转化为字符串，这里只写三位的转化，再长一些也同理处理，
//可以多写一些，然后根据要求再写if截取
/*string numberToString3( int a )
{
    string fun;
    if ( a >= 0 && a <= 999)
    {
        char b = ( (a / 100) + 48);
        char c = ( (a / 10 % 10) +48);
        char d = ( (a % 10) +48);
        fun = b + c + d;
    }
    else
        throw ("function numberToString wrong");
}
*/
//没写成功，调用函数 to_string
void Zoo::increaseVisitorAmount(int TodayVisitor)
{
    this->historicVisitorAmount += TodayVisitor;
}
void Zoo::openZoo()
{
    this->openStats = true;
}