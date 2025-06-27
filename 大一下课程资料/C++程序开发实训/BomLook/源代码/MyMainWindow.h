#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QParallelAnimationGroup>
#include <QPushButton>
#include <QKeyEvent>
#include <QLabel>
#include "GameIntroduction.h"
#include "LevelTwo.h"
#include "Login.h"
#include "Home.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MyMainWindow;
}
QT_END_NAMESPACE

class MyMainWindow : public QWidget
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
protected:
    void closeEvent(QCloseEvent *event)override;    //重载closeEvent函数，用于确认退出游戏时，对文件进行更新
    void paintEvent(QPaintEvent *event)override;    //重载paintEvent函数，用于自动调整背景页面的大小
    bool eventFilter(QObject *obj, QEvent *event)override;  //重载eventFilter函数，用于键盘操作
public slots:
    void switchToSubPage();                             //跳转到子页面：获取要切换到的子页面的按钮对应的页码
    void enterToSubPage(int);                           //跳转到子页面: 键盘控制
    void switchToMainPage();                            //跳转到主页面
    void animateSwitch(int fromIndex,int toIndex);      //负责跳转页面的执行
private:
    Ui::MyMainWindow *ui;
    void setupMainPage();           //设置主页面函数
    void setupSubPages();           //设置子页面函数

    QImage background;                      //背景图片
    QStackedWidget pages;                   //用于存储子页面
    QParallelAnimationGroup animation;      //一组页面切换动画
    GameIntroduction *gameIntroduction;     //游戏介绍页面
    LevelTwo *startGame;                    //游戏模式选择页面
    Login *login;                           //登录页面
    Player *onlinePlayer;                   //当前在线的玩家
    Home *home;                             //玩家的个人用户页面
};
#endif // MYMAINWINDOW_H
