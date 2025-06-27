#include "MapChoose.h"
#include <QFile>
MapChoose::MapChoose(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *Hlayout=new QHBoxLayout;

    //设置返回主页面的按钮
    backButton=new QPushButton(this);
    backButton->setText("#over 返回#  ^-^");


    backButton->setStyleSheet("QPushButton {"
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
    backButton->setFixedSize(200,100);
    Hlayout->addStretch(1);
    Hlayout->addWidget(backButton);
    Hlayout->addStretch(1);
    connect(backButton,&QPushButton::clicked,this,&MapChoose::onBackButtonClicked);

    //创建地图选择按钮
    mapButton = new QPushButton[18];

    QGridLayout *gridLayout=new QGridLayout;
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    for(int i=1;i<=12;i++)
    {
        mapButton[i].setFixedSize(300,100);
        connect(&mapButton[i], &QPushButton::clicked,this,[this, i]() {
            emit emitNumber(i);         //发送对应的关卡编码，由Game对象接受，并生成对应的关卡
        });

        //发送跳转到游戏的信号，由LevelTwo对象接收，跳转到游戏页面
        connect(&mapButton[i],&QPushButton::clicked,this,&MapChoose::ToGame);

        gridLayout->addWidget(&mapButton[i],(i-1)/4,(i%4?(i-(i/4)*4):4));
    }

    //设置按钮的格式
    mapButton[1].setText(QString("#1#  AC  <（￣︶￣）>"));
    mapButton[1].setStyleSheet("QPushButton {"
                               "    background-color: green;"
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
                               "}"
                               );

    mapButton[2].setText(QString("#2#  WA  〒▽〒"));
    mapButton[2].setStyleSheet("QPushButton {"
                               "    background-color: red;"
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

    mapButton[3].setText(QString("#3#  TLE  ╮(￣▽￣”)╭"));
    mapButton[3].setStyleSheet("QPushButton {"
                               "    background-color: darkBlue;"
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

    mapButton[4].setText(QString("#4#  WA  ～>_<～"));
    mapButton[4].setStyleSheet("QPushButton {"
                               "    background-color: red;"
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

    mapButton[5].setText(QString("#5#  RE  （￣口￣）"));
    mapButton[5].setStyleSheet("QPushButton {"
                               "    background-color: purple;"
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

    mapButton[6].setText(QString("#6#  AC  ╰（￣▽￣）╭"));
    mapButton[6].setStyleSheet("QPushButton {"
                               "    background-color: green;"
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
    mapButton[7].setText(QString("#7#  PC  （╯‵□′）╯︵┴─┴"));
    mapButton[7].setStyleSheet("QPushButton {"
                               "    background-color: orange;"
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
    mapButton[8].setText(QString("#8#  RE  囧"));
    mapButton[8].setStyleSheet("QPushButton {"
                               "    background-color: purple;"
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

    mapButton[9].setText(QString("#9#  MLE …（⊙_⊙；）… 嘎？"));
    mapButton[9].setStyleSheet("QPushButton {"
                               "    background-color: darkBlue;"
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

    mapButton[10].setText(QString("#10#  CE  （┬_┬）↘"));
    mapButton[10].setStyleSheet("QPushButton {"
                               "    background-color: rgb(210, 210, 0);"
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

    mapButton[11].setText(QString("#11#  UKE  （╬￣皿￣）=○"));
    mapButton[11].setStyleSheet("QPushButton {"
                               "    background-color: Gray;"
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

    mapButton[12].setText(QString("#12#  AC  （￣︶￣）↗"));
    mapButton[12].setStyleSheet("QPushButton {"
                               "    background-color: green;"
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


    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(Hlayout);
}

MapChoose::~MapChoose()
{
    if(backButton!=nullptr)
    {
        delete backButton;
        backButton=nullptr;
    }
    if(mapButton!=nullptr)
    {
        delete []mapButton;
        mapButton=nullptr;
    }
}

void MapChoose::onBackButtonClicked()
{
    emit backToMain();
}


