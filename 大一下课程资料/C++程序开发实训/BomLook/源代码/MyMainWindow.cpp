#include "MyMainWindow.h"
#include<QLabel>
#include<QVBoxLayout>
#include<QKeyEvent>
#include<QPropertyAnimation>
#include "LevelTwo.h"
#include <QPainter>
#include <QApplication>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QWidget(parent)
{
    onlinePlayer=new Player;
    for(int i=1;i<=12;i++)
    {
        QString fileName=QString("./Ranking%1.bin").arg(i);
        QFile rankingFile(fileName);
        QFileInfo rankingInfo(rankingFile);
        if(!rankingInfo.size())
        {
            if(rankingFile.open(QIODevice::WriteOnly))
            {
                QDataStream out(&rankingFile);
                out<<"tourist"<<0<<500;
                qInfo()<<QString("排行榜创建成功 %1").arg(i);
                rankingFile.close();
            }
        }
    }

    setupMainPage();
    setupSubPages();

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(&pages);
    //setLayout(mainLayout);

    this->installEventFilter(this);                             //安装事件过滤器
    background=QImage(":/images/resource/picture/backGround.jpg"); //设置背景页面

    QFile file("./AccountData.bin");
    QFileInfo fileInfo(file);
    if(!fileInfo.size())
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            out<<*onlinePlayer;
        }
    }
    file.close();

    QString dirName("/PlayerMap");
    QString path=QApplication::applicationDirPath();
    QString dirPath=path+dirName;
    QDir *folder=new QDir;
    bool exit=folder->exists(dirPath);
    if(exit)
    {
        qDebug()<<"该文件夹已经被创建";
    }
    else
    {
        bool ok=folder->mkpath(dirPath);
        if(ok)  qDebug()<<"文件夹创建成功";
        else    qDebug()<<"文件夹还没有完成创建";
    }
}


MyMainWindow::~MyMainWindow()
{
    if(onlinePlayer!=nullptr)
    {
        delete onlinePlayer;
        onlinePlayer=nullptr;
    }
    if(gameIntroduction!= nullptr)
    {
        delete gameIntroduction;
        gameIntroduction=nullptr;
    }
    if(startGame!=nullptr)
    {
        delete startGame;
        startGame=nullptr;
    }
    if(home!=nullptr)
    {
        delete home;
        home=nullptr;
    }
}


void MyMainWindow::setupMainPage() {

    //为主页添加名字
    //设置字体
    QFont font("Lucida Handwriting");
    font.setPointSize(100);
    QLabel *GameTitle= new QLabel(this);
    GameTitle->setStyleSheet("color: orange");

    //设置阴影
    QGraphicsDropShadowEffect *shadowEffect=new QGraphicsDropShadowEffect(GameTitle);
    shadowEffect->setBlurRadius(10.0);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    shadowEffect->setOffset(5.0);

    //应用设置
    GameTitle->setFont(font);
    GameTitle->setText("Fire Painting");
    GameTitle->setGraphicsEffect(shadowEffect);


    QWidget *mainPage=new QWidget(this);                    //创建主页面
    QVBoxLayout *mainLayout=new QVBoxLayout(mainPage);      //主布局
    QHBoxLayout *buttonLayout=new QHBoxLayout;    //按钮布局
    QHBoxLayout *titleLayout=new QHBoxLayout;     //标题布局

    //调整布局
    mainLayout->addStretch(1);
    titleLayout->addStretch(1);
    titleLayout->addWidget(GameTitle);
    titleLayout->addStretch(3);
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

    //设置按钮，并且添加到布局中
    QPushButton *button1=new QPushButton(QString("开始游戏"),mainPage);
    QIcon icon1(":/icons/resource/icons/游戏机pixel.png");
    button1->setIcon(icon1);
    button1->setIconSize(QSize(40,40));
    button1->setStyleSheet(globalStylesheet);

    connect(button1,&QPushButton::clicked,this,&MyMainWindow::switchToSubPage);
    //设置按钮索引
    button1->setProperty("PageIndex",1);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button1);

    QPushButton *button2 = new QPushButton(QString("游戏介绍"),mainPage);
    QIcon icon2(":/icons/resource/icons/信封pixel.png");
    button2->setIcon(icon2);
    button2->setIconSize(QSize(40,40));
    button2->setStyleSheet(globalStylesheet);
    connect(button2,&QPushButton::clicked,this,&MyMainWindow::switchToSubPage);
    //设置按钮索引
    button2->setProperty("PageIndex",2);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button2);

    QPushButton *button3=new QPushButton(QString("登录"),mainPage);
    QIcon icon3(":/icons/resource/icons/锁pixel.png");
    button3->setIcon(icon3);
    button3->setIconSize(QSize(40,40));
    button3->setStyleSheet(globalStylesheet);
    login=new Login(nullptr,onlinePlayer);
    connect(button3,&QPushButton::clicked,login,&Login::show);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button3);


    QPushButton *button4=new QPushButton(QString("个人用户"),mainPage);
    QIcon icon4(":/icons/resource/icons/房子pixel.png");
    button4->setIcon(icon4);
    button4->setIconSize(QSize(40,40));
    button4->setStyleSheet(globalStylesheet);
    connect(button4,&QPushButton::clicked,this,&MyMainWindow::switchToSubPage);
    button4->setProperty("PageIndex",3);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button4);

    QPushButton *button6=new QPushButton(QString("退出游戏"),mainPage);
    QIcon icon6(":/icons/resource/icons/钥匙pixel.png");
    button6->setIcon(icon6);
    button6->setIconSize(QSize(40,40));
    button6->setStyleSheet(globalStylesheet);
    connect(button6,&QPushButton::clicked,this,&MyMainWindow::close);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button6);
    buttonLayout->addStretch(1);


    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    pages.addWidget(mainPage);  //添加主页面

    mainPage->show();           //显示主页面
}


