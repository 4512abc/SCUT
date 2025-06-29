#include "accountwidget.h"
#include "config.h"
#include "player.h"
#include "myController.h"

accountWidget::accountWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //头像
    ImageLabel = new QLabel(this);
    QPixmap pixmap(":/res/background.png");
    ImageLabel->setFixedSize(200,200);
    ImageLabel->setPixmap(pixmap);
    ImageLabel->setScaledContents(true);
    // 账号输入框
    account = new QLabel(this);
    account->setPixmap(QPixmap(QString(":/res/account.png")));
    account->setFixedSize(80,80);
    accountInput = new QLineEdit(this);
    accountInput->setPlaceholderText(QStringLiteral("请输入账号"));
    accountInput->setFixedSize(400,40);
    accountInput->setStyleSheet(R"(
        QLineEdit#accountInput {
            border: 2px solid #4CAF50;
            border-radius: 10px;
            background-color: white;
            padding: 5px;
            font-size: 14px;
            color: #333;
        }
        QLineEdit#accountInput:hover {
            border-color: #007bff;
        }
    )");

    // 密码输入框以及隐藏与显示密码
    passWord = new QLabel(this);
    passWord->setPixmap(QPixmap(QString(":/res/passwordLabel.png")));
    passWord->setFixedSize(80,80);

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText(QStringLiteral("请输入密码"));
    passwordInput->setFixedSize(400,40);
    passwordInput->setEchoMode(QLineEdit::Password);//隐藏密码
    showPasswordCheckBox = new QCheckBox(this);
    showPasswordCheckBox->setChecked(false);
    showPasswordCheckBox->setIcon(QIcon(":/res/showPasswordBtn.png"));
    showPasswordCheckBox->setIconSize(QSize(100,80));
    showPasswordCheckBox->setFixedSize(100,100);
        //连接复选框的状态变化信号到槽函数
    connect(showPasswordCheckBox,&QCheckBox::stateChanged,[=](){
        if(showPasswordCheckBox->checkState())
            passwordInput->setEchoMode(QLineEdit::Normal);
        else
            passwordInput->setEchoMode(QLineEdit::Password);
    });


    // 注册按钮
    registerButton = new QPushButton(this);
    registerButton->setIcon(QIcon(":/res/register.png"));
    registerButton->setFlat(true);
    registerButton->setFixedSize(120,120);
    registerButton->setIconSize(QSize(120,120));
    connect(registerButton, &QPushButton::clicked, this, &accountWidget::registerBtnClicked);
    //找回密码按钮
    findPasswordBtn = new QPushButton(this);
    findPasswordBtn->setIcon(QIcon(":/res/findPasswordBtn.png"));
    findPasswordBtn->setFlat(true);
    findPasswordBtn->setFixedSize(120,100);
    findPasswordBtn->setIconSize(QSize(250,100));
    connect(findPasswordBtn,&QPushButton::clicked,[=](){
        FindPasswordWidget *findpasswordWidget = new FindPasswordWidget();
    });
    //此时采用输入账号，自动找回的方式，写了Account类之后直接在文件中读取。不存在该账户弹出提示框


    // 登录按钮
    loginButton = new QPushButton(this);
    loginButton->setIcon(QIcon(":/res/Login.png"));
    loginButton->setIconSize(QSize(250,100));
    loginButton->setFixedSize(120,100);
    loginButton->setFlat(true);
    connect(loginButton, &QPushButton::clicked, this, &accountWidget::onLoginButtonClicked);
    //以游客模式开始游戏
    NoAccountBtn = new QPushButton(this);
    NoAccountBtn->setIcon(QIcon(":/res/VisitorBtn.png"));
    NoAccountBtn->setIconSize(QSize(250,125));
    NoAccountBtn->setFixedSize(280,125);
    NoAccountBtn->setFlat(true);
    connect(NoAccountBtn,&QPushButton::clicked,this,&accountWidget::onGuestModeContinueClicked);
    //返回按钮
    returnButton = new QPushButton(this);
    returnButton->setIcon(QIcon(":/res/returnBtn.png"));
    returnButton->setIconSize(QSize(100,200));
    returnButton->setFixedSize(100,200);
    returnButton->setFlat(true);
    connect(returnButton,&QPushButton::clicked,this,&accountWidget::returnToMainPage);
    // 布局管理
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ImageLabel,0,0,3,1);
    mainLayout->addWidget(account,0,1,1,1);
    mainLayout->addWidget(accountInput,0,2,1,2);
    mainLayout->addWidget(registerButton,0,4,1,1);
    mainLayout->addWidget(passWord,1,1,1,1);
    mainLayout->addWidget(passwordInput,1,2,1,2);
    mainLayout->addWidget(showPasswordCheckBox,1,4,1,1);
    mainLayout->addWidget(loginButton,3,1,1,2);
    mainLayout->addWidget(findPasswordBtn,3,3,1,2);
    mainLayout->addWidget(NoAccountBtn,7,2,2,4);
    mainLayout->setContentsMargins(90, 100, 80, 50);

    setLayout(mainLayout);

}

