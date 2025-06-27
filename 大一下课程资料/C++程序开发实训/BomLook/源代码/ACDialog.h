#ifndef ACDIALOG_H
#define ACDIALOG_H

#include <QDialog>

class ACDialog : public QDialog
{
    Q_OBJECT
public:
    ACDialog();
    ~ACDialog();
public slots:
    void back();    //返回到主页面的函数
    void next();    //跳转到下一个关卡的函数
signals:
    void backToMain();          //发送信号：返回到主页面的函数
    void goToNextLevel();       //发送信号：跳转到下一个页面的函数
};

#endif // ACDIALOG_H
