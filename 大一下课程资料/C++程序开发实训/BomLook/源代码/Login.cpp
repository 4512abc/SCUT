#include "Login.h"
#include "ui_Login.h"
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QMessageBox>
Login::Login(QWidget *parent, Player *onlinePlayer)
    : QWidget(parent)
    , ui(new Ui::Login),m_player(onlinePlayer)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    //设置title和icon
    setWindowTitle("Login");
    QIcon icon(":/icons/resource/icons/登录.png");
    setWindowIcon(icon);

    ui->setupUi(this);
    ui->name->setStyleSheet("color: black; font-size: 14px;");
    ui->password->setStyleSheet("color: black; font-size: 14px;");

    //设置页面和布局
    m_register=new Register(nullptr,m_player);
    connect(m_register,&Register::backToLogin,this,&::Login::switchToLogin);
    QPixmap *picture=new QPixmap(":/images/resource/picture/微信图片_20231107235826.jpg");
    QSize size=ui->label_image->size();
    ui->label_image->setPixmap(picture->scaled(size));

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#88888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);
    connect(ui->signIn,&QPushButton::clicked,this,&Login::testLogin);

    this->setFixedSize(780,520);

    connect(ui->signUp,&QPushButton::clicked,this,&Login::switchToRegister);    //跳转到注册页面
    connect(ui->exitButton,&QPushButton::clicked,this,&Login::checkIsOnline);   //查看当前是否处于登录状态
}

void Login::testLogin()
{
    //检测输入是否合法
    QString inputName;
    QString inputPwd;
    int userID=-1;
    if(ui->name->text()=="")        //如果输入的用户名为空，提示用户重新输入
    {
        QMessageBox::critical(nullptr,"错误","用户名为空，请重新输入用户名");
        ui->name->clear();
        ui->password->clear();
        ui->name->setFocus();
    }
    else if(ui->password->text()=="")       //如果输入的密码为空，提示用户重新输入
    {
        QMessageBox::critical(nullptr,"错误","密码为空，请重新输入密码");
        ui->name->clear();
        ui->password->clear();
        ui->name->setFocus();
    }
    else if(m_player->getUserName()==ui->name->text())      //如果当前账号的用户名和输入的用户名相同，提示用户已经登录该账号
    {
        QMessageBox::critical(nullptr,"错误","你已经登录了该账号");
        ui->name->clear();
        ui->password->clear();
        ui->name->setFocus();
    }
    else if(m_player->getUserName()!="tourist")         //如果当前的用户名不是tourist，提示当前处于登录状态
    {
        QMessageBox::critical(nullptr,"错误","你现在处于登录状态，请先退出账号");
        ui->name->clear();
        ui->password->clear();
        ui->name->setFocus();
    }
    else    //开始检测输入的账户是否存在
    {
        inputName=ui->name->text();
        inputPwd=ui->password->text();
        bool state=isExit(inputName,inputPwd);
        if(state)       //存在
        {
            QMessageBox::information(nullptr,"成功","登录成功");
            return;
        }
        else            //不存在，提示玩家重新输入
        {
            QMessageBox::critical(nullptr,"错误","该账户不存在，请重新输入账户名和密码");
            ui->name->clear();
            ui->password->clear();
            ui->name->setFocus();
        }
    }
}

//检测当前输入的用户名是否存在
bool Login::isExit(const QString &inputName,const QString &inputPwd)
{
    QFile playerData("./AccountData.bin");
    QDataStream in(&playerData);
    if(!playerData.open(QIODevice::ReadOnly))
    {
        qCritical() << "无法打开文件进行读取 accountData login isExit";
        return false;
    }
    Player temp;
    while(!in.atEnd())
    {
        in>>temp;
        //如果找到了，对player进行更新，并且返回true
        if(temp.getUserName()==ui->name->text() && temp.getPwd()==ui->password->text())
        {
            m_player->setUserName(temp.getUserName());
            m_player->setPwd(temp.getPwd());
            m_player->setID(temp.getID());
            for(int i=1;i<=12;i++)
            {
                m_player->setHasPlayed(temp.getHasPlayed(i),i);
                m_player->setSteps(temp.getSteps(i),i);
                m_player->setBackSteps(temp.getBackSteps(i),i);
                m_player->setTime(temp.getTime(i),i);
            }
            qDebug()<<"yes";
            playerData.close();
            emit updatePlayer();        //发送更新账户信息的信号
            return true;
        }
    }
    playerData.close();
    return false;       //找不到，返回false
}

