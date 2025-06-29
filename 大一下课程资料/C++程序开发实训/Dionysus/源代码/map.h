#ifndef MAP_H
#define MAP_H

#include <QRect>
#include <QFile>
#include <QThread>
#include <QTime>
#include <QElapsedTimer>
#include "config.h"
#include "slice.h"

class CustomMatrix//用于生成地图的随机类
{
    QList<int> sliceToPut = {4,3,3,2,2,1,1};
public:
    // 使用QVector来存储每一行
    QVector<QVector<int>> data;//从0到5
    //使用QVector来记录步数，以便于提示
    QVector<int> sliceKind;
    QVector<int> pos_X;
    QVector<int> pos_Y;

    // 初始化6x6的矩阵
    CustomMatrix();
    // 施放函数
    void cast(int size, int x, int y);
    bool isCastable(int size, int x, int y);
    bool generateMapRandomly();

    void updateSliceToPutList();//在无尽模式点击重置后要更新，否则生成完之后List是空的
};

//以下是判断地图是否有解的工具类
enum Status{correct, hungry, full};
enum ElementKind{CROSS,TRIANGLE,CIRCLEINPRACTICE,CIRCLEINCOMPETITION,SQUARE};

class Element
{
private:
    int castAmount = 0;
public:
    Element() { castAmount = 0; }
    ~Element(){}

    virtual float convertAmountToHungry() { return 0; }
    virtual bool isFull() { return true; }
    virtual bool isAnswer() { return false; }
    virtual int getElementKind() { return -1; }
    void addCastedAmount();
    void decCastedAmount();
    int getAmount();
};

class Square : public Element
{
public:
    float convertAmountToHungry() override;
    bool isFull() override;
    bool isAnswer() override;
    int getElementKind() override;
};

class CircleInPractice : public Element
{
public:
    float convertAmountToHungry() override;
    bool isFull() override;
    bool isAnswer() override;
    int getElementKind()override;
};

class CircleInCompetition : public Element
{
public:
    float convertAmountToHungry() override;
    bool isFull() override;
    bool isAnswer() override;
    int getElementKind()override;
};

class Triangle : public Element
{
public:
    float convertAmountToHungry() override;
    bool isFull() override;
    bool isAnswer() override;
    int getElementKind() override;
};
class Cross : public Element
{
public:
    float convertAmountToHungry() override;
    bool isFull() override;
    bool isAnswer() override;
    int getElementKind() override;
};

class Map
{
public:
    Map();

    void loadSliceFromFile(int mapMode);//就只读地图吧，切片默认设置为七个？不行不行，还是都读好了，然后读单个的
        //个数据类型，QT一般不可以像书上那样实现一整个对象的读取，那要写入的可能需要慎重一些，或者说不同文件用相同的序号，那还是要重新创文件
    void loadSliceFromInput(int *arr);
    void loadSliceFromOther(int playMode);
    void loadSliceRandomly();
    void defaultSliceToPut();
    bool HasAnswer(){return hasAnswer;}
    bool setHasAnswer(bool a){hasAnswer = a;}
    void setTargetSlicePixmap(int mapMode);
    void setSliceToPutPixmap();
    //一些基本的接口函数，定义将就在头文件中写
    Slice &getTargetSlice(int i){return targetSlice[i];}
    sliceToPut &getSliceToPut(int i){return sliceToPut[i];}
    QString getTips(QVector<int> sliceKind, QVector<int> numberInArray,
                    QVector<int> dropPos_x, QVector<int> dropPos_y);//根据playwidget的存储模式，设置提示


    //用于判断是否有解的函数
    ~Map();//全部delete掉，目前用vector不需要了
    //先写不加饥饿感的版本，但是显然在我的架构下不可以，直接开写饥饿版！我看我也是饿了
    int solveWays();//解的数量，map可以有一个解法的vector，第一层是解法，第二层存储切片类型，第三层是切片应当放置的位置
    bool canBeSolved();//优先级最高算法，有就返回

    bool canBeCasted(int size, int column, int row);//判断该位置能不能放
    void cast(int size, int column, int row);//放上去
    bool isAnswer();//检测是否为答案
    Element getElementArray(int i) { return *elementArray[i]; }
    //必要的一些函数
    void setMapInInt(int* a);//设置

    //饥饿感参数设置在比赛模式下没有特别的
    //加入饥饿感后需要的函数
    int mostHungryArea(int sliceSize, QVector<QVector<bool>>);//计算的是该切片所有放置位置中饥饿感最强的位置，
        //传入一个bool类型可放置位置的数组，利用convertAmountToStatus计算，返回放置区域在地图中的索引
    void convertMapToElement(int mode);
    void resetPotential(QVector<QVector<bool>>&);
    void printElementMap();
    void deCast(int size, int pos_x, int pos_y);

private:
    class Slice targetSlice[36];
    class sliceToPut sliceToPut[7];//按照一个4*4，两个3*3，两个2*2，一个1*1的顺序
    int mapInInt[36];//支持后续的文件输入输出一个数字序列，对应slice的枚举类型
    int answer_sliceKind[7] = {0};
    int answer_pos_X[7] = {0};
    int answer_pos_Y[7] = {0};
    bool hasAnswer = false;
    //用于判断地图是否有解的数据成员
    Element* elementArray[36];
    QVector<QVector<bool>> potential0;
    QVector<QVector<bool>> potential1;
    QVector<QVector<bool>> potential2;
    QVector<QVector<bool>> potential3;
    QVector<QVector<bool>> potential4;

    Square square_ForChoose[36];
    Triangle triangle_ForChoose[36];
    CircleInCompetition circleInCompetition_ForChoose[36];
    CircleInPractice circleInPractice_ForChoose[36];
    Cross cross_ForChoose[36];

};
#endif // MAP_H
