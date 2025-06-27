#ifndef TIMEWATCH_H
#define TIMEWATCH_H

#include <QDialog>
#include <QLabel>

class TimeWatch : public QWidget
{
    Q_OBJECT
public:
    explicit TimeWatch(QWidget *parent=nullptr);
    ~TimeWatch();
public slots:
    void startTimeWatch();      //开始计时
    void stopTimeWatch();       //停止计时
    void resetTimeWatch();      //复位为0
    void updateTime();          //更新当前时间
    int passTimeRecord();       //传递时间
    void original();            //退出关卡时归0
private:
    void updateTimeDisplay();       //更新显示时间
    QLabel *timerLabel;             //显示时间的label
    QTimer* timer;                  //响应时间的QTimer，用来更新显示的时间
    int elapsedMillSeconds;         //记录总时间
};

#endif // TIMEWATCH_H
