#include "Game.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QGridLayout>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include <QMessageBox>
#include "Cell.h"
#include "ACDialog.h"
#include "Game.h"
#include "WADialog.h"
#include <Qt>
#include <QRegularExpression>
Game::Game(QWidget *parent, size_t size,Player *onlinePlayer)
    :QWidget(parent),m_size(size),m_player(onlinePlayer),steps(0),backSteps(0),isLevel(true),nowLevel(1),randomMapLevel(0),TimeWatchWidget(nullptr),acDialog(nullptr),waDialog(nullptr)
{
    gridLayout=new QGridLayout;
    answerLayout=new QGridLayout;
    //添加计时器
    TimeWatchWidget=new TimeWatch(this);
    m_timer=new QTimer(this);

    m_cells=std::vector<std::vector<Cell>>(m_size,std::vector<Cell>(m_size));       //初始化m_cells二维数组的大小，也就是要玩家操作的画的大小
    answers=std::vector<std::vector<Cell>>(m_size,std::vector<Cell>(m_size));       //初始化answers二维数组的大小，也就是答案画的大小

    setLayoutAndForm();
    setGame(1);
}

Game::~Game()
{
    if(TimeWatchWidget!=nullptr)
    {
        delete TimeWatchWidget;
        TimeWatchWidget=nullptr;
    }
    if(waDialog!=nullptr)
    {
        delete waDialog;
        waDialog=nullptr;
    }
    if(acDialog!=nullptr)
    {
        delete acDialog;
        acDialog=nullptr;
    }
}

//设置游戏：level对应的是关卡编号
void Game::setGame(int level)
{
    helps.clear();
    if(isLevel==false)                          //这里需要注意，如果是从随机模式切换到关卡模式，可能会因为画大小规格的不同，导致程序崩溃，所以需要对
    {                                           //原来的网格布局进行清空，等数据初始完后，再重新将m_cells和answers添加到网格布局中
        cleanGridLayout(gridLayout);
        cleanGridLayout(answerLayout);
    }
    //connectOperation();                         //重新连接操作按钮
    steps=0;                                    //操作步数初始化为0
    backSteps=0;                                //撤回步数初始化为0
    nowLevel=0;                                 //当前关卡等级初始化为0

    TimeWatchWidget->original();                //计时器初始化为0
    while(m_cellsHistory.size())                //注意：对原有的栈中数据需要进行清空，不然可能会跳转到上一幅地图
    {
        m_cellsHistory.pop();
    }

    nowLevel=level;                             //重新设定当前的等级
    qDebug()<<"setGame:"<<nowLevel;

    //打开文件，导入地图。
    QString fileName=QString(":/map/resource/map/level%1.bin").arg(level);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "无法打开文件进行读取";
        return;
    }

    //使用QDataStream读取文件
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    int width,height;
    in>>width>>height;
    m_size=width;
    qDebug()<<width<<height<<"\n";

    QVector<QVector<int>> num;
    num=QVector<QVector<int>>(height,QVector<int>(width));
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            in>>num[i][j];
        }
    }

    QVector<QVector<QString>> matrix;
    matrix=QVector<QVector<QString>>(height,QVector<QString>(width));
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            in>>matrix[i][j];
        }
    }

    QVector<QVector<int>> answer_num;
    answer_num=QVector<QVector<int>>(height,QVector<int>(width));
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            in>>answer_num[i][j];
        }
    }

    QVector<QVector<QString>> answer_matrix;
    answer_matrix=QVector<QVector<QString>>(height,QVector<QString>(width));
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            in>>answer_matrix[i][j];
        }
    }
    file.close();           //注意需要将文件关闭

    //注意：这里需要判断原来是关卡模式，还是随机模式，
    //如果原来是关卡模式：盘面大小不会发生改变，直接跳过即可
    //如果原来是随机模式：盘面的大小可能会发生改变，所以需要将m_cells和answers数组进行初始化操作
    //否则会导致数组越界，进而程序崩溃。
    if(isLevel==false)
    {
        m_cells=std::vector<std::vector<Cell>>(m_size,std::vector<Cell>(m_size));
        answers=std::vector<std::vector<Cell>>(m_size,std::vector<Cell>(m_size));
    }

    isLevel=true;           //设定当前模式为关卡模式
    createGridLayout(gridLayout,m_cells);           //重新创建gridlayout布局和answeLayout布局
    createGridLayout(answerLayout,answers);

    //接下来是更新m_cells和answers的数据
    for(int i=0;i<m_size;i++)
    {
        for(int j=0;j<m_size;j++)
        {
            m_cells[i][j].setNumAndColor(num[i][j],matrix[i][j].toStdString());
        }
    }

    for(int i=0;i<m_size;i++)
    {
        for(int j=0;j<m_size;j++)
        {
            answers[i][j].setNumAndColor(answer_num[i][j],answer_matrix[i][j].toStdString());
        }
    }
    m_cellsHistory.push(m_cells);                       //将最原始的地图存入其中
}

