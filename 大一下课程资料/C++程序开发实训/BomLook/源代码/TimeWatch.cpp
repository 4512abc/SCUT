#include "TimeWatch.h"

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
TimeWatch::TimeWatch(QWidget *parent)
    : QWidget{parent},elapsedMillSeconds(0)
{
    //设置timerLabel
    timerLabel=new QLabel("00:00:00",this);
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("background-colror: ;color: ;border:;"
                              "padding: 5px 12px; "
                              "text-align: center; text-decoration: none; "
                              "display: inline-block; ");
    QFont timeLabelFont("Arial", 20);
    timerLabel->setFont(timeLabelFont);
    timerLabel->setFixedSize(200,100);

    //调整布局
    QHBoxLayout *HLayout=new QHBoxLayout(this);
    HLayout->addWidget(timerLabel);

    //timer响应并更新时间
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&TimeWatch::updateTime);
}


TimeWatch::~TimeWatch()
{
    if(timerLabel!=nullptr){
        delete timerLabel;
        timerLabel=nullptr;
    }
    if(timer!=nullptr){
        delete timer;
        timer=nullptr;
    }
}


void TimeWatch::startTimeWatch()
{
    timer->start(10);        //每10ms触发一次timeout信号
}


void TimeWatch::stopTimeWatch()
{
    timer->stop();          //停止计时
}


void TimeWatch::resetTimeWatch()
{
    elapsedMillSeconds=0;   //时间归为0
    updateTimeDisplay();    //显示的时间进行更新
}


void TimeWatch::updateTime()
{
    elapsedMillSeconds++;   //秒数计时
    updateTimeDisplay();    //显示的时间进行更新
}


void TimeWatch::updateTimeDisplay()
{
    //转换成对应分钟，秒数，毫秒数
    int minutes=(elapsedMillSeconds/(100*60))%60;
    int seconds=(elapsedMillSeconds/100)%60;
    int milliseconds=elapsedMillSeconds%100;

    //更新显示的时间
    QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                             .arg(seconds,2,10,QChar('0'))
                             .arg(milliseconds,2,10,QChar('0'));
    timerLabel->setText(timeString);
}

int TimeWatch::passTimeRecord()
{
    return elapsedMillSeconds;
}

void TimeWatch::original()
{
    //总时间归为0
    elapsedMillSeconds=0;
    int minutes=0;
    int seconds=0;
    int milliseconds=0;

    //更新显示的时间
    QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                             .arg(seconds,2,10,QChar('0'))
                             .arg(milliseconds,2,10,QChar('0'));
    timerLabel->setText(timeString);
}