void accountWidget::onLoginButtonClicked()
{
    {
        Player player;
        // 实现登录验证逻辑，比如检查用户名和密码
        bool loginSuccessful = false;
        int index = -1;//序列号
        QString qusername = accountInput->text();
        QString qpassword = passwordInput->text();//Qstring出了问题,没有用导致的吗？在下面用了还是报错.原来是在cpp中多声明了

        //验证账号密码的机制
        QFile file(ACCOUNTLISTROAD);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_5); // 使用你的Qt版本
            bool hasAccount = false;
            // 从文件中读取testPlayer对象
            while(!in.atEnd()){
                Player testPlayer;
                in >> testPlayer;
                if(testPlayer.getAccount() == qusername)
                {
                    hasAccount = true;
                    if(testPlayer.getPassword() == qpassword){
                        loginSuccessful = true;
                        index ++;
                        player = testPlayer;
                        break;
                    }
                    else{
                        QMessageBox::critical(this, tr("登录失败"), tr("密码错误，请重试。"));
                        break;
                    }
                }
                index ++;
            }
            if(!hasAccount)
                QMessageBox::critical(this, tr("登录失败"), tr("不存在该账号，请重试。"));
        }

        if (loginSuccessful)
        {
            // 登录成功，弹出消息框，由于从文件中只读取开始位置、账号、密码、宿舍号、电话号，还要设置其他的
            *onLoginPlayer = player;

            QMessageBox::information(this, tr("登录成功"), tr("欢迎回来！您的登录已成功。"));
            // 完成游戏记录匹配
            // 匹配索引号，通过索引号读取各文件信息
            onLoginPlayer->getPracticeRecord().setIndex(onLoginPlayer->getIndex());
            onLoginPlayer->getCompetitionRecord().setIndex(onLoginPlayer->getIndex());
            onLoginPlayer->getEndlessPracticeRecord().setIndex(onLoginPlayer->getIndex());
            onLoginPlayer->getEndlessCompetitonRecord().setIndex(onLoginPlayer->getIndex());
            //
            // 匹配游戏记录、数据，模块化一下
            onLoginPlayer->getPracticeRecord().matchRecord(PRACTICE_RECORD_PATH);
            onLoginPlayer->getCompetitionRecord().matchRecord(COMPETITION_RECORD_PATH);
            onLoginPlayer->getEndlessPracticeRecord().matchRecord(ENDLESSPRACTICE_RECORD_PATH);
            onLoginPlayer->getEndlessCompetitonRecord().matchRecord(ENDLESSCOMPETITION_RECORD_PATH);
            // //修改全局的onloginplayer
            // *onLoginPlayer = player;
            qDebug() << onLoginPlayer->getAccount();
            qDebug() << onLoginPlayer->getIndex();


            //清空一下输入框，便于重新登录
            accountInput->clear();
            passwordInput->clear();
            emit StartPlayWithAccount();
        }

    }
}

//游客模式开始游戏
void accountWidget::onGuestModeContinueClicked()
{
    QMessageBox messageBox;
    messageBox.setText("以游客模式游玩将不保存游戏记录");
    messageBox.setInformativeText("您确定要继续吗？");
    messageBox.setIcon(QMessageBox::Information);

    // 添加自定义按钮并设置默认按钮
    QPushButton *okButton = messageBox.addButton(QString("确定，开始游戏"), QMessageBox::ActionRole);
    QPushButton *loginButton = messageBox.addButton(QString("登录账号"), QMessageBox::ActionRole);
    messageBox.setDefaultButton(okButton);

    // 连接确认继续的按钮的clicked信号到槽函数
    connect(okButton, &QPushButton::clicked, this, &accountWidget::onGuestModeConfirmed);

    // 显示对话框
    messageBox.exec();
}