void Game::onBackButtonClicked()
{
    endAgainst();
    emit end();
    emit backToMain();
}

void Game::left_rotate()
{
    //左旋转矩阵
    size_t row=m_size;
    size_t col=m_size;

    std::vector<std::vector<Cell>> rotated(col,std::vector<Cell>(row));
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            rotated[col-j-1][i]=m_cells[i][j];
        }
    }

    //更新历史状态
    //将操作后的矩阵存入栈中
    m_cellsHistory.push(rotated);

    //更新当前的矩阵
    m_cells=rotated;
    update();
}


void Game::right_rotate()
{
    //右旋转矩阵
    size_t row=m_size;
    size_t col=m_size;
    std::vector<std::vector<Cell>> rotated(col, std::vector<Cell>(row));
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            rotated[j][row-i-1]=m_cells[i][j];
        }
    }

    //更新历史状态
    //将操作后的矩阵存入栈中
    m_cellsHistory.push(rotated);

    //更新当前的矩阵
    m_cells=rotated;
    update();
}

void Game::setLayoutAndForm()
{
    createGridLayout(gridLayout,m_cells);
    createGridLayout(answerLayout,answers);


    QString globalStylesheet=R"(
        QPushButton {
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

    // 设置窗口的布局
    button1=new QPushButton("左旋转");
    QIcon icon1(":/icons/resource/icons/lamb-left.png");
    button1->setIcon(icon1);
    button1->setIconSize(QSize(40,40));
    button1->setStyleSheet(globalStylesheet);
    button1->setFixedSize(150,60);

    button2=new QPushButton("右旋转");
    QIcon icon2(":/icons/resource/icons/lamb-right.png");
    button2->setIcon(icon2);
    button2->setIconSize(QSize(40,40));
    button2->setStyleSheet(globalStylesheet);
    button2->setFixedSize(150,60);

    button3=new QPushButton("燃烧");
    QIcon icon3(":/icons/resource/icons/火pixel.png");
    button3->setIcon(icon3);
    button3->setIconSize(QSize(40,40));
    button3->setStyleSheet(globalStylesheet);
    button3->setFixedSize(150,60);

    button4=new QPushButton("撤回");
    QIcon icon4(":/icons/resource/icons/金币pixel.png");
    button4->setIcon(icon4);
    button4->setIconSize(QSize(40,40));
    button4->setStyleSheet(globalStylesheet);
    button4->setFixedSize(150,60);

    QPushButton *button5=new QPushButton("对抗启动");
    QIcon icon5(":/icons/resource/icons/闪电pixel.png");
    button5->setIcon(icon5);
    button5->setIconSize(QSize(40,40));
    button5->setStyleSheet(globalStylesheet);
    button5->setFixedSize(150,60);

    QPushButton *button6=new QPushButton("结束对抗");
    QIcon icon6(":/icons/resource/icons/齿轮pixel_.png");
    button6->setIcon(icon6);
    button6->setIconSize(QSize(40,40));
    button6->setStyleSheet(globalStylesheet);
    button6->setFixedSize(150,60);

    QPushButton *backButton=new QPushButton("返回");
    QPushButton *submitButton=new QPushButton("提交");
    QPushButton *helpButton=new QPushButton("提示");

    QIcon backIcon(":/icons/resource/icons/钥匙pixel.png");
    backButton->setIcon(backIcon);
    backButton->setIconSize(QSize(40,40));
    backButton->setStyleSheet(globalStylesheet);
    backButton->setFixedSize(150,60);


    QIcon submitIcon(":/icons/resource/icons/放大镜pixel_.png");
    submitButton->setIcon(submitIcon);
    submitButton->setIconSize(QSize(40,40));
    submitButton->setStyleSheet(globalStylesheet);
    submitButton->setFixedSize(150,60);

    QIcon helpIcon(":/icons/resource/icons/星星pixel.png");
    helpButton->setIcon(helpIcon);
    helpButton->setIconSize(QSize(40,40));
    helpButton->setStyleSheet(globalStylesheet);
    helpButton->setFixedSize(150,60);

    //连接按钮 执行四个基本操作：左旋转 右旋转 燃烧 撤回
    connect(backButton,&QPushButton::clicked,this,&Game::onBackButtonClicked);
    connect(backButton,&QPushButton::clicked,this,&Game::end);
    connect(backButton,&QPushButton::clicked,TimeWatchWidget,&TimeWatch::resetTimeWatch);

    connect(button1,&QPushButton::clicked,this,&Game::left_rotate);
    connect(button2,&QPushButton::clicked,this,&Game::right_rotate);
    connect(button3,&QPushButton::clicked,this,&Game::burn);
    connect(button4,&QPushButton::clicked,this,&Game::undo);

    connectOperation();

    connect(button5,&QPushButton::clicked,this,&Game::startAaginst);
    connect(button6,&QPushButton::clicked,this,&Game::endAgainst);

    connect(this,&Game::start,TimeWatchWidget,&TimeWatch::startTimeWatch);
    connect(this,&Game::end,TimeWatchWidget,&TimeWatch::stopTimeWatch);

    //提交按钮 判断答案
    connect(submitButton,&QPushButton::clicked,this,&Game::judge);

    //帮助按钮
    connect(helpButton,&QPushButton::clicked,this,&Game::help);

    Vlayout=new QVBoxLayout;
    Vlayout->addStretch(1);

    paintingLayout=new QHBoxLayout;

    paintingLayout->addStretch(1);
    paintingLayout->addWidget(TimeWatchWidget);
    paintingLayout->addStretch(1);
    paintingLayout->addLayout(gridLayout);
    paintingLayout->addStretch(1);
    paintingLayout->addLayout(answerLayout);
    paintingLayout->addStretch(1);

    Vlayout->addLayout(paintingLayout);
    Vlayout->addStretch(1);

    Hlayout_1=new QHBoxLayout;
    Hlayout_1->addStretch(1);
    Hlayout_1->addWidget(button1);
    Hlayout_1->addStretch(1);
    Hlayout_1->addWidget(button2);
    Hlayout_1->addStretch(1);
    Hlayout_1->addWidget(button3);
    Hlayout_1->addStretch(1);
    Hlayout_1->addWidget(button4);
    Hlayout_1->addStretch(1);

    Hlayout_2=new QHBoxLayout;
    Hlayout_2->addStretch(1);
    Hlayout_2->addWidget(button5);
    Hlayout_2->addStretch(1);
    Hlayout_2->addWidget(button6);
    Hlayout_2->addStretch(1);
    Hlayout_2->addWidget(submitButton);
    Hlayout_2->addStretch(1);
    Hlayout_2->addWidget(backButton);
    Hlayout_2->addStretch(1);
    Hlayout_2->addWidget(helpButton);
    Hlayout_2->addStretch(1);

    Vlayout->addLayout(Hlayout_1);
    Vlayout->addStretch(1);
    Vlayout->addLayout(Hlayout_2);
    Vlayout->addStretch(1);
    setLayout(Vlayout);
}

void Game::burn()
{
    //燃烧矩阵
    //根据游戏规则，可以理解为，先判断当前方格内的值是否为1，如果是，则不会向下burn，
    //否则，向下burn，同时将burn后的数值变为1，位于其正下方的方格的颜色也会发生相应的改变
    //根据游戏规则，由下向上遍历
    //考虑到特判情况，位于最下面的一行无法往下流动，所以当其数值不为1时，burn后也会自动转化为1
    size_t row=m_size;
    size_t col=m_size;
    for(size_t i=row-1;i>0;--i)
    {
        for(size_t j=0;j<col;++j)
        {
            if(i==row-1)
            {
                if(m_cells[i][j].getValue()!=1 && m_cells[i-1][j].getValue()==1)
                {
                    m_cells[i][j].setNum(1);
                }
            }
            if(m_cells[i-1][j].getValue()>1)
            {
                m_cells[i][j].setNum(m_cells[i-1][j].getValue()-1);
                m_cells[i-1][j].setNum(1);
                m_cells[i][j].setColor(m_cells[i-1][j].getColor());
            }
        }
    }
    // std::vector<std::vector<Cell>> temp(col,std::vector<Cell>(row));
    // temp=m_cells;
    m_cellsHistory.push(m_cells);
    update();
}


void Game::undo()       //撤回操作
{
    if(m_cellsHistory.size()==1)
    {
        qDebug()<<"No more undo"<<Qt::endl;
        return;
    }
    if(m_cellsHistory.size()>1)
    {
        m_cellsHistory.pop();
        m_cells=m_cellsHistory.top();
        qDebug()<<"Undo successfully"<< Qt::endl;
        qDebug()<<"stack size: "<<m_cellsHistory.size()<<Qt::endl;
    }
    else
    {
        qDebug()<<"Unsuccessful"<<Qt::endl;
    }
    update();
}

inline QColor parseRGB(const QString &rgbStr)
{
    static QRegularExpression rx(R"(rgb\((\d+),\s*(\d+),\s*(\d+)\))");          //声明为static变量，因为创建正则表达式是相对耗时的操作，如果频繁创建会影响性能
    QRegularExpressionMatch match=rx.match(rgbStr);
    if(match.hasMatch())
    {
        int r=match.captured(1).toInt();
        int g=match.captured(2).toInt();
        int b=match.captured(3).toInt();
        return QColor(r, g, b);
    }
    else
    {
        throw std::invalid_argument("Invalid RGB string format");
    }
}

inline bool compareRgb(const QString &rgbStr1, const QString &rgbStr2) {
    QColor color1=parseRGB(rgbStr1);
    QColor color2=parseRGB(rgbStr2);

    qDebug()<<color1.red()<<color1.green()<<color1.blue();
    qDebug()<<color2.red()<<color2.green()<<color2.blue();

    int red=abs(color1.red()-color2.red());
    int green=abs(color1.green()-color2.green());
    int blue=abs(color1.blue()-color2.blue());
    if(red<=15 && green<=15 && blue<=15)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//判断是否正确
void Game::judge()
{
    std::cout<<"judging\n";
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {
            if(isLevel)
            {   //对应rgb格式
                if(compareRgb(QString::fromStdString(m_cells[i][j].getColor()),QString::fromStdString(answers[i][j].getColor())) || m_cells[i][j].getValue()!=1)
                {
                    qDebug()<<m_cells[i][j].getColor();
                    qDebug()<<answers[i][j].getColor();
                    WA();
                    return;
                }
            }
            else
            {
                //对应随机模式，也就是简单的单词描述
                if(m_cells[i][j].getColor()!=answers[i][j].getColor() || m_cells[i][j].getValue()!=1)
                {
                    WA();
                    return;
                }
            }
        }
    }
    emit end();     //发送结束信号
    if(isLevel)     //如果是是isLevel，也即是关卡模式
    {
        m_player->setHasPlayed(true,nowLevel);      //对用户的数据进行更新
        updatePlayer();                             //对当前在线的用户数据进行更新
        emit updateRanking(nowLevel);               //发送信号，更新排行榜
        emit updateData(nowLevel);                  //发送信号，更新排行榜的文件文件
    }
    AC();           //显示AC对话框
    return;
}

void Game::WA()
{
    waDialog=new WADialog(this);
    connect(waDialog,&WADialog::backToMain,this,&Game::onBackButtonClicked);
    waDialog->exec();
    return;
}


void Game::AC()
{
    acDialog=new ACDialog();
    connect(acDialog,&ACDialog::backToMain,this,&Game::onBackButtonClicked);
    connect(acDialog,&ACDialog::goToNextLevel,this,&Game::setNewGame);
    acDialog->exec();
    return;
}

void Game::setNewGame()
{
    if(isLevel)
    {
        nowLevel++;
        if(nowLevel+1>12)
        {
            nowLevel%=12;
            setGame(nowLevel);
        }
        else    setGame(nowLevel);
        return;
    }
    else
    {
        generateRandomMap(randomMapLevel);
        return;
    }
}

void Game::calculateSteps()         //计算操作步数
{
    steps++;
    qDebug()<<"steps："<<steps;
}

void Game::calculateBackSteps()     //计算回退步数
{
    backSteps++;
    qDebug()<<"backSteps："<<backSteps;
}

void Game::calculateTime()          //计算时间
{
    emit start();
}

void Game::generateRandomMap(const int num)     //生成随机地图
{
    helps.clear();
    TimeWatchWidget->original();
    //connectOperation();
    isLevel=false;
    std::string colors[10]
    {
        "red","green","blue","lightBlue","yellow","orange","pink","purple","cyan"
    };
    qDebug()<<"success\n";
    int level=num;
    randomMapLevel=num;
    std::random_device rd_operation;     //随机数发生器种子
    std::mt19937 gen_number(rd_operation());   //使用Mersenne Twister算法生成伪随机数

    std::uniform_int_distribution<> dis_color(0,8);     //生成颜色的种类
    std::uniform_int_distribution<> dis_operation(0,2);     //生成操作类型
    int optNumber=0;
    if(level==1)        //对应难度为1
    {
        m_size=5;
        m_cells=std::vector(m_size, std::vector<Cell>(m_size));
        int number=0;
        std::string color;
        std::uniform_int_distribution<> dis_number(1,6);        //生成数字：1-6
        std::uniform_int_distribution<> dis_steps(5,6);         //生成操作步数：5-6
        optNumber=dis_steps(gen_number);
        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                number=dis_number(gen_number);
                color=colors[dis_color(gen_number)];
                m_cells[i][j].setNumAndColor(number,color);
                gridLayout->addWidget(&m_cells[i][j],i,j);
                m_cells[i][j].setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // 设置小方块的大小策略为Preferred
                m_cells[i][j].setFixedSize(100, 100); // 设置小方块的固定大小为100x100像素
            }
        }
    }
    else if(level==2)
    {
        m_size=7;
        m_cells=std::vector(m_size, std::vector<Cell>(m_size));
        int number=0;
        std::string color;
        std::uniform_int_distribution<> dis_number(1,11);        // 生成数字：1-11
        std::uniform_int_distribution<> dis_steps(9,12);        // 生成操作步数：9-12
        optNumber=dis_steps(gen_number);
        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                number=dis_number(gen_number);
                color=colors[dis_color(gen_number)];
                m_cells[i][j].setNumAndColor(number,color);
                gridLayout->addWidget(&m_cells[i][j],i,j);
                m_cells[i][j].setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // 设置小方块的大小策略为Preferred
                m_cells[i][j].setFixedSize(75, 75); // 设置小方块的固定大小为100x100像素
            }
        }
    }
    else
    {
        m_size=9;
        m_cells=std::vector(m_size, std::vector<Cell>(m_size));
        int number=0;
        std::string color;
        std::uniform_int_distribution<> dis_number(1,15);        // 生成数字：1-15
        std::uniform_int_distribution<> dis_steps(13,18);       // 生成操作步数：13-18
        optNumber=dis_steps(gen_number);
        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                number=dis_number(gen_number);
                color=colors[dis_color(gen_number)];
                m_cells[i][j].setNumAndColor(number,color);
                gridLayout->addWidget(&m_cells[i][j],i,j);
                m_cells[i][j].setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // 设置小方块的大小策略为Preferred
                m_cells[i][j].setFixedSize(50, 50); // 设置小方块的固定大小为100x100像素
            }
        }
    }

    //生成一系列操作，并且存入队列中
    std::queue<Operation> opt;
    Operation last;
    while(true)
    {
        Operation op=Operation(dis_operation(gen_number));
        if(op==BURN && last!=op)        //防止可能一直是燃烧操作的情况
        {
            optNumber--;
            opt.push(op);
            helps.push_back(op);
            if(optNumber==0)   break;
        }
        else if(op==BURN && last==BURN)
        {
            continue;
        }
        else
        {
            opt.push(op);
            helps.push_back(op);
        }
        last=op;
    }

    int maxNumber=0;
    for(int i=0;i<m_size;i++)
    {
        for(int j=0;j<m_size;j++)
        {
            maxNumber=std::max(maxNumber,m_cells[i][j].getValue());
        }
    }
    if(maxNumber>1)     maxNumber--;
    while(true)
    {
        Operation op=Operation(dis_operation(gen_number));
        if(op==BURN && last!=op)        //防止可能一直是燃烧操作的情况
        {
            maxNumber--;
            opt.push(op);
            helps.push_back(op);
            if(maxNumber==0)   break;
        }
        else if(op==BURN && last==BURN)
        {
            continue;
        }
        else
        {
            opt.push(op);
            helps.push_back(op);
        }
        last=op;
    }
    calculateHelp();

    size_t row=m_size;
    size_t col=m_size;
    std::vector<std::vector<Cell>> rotated;
    std::vector<std::vector<Cell>> question;
    rotated=std::vector(col, std::vector<Cell>(row));
    answers=std::vector(col, std::vector<Cell>(row));
    question=m_cells;

    while(opt.size())
    {
        Operation now=opt.front();
        opt.pop();
        switch(now)
        {
            case LEFT_ROTATE:
            {
                for(int i=0;i<row;++i)
                {
                    for(int j=0;j<col;++j)
                    {
                        rotated[col-j-1][i]=question[i][j];
                    }
                }
                question=rotated;
                break;
            }
            case RIGHT_ROTATE:
            {
                for(int i=0;i<row;++i)
                {
                    for(int j=0;j<col;++j)
                    {
                        rotated[j][row-i-1]=question[i][j];
                    }
                }
                question=rotated;
                break;
            }
            case BURN:
            {
                for(size_t i=row-1;i>0;--i)
                {
                    for(size_t j=0;j<col;++j)
                    {
                        if(i==row-1)
                        {
                            if(question[i][j].getValue()!=1 && question[i-1][j].getValue()==1)
                            {
                                question[i][j].setNum(1);
                            }
                        }
                        if(question[i-1][j].getValue()>1)
                        {
                            question[i][j].setNum(question[i-1][j].getValue()-1);
                            question[i-1][j].setNum(1);
                            question[i][j].setColor(question[i-1][j].getColor());
                        }
                    }
                }
                break;
            }
        }
    }
    answers=question;
    if(level==1)
    {
        for(size_t i=0;i<m_size;i++){
            for(size_t j=0;j<m_size;j++){
                answerLayout->addWidget(&answers[i][j],i,j);
                answers[i][j].setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
                answers[i][j].setFixedSize(100,100);
            }
        }
        //设置布局的对齐方式为居中对齐
        answerLayout->setAlignment(Qt::AlignCenter);
    }
    else if(level==2)
    {
        for(size_t i=0;i<m_size;i++){
            for(size_t j=0;j<m_size;j++){
                answerLayout->addWidget(&answers[i][j],i,j);
                answers[i][j].setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
                answers[i][j].setFixedSize(75,75);
            }
        }
        //设置布局的对齐方式为居中对齐
        answerLayout->setAlignment(Qt::AlignCenter);
    }
    else
    {
        for(size_t i=0;i<m_size;i++){
            for(size_t j=0;j<m_size;j++){
                answerLayout->addWidget(&answers[i][j],i,j);
                answers[i][j].setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
                answers[i][j].setFixedSize(50,50);
            }
        }
        //设置布局的对齐方式为居中对齐
        answerLayout->setAlignment(Qt::AlignCenter);
    }

    while(m_cellsHistory.size())
    {
        m_cellsHistory.pop();
    }
    m_cellsHistory.push(m_cells);
    update();
}

