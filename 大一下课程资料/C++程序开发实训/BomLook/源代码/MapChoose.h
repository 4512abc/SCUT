#ifndef MAPCHOOSE_H
#define MAPCHOOSE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
class MapChoose : public QWidget
{
    Q_OBJECT
public:
    explicit MapChoose(QWidget *parent = nullptr);
    ~MapChoose();
    void onBackButtonClicked();         //接受返回按钮点击的槽函数
    void openMap(int number);           //打开地图
private:
    QPushButton *backButton;            //返回主页面的地图
    QPushButton *mapButton;             //12个关卡对应的地图
signals:
    void backToMain();                  //发送返回主页面的信号
    void emitNumber(int number);        //发送对应的关卡编码，由Game对象接受，并生成对应的关卡
    void ToGame();                      //发送跳转到游戏的信号，由LevelTwo对象接收，跳转到游戏页面
};

#endif // MAPCHOOSE_H
