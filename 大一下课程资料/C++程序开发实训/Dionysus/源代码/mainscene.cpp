#include "mainscene.h"
#include "config.h"
#include "map.h"

MainScene::MainScene(QWidget *parent)
    : QWidget(parent),
    //new出窗口对象以及堆栈
    mainPage(new QWidget(this)),
    setW(new setWidget(this)),
    helpW(new helpWidget(this)),
    gameW(new gameWidget(this)),
    accountW(new accountWidget(this)),
    stackedWidget(new QStackedWidget(this)),
    playwidget(new playWidget(this)),
    rankwidget(new rankWidget(this))
{
    this->hide();
    setW->hide();
    helpW->hide();
    accountW->hide();  accountW->setOnLoginPlayer(this->onLoginPlayer);
    gameW->hide();  gameW->setOnLoginPlayer(this->onLoginPlayer);
    playwidget->hide(); playwidget->setOnLoginPlayer(this->onLoginPlayer);//该窗口可视化不写在构造函数里，用其他成员函数，以免主窗口无法有固定的stack序号
    //还是要写的，框架要搭一下，不过重写一个根据map对象修改qlable的函数，qlable用网格布局
    rankwidget->hide(); rankwidget->setOnLoginPlayer(this->onLoginPlayer);

    this->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    this->setGeometry(350, 170, GAME_WIDTH, GAME_HEIGHT);
    mainPage->setWindowTitle("ZhiciQingLv");
    mainPage->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    mainPage->setGeometry(100, 100, GAME_WIDTH, GAME_HEIGHT);
    mainPage->setWindowTitle("ZhiciQingLv");
    this->setWindowIcon(QIcon(":/res/background.png"));
    //设置背景
    QImage background(BACKGROUND_PATH);
    background = background.scaled(mainPage->width(), mainPage->height(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(mainPage->backgroundRole(), QBrush(background));
    this->setPalette(palette);

    //标签初始化
    this->lable = new QLabel(this);
    lable->setPixmap(QPixmap(GAMENAME_PATH));
    lable->setFixedSize(1000,160);
    lable->setContentsMargins(200,0,0,0);

    //添加按钮
    this->startButton = new MyPushButton(this);//初始化
    this->startButton->setIcon(QIcon(":/res/mainpageStart.png"));//设置图标
    startButton->setFixedSize(750,125);
    startButton->setContentsMargins(0,0,0,0);
    this->startButton->setIconSize(QSize(350,88));//设置按钮大小
    this->startButton->setFlat(true);//去掉白边
    this->startButton->setFocusPolicy(Qt::NoFocus);//不聚焦，鼠标停留的时候不会出现框

    this->helpButton = new QPushButton(this);
    this->helpButton->setIcon(QIcon(":/res/mainpageHelp.png"));
    this->helpButton->setFlat(true);
    helpButton->setFixedSize(400,80);
    this->helpButton->setIconSize(QSize(200,80));
    helpButton->setContentsMargins(0,0,100,0);
    this->helpButton->setFocusPolicy(Qt::NoFocus);


    this->quitButton = new QPushButton(this);
    this->quitButton->setIcon(QIcon(":/res/quit.png"));
    this->quitButton->setFlat(true);
    this->quitButton->setIconSize(QSize(140,50));
    this->quitButton->setFocusPolicy(Qt::NoFocus);
    quitButton->setFixedSize(400,50);

    QLabel *lable1 = new QLabel(this);

    //创建垂直布局，这样避免设置坐标并且随窗口变化
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(lable,0,0,1,7);
    mainLayout->addWidget(startButton,1,1,1,3);
    mainLayout->addWidget(helpButton,3,2,1,3);
    mainLayout->addWidget(quitButton,5,2,1,3);
    mainLayout->addWidget(lable1,7,2,1,3);


    //将页面添加到widgetStack里面
    //创建一个主页面使它可以加入到stack里，由于所有布局都是属于this的
    mainPage->setContentsMargins(0,0,0,0);
    QWidget *mainPage = new QWidget(this);
    mainPage->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    mainLayout->setContentsMargins(0,100,0,10);
    mainPage->setLayout(mainLayout);
    stackedWidget->addWidget(mainPage);
    stackedWidget->addWidget(accountW);
    stackedWidget->addWidget(setW);
    stackedWidget->addWidget(helpW);
    stackedWidget->addWidget(gameW);
    stackedWidget->addWidget(playwidget);
    stackedWidget->addWidget(rankwidget);

    // //添加音乐
    music.setSource(QUrl::fromLocalFile("D://QT project//ZZz//res//5月29日.WAV"));
    music.setLoopCount(QSoundEffect::Infinite);
    music.setVolume(0.3);
    music.play();


    //实现按钮功能
    connect(startButton,SIGNAL(clicked()),this,SLOT(showStartWidget()));
    connect(helpButton,SIGNAL(clicked()),this,SLOT(showHelpWidget()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));

    //监听子页面传来的返回信号
    connect(accountW,&accountWidget::returnToMainPage,[=](){
        stackedWidget->setCurrentIndex(0);
    });
    connect(setW,&setWidget::returnToMainPage,[=](){
        stackedWidget->setCurrentIndex(0);
    });
    connect(helpW,&helpWidget::returnToMainPage,[=](){
        stackedWidget->setCurrentIndex(0);
    });
    connect(gameW,&gameWidget::returnToMainPage,[=](){
        stackedWidget->setCurrentIndex(0);
    });
    connect(playwidget,&playWidget::returnToGameScene,[=](){

        stackedWidget->setCurrentIndex(4);
    });

    //监听账户页面发来的开始游戏信号
    //无账号
    connect(accountW,&accountWidget::StartPlay,this,&MainScene::startPlayGame);
    connect(accountW,&accountWidget::StartPlayWithAccount,this,&MainScene::startPlayGameWithAccount);
    //监听游戏选择页面发来的信号
    connect(gameW,&gameWidget::ToPractice,this,&MainScene::showPracticeWidget);
    connect(gameW,&gameWidget::ToCompetition,this,&MainScene::showCompetitionWidget);
    connect(gameW,&gameWidget::ToRankWidget,this,&MainScene::showRankWidget);

    connect(rankwidget,&rankWidget::returnToGameScene,[=](){
        stackedWidget->setCurrentIndex(4);
    });
    connect(gameW,&gameWidget::ToEndless,this,&MainScene::showEndlessWidget);

    connect(gameW,&gameWidget::ToCustom,this,&MainScene::showCustomWidget);
    connect(playwidget,&playWidget::recustom,this,&MainScene::showCustomWidget);
    connect(playwidget,&playWidget::selectOtherMode,this,&MainScene::startPlayGame);
    connect(playwidget,&playWidget::toRank,this,&MainScene::showRankWidget);

}
//编写槽函数，实现页面跳转
void MainScene::returnToMainPage()
{
    stackedWidget->setCurrentIndex(0);
}
void MainScene::showStartWidget()
{
    //如果已经登录，跳转到游戏页面；
    if(onLoginPlayer.getAccount() == "游客"){
        stackedWidget->setCurrentIndex(1);
    }
    else stackedWidget->setCurrentIndex(4);
}
void MainScene::showSetWidget()
{
    stackedWidget->setCurrentIndex(2);
}
void MainScene::showHelpWidget()
{
    stackedWidget->setCurrentIndex(3);
}
void MainScene::startPlayGame()
{
    stackedWidget->setCurrentIndex(4);
}
void MainScene::startPlayGameWithAccount()//登录后的游玩
{
    stackedWidget->setCurrentIndex(4);
}

void MainScene::showPracticeWidget()
{

    playwidget->setPlayMode(practiceMode);//下次要在配置文件中写一个emnum类型，按照枚举类型来匹配模式，用数字容易搞混乱
    playwidget->reShowWidget();
    stackedWidget->setCurrentIndex(5);
}

void MainScene::showCompetitionWidget()
{

    playwidget->setPlayMode(competitionMode);
    playwidget->reShowWidget();
    stackedWidget->setCurrentIndex(5);
}
void MainScene::showEndlessWidget()
{
    QWidget *selectMode = new QWidget();
    QLabel *intro = new QLabel("请选择您要游玩的模式",selectMode);
    intro->setFixedSize(300,50);

    selectMode->setFixedSize(400,300);
    QPushButton *practice = new QPushButton("练习无尽模式",selectMode);
    practice->setFixedSize(150,100);

    QPushButton *competition = new QPushButton("比赛无尽模式",selectMode);
    competition->setFixedSize(150,100);

    QVBoxLayout *main = new QVBoxLayout(selectMode);
    QHBoxLayout *selection = new QHBoxLayout();

    selection->addWidget(practice);
    selection->addWidget(competition);
    main->addWidget(intro);
    main->setAlignment(Qt::Alignment(Qt::AlignHCenter));

    main->addLayout(selection);

    selectMode->setLayout(main);
    selectMode->show();

    connect(practice,&QPushButton::clicked,[=](){
        playwidget->setEndlessPlayMode(practiceMode);
        selectMode->close();
    });
    connect(competition,&QPushButton::clicked,[=](){
        playwidget->setEndlessPlayMode(competitionMode);
        selectMode->close();
    });
    playwidget->setPlayMode(endlessMode);
    playwidget->reShowWidget();
    stackedWidget->setCurrentIndex(5);
}

void MainScene::showCustomWidget()
{
    QWidget *selectMode = new QWidget();
    QLabel *intro = new QLabel("请选择您要游玩的模式",selectMode);
    intro->setFixedSize(300,50);

    selectMode->setFixedSize(400,300);
    QPushButton *practice = new QPushButton("自定义练习模式",selectMode);
    practice->setFixedSize(150,100);

    QPushButton *competition = new QPushButton("自定义比赛模式",selectMode);
    competition->setFixedSize(150,100);

    QVBoxLayout *main = new QVBoxLayout(selectMode);
    QHBoxLayout *selection = new QHBoxLayout();

    selection->addWidget(practice);
    selection->addWidget(competition);
    main->addWidget(intro);
    main->setAlignment(Qt::Alignment(Qt::AlignHCenter));

    main->addLayout(selection);

    selectMode->setLayout(main);
    selectMode->show();

    connect(practice,&QPushButton::clicked,[=](){
        playwidget->setPlayMode(practiceMode);
        playwidget->customMode();
        playwidget->reShowWidget();
        selectMode->close();
        stackedWidget->setCurrentIndex(5);
        emit reviseLayout();
    });
    connect(competition,&QPushButton::clicked,[=](){
        playwidget->setPlayMode(competitionMode);
        playwidget->customMode();
        playwidget->reShowWidget();
        selectMode->close();
        stackedWidget->setCurrentIndex(5);
        emit reviseLayout();

    });
    connect(this,&MainScene::reviseLayout,playwidget,&playWidget::showCustom);
}


void MainScene::showRankWidget()
{
    rankwidget->loadContent(PRACTICE_RECORD_PATH);//默认先显示练习模式
    //弹出消息框，在上方选择排序模式

    stackedWidget->setCurrentIndex(6);
    QMessageBox::information(nullptr,
                             "排序模式提示",  //消息框标题
                             "请在右侧选择你要查看的排行榜"
                             "\n\n请在上选择排序模式：\n1. 单局最快\n2. 平均用时最少\n3. 成功次数最多");  // 显示的信息
}


MainScene::~MainScene()
{}


