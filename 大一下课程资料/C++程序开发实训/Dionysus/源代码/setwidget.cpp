#include "setwidget.h"
#include "config.h"

setWidget::setWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //返回主页面按钮
    QPushButton *returnButton = new QPushButton(QString("返回"), this);
    connect(returnButton,&QPushButton::clicked,this,&setWidget::returnToMainPage);
}
