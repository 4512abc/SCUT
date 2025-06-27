#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <stack>
#include <vector>
#include "Cell.h"
#include "WADialog.h"
#include "ACDialog.h"
#include "TimeWatch.h"
#include "Player.h"
#include "qgridlayout.h"
#include <QTimer>
enum Operation {
    LEFT_ROTATE,  // 左旋转操作
    RIGHT_ROTATE, // 右旋转操作
    BURN          // 燃烧操作
};
class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr,size_t=3,Player *onlinePlayer=nullptr);
    ~Game();
    void onBackButtonClicked();             //用于响应返回按钮的点击的槽函数
    void setLayoutAndForm();                //设置和调整布局
    void left_rotate();                     //左旋转操作
    void right_rotate();                    //右旋转操作
    void burn();                            //燃烧操作
    void undo();                            //回撤操作
    void judge();                           //判断操作
    void WA();                              //响应WA的函数，提示用户答案错误
    void AC();                              //响应AC的函数，提示用户答案正确
    void calculateTime();                   //计算时间
    void calculateSteps();                  //计算步数
    void calculateBackSteps();              //计算回退步数
    void generateRandomMap(const int);      //生成不同难度的随机地图
    void setGame(const int gameNumber);     //设置游戏
    void updatePlayer();                    //更新用户信息
    void startAaginst();                    //开始对抗的函数
    void endAgainst();                      //结束对抗的函数
    void change();                          //执行对抗的函数
    void setNewGame();                      //负责跳转到下一个关卡
    void connectOperation();                //连接操作计数
    void cleanGridLayout(QGridLayout*);     //切换模式需要修改布局，先清空布局
    void createGridLayout(QGridLayout*,std::vector<std::vector<Cell>>&);            //再重新构建布局
    void help();                            //调用提示功能
    void calculateHelp();                   //产生提示功能
    bool checkIsAllOne();                   //检查是否全部为1
signals:
    void backToMain();                      //发送返回到主页面信号
    void start();                           //发送开始计时的信号
    void end();                             //发送结束计时的信号
    void updateRanking(const int);          //更新排行榜
    void updateData(const int);             //更新玩家的游戏记录
private:
    size_t m_size;                                              //关卡的大小
    std::vector<std::vector<Cell>> m_cells;                     //玩家操作的地图
    std::vector<std::vector<Cell>> answers;                     //答案
    std::stack<std::vector<std::vector<Cell>>> m_cellsHistory;  //存储每一次操作的栈，用于回撤
    TimeWatch *TimeWatchWidget;             //计时器
    int steps;                              //操作步数
    int backSteps;                          //回退步数
    int nowLevel;                           //当前等级
    bool isLevel;                           //是否是关卡模式
    int randomMapLevel;                     //随机模式难度
    WADialog *waDialog;                     //waDialog对话框，提示玩家答案错误
    ACDialog *acDialog;                     //acDialog对话框，提示玩家答案正确
    Player *m_player;                       //一个指向在线玩家的指针
    QTimer *m_timer;                        //用于响应时间，执行对抗
    QGridLayout *gridLayout;                //操作图的布局
    QGridLayout *answerLayout;              //答案图的布局
    QHBoxLayout *paintingLayout;            //显示框：计时器，操作图，答案图
    QVBoxLayout *Vlayout;                   //主布局
    QHBoxLayout *Hlayout_1;                 //水平布局一：调整：燃烧，左旋转，右旋转，回撤这四个按钮的布局
    QHBoxLayout *Hlayout_2;                 //水平布局二：调整，启动对抗，结束对抗，提交，退出四个按钮的布局
    QPushButton *button1;                   //左旋转按钮
    QPushButton *button2;                   //右旋转按钮
    QPushButton *button3;                   //燃烧按钮
    QPushButton *button4;                   //回撤按钮
    QVector<Operation> helps;               //提示功能
    QVector<Operation> Finals;              //最后的提示功能
};

#endif // GAME_H