void Game::updatePlayer()       //更新当前在线玩家的游戏记录
{
    qDebug()<<m_player->getUserName()<<m_player->getTime(nowLevel);
    auto spendTime=TimeWatchWidget->passTimeRecord();
    if(m_player->getTime(nowLevel)>spendTime)
    {
        qDebug()<<"Game 1";
        qDebug()<<"now level"<<nowLevel;
        m_player->setHasPlayed(true,nowLevel);
        m_player->setTime(spendTime,nowLevel);
        m_player->setSteps(steps,nowLevel);
        m_player->setBackSteps(backSteps,nowLevel);
        m_player->setLevelneedUpdate(nowLevel);
        qDebug()<<"player now information:"<<m_player->getTime(nowLevel)<<m_player->getSteps(nowLevel)<<m_player->getBackSteps(nowLevel);
    }
    else if(m_player->getTime(nowLevel)==spendTime)
    {
        if(m_player->getSteps(nowLevel)>=steps||m_player->getBackSteps(nowLevel)>=backSteps)
        {
            qDebug()<<"Game 2";
            m_player->setHasPlayed(true,nowLevel);
            m_player->setSteps(steps,nowLevel);
            m_player->setBackSteps(backSteps,nowLevel);
            m_player->setLevelneedUpdate(nowLevel);
        }
    }
}

