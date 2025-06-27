#include "Register.h"
#include "ui_Register.h"
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include "Player.h"
Register::Register(QWidget *parent,Player *onlinePlayer)
    : QWidget(parent)
    , ui(new Ui::Register),m_player(onlinePlayer)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    //设置TiTle和Icon
    setWindowTitle("Register");
    QIcon icon(":/icons/resource/icons/注册.png");
    setWindowIcon(icon);

    //设置页面的ui
    ui->setupUi(this);
    ui->name->setStyleSheet("color: black; font-size: 14px;");
    ui->password->setStyleSheet("color: black; font-size: 14px;");
    ui->ensurePassword->setStyleSheet("color: black; font-size: 14px;");

    QPixmap *picture = new QPixmap(":/images/resource/picture/微信图片_20231107235839.jpg");
    QSize size=ui->label_image->size();
    ui->label_image->setPixmap(picture->scaled(size));
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#88888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);

    //固定大小为780,520
    this->setFixedSize(780,520);
    connect(ui->backToLogin,&QPushButton::clicked,this,&Register::onBackLogin);
    connect(ui->sure,&QPushButton::clicked,this,&Register::testRegister);           //开始检测输入是否合法
}

void Register::testRegister()
{
    QString inputName;      //输入的名
    QString inputPwd;       //输入的密码
    int userID=-1;
    if(ui->name->text()=="")        //如果输入的用户名为空，提示用户重新输入
    {
        QMessageBox::critical(nullptr,"错误","用户名为空，请重新输入用户名");
        ui->name->clear();
        ui->password->clear();
        ui->name->setFocus();
    }
    else if(ui->password->text()=="")   //如果输入的密码为空，提示用户重新输入
    {
        QMessageBox::critical(nullptr,"错误","密码为空，请重新输入密码");
        ui->name->clear();
        ui->password->clear();
        ui->password->setFocus();
    }
    else if(ui->ensurePassword->text()=="")     //如果确认密码为空，提示用户重新输入
    {
        QMessageBox::critical(nullptr,"错误","确认密码为空，请重新输入确认密码");
        ui->ensurePlayerPassword->setFocus();
    }
    else if(ui->ensurePassword->text()!=ui->password->text())   //如果输入的确认密码和密码不同，提示用户重新输入
    {
        QMessageBox::critical(nullptr,"错误","输入密码与确认密码不同，请重新输入");
        ui->password->clear();
        ui->ensurePlayerPassword->clear();
        ui->password->setFocus();
    }
    else    //否则开始在文件中查找
    {
        inputName=ui->name->text();
        inputPwd=ui->password->text();
        bool state=isExit(inputName,inputPwd);      //获取在文件中是否查找到的状态
        if(!state)      //不存在，说明创建成功
        {
            addPlayer();    //添加到文件中
            QMessageBox::information(nullptr,"成功","注册成功");
        }
        else            //存在，说明创建不成功，提示用户重新创建
        {
            QMessageBox::critical(nullptr,"错误","该用户名已经存在，请重新输入");
            ui->name->clear();
            ui->password->clear();
            ui->ensurePassword->clear();
            ui->name->setFocus();
        }
    }

}

bool Register::isExit(const QString &inputName,const QString &inputPwd)
{
    QFile playerData("AccountData.bin");
    QDataStream in(&playerData);
    if(!playerData.open(QIODevice::ReadOnly))
    {
        qCritical() << "无法打开文件进行读取 accountData isExit";
        return false;
    }
    Player temp;
    while(!in.atEnd())
    {
        in>>temp;
        //如果找到，则返回true
        if(temp.getUserName()==ui->name->text() && temp.getPwd()==ui->password->text())
        {
            playerData.close();
            return true;
        }
    }
    playerData.close();
    return false;   //否则返回false
}

void Register::addPlayer()
{
    QString inputName;
    QString inputPwd;
    inputName=ui->name->text();                 //获取输入的名
    inputPwd=ui->ensurePassword->text();        //获取输入的密码

    //写入文件中
    QFile accountData("AccountData.bin");
    QDataStream out(&accountData);
    if (!accountData.open(QIODevice::Append)) {
        qCritical() << "无法打开文件进行写入";
        return;
    }
    Player temp;
    temp.totIDadd();
    temp.setID(temp.getTotID()),temp.setUserName(inputName),temp.setPwd(inputPwd);
    out.setVersion(QDataStream::Qt_6_0);
    out<<temp;
    accountData.close();
}

void Register::onBackLogin()
{
    emit backToLogin();
}

Register::~Register()
{
    delete ui;
}
