#include "ACDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
ACDialog::ACDialog()
{
    //this->setAttribute(Qt::WA_QuitOnClose, false);
    setWindowTitle("Accepted");                                 //设置AC对话框的标题为Accepted
    QIcon icon(":/icons/resource/icons/黑客 (时间轴).png");      //设置AC对话框的icon图片
    setWindowIcon(icon);                                        //设置icon为AC对话框的图标

    //设置label图片，祝贺玩家通关游戏
    QLabel *label=new QLabel(this);
    QPixmap img(":/images/resource/picture/v2-30718c06f344034c0800518670382a79_1440w.png");
    label->setPixmap(img);

    QVBoxLayout *Vlayout=new QVBoxLayout(this);

    //设置返回按钮和跳转到下一个关卡的按钮
    QPushButton *BackButton=new QPushButton("返回",this);
    connect(BackButton,&QPushButton::clicked,this,&ACDialog::back);
    QPushButton *NextLevelButton=new QPushButton("下一关",this);
    connect(NextLevelButton,&QPushButton::clicked,this,&ACDialog::next);

    //调整按钮和label的布局
    QHBoxLayout *Hlayout=new QHBoxLayout;
    Hlayout->addStretch(1);
    Hlayout->addWidget(BackButton);
    Hlayout->addStretch(1);
    Hlayout->addWidget(NextLevelButton);
    Hlayout->addStretch(1);
    Vlayout->addWidget(label);
    Vlayout->addLayout(Hlayout);
}


ACDialog::~ACDialog()
{

}


void ACDialog::back()
{
    //发出信号，回到主页面，也就是LevelTwo页面
    emit backToMain();
    this->close();
}

void ACDialog::next()
{
    //发出信号，跳转到下一个关卡
    emit goToNextLevel();
    this->close();
}

