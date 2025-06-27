#include "GameIntroduction.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextStream>
#include <QResource>
#include <_mingw_mac.h>
GameIntroduction::GameIntroduction(QWidget *parent)
{

    QHBoxLayout *Hlayout=new QHBoxLayout(this);        //水平布局
    QVBoxLayout *mainLayout=new QVBoxLayout;    //主布局

    QPushButton *backButton=new QPushButton("Back to Main");     //返回主页面按钮

    //设置按钮的格式
    QIcon icon(":/icons/resource/icons/钥匙pixel.png");
    backButton->setIcon(icon);
    backButton->setIconSize(QSize(40,40));
    backButton->setStyleSheet("QPushButton {"
                           "    width: 150px;"
                           "    height: 75px;"
                           "    background-color: transparent;"
                           "    border: 2px solid white;"
                           "    border-radius: 10px;"
                           "    color: white;"
                           "    font-family: 'Microsoft YaHei';"
                           "    font-weight: bold;"
                           "    font-size: 20px"
                           "}"
                           "QPushButton:hover {"
                           "    background-color: rgba(255, 255, 255, 0.1);"
                           "}"
                           "QPushButton:pressed {"
                           "    background-color: rgba(255, 255, 255, 0.3);"
                           "}"
                           "QPushButton::icon {"
                           "    padding-right: 10px;"
                           "}"
                           "QPushButton#myButton {"
                           "    border: 2px solid rgba(0, 0, 0, 0.2);"
                           "    box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.4);"
                           "}");

    connect(backButton,&QPushButton::clicked,this,&GameIntroduction::onBackButtonClicked);      //连接按钮点击与返回主页面的槽函数

    //游戏介绍
    QFont Titlefont("Microsoft YaHei",14);
    QFont labelfont("Microsoft YaHei",12);
    QLabel *gameIntroduction=new QLabel("游戏介绍",this);
    gameIntroduction->setFont(Titlefont);
    QLabel *gameIntroductionContent=new QLabel("燃烧的画是一款需要玩家运用逻辑思维和策略的益智游戏，通过移动格子和改变数字来匹配目标图案，最终达到解谜的目的。\n");
    gameIntroductionContent->setFont(labelfont);


    //游戏规则
    QLabel *Title=new QLabel("游戏规则",this);
    Title->setFont(Titlefont);
    QLabel *content=new QLabel("1.点击燃烧：当您点击燃烧按钮时，盘面上所有数字大于1的格子（记作N）的颜色会向下流动。这些格子的颜色将会覆盖下面的格子，并且下面格子的数字会更新为N-1，而被点击的格子的数字更新为1。\n"
                   "2.点击左转、右转按钮：可以使盘面进行旋转，从而改变盘面中格子的位置。\n"
                   "3.点击回撤按钮：点击回撤按钮可将盘面回退到上一个状态。这可以帮助您在错误操作后恢复到之前的状态，重新思考解决方案。\n"
                   "4.点击提交按钮：当盘面上所有格子的颜色、数目与目标图案完全一致时，您可以点击提交按钮。如果您的解决方案正确，则您将获得Accepted（AC）的结果，否则将会获得Wrong Answer（WA）的结果。\n"
                   "5.得分计算：系统会根据您的操作步数和完成某个关卡所花费的时间来计算您的得分。这将影响您在排行榜上的排名。",this);
    content->setFont(labelfont);


    //注意事项
    QLabel *addTitle=new QLabel("注意事项",this);
    addTitle->setFont(Titlefont);
    QLabel *addContent=new QLabel("注意：一旦点击燃烧、回撤、左旋转、右旋转这四个按钮中的任意一个，计时器将自动开始计时。\n"
                                  "如果提交结果为WA，系统不会停止计时，请您注意好时间",this);
    addContent->setFont(labelfont);
    QLabel *modelTitel=new QLabel("游戏模式",this);
    modelTitel->setFont(Titlefont);
    QLabel *modelContent=new QLabel("总共有三种游戏模式：关卡模式，随机模式，趣味模式"
                                    "关卡模式一个有十二个关卡，关卡难度由简到难，关卡模式会对玩家进行计时和评分，并且生成排行榜。\n"
                                    "关卡模式还提供了对抗选项，玩家可以通过点击对抗按钮启动对抗，系统会对玩家的操作造成一些小干扰。注意，这不会影响到排行榜。\n"
                                    "随机模式由关卡随机生成地图，随机模式会对玩家的用时进行计算，但是不会生成排行榜。\n"
                                    "趣味模式需要玩家自己导入地图，并且由系统生成地图，玩家可以进行游玩，并且可以保存地图，导入新地图或者旧地图进行游玩。\n",this);
    modelContent->setFont(labelfont);

    //调整布局
    mainLayout->addStretch(1);
    mainLayout->addWidget(gameIntroduction);
    mainLayout->addStretch(1);
    mainLayout->addWidget(gameIntroductionContent);
    mainLayout->addStretch(1);
    mainLayout->addWidget(Title);
    mainLayout->addStretch(1);
    mainLayout->addWidget(content);
    mainLayout->addStretch(1);
    mainLayout->addWidget(modelTitel);
    mainLayout->addStretch(1);
    mainLayout->addWidget(modelContent);
    mainLayout->addStretch(1);
    mainLayout->addWidget(addTitle);
    mainLayout->addStretch(1);
    mainLayout->addWidget(addContent);
    mainLayout->addStretch(1);
    mainLayout->addWidget(backButton);
    mainLayout->addStretch(1);

    Hlayout->addStretch(1);
    Hlayout->addLayout(mainLayout);
    Hlayout->addStretch(1);
}

GameIntroduction::~GameIntroduction()
{
}

void GameIntroduction::onBackButtonClicked()
{
    emit backToMain();
}