void MyMainWindow::setupSubPages() {

    //创建levelTwo页面
    startGame=new LevelTwo(this,onlinePlayer);
    connect(startGame,&LevelTwo::backToMain,this,&MyMainWindow::switchToMainPage);
    pages.addWidget(startGame);
    startGame->hide();

    //创建gameIntroduction页面
    gameIntroduction=new GameIntroduction(this);
    connect(gameIntroduction,&GameIntroduction::backToMain,this,&MyMainWindow::switchToMainPage);
    pages.addWidget(gameIntroduction);
    gameIntroduction->hide();

    //创建home页面
    home=new Home(this,onlinePlayer);
    connect(home,&Home::backToMain,this,&MyMainWindow::switchToMainPage);
    pages.addWidget(home);
    home->hide();

    connect(login,&Login::updatePlayer,home,&Home::updatePlayer);
}


void MyMainWindow::switchToSubPage()
{
    qDebug()<<"Switching to sub page...111";
    QObject *senderObj=sender();
    if(senderObj)
    {
        qDebug()<<"Sender object is not null.";
        QPushButton *button=qobject_cast<QPushButton*>(senderObj);  //强制类型转换为QPushButton
        if(button)      //转换成功
        {
            qDebug()<<"Sender is a QPushButton.";
            int pageIndex=button->property("PageIndex").toInt();    //获取按钮对应页面的索引
            animateSwitch(0, pageIndex);                            //0是主页面的索引
        }
        else            //转换失败
        {
            qDebug()<<"Sender is not a QPushButton.";
        }
    }
    else
    {
        qDebug()<<"Sender object is null.";
    }
}

//键盘操作：跳转到子页面
void MyMainWindow::enterToSubPage(int pageIndex)
{
    animateSwitch(0,pageIndex);
}

//跳转到主页面
void MyMainWindow::switchToMainPage()
{
    animateSwitch(pages.currentIndex(),0); //0是主页面的索引
}

//跳转页面动画
void MyMainWindow::animateSwitch(int fromIndex, int toIndex)
{
    //为特定属性创建动画
    //pages.widget(fromIndex)   返回索引为fromIndex的页面部件
    //geometry指明了要动画化的属性，也就是几何属性
    QPropertyAnimation *pageAnimation=new QPropertyAnimation(pages.widget(fromIndex),"geometry");
    pageAnimation->setDuration(500);                                    //设置动画的持续时间
    pageAnimation->setStartValue(pages.widget(fromIndex)->geometry());  //设置起始页面的几何属性
    pageAnimation->setEndValue(pages.widget(toIndex)->geometry());      //设置结束页面的几何属性

    pages.setCurrentIndex(toIndex);     //设置当前页面索引设置为toIndex，立即切换到目标页面

    animation.clear();                      //清空原来的动画
    animation.addAnimation(pageAnimation);  //加入新动画
    animation.start();                      //开始执行动画
}

