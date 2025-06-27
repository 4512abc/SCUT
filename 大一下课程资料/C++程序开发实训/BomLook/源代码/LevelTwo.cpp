#include "LevelTwo.h"
#include <QPushButton>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QPropertyAnimation>
LevelTwo::LevelTwo(QWidget *parent,Player *onlinePlayer)
    :QWidget(parent),m_player(onlinePlayer),game(nullptr),mapChoose(nullptr),m_ranking(nullptr),dialog(nullptr)
{
    setupMainPage();
    setupSubPage();

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(&subPage_Pages);

    this->installEventFilter(this);     //安装事件过滤器
}

LevelTwo::~LevelTwo() {
    if(mapChoose!=nullptr)
    {
        delete mapChoose;
        mapChoose=nullptr;
    }
    if(game!=nullptr)
    {
        delete game;
        game=nullptr;
    }
    if(m_ranking!=nullptr)
    {
        delete m_ranking;
        m_ranking=nullptr;
    }
    if(m_funny!=nullptr)
    {
        delete m_funny;
        m_funny=nullptr;
    }
    if(dialog!=nullptr)
    {
        delete dialog;
        dialog=nullptr;
    }
}


void LevelTwo::setupMainPage()
{
    //游戏模式选择
    QLabel *title=new QLabel;
    QFont font("Microsoft YaHei");
    font.setPointSize(70);
    title->setStyleSheet("color: orange");
    title->setFont(font);
    title->setText("Fire Painting");
    title->setText("选择模式");

    QWidget *mainPage=new QWidget(this);
    QVBoxLayout *mainLayout=new QVBoxLayout(mainPage);
    QHBoxLayout *buttonLayout=new QHBoxLayout;
    QHBoxLayout *titleLayout=new QHBoxLayout;

    //设置按钮和调整布局
    mainLayout->addStretch(1);
    titleLayout->addStretch(1);
    titleLayout->addWidget(title);
    titleLayout->addStretch(1);
    mainLayout->addLayout(titleLayout);
    mainLayout->addStretch(4);

    QString globalStylesheet=R"(
        QPushButton {
        width: 150px;
        height: 75px;
        background-color: transparent;
        border: 2px solid white;
        border-radius: 10px;
        color: white;
        font-family: 'Microsoft YaHei';
        font-weight: bold;
        font-size: 20px
        }
        QPushButton:hover {
        background-color: rgba(255, 255, 255, 0.1);
        }
        QPushButton:pressed {
        background-color: rgba(255, 255, 255, 0.3);
        }
        QPushButton::icon {
        padding-right: 10px;
        }
        QPushButton#myButton {
        border: 2px solid rgba(0, 0, 0, 0.2);
        box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.4);
        }
    )";

    QPushButton *button1=new QPushButton(QString("关卡模式"),mainPage);
    QIcon icon1(":/icons/resource/icons/宝箱pixel.png");
    button1->setIcon(icon1);
    button1->setIconSize(QSize(40,40));
    button1->setStyleSheet(globalStylesheet);

    connect(button1, &QPushButton::clicked, this, &LevelTwo::switchToSubPage);
    //设置按钮索引
    button1->setProperty("PageIndex",1);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button1);

    QPushButton *button2=new QPushButton(QString("随机模式"),mainPage);
    QIcon icon2(":/icons/resource/icons/电池pixel.png");
    button2->setIcon(icon2);
    button2->setIconSize(QSize(40,40));
    button2->setStyleSheet(globalStylesheet);

    connect(button2,&QPushButton::clicked,this,&LevelTwo::generateRandom);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button2);

    QPushButton *button4 = new QPushButton(QString("趣味模式"),mainPage);
    QIcon icon4(":/icons/resource/icons/灯泡pixel.png");
    button4->setIcon(icon4);
    button4->setIconSize(QSize(40,40));
    button4->setStyleSheet(globalStylesheet);


    connect(button4, &QPushButton::clicked, this, &LevelTwo::switchToSubPage);
    //设置按钮索引
    button4->setProperty("PageIndex",3);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button4);

    m_ranking=new Ranking(nullptr,m_player);
    QPushButton *button6=new QPushButton(QString("排行榜"),mainPage);
    QIcon icon6(":/icons/resource/icons/奖杯pixel.png");
    button6->setIcon(icon6);
    button6->setIconSize(QSize(40,40));
    button6->setStyleSheet(globalStylesheet);
    connect(button6,&QPushButton::clicked,m_ranking,&Ranking::show);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button6);
    buttonLayout->addStretch(1);

    QPushButton *backButton=new QPushButton("Back To Main",mainPage);
    QIcon backIcon(":/icons/resource/icons/钥匙pixel.png");
    backButton->setIcon(backIcon);
    backButton->setIconSize(QSize(40,40));
    backButton->setStyleSheet(globalStylesheet);


    connect(backButton,&QPushButton::clicked,this,&LevelTwo::OnBackButtonClicked);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    mainLayout->addWidget(backButton);
    mainLayout->addStretch(1);

    subPage_Pages.addWidget(mainPage);
}


void LevelTwo::setupSubPage()
{
    //设置选择关卡页面
    mapChoose=new MapChoose(this);
    connect(mapChoose,&MapChoose::backToMain,this,&LevelTwo::switchToMainPage);
    subPage_Pages.addWidget(mapChoose);
    mapChoose->hide();

    //设置游戏页面
    game=new Game(this,5,m_player);
    connect(game,&Game::backToMain,this,&LevelTwo::switchToMainPage);
    connect(mapChoose,&MapChoose::emitNumber,game,&Game::setGame);          //连接emitNumber和setGame函数
    connect(mapChoose,&MapChoose::ToGame,this,&LevelTwo::switchToGame);     //连接ToGame和switchToGame函数
    connect(this,&LevelTwo::MakeRandom,game,&Game::generateRandomMap);
    subPage_Pages.addWidget(game);
    game->hide();

    //设置funny页面
    m_funny=new Funny(this);
    connect(m_funny,&Funny::backToMain,this,&LevelTwo::switchToMainPage);
    subPage_Pages.addWidget(m_funny);
    m_funny->hide();

    connect(game,&Game::updateRanking,m_ranking,&Ranking::updateRanking);
    connect(game,&Game::updateData,m_ranking,&Ranking::updateData);
}