void accountWidget::onGuestModeConfirmed()
{
    emit StartPlay();
}
void accountWidget::registerBtnClicked(){
    RegisterWidget *registerwidget = new RegisterWidget();
}
//注册窗口类
RegisterWidget::RegisterWidget(QWidget *parent)
    :QWidget(parent)
{

    this->setWindowTitle(QString("注册账号"));
    this->setFixedSize(600,400);
    //设置按钮和文本框
    welcome = new QLabel(QString("欢迎来到Dionysus开发的植此青绿游戏"),this);
    poem = new QLabel(QString("表里俱澄澈"),this);
    poem2 = new QLabel(QString("肝肺皆冰雪"),this);

    introduction2 = new QLabel("账号12位以内、密码6-18位任意字符,不允许空格");
    account = new QLabel(QString("注册账号："),this);
    password = new QLabel(QString("输入密码："),this);
    confirmPassword = new QLabel(QString("确认密码"),this);
    AccountInput = new QLineEdit(this);
    AccountInput->setPlaceholderText(QStringLiteral("请输入账号"));
    PasswordInput = new QLineEdit(this);
    PasswordInput->setEchoMode(QLineEdit::Password);//隐藏密码
    confirmPasswordInput = new QLineEdit(this);
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->setFixedWidth(220);
    AccountInput->setFixedWidth(220);
    PasswordInput->setFixedWidth(220);

    showpasswordCheckBox = new QCheckBox(QString("显示密码"),this);
    showpasswordCheckBox->setChecked(false);
    showConfirmPassWordCheckBox = new QCheckBox(QString("显示密码"),this);
    showConfirmPassWordCheckBox->setChecked(false);
        //连接复选框的状态变化信号到槽函数
    connect(showpasswordCheckBox,&QCheckBox::stateChanged,[=](){
        if(showpasswordCheckBox->checkState())
            PasswordInput->setEchoMode(QLineEdit::Normal);
        else
            PasswordInput->setEchoMode(QLineEdit::Password);
    });
    connect(showConfirmPassWordCheckBox,&QCheckBox::stateChanged,[=](){
        if(showConfirmPassWordCheckBox->checkState())
            confirmPasswordInput->setEchoMode(QLineEdit::Normal);
        else
            confirmPasswordInput->setEchoMode(QLineEdit::Password);
    });
    PasswordInput->setPlaceholderText(QString("请输入密码"));
    confirmPasswordInput->setPlaceholderText("请再次输入密码");

    //利用样式表为按钮设置颜色
    registerBtn = new QPushButton(QString("下一步"),this);
    registerBtn->setStyleSheet("QPushButton {background-color: #00FF00; color: #000000}");

    //添加到布局中
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(welcome,0,0,1,3);
    mainLayout->addWidget(poem,0,3,2,2);
    mainLayout->addWidget(introduction2,1,0,1,3);
    mainLayout->addWidget(poem2,1,3,2,2);
    mainLayout->addWidget(account,2,0,1,1);
    mainLayout->addWidget(AccountInput,2,1,1,2);
    mainLayout->addWidget(password,3,0,1,1);
    mainLayout->addWidget(PasswordInput,3,1,1,2);
    mainLayout->addWidget(showpasswordCheckBox,3,3,1,1);
    mainLayout->addWidget(confirmPassword,4,0,1,1);
    mainLayout->addWidget(confirmPasswordInput,4,1,1,2);
    mainLayout->addWidget(showConfirmPassWordCheckBox,4,3,1,1);
    mainLayout->setSpacing(50);
    mainLayout->addWidget(registerBtn,5,0,1,5);

    this->setLayout(mainLayout);
    this->show();

    connect(registerBtn, &QPushButton::clicked,this,&RegisterWidget::registerAccount);


}