inline int getRandNumer()
{
    std::random_device rd_operation;                                    //随机数发生器种子
    std::mt19937 gen_operation(rd_operation());                         //使用Mersenne Twister算法生成伪随机数
    std::uniform_int_distribution<> dis_operation(1, 2);                //均匀分布，范围为[1,2]
    int num=static_cast<int>(dis_operation(gen_operation));             //从分布中抽取一个整数并转换为Operation枚举值
    return num;
}

void Game::change()
{
    int num=getRandNumer();
    switch (num) {
    case 1:
        this->left_rotate();
        break;
    case 2:
        this->right_rotate();
        break;
    default:
        break;
    }
}

void Game::startAaginst()       //启动对抗
{
    m_timer->start(1000);
    connect(m_timer,&QTimer::timeout,this,&Game::change);
}

void Game::endAgainst()         //结束对抗
{
    disconnect(m_timer,&QTimer::timeout,this,&Game::change);
}

void Game::connectOperation()
{
    //连接四个按钮 记录当前的操作步数
    connect(button1,&QPushButton::clicked,this,&Game::calculateSteps);
    connect(button2,&QPushButton::clicked,this,&Game::calculateSteps);
    connect(button3,&QPushButton::clicked,this,&Game::calculateSteps);
    connect(button4,&QPushButton::clicked,this,&Game::calculateSteps);
    connect(button4,&QPushButton::clicked,this,&Game::calculateBackSteps);

    //连接四个按钮 开始计时
    connect(button1,&QPushButton::clicked,this,&Game::calculateTime);
    connect(button2,&QPushButton::clicked,this,&Game::calculateTime);
    connect(button3,&QPushButton::clicked,this,&Game::calculateTime);
    connect(button4,&QPushButton::clicked,this,&Game::calculateTime);
}

