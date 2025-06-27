#ifndef GAMEINTRODUCTION_H
#define GAMEINTRODUCTION_H

#include <QWidget>

class GameIntroduction: public QWidget
{
    Q_OBJECT
public:
    GameIntroduction(QWidget *parent);
    ~GameIntroduction();
    void onBackButtonClicked();     //槽函数，接受返回主页面按钮的点击
signals:
    void backToMain();      //发出返回主页面的信号：主页面接收
};

#endif // GAMEINTRODUCTION_H
