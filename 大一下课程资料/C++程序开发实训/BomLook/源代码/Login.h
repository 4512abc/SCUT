#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Player.h"
#include "Register.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr, Player *onlinePlayer=nullptr);
    ~Login();
signals:
    void updatePlayer();
private:
    bool isExit(const QString&,const QString&);       //判断当前用户账号是否存在
    void testLogin();                               //用于检测输入是否合法
    void switchToRegister();                        //跳转到注册页面
    void switchToLogin();                           //跳转到登录页面
    void checkIsOnline();                           //检测是否处于登录状态
    Ui::Login *ui;
    Register *m_register;                           //注册页面
    Player *m_player;                               //当前登录的账号
};

#endif // LOGIN_H