void Game::cleanGridLayout(QGridLayout *layout)
{
    //清空m_layoutMain原布局内的所有元素
    for(int row=layout->rowCount()-1;row>=0;--row)
    {
        for(int col=layout->columnCount()-1;col>=0;--col)
        {
            QLayoutItem* item=layout->itemAtPosition(row, col);         //QLayoutItem是管理layout中小控件的一个接口，对小控件进行管理
            if(item)                                                    //delete item后不会删除掉m_cells或answers
            {
                layout->removeItem(item);
                delete item;
            }
        }
    }
}

void Game::createGridLayout(QGridLayout *layout,std::vector<std::vector<Cell>> &map)
{
    layout->setSpacing(5);                              //设置间距
    layout->setAlignment(Qt::AlignCenter);              //设置布局的对齐方式为居中对齐
    for(size_t i=0;i<m_size;i++){
        for(size_t j=0;j<m_size;j++){
            layout->addWidget(&map[i][j],i,j);
            map[i][j].setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);        //设置小方块的大小策略为Preferred
            map[i][j].setFixedSize(100, 100);           //设置小方块的固定大小为100x100像素
        }
    }
}

void Game::help()
{
    if(isLevel)
    {
        QMessageBox::information(nullptr,"提示","关卡模式比较简单，公平起见，还是自己动脑筋解决吧");
        return;
    }
    else
    {
        if(Finals.empty() || checkIsAllOne())
        {
            QMessageBox::information(nullptr,"提示","所有提示已经提供完毕");
            return;
        }
        Operation topOperation=Finals.front();
        switch(topOperation)
        {
        case BURN:
            QMessageBox::information(nullptr,"提示","下一步操作是燃烧\n注意：玩家请按照提示操作，不要做与提示不符的操作，否则只能撤回");
            break;
        case LEFT_ROTATE:
            QMessageBox::information(nullptr,"提示","下一步操作时左旋转\n注意：玩家请按照提示操作，不要做与提示不符的操作，否则只能撤回");
            break;
        case RIGHT_ROTATE:
            QMessageBox::information(nullptr,"提示","下一步操作时右旋转\n注意：玩家请按照提示操作，不要做与提示不符的操作，否则只能撤回");
            break;
        }
        Finals.pop_front();
    }
}

