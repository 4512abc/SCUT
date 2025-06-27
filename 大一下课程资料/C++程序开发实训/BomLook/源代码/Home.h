#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "Player.h"
#include "qlabel.h"
#include "qtableview.h"
#include <QTime>
#include <QStandardItemModel>
#include <QGridLayout>
#include "musicPlayer.h"
namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr,Player *onlinePlayer=nullptr);
    ~Home();
    void setFormAndLayout();        //设置与调整布局
    void updatePlayer();            //更新整个用户的数据
    void createModel();             //创建model，生成游戏记录显示的表格
    void updateRow();               //对玩家第一次游玩的某个关卡游戏记录进行更新
    void onBackButtonClicked();     //点击返回主页面按钮，连接的槽函数，并发出返回主页面的信号
signals:
    void backToMain();              //发出返回主页面的信号，由主页面接受并响应
private:
    Ui::Home *ui;
    QLabel *title_name;             //介绍用户名
    QLabel *name;                   //用户名标签
    Player *m_player;               //指向当前登录玩家账号的指针，用于获取数据并生成或者更新游戏记录，
    QTimer *m_timer;                //计时器，用于更新游戏记录
    QStandardItemModel *model;      //生成游戏记录的model
    QTableView *view;               //TableView视图
    QGridLayout *main_layout;       //主布局
    musicPlayer *m_musicPlayer;     //音乐播放器
};

#endif // HOME_H
