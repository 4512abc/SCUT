#include "helpwidget.h"
#include "config.h"

helpWidget::helpWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //返回主页面按钮
    returnButton = new QPushButton(this);
    returnButton->setIcon(QIcon(":/res/returnBtn.png"));
    returnButton->setIconSize(QSize(150,180));
    returnButton->setFixedSize(150,180);
    returnButton->setFlat(true);
    returnButton->move(820,150);
    returnButton->raise();
    returnButton->show();
    connect(returnButton,&QPushButton::clicked,this,&helpWidget::returnToMainPage);

    QLabel *cross = new QLabel(this);
    cross->setPixmap(QPixmap(":/res/叉.png"));
    QLabel *crossText = new QLabel("<b>代表该方格没有树</b>",this);
    crossText->setStyleSheet("font-family: Arial; font-size: 16px;");
    crossText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLabel *triangle = new QLabel(this);
    triangle->setPixmap(QPixmap(":/res/triangle (2).png"));
    QLabel *triangleText = new QLabel("<b>代表该方格有1或3颗树</b>",this);
    triangleText->setStyleSheet("font-family: Arial; font-size: 16px;");
    triangleText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLabel *circle = new QLabel(this);
    circle->setPixmap(QPixmap(":/res/circle.png"));
    QLabel *circleText = new QLabel("<b>代表该方格有2颗树或0颗树\n"
                                    "<br><br>在练习模式中,该方格仅仅代表有一棵树</b>",this);
    circleText->setStyleSheet("font-family: Arial; font-size: 16px;");
    circleText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLabel *Square = new QLabel(this);
    Square->setPixmap(QPixmap(":/res/Square (2).png"));
    QLabel *SquareText = new QLabel("<b>代表该方格有4颗树</b>",this);
    SquareText->setStyleSheet("font-family: Arial; font-size: 16px;");
    SquareText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLabel *introSlice = new QLabel("<b>您有以下种类的切片,图片上的树木量为其可以填充的区域大小<b>",this);
    introSlice->setStyleSheet("font-family: Arial; font-size: 16px;");
    introSlice->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *slicetoput1 = new QLabel(this);
    slicetoput1->setPixmap(QPixmap(":/res/sliceToPut1.png"));

    QLabel *slicetoput2 = new QLabel(this);
    slicetoput2->setPixmap(QPixmap(":/res/slicetoPut2.png"));
    QLabel *slicetoput3 = new QLabel(this);
    slicetoput3->setPixmap(QPixmap(":/res/sliceToPut3.png"));
    QLabel *slicetoput4 = new QLabel(this);
    slicetoput4->setPixmap(QPixmap(":/res/sliceToPut4.png"));

    QLabel *addition = new QLabel("<b>1.你需要通过拖动树木图标填充到盘面上的具体位置；"
                                  "</b><br><br> <b>"
                                  "2.中间盘面格子右上角的数字代表该方格已经种树木的树量；</b><br><br><b>"
                                  "3.当所有的图标都满足其所要种的树木量时，即可通关</b>",this);
    addition->setStyleSheet("font-family: Arial; font-size: 16px;"); // 调整字体大小

    //添加到布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(triangle,0,1,1,1);
    mainLayout->addWidget(triangleText,0,2,1,3);
    mainLayout->addWidget(circle,1,1,1,1);
    mainLayout->addWidget(circleText,1,2,1,3);
    mainLayout->addWidget(Square,2,1,1,1);
    mainLayout->addWidget(SquareText,2,2,1,3);
    mainLayout->addWidget(cross,3,1,1,1);
    mainLayout->addWidget(crossText,3,2,1,3);
    mainLayout->addWidget(introSlice,4,4,1,3);
    mainLayout->addWidget(slicetoput1,5,4,1,1);
    mainLayout->addWidget(slicetoput2,5,5,1,1);
    mainLayout->addWidget(slicetoput3,5,6,1,1);
    mainLayout->addWidget(slicetoput4,5,7,1,1);

    mainLayout->addWidget(addition,0,4,2,4);
    this->setLayout(mainLayout);

}


void helpWidget::showBtn()
{
    returnButton->show();
}
void helpWidget::hideBtn()
{
    returnButton->hide();
}