void Game::calculateHelp()
{
    Finals.clear();
    int lefts=0;
    int rights=0;
    for(int i=0;i<helps.size();i++)
    {
        if(helps[i]==BURN)
        {
            int cnt=lefts-rights;
            cnt%=4;
            if(cnt==0)
            {
            }
            else if(cnt>0)
            {
                if(cnt==3)
                {
                    Finals.push_back(RIGHT_ROTATE);
                }
                else
                {
                    for(int j=1;j<=cnt;j++)
                    {
                        Finals.push_back(LEFT_ROTATE);
                    }
                }
            }
            else
            {
                cnt=abs(cnt);
                if(cnt==3)
                {
                    Finals.push_back(LEFT_ROTATE);
                }
                for(int j=1;j<=cnt;j++)
                {
                    Finals.push_back(RIGHT_ROTATE);
                }
            }
            Finals.push_back(BURN);
            lefts=0;
            rights=0;
        }
        else if(helps[i]==LEFT_ROTATE)
        {
            lefts++;
        }
        else if(helps[i]==RIGHT_ROTATE)
        {
            rights++;
        }
    }
}

bool Game::checkIsAllOne()
{
    for(int i=0;i<m_size;i++)
    {
        for(int j=0;j<m_size;j++)
        {
            if(m_cells[i][j].getValue()!=1)     return false;
        }
    }
    return true;
}
