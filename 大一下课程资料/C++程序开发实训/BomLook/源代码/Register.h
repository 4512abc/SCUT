#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "Player.h"
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr,Player *onlinePlayer=nullptr);
    ~Register();
public slots:
    void onBackLogin();                             //响应返回login页面的槽函数
signals:
    void backToLogin();                             //发送信号：返回login页面
private:
    bool isExit(const QString&,const QString&);       //判断当前注册的账号是否已经存在
    void testRegister();                            //检测注册是否合法的函数
    void addPlayer();                               //更新文件

    Ui::Register *ui;
    Player *m_player;
};

#endif // REGISTER_H