void RegisterWidget::registerAccount()
{
    QString account = AccountInput->text();
    QString password = PasswordInput->text();
    QString confirmPassword = confirmPasswordInput->text();
    bool registerSuccess = this->registerAccountLogic(account,password);

    if (password != confirmPassword) {
        QMessageBox::warning(nullptr, tr("错误"), tr("两次输入的密码不一致，请重新输入！"));
        registerSuccess = false;

    }
    if(registerSuccess)
    {
        //设置密保问题

        //移除当前布局
        mainLayout->removeWidget(AccountInput);
        AccountInput->hide();
        mainLayout->removeWidget(PasswordInput);
        PasswordInput->hide();
        mainLayout->removeWidget(registerBtn);
        registerBtn->hide();
        mainLayout->removeWidget(this->confirmPassword);
        this->confirmPassword->hide();
        mainLayout->removeWidget(confirmPasswordInput);
        confirmPasswordInput->hide();
        mainLayout->removeWidget(showConfirmPassWordCheckBox);
        showConfirmPassWordCheckBox->hide();
        mainLayout->removeWidget(showpasswordCheckBox);
        showpasswordCheckBox->hide();


        dormitoryInput = new QLineEdit(this);
        dormitoryInput->setPlaceholderText("请输入您的寝室号");
        phoneNumberInput = new QLineEdit(this);
        phoneNumberInput->setPlaceholderText("请输入您的电话号码");
        setProtectQuestionBtn = new QPushButton("设置密保问题",this);
        setProtectQuestionBtn->setFixedSize(250,40);
        skipBtn = new QPushButton("跳过，立即注册",this);
        skipBtn->setFixedSize(250,40);

        this->account->setText("寝室号");
        this->password->setText("电话号码");
        mainLayout->addWidget(dormitoryInput,2,1,1,3);
        mainLayout->addWidget(phoneNumberInput,3,1,1,3);
        mainLayout->addWidget(setProtectQuestionBtn,4,0,1,2);
        mainLayout->addWidget(skipBtn,4,2,1,2);

        this->setLayout(mainLayout);

        connect(setProtectQuestionBtn,&QPushButton::clicked,[=](){
            registerplayer.setDormitoryNumber(dormitoryInput->text());
            registerplayer.setPhoneNumber(phoneNumberInput->text());
            writeToFile();
            QMessageBox::information(nullptr, "注册成功", "恭喜您，注册成功！");
            this->close();
        });

        connect(skipBtn,&QPushButton::clicked,[=](){
            QMessageBox messageBox;
            messageBox.setText("不设置密保可能导致后续无法找回密码");
            messageBox.setInformativeText("您确定要跳过吗？");
            messageBox.setIcon(QMessageBox::Information);

            // 添加自定义按钮并设置默认按钮
            QPushButton *okButton = messageBox.addButton(QString("跳过，直接注册"), QMessageBox::ActionRole);
            QPushButton *loginButton = messageBox.addButton(QString("设置密保"), QMessageBox::ActionRole);
            messageBox.setDefaultButton(okButton);

            // 确定就跳转到登录页面，这个页面直接关闭就行
            connect(okButton, &QPushButton::clicked, [=](){
                this->writeToFile();
                QMessageBox::information(nullptr, "注册成功", "恭喜您，注册成功！");
                this->close();
            });
            messageBox.exec();
        });

    }
    else{
        // 注册失败，可以弹出错误信息
        QMessageBox::critical(this, tr("注册失败"), tr("用户名或密码不符合规范，请重试。"));
    }
}

    //注册账号实现的逻辑，只涉及账号密码，还没有游戏游玩信息，传入两个string判断即可
bool RegisterWidget::registerAccountLogic(QString acInput, QString pwInput)
{
    //判断输入的账号密码是否符合要求，符合要求再开始判断
    if(registerplayer.setAccount(acInput) && registerplayer.setPassword(pwInput))
    {
        //读取文件，找到序列号
        Player testPlayer;
        int index = 0;//序列号

        QFile file(ACCOUNTLISTROAD);
        file.open(QIODevice::ReadOnly);

        if(file.isOpen()){
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_5); // 使用你的Qt版本

            // 顺序读取player，递增序列号
            while(!in.atEnd()){
                in >> testPlayer;
                index ++;
            }
            registerplayer.setStartPos(file.pos());
            file.close();
        }
        //设置序列号
        registerplayer.setIndex(index);
        //特殊情况，文件未创建的时候，设置会报成：277920842048
        if(registerplayer.getIndex() == 0){
            registerplayer.setStartPos(0);
        }
        return true;
    }
    else{
        return false;
    }
    //看看能不能上传头像
}