//跳转到注册页面
void Login::switchToRegister()
{
    this->hide();
    m_register->show();
}

//跳转到登录页面
void Login::switchToLogin()
{
    this->show();
    m_register->close();
}

//检测当前是否处于登录状态
void Login::checkIsOnline()
{
    //未登录状态
    if(m_player->getUserName()=="tourist")
    {
        QMessageBox::critical(nullptr,"错误","你没有登录过任何账号");
        return;
    }
    else    //否则，对文件数据进行更新
    {
        QFile accountData("AccountData.bin");
        QDataStream inFromFile(&accountData);
        if(!accountData.open(QIODevice::ReadOnly))
        {
            qCritical() << "无法打开文件进行读取 accountData isExit";
            return;
        }

        //打开文件后：
        bool isFind=false;                              //是否找到要修改的对象数据
        qint64 beforeSize=0;                            //在此对象之前的所有数据的字节大小
        qint64 endSize=0;                               //在包括文件头开始，到此对象数据结束的所有数据的字节大小
        Player temp;
        while(!inFromFile.atEnd())
        {
            qDebug()<<"error checkIsOnline login";

            inFromFile>>temp;
            if(temp.getUserName()==m_player->getUserName() && temp.getPwd()==m_player->getPwd())
            {
                endSize=accountData.pos();              //获取endsize的大小
                isFind=true;
            }
            else if(!isFind)
            {
                beforeSize=accountData.pos();           //获取beforesize的大小
            }
        }
        accountData.close();

        QFile targetFile("AccountData.bin");
        QByteArray beforeData;
        QByteArray afterData;
        QDataStream readFromFile(&targetFile);

        if(targetFile.open(QIODevice::ReadOnly))
        {
            beforeData=targetFile.read(beforeSize);                     //读取修改对象前面的数据
            targetFile.seek(endSize);                                   //定位到该对象后面，开始读取后续的对象到afterdata这个二进制数组
            //应该还有一种方法，用文件总大小减去endSize，然后读取这么长就行,
            //它是不是结构化的Player不重要，反序列的时候肯定能读出来的
            Player temp;
            while(!targetFile.atEnd())                                  //完成修改前后的预备操作
            {
                QDataStream toByteArray(&afterData,QIODevice::WriteOnly|QIODevice::Append);
                readFromFile>>temp;
                toByteArray<<temp;
            }
        }
        else
        {
            qDebug()<<"错误，无法打开用户信息文件，进行读取:  check is online";
        }

        //将修改后的玩家二进制化到数组里
        QByteArray revisedData;
        QDataStream revisedStream(&revisedData,QIODevice::WriteOnly);
        revisedStream<<*m_player;

        //开始合并数据
        QByteArray updatedData;
        updatedData=beforeData+revisedData+afterData;

        targetFile.close();                                             //关闭一下文件，怕出什么问题
        if(targetFile.open(QIODevice::WriteOnly))
        {
            targetFile.write(updatedData);                              //直接用write函数代替上面两行
            targetFile.close();                                         //关闭文件
        }
        else
        {
            qDebug()<<"错误，无法打开用户信息文件，进行修改：check is Online";
        }

        m_player->original();                                           //用户页面的数据也进行了更新
        QMessageBox::information(nullptr,"成功","退出登录成功");
    }
}

Login::~Login()
{
    if(m_register!=nullptr)
    {
        delete m_register;
        m_register=nullptr;
    }
    // if(m_player!=nullptr)
    // {
    //     delete m_player;
    //     m_player=nullptr;
    // }
    delete ui;
}

