#include "Home.h"
#include "qheaderview.h"
#include "qtimer.h"
#include "ui_Home.h"
#include <QLabel>
#include <QPushButton>
Home::Home(QWidget *parent, Player *onlinePlayer)
    : QWidget(parent)
    , ui(new Ui::Home),m_player(onlinePlayer)
{
    m_musicPlayer=new musicPlayer(this);
    setFormAndLayout();
    m_timer=new QTimer(this);
    m_timer->start(1000);                                                   //更新速度，单位毫秒
    connect(m_timer,&QTimer::timeout,this,&Home::updatePlayer);
    connect(m_timer,&QTimer::timeout,this,&Home::updateRow);

    model=new QStandardItemModel(this);
    createModel();

    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);               //设置为无法编辑状态

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);     //设置行为固定的大小
    view->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);       //设置列为固定的大小

    for(int col=0;col<view->model()->columnCount();col++)
    {
        view->setColumnWidth(col, 100); // 示例固定宽度
    }
    for(int row=0;row<view->model()->rowCount();row++)
    {
        view->setRowHeight(row, 50); // 示例固定高度
    }

    int width=view->verticalHeader()->width()+view->model()->columnCount()*100;
    int height=view->horizontalHeader()->height()+view->model()->rowCount()*50;

    view->setFixedSize(width,height);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);             //滚动条隐藏
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);               //滚动条隐藏
}

//设置和调整布局
void Home::setFormAndLayout()
{
    view=new QTableView(this);
    title_name=new QLabel(this);
    title_name->setText(QString("用户名"));
    title_name->setFixedSize(100,50);
    title_name->setStyleSheet("QLabel { "
                              "border: 3px solid #4CAF50; "                 //绿色边框
                              "border-radius: 15px; "                       //圆角
                              "padding: 10px; "                             //内边距
                              "background-color: rgba(255,255,255,150); "   //背景颜色
                              "color: #333333; "                            //文字颜色
                              "font-size: 18px; "                           //字体大小
                              "font-family: 'Microsoft YaHei';"
                              "}");

    QPushButton *backButton=new QPushButton("返回",this);
    backButton->setFixedSize(100,50);
    connect(backButton,&QPushButton::clicked,this,&Home::onBackButtonClicked);
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
                              "}"
                              "QPushButton#myButton {"
                              "    border: 2px solid rgba(0, 0, 0, 0.2);"
                              "    box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.4);"
                              "}");

    name=new QLabel(this);
    name->setText(m_player->getUserName());
    name->setFixedSize(100,50);
    name->setStyleSheet("QLabel { "
                        "border: 3px solid #4CAF50; "
                        "border-radius: 15px; "
                        "padding: 10px; "
                        "background-color: rgba(255,255,255,150); "
                        "color: #333333; "
                        "font-size: 18px; "
                        "}");


    main_layout=new QGridLayout(this);
    main_layout->setSpacing(2);
    main_layout->addWidget(title_name,0,1);
    main_layout->addWidget(name,1,1);
    main_layout->addWidget(view,2,1);
    main_layout->addWidget(backButton,1,2);

    main_layout->addWidget(m_musicPlayer,2,4);
}

//更新整个用户的数据
void Home::updatePlayer()
{
    //qDebug()<<"home updatePlayer函数被调用";
    //qDebug()<<"调用者是"<<m_player->getUserName();
    name->setText(m_player->getUserName());
    for(int i=1;i<=12;i++)
    {
        int index=i-1;
        QStandardItem *level_item=model->item(index,0);
        QStandardItem *time_item=model->item(index,1);
        QStandardItem *steps_item=model->item(index,2);
        QStandardItem *backSteps_item=model->item(index,3);
        if(m_player->getHasPlayed(i))
        {
            level_item->setText(QString::number(i));
            int time=m_player->getTime(i);
            int minutes=(time/(100*60))%60;
            int seconds=(time/100)%60;
            int milliseconds=time%100;
            QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                                     .arg(seconds,2,10,QChar('0'))
                                     .arg(milliseconds,2,10,QChar('0'));
            time_item->setText(timeString);
            steps_item->setText(QString::number(m_player->getSteps(i)));
            backSteps_item->setText(QString::number(m_player->getBackSteps(i)));
        }
        else
        {
            level_item->setText(QString::number(i));
            time_item->setText(QString("0"));
            steps_item->setText(QString("0"));
            backSteps_item->setText(QString("0"));
        }
    }
    emit model->dataChanged(model->index(0, 0), model->index(11, 0));
}