FindPasswordWidget::FindPasswordWidget(QWidget *parent)
    :QWidget(parent)
{

    this->setWindowTitle(QString("找回密码"));
    this->setFixedSize(500,300);
    //设置按钮和文本框

    account = new QLabel(QString("账号："),this);

    AccountInput = new QLineEdit(this);
    AccountInput->setPlaceholderText(QStringLiteral("请输入账号"));

    //利用样式表为按钮设置颜色
    continueBtn = new QPushButton(QString("继续"),this);
    continueBtn->setStyleSheet("QPushButton {background-color: #00FF00; color: #000000}");

    //添加到布局中
    mainLayout = new QGridLayout(this);

    mainLayout->addWidget(account,1,0,1,1);
    mainLayout->addWidget(AccountInput,1,1,1,2);
    mainLayout->setSpacing(50);
    mainLayout->addWidget(continueBtn,4,0,1,3);

    connect(continueBtn, &QPushButton::clicked,this,&FindPasswordWidget::continueBtnClicked);

    this->setLayout(mainLayout);
    this->show();

}

void FindPasswordWidget::modifyPassword(const QString &newPassword)
{
    Player testPlayer;
    if(testPlayer.setPassword(newPassword)){
        //如果新密码符合条件，那么修改数据
        //获取新玩家的数据的二进制表示

        QByteArray newdata;
        //创建qdatastream，写入模式，对象为newdata
        QDataStream out(&newdata, QIODevice::WriteOnly);
        findpasswordPlayer.setPassword(newPassword);
        out << findpasswordPlayer;
        qDebug() << newdata.size();
        //获取该用户数据在文件中的偏移量，在注册的时候赋了起始位置StartPos，现在要读末尾位置
        qint64 endPos;
        QFile readFile(ACCOUNTLISTROAD);
        if(readFile.open(QIODevice::ReadOnly)){
            QDataStream in(&readFile);
            while(!readFile.atEnd()){
                in >> testPlayer;
                if(testPlayer.getAccount() == findpasswordPlayer.getAccount()){
                    endPos = readFile.pos();
                }
            }
            readFile.close();
        }

        //已经得到该对象在原文件的始末位置，开始修改
        //打开文件
        QFile file(ACCOUNTLISTROAD);
        //判断是否正常打开
        if(!file.open(QIODevice::ReadOnly)){
            qDebug() << "Failed to open the file for reading.";
            return;
        }
        //开始读取内容
        QByteArray originalData = file.readAll();

        file.close();//关闭文件

        //在指定位置修改数据
        QByteArray updatedData;
        updatedData.reserve(originalData.size() + newdata.size());//完成预分配空间
        updatedData.append(originalData.mid(0,findpasswordPlayer.getStartPos()));//插入前面的数据
        updatedData.append(newdata);//插入修改新数据
        updatedData.append(originalData.mid(endPos) );

        //重新打开文件写入，完成密码修改
        if(file.open(QIODevice::WriteOnly)){
            file.write(updatedData);
            file.close();
        }
        else {
            qDebug() << "打开文件失败";
            return;
        }
    }
}

void FindPasswordWidget::continueBtnClicked()
{
    QString qusername = AccountInput->text();
    //验证是否存在该账号
    QFile file(ACCOUNTLISTROAD);
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_5); // 使用你的Qt版本
        hasAccount = false;
        // 从文件中读取testPlayer对象
        while(!in.atEnd()){
            in >> findpasswordPlayer;//全局的成员
            if(findpasswordPlayer.getAccount() == qusername){
                hasAccount = true;
                break;
                }
            }
        if(!hasAccount)
            QMessageBox::critical(this, tr("错误"), tr("不存在该账号，请重试。"));
        else toProtectQuesetion();
    }
}

