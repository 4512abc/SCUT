#include "WADialog.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
WADialog::WADialog(QWidget *parent)
{
    //this->setAttribute(Qt::WA_QuitOnClose, false);
    setWindowTitle("Wrong Answer!");                     //设置WA对话框的标题为Wrong Answer
    QIcon icon(":/icons/resource/icons/黑客攻击.png");    //设置WA对话框的icon图片
    setWindowIcon(icon);                                 //设置icon为WA对话框的图标

    //设置label图片，提示玩家当前答案错误
    QLabel *label=new QLabel(this);
    QPixmap img(":/images/resource/picture/v2-34eaa3567c7e44512fedff2eb7d43674_1440w.jpg");
    label->setPixmap(img);
    QVBoxLayout *Vlayout=new QVBoxLayout(this);

    //设置返回按钮和继续游戏按钮
    QPushButton *NextButton=new QPushButton("退出",this);
    connect(NextButton,&QPushButton::clicked,this,&WADialog::back);
    QPushButton *GoOnButton=new QPushButton("继续尝试",this);
    connect(GoOnButton,&QPushButton::clicked,this,&WADialog::GoOn);

    //调整按钮和label的布局
    QHBoxLayout *Hlayout=new QHBoxLayout();
    Hlayout->addWidget(NextButton);
    Hlayout->addWidget(GoOnButton);
    Vlayout->addWidget(label);
    Vlayout->addLayout(Hlayout);
    setLayout(Vlayout);
}


WADialog::~WADialog()
{

}


void WADialog::back()
{
    //发出信号，回到主页面，也就是LevelTwo页面
    emit backToMain();
    this->close();
}


void WADialog::GoOn()
{
    //继续游戏，关闭当前对话框
    this->close();
}