//创建model：用于展示游戏记录
void Home::createModel()
{
    model->setHorizontalHeaderLabels(QStringList()<<"关卡名"<<"时间"<<"步数"<<"撤回步数");
    for(int i=1;i<=12;i++)
    {
        int index=i-1;
        if(m_player->getHasPlayed(i))               //如果已经游玩过该关卡
        {
            QStandardItem *level_item=new QStandardItem(QString::number(i));
            int time=m_player->getTime(i);
            int minutes=(time/(100*60))%60;
            int seconds=(time/100)%60;
            int milliseconds=time%100;
            QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                                     .arg(seconds,2,10,QChar('0'))
                                     .arg(milliseconds,2,10,QChar('0'));
            QStandardItem *time_item=new QStandardItem(timeString);
            QStandardItem *steps_item=new QStandardItem(QString::number(m_player->getSteps(i)));
            QStandardItem *backSteps_item=new QStandardItem(QString::number(m_player->getBackSteps(i)));
            level_item->setTextAlignment(Qt::AlignHCenter);
            level_item->setSizeHint(QSize(100, 50));
            time_item->setTextAlignment(Qt::AlignHCenter);
            time_item->setSizeHint(QSize(100, 50));
            steps_item->setTextAlignment(Qt::AlignHCenter);
            steps_item->setSizeHint(QSize(100, 50));
            backSteps_item->setTextAlignment(Qt::AlignHCenter);
            backSteps_item->setSizeHint(QSize(100, 50));
            model->setItem(index,0,level_item);
            model->setItem(index,1,time_item);
            model->setItem(index,2,steps_item);
            model->setItem(index,3,backSteps_item);
        }
        else                                        //如果没有游玩过该关卡
        {
            QStandardItem *level_item=new QStandardItem(QString("0"));
            QStandardItem *time_item=new QStandardItem(QString("00:00:00"));
            QStandardItem *steps_item=new QStandardItem(QString("0"));
            QStandardItem *backSteps_item=new QStandardItem(QString("0"));
            level_item->setTextAlignment(Qt::AlignHCenter);
            level_item->setSizeHint(QSize(100, 50));
            time_item->setTextAlignment(Qt::AlignHCenter);
            time_item->setSizeHint(QSize(100, 50));
            steps_item->setTextAlignment(Qt::AlignHCenter);
            steps_item->setSizeHint(QSize(100, 50));
            backSteps_item->setTextAlignment(Qt::AlignHCenter);
            backSteps_item->setSizeHint(QSize(100, 50));
            model->setItem(index,0,level_item);
            model->setItem(index,1,time_item);
            model->setItem(index,2,steps_item);
            model->setItem(index,3,backSteps_item);
        }
    }

}

//某一关卡的数据进行更新
void Home::updateRow()
{
    //qDebug()<<"home updateRow函数被调用";
    //qDebug()<<"调用者是"<<m_player->getUserName();
    int level=m_player->getLevelNeedUpdate();
    int index=level-1;
    if(index<0||index>=model->rowCount())
    {
        return;
    }
    QStandardItem *level_item=model->item(index,0);
    int time=m_player->getTime(level);
    int minutes=(time/(100*60))%60;
    int seconds=(time/100)%60;
    int milliseconds=time%100;
    QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                             .arg(seconds,2,10,QChar('0'))
                             .arg(milliseconds,2,10,QChar('0'));
    QStandardItem *time_item=model->item(index,1);
    QStandardItem *steps_item=model->item(index,2);
    QStandardItem *backSteps_item=model->item(index,3);
    level_item->setText(QString::number(level));
    time_item->setText(timeString);
    steps_item->setText(QString::number(m_player->getSteps(level)));
    backSteps_item->setText(QString::number(m_player->getBackSteps(level)));
    emit model->dataChanged(model->index(index, 0), model->index(index, 3));
}

void Home::onBackButtonClicked()
{
    emit backToMain();
}

Home::~Home()
{
    delete ui;
}
