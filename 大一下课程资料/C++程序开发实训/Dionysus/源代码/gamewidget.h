#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPalette>
#include <QBrush>
class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(QWidget *parent = nullptr);
    ~gameWidget(){}
private:
    QPushButton *practiceBtn;
    QPushButton *competitionBtn;
    QPushButton *GradesRankBtn;
    QPushButton *LogOutBtn;
    QLabel *lable;
    QPushButton *quit;
    QVBoxLayout *vlayout;
signals:
    //告诉主场景点击了返回

};

#endif // GAMEWIDGET_H