void FindPasswordWidget::toProtectQuesetion()
{
    // 移除现有布局
    mainLayout->removeWidget(account);
    account->hide();
    mainLayout->removeWidget(AccountInput);
    AccountInput->hide();
    mainLayout->removeWidget(continueBtn);
    continueBtn->hide();

    QLabel *protectQuestion = new QLabel("密保问题",this);
    QLineEdit *protectQuestionInput = new QLineEdit(this);
    protectQuestionInput->setPlaceholderText("请输入您的寝室号或者手机号");
    QPushButton *verifyQuestionBtn = new QPushButton("立即验证",this);

    mainLayout->addWidget(protectQuestion,1,0,1,1);
    mainLayout->addWidget(protectQuestionInput,1,1,1,3);
    mainLayout->addWidget(verifyQuestionBtn,4,2,1,2);


    this->setLayout(mainLayout);

    connect(verifyQuestionBtn,&QPushButton::clicked,[=](){
        QString a = protectQuestionInput->text();
        verifyQuestion(a);
    });

}

void FindPasswordWidget::verifyQuestion(QString input)
{
    if(input == findpasswordPlayer.getPhoneNumber() ||
        input == findpasswordPlayer.getDormitoryNumber())
    {//验证成功
        this->hide();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("恭喜您找回密码: "+ findpasswordPlayer.getPassword());
        msgBox.addButton("返回登录页面", QMessageBox::AcceptRole);
        msgBox.addButton("修改密码", QMessageBox::RejectRole);
        int buttonIndex = msgBox.exec(); // 获取用户点击的按钮索引

        QMessageBox::StandardButton result = QMessageBox::StandardButton(buttonIndex); // 转换为枚举值
        if (result == QMessageBox::AcceptRole) {
            // 用户点击了"返回登录页面"，点击之后直接返回
        }
        else if (result == QMessageBox::RejectRole) {
            // 用户点击了"修改密码"
            //开一个新窗口，设置一下布局，命名添个1防止与findPassword页面的重复
            QWidget *revisePasswordWidget = new QWidget();
            QLabel *password1 = new QLabel(QString("输入密码："),revisePasswordWidget);
            QLabel *confirmPassword1 = new QLabel(QString("确认密码"),revisePasswordWidget);
            QLineEdit *PasswordInput1 = new QLineEdit(revisePasswordWidget);
            PasswordInput1->setEchoMode(QLineEdit::Password);//隐藏密码
            QLineEdit *confirmPasswordInput1 = new QLineEdit(revisePasswordWidget);
            confirmPasswordInput1->setEchoMode(QLineEdit::Password);
            confirmPasswordInput1->setFixedWidth(220);
            PasswordInput1->setFixedWidth(220);
            PasswordInput1->setPlaceholderText(QString("请输入新密码"));
            confirmPasswordInput1->setPlaceholderText("请再次输入新密码");

            QPushButton *confirmBtn = new QPushButton("确认修改",revisePasswordWidget);

            QGridLayout *reviseLayout = new QGridLayout(revisePasswordWidget);
            reviseLayout->addWidget(password1,0,0,1,1);
            reviseLayout->addWidget(PasswordInput1,0,1,1,2);
            reviseLayout->addWidget(confirmPassword1,1,0,1,1);
            reviseLayout->addWidget(confirmPasswordInput1,1,1,1,2);
            reviseLayout->addWidget(confirmBtn,2,1,1,1);

            revisePasswordWidget->show();
            connect(confirmBtn,&QPushButton::clicked,[=](){
                if(PasswordInput1->text() == confirmPasswordInput1->text()){
                    modifyPassword(PasswordInput1->text());
                    revisePasswordWidget->close();
                }
                else QMessageBox::warning(nullptr, "修改失败", "两次密码输入不一致");
            });
        }
    }
    else{
        this->hide();
        errorProtectQuestionDialog *select = new errorProtectQuestionDialog(nullptr);
        select->show();
        connect(select,&errorProtectQuestionDialog::showFindPassWordWidget,[=](){
            FindPasswordWidget *find = new FindPasswordWidget(nullptr);
        });
    }
}

void RegisterWidget::writeToFile(){
    //写入文件
    QFile file(ACCOUNTLISTROAD);
    if(file.open(QIODevice::WriteOnly|QIODevice::Append)){
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_6_5);//使用当前qt版本
        //将对象写入文件
        out << registerplayer;
        file.close();
    }
    else{
        qDebug() << "文件打开失败";
    }
}