//跳转到子页面
void LevelTwo::switchToSubPage()
{
    qDebug()<< "Switching to sub page...111";
    QObject *senderObj=sender();
    if(senderObj)
    {
        qDebug()<<"Sender object is not null.";
        QPushButton *button=qobject_cast<QPushButton*>(senderObj);
        if(button)
        {
            qDebug()<<"Sender is a QPushButton.";
            int pageIndex=button->property("PageIndex").toInt();  //获取按钮索引
            animateSwitch(0, pageIndex);  //0是主页面的索引
        }
        else
        {
            qDebug() << "Sender is not a QPushButton.";
        }
    }
    else
    {
        qDebug()<<"Sender object is null.";
    }
}

//键盘操作：跳转到子页面
void LevelTwo::enterToSubPage(int pageIndex)
{
    animateSwitch(0,pageIndex);
}

//跳转到主页面
void LevelTwo::switchToMainPage()
{
    animateSwitch(subPage_Pages.currentIndex(),0); // 0 是主页面的索引
}

//跳转到游戏页面
void LevelTwo::switchToGame()
{
    animateSwitch(0,2);
}

//页面切换动画函数
void LevelTwo::animateSwitch(int fromIndex,int toIndex)
{
    QPropertyAnimation *pageAnimation=new QPropertyAnimation(subPage_Pages.widget(fromIndex), "geometry");
    pageAnimation->setDuration(500);
    pageAnimation->setStartValue(subPage_Pages.widget(fromIndex)->geometry());
    pageAnimation->setEndValue(subPage_Pages.widget(toIndex)->geometry());

    subPage_Pages.setCurrentIndex(toIndex);

    animation.clear();
    animation.addAnimation(pageAnimation);
    animation.start();
}


bool LevelTwo::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Return)
        {
            qDebug() << "Enter key pressed...2";
            if(subPage_Pages.currentIndex() == 0)
            {
                qDebug()<<"Switching to sub page...2";
                QWidget *focusWidget=QApplication::focusWidget();
                if(focusWidget &&focusWidget->property("PageIndex").isValid())
                {
                    qDebug()<<"Switch to sub page...222";
                    int pageIndex=focusWidget->property("PageIndex").toInt();
                    enterToSubPage(pageIndex);
                }
                else
                {
                    qDebug()<<"Switch to main page....222";
                    emit backToMain();
                }
            }
            else
            {
                qDebug() << "Switching to main page...2";
                switchToMainPage();
            }
            return true; // 拦截键盘事件，不再继续传递
        }
    }
    // 其他事件交给父类处理
    return QWidget::eventFilter(obj, event);
}


void LevelTwo::OnBackButtonClicked()
{
    emit backToMain();
}

//生成选择游戏难度的窗口
void LevelTwo::generateRandom()
{
    dialog=new QDialog(this);
    dialog->setWindowTitle("请选择关卡难度");
    QIcon icon(":/icons/resource/icons/藏剑.png");
    dialog->setWindowIcon(icon);
    QLabel *label1=new QLabel(dialog);
    QPixmap img1(":/icons/resource/icons/移动端-LOL剑@3-copy.png");
    label1->setPixmap(img1);
    QLabel *label2=new QLabel(dialog);
    QPixmap img2(":/icons/resource/icons/十字剑.png");
    label2->setPixmap(img2);
    QLabel *label3=new QLabel(dialog);
    QPixmap img3(":/icons/resource/icons/藏剑.png");
    label3->setPixmap(img3);

    QHBoxLayout *Hlayout1=new QHBoxLayout;
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(label1);
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(label2);
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(label3);
    Hlayout1->addStretch(1);

    QPushButton *button1=new QPushButton("难度一",dialog);
    QPushButton *button2=new QPushButton("难度二",dialog);
    QPushButton *button3=new QPushButton("难度三",dialog);

    QHBoxLayout *Hlayout2=new QHBoxLayout;
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(button1);
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(button2);
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(button3);
    Hlayout2->addStretch(1);

    QVBoxLayout *Vlayout=new QVBoxLayout(dialog);
    Vlayout->addLayout(Hlayout1);
    Vlayout->addLayout(Hlayout2);
    connect(button1,&QPushButton::clicked,this,[this](){emit MakeRandom(1);});
    connect(button2,&QPushButton::clicked,this,[this](){emit MakeRandom(2);});
    connect(button3,&QPushButton::clicked,this,[this](){emit MakeRandom(3);});

    connect(button1,&QPushButton::clicked,dialog,&QDialog::close);
    connect(button2,&QPushButton::clicked,dialog,&QDialog::close);
    connect(button3,&QPushButton::clicked,dialog,&QDialog::close);

    button1->setProperty("PageIndex",2);
    button2->setProperty("PageIndex",2);
    button3->setProperty("PageIndex",2);

    connect(button1,&QPushButton::clicked,this,&LevelTwo::switchToSubPage);
    connect(button2,&QPushButton::clicked,this,&LevelTwo::switchToSubPage);
    connect(button3,&QPushButton::clicked,this,&LevelTwo::switchToSubPage);

    dialog->show();
}