//重载：通过键盘操作跳转到子页面
bool MyMainWindow::eventFilter(QObject *obj,QEvent *event) {
    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
        if(keyEvent->key()==Qt::Key_Return)
        {
            if(pages.currentIndex()==0)             //当前主页面是主页面时，跳转到子页面
            {
                qDebug()<<"Switching to sub page...";
                QWidget *focusWidget=QApplication::focusWidget();
                if(focusWidget && focusWidget->property("PageIndex").isValid())
                {
                    int pageIndex=focusWidget->property("PageIndex").toInt();
                    enterToSubPage(pageIndex);      //跳转到子页面
                }
            }
            else    //当前页面是子页面，则跳转到主页面
            {
                qDebug()<<"Switching to main page...";
                switchToMainPage();
            }
            return true;    //拦截键盘事件，不再继续传递
        }
    }
    //其他事件交给父类处理
    return QWidget::eventFilter(obj, event);
}

//重载：closeEvent函数，用于关闭游戏时，对文件进行更新
void MyMainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this, "Game Close", "你真的确定退出游戏吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        //如果是tourist，即游客模式，不对文件进行更新
        if(onlinePlayer->getUserName()=="tourist")
        {
            qInfo()<<"不需要更新主页";
            event->accept();
            return;
        }

        QFile accountData("AccountData.bin");
        QDataStream inFromFile(&accountData);

        if(!accountData.open(QIODevice::ReadOnly))
        {
            qCritical() << "无法打开文件进行读取 accountData isExit";
            return;
        }


        //打开文件后：
        bool isFind=false;                              //是否找到要修改的对象的数据
        qint64 beforeSize=0;                            //在此对象之前的所有数据的字节大小
        qint64 endSize=0;                               //在包括文件头开始，到此对象数据结束的所有数据的字节大小

        Player temp;
        while(!inFromFile.atEnd())
        {
            qDebug()<<"error checkIsOnline MyMainWindow";

            inFromFile>>temp;
            if(temp.getUserName()==onlinePlayer->getUserName() && temp.getPwd()==onlinePlayer->getPwd())
            {
                endSize=accountData.pos();              //获取endSize的大小
                isFind=true;
            }
            else if(!isFind)
            {
                beforeSize=accountData.pos();           //获取beforeSize的大小
            }
        }
        accountData.close();


        QFile targetFile("AccountData.bin");
        QByteArray beforeData;
        QByteArray afterData;
        QDataStream readFromFile(&targetFile);

        if(targetFile.open(QIODevice::ReadOnly)){
            beforeData=targetFile.read(beforeSize);               //读取修改对象前面的数据
            targetFile.seek(endSize);                               //定位到该对象后面，开始读取后续的对象到afterdata这个二进制数组
            /*应该还有一种方法，用文件总大小减去endSize，然后读取这么长就行,
            它是不是结构化的Player不重要，反序列的时候肯定能读出来的*/

            Player temp;
            while(!targetFile.atEnd()){
                QDataStream toByteArray(&afterData,QIODevice::WriteOnly|QIODevice::Append);
                readFromFile>>temp;
                toByteArray<<temp;
            }
        }
        else
        {
            qDebug()<<"错误，无法打开用户信息文件，进行读取:  MyMainWindow 退出页面";
        }

        //将修改后的玩家二进制化到数组里
        QByteArray revisedData;
        QDataStream revisedStream(&revisedData,QIODevice::WriteOnly);
        revisedStream<<*onlinePlayer;

        //开始合并数据
        QByteArray updatedData;
        updatedData=beforeData+revisedData+afterData;

        targetFile.close();//重新打开一下文件，怕出什么问题
        if(targetFile.open(QIODevice::WriteOnly)){
            targetFile.write(updatedData);
        }
        else
        {
            qDebug()<<"错误，无法打开用户文件信息，进行修改：MyMainWindow";
        }
        //关闭文件
        targetFile.close();

        event->accept();
    }
    else
    {
        event->ignore();
    }
}

//重载：使得能自动调节背景页面大小并更新
void MyMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //将背景图片缩放到窗口大小，并绘制背景
    QImage scaledBackground=background.scaled(this->size(),Qt::IgnoreAspectRatio);
    painter.drawImage(0,0,scaledBackground);
}
