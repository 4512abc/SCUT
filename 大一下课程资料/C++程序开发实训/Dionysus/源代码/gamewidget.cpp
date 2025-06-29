#include "gamewidget.h"
#include "config.h"
gameWidget::gameWidget(QWidget *parent)
    : QWidget(parent)

{
    //同主窗口一致
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setGeometry(100, 100, GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle("ZhiciQingLv");
    setWindowIcon(QIcon(":/res/background.png"));
    this->setAutoFillBackground(true);
    //设置背景
    QImage background(":/res/background2.png");
    background = background.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(background));
    this->setPalette(palette);

    //标签初始化
    this->lable = new QLabel(this);
    lable->setPixmap(QPixmap(":/res/zhiciqinglv.jpg"));
    //添加按钮
    this->practiceBtn = new QPushButton(this);//初始化
    this->practiceBtn->setIcon(QIcon(":/res/Practice.jpg"));//设置图标
    this->practiceBtn->setIconSize(QSize(240,65));//设置按钮大小
    this->practiceBtn->setFlat(true);//去掉白边
    this->practiceBtn->setFocusPolicy(Qt::NoFocus);//不聚焦，鼠标停留的时候不会出现框

    this->competitionBtn = new QPushButton(this);
    this->competitionBtn->setIcon(QIcon(":/res/Competition.jpg"));
    this->competitionBtn->setFlat(true);
    this->competitionBtn->setIconSize(QSize(220,56));
    this->competitionBtn->setFocusPolicy(Qt::NoFocus);

    this->GradesRankBtn = new QPushButton(this);
    this->GradesRankBtn->setIcon(QIcon(":/res/gradesRank.jpg"));
    this->GradesRankBtn->setFlat(true);
    this->GradesRankBtn->setIconSize(QSize(180,50));
    this->GradesRankBtn->setFocusPolicy(Qt::NoFocus);

    this->LogOutBtn = new QPushButton(this);
    this->LogOutBtn->setIcon(QIcon(":/res/logout.jpg"));
    this->LogOutBtn->setFlat(true);
    this->LogOutBtn->setIconSize(QSize(160,50));
    this->LogOutBtn->setFocusPolicy(Qt::NoFocus);

    this->quit->setText("quit game");
    this->quit->setFixedSize(40,40);
    this->quit->move(GAME_HEIGHT-60,GAME_WIDTH-60);
    //创建垂直布局，这样避免设置坐标并且随窗口变化
    this->vlayout = new QVBoxLayout(this);//传不传窗口用F1查看是否继承自Qwidget,label、button同理
    this->vlayout->addWidget(lable);
    this->vlayout->addSpacing(50);
    this->vlayout->addWidget(practiceBtn);
    this->vlayout->addWidget(competitionBtn);
    this->vlayout->addWidget(GradesRankBtn);
    this->vlayout->addWidget(LogOutBtn);
    this->vlayout->setAlignment(Qt::AlignHCenter);//设置对齐方式，f1查看可传参数

    //退出按钮
    // this->connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    //返回按钮

}
