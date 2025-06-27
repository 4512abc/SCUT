#ifndef LEVELTWO_H
#define LEVELTWO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QVector>
#include "Game.h"
#include "Player.h"
#include "MapChoose.h"
#include "Ranking.h"
#include "Funny.h"
class LevelTwo:public QWidget
{
    Q_OBJECT
public:
    LevelTwo(QWidget *parent=nullptr,Player *onlinePlayer=nullptr);
    ~LevelTwo();
signals:
    void MakeRandom(const int);                 //发出信号，生成随机地图
    void backToMain();                          //发出信号：返回主页面
public slots:
    void OnBackButtonClicked();                 //接收返回按钮点击的槽函数
    void switchToSubPage();                     //跳转到子页面
    void enterToSubPage(int);                   //键盘操作：操作跳转到子页面
    void switchToGame();                        //跳转到游戏页面
    void switchToMainPage();                    //跳转到主页面
    void generateRandom();                      //选择游戏难度的页面
    void animateSwitch(int fromIndex,int toIndex);      //负责页面切换的函数
    bool eventFilter(QObject *obj,QEvent *event)override;      //重载eventFilter函数，用于键盘操作
private:
    void setupMainPage();                       //设置主页面的函数
    void setupSubPage();                        //设置子页面的函数
    QStackedWidget subPage_Pages;               //用于存储子页面
    QParallelAnimationGroup animation;          //一组页面切换动画
    MapChoose *mapChoose;                       //选择关卡的页面
    Game *game;                                 //游戏页面
    Ranking *m_ranking;                         //排行榜页面
    Funny *m_funny;                             //趣味模式页面
    Player *m_player;                           //指向在线玩家的指针

    QDialog *dialog;                            //显示框，用于选择随机模式的难度
};

#endif // LEVELTWO_H
