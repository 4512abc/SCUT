#include "gamescene.h"
#include "config.h"
#include <QSize>
#include <QMargins>
#include "accountwidget.h"
#include "DragAndDrop.h"
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
    this->titleLable = new QLabel(this);
    titleLable->setPixmap(QString(":/res/title.png"));
    //添加按钮
    this->practiceBtn = new QPushButton(this);//初始化
    this->practiceBtn->setIcon(QIcon(":/res/practiceBtn.png"));//设置图标
    this->practiceBtn->setFlat(true);//去掉白边
    this->practiceBtn->setFocusPolicy(Qt::NoFocus);//不聚焦，鼠标停留的时候不会出现框
    practiceBtn->setFixedSize(260,260);
    practiceBtn->setIconSize(QSize(260,260));

    this->competitionBtn = new QPushButton(this);
    this->competitionBtn->setIcon(QIcon(":/res/competitionBtn.png"));
    this->competitionBtn->setFlat(true);
    competitionBtn->setFixedSize(260,260);
    this->competitionBtn->setIconSize(QSize(260,260));
    this->competitionBtn->setFocusPolicy(Qt::NoFocus);

    this->endlessBtn = new QPushButton(this);
    endlessBtn->setFlat(true);
    endlessBtn->setIcon(QIcon(":/res/endlessBtn.png"));
    endlessBtn->setIconSize(QSize(175,185));
    endlessBtn->setFixedSize(175,175);
    endlessBtn->setContentsMargins(30,0,0,0);
    connect(endlessBtn,&QPushButton::clicked,[=](){
        emit ToEndless();
    });


    this->GradesRankBtn = new QPushButton(this);
    this->GradesRankBtn->setIcon(QIcon(":/res/rank.png"));
    this->GradesRankBtn->setFlat(true);
    this->GradesRankBtn->setIconSize(QSize(500,70));
    GradesRankBtn->setFixedSize(500,70);
    this->GradesRankBtn->setFocusPolicy(Qt::NoFocus);
    connect(GradesRankBtn,&QPushButton::clicked,this,&gameWidget::ToRankWidget);

    this->LogOutBtn = new QPushButton(this);
    this->LogOutBtn->setIcon(QIcon(":/res/logoutBtn.png"));
    this->LogOutBtn->setFlat(true);
    this->LogOutBtn->setIconSize(QSize(160,50));
    this->LogOutBtn->setFocusPolicy(Qt::NoFocus);
    connect(LogOutBtn,&QPushButton::clicked,[=](){
        this->onLoginPlayer->reInitialize();
        emit returnToMainPage();
    });

    poem1 = new QLabel(this);
    poem1->setPixmap(QString(":/res/poem1.png"));
    poem1->setContentsMargins(60,0,0,0);
    poem2 = new QLabel(this);
    poem2->setPixmap(QString(":/res/poem2.png"));


    player_definedBtn = new QPushButton(this);
    player_definedBtn->setIcon(QIcon(":/res/player_defineBtn.png"));
    player_definedBtn->setFixedSize(200,200);
    player_definedBtn->setIconSize(QSize(200,200));
    player_definedBtn->setFlat(true);
    connect(player_definedBtn, &QPushButton::clicked,[=](){
        emit ToCustom();
    });

    //返回主页面按钮
    returnButton = new QPushButton(this);
    returnButton->setFlat(true);
    returnButton->setIcon(QIcon(":/res/returnBtn.png"));
    returnButton->setIconSize(QSize(80,150));
    returnButton->setFixedSize(80,150);

    connect(returnButton,&QPushButton::clicked,this,&gameWidget::returnToMainPage);

    //QLabel *put = new QLabel(this);
    this->mainLayout = new QGridLayout(this);
    mainLayout->addWidget(returnButton,0,0,1,1);
    mainLayout->addWidget(titleLable,0,3,2,3);
    mainLayout->addWidget(poem1,3,0,6,2);
    mainLayout->addWidget(practiceBtn,3,2,2,2);
    mainLayout->addWidget(competitionBtn,3,5,2,2);
    mainLayout->addWidget(poem2,3,7,6,2);
    mainLayout->addWidget(endlessBtn,6,3,2,2);
    mainLayout->addWidget(player_definedBtn,6,5,2,2);
    mainLayout->addWidget(GradesRankBtn,9,3,1,3);
    mainLayout->addWidget(LogOutBtn,10,2,1,5);
    //mainLayout->addWidget(put,11,2,1,5);
    mainLayout->setContentsMargins(0, 0, 0, 50);
    GradesRankBtn->raise();
    LogOutBtn->raise();
    this->setLayout(mainLayout);


    //进入到游戏页面、排行榜页面、以及退出登录的实现
    connect(practiceBtn,&QPushButton::clicked,[=](){
        emit ToPractice();
    });
    connect(competitionBtn,&QPushButton::clicked,[=](){
        emit ToCompetition();

    });
    connect(LogOutBtn,&QPushButton::clicked,this,&gameWidget::loginOutSignal);

}





//playWidget
playWidget::playWidget(QWidget *parent)//写一下playwidget的布局
    : QWidget(parent)
{
    for (int i = 0; i < 7; ++i) {
        SliceToPut[i] = nullptr;
    }
    for (int i = 0; i < 36; i++){
        targetSlice[i] = nullptr;
    }
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


    Custom = new QPushButton(this);
    Custom->hide();
    //控件
    returnGameSceneBtn = new QPushButton(this);
    returnGameSceneBtn->setFlat(true);
    returnGameSceneBtn->setIcon(QIcon(":/res/returnBtn.png"));
    returnGameSceneBtn->setFixedSize(100,180);
    returnGameSceneBtn->setIconSize(QSize(100,180));
    connect(returnGameSceneBtn,&QPushButton::clicked,this,&playWidget::returnToGameScene);
    connect(returnGameSceneBtn,&QPushButton::clicked,[=](){
        startBtn->show();
        Custom->hide();
    });
    helpBtn = new QPushButton(this);
    helpBtn->setIcon(QIcon(":/res/mainpageHelp.png"));
    helpBtn->setFixedSize(100,50);
    helpBtn->setIconSize(QSize(100,50));
    helpBtn->setFlat(true);
    connect(helpBtn,&QPushButton::clicked,[=](){
        helpWidget *help = new helpWidget();
        help->hideBtn();
        help->show();
    });
    // player_definedMapBtn = new QPushButton(this);
    // player_definedMapBtn->setText("自定义地图");
    // player_definedMapBtn->setFixedSize(70,60);
    // connect(player_definedMapBtn, &QPushButton::clicked,[=](){
    //     customMode();
    // });

    timer = new QTimer(this);
    usedTime = new QLabel(this);

    withdrawBtn = new QPushButton(this);
    withdrawBtn->setIcon(QIcon(":/res/withdrawBtn.png"));
    withdrawBtn->setFixedSize(150,150);
    withdrawBtn->setIconSize(QSize(150,150));
    withdrawBtn->setFlat(true);

    connect(withdrawBtn,&QPushButton::clicked,this,&playWidget::withdraw);

    startBtn= new QPushButton(this);
    startBtn->setIcon(QIcon(":/res/startInGame.png"));
    startBtn->setFlat(true);
    startBtn->setIconSize(QSize(100,100));
    startBtn->setFixedSize(100,100);//这个按钮的信号槽需要复用一下，当gameWidget发送游玩的模式信号之后，给playwidget设置mode，每个mode连接不同的开始，当返回时断开连接
    connect(startBtn,&QPushButton::clicked,[=](){
        //再模块化一下
        cleanWidget();//避免delete空区域
        restart();
    });

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&playWidget::updateTime);//计时器实现

    introTime = new QLabel(this);//时间：
    introTime->setPixmap(QPixmap(":/res/TimeUsed.png"));
    introTime->setFixedSize(460,103);

    introTime->move(210,530);
    introTime->show();

    timeLable = new QLabel("00:00:00",this);//计时
    QFont font =timeLable->font();
    font.setPointSize(24);
    timeLable->setFont(font);

    tipsBtn = new QPushButton(this);
    tipsBtn->setFixedSize(100,100);
    tipsBtn->setIcon(QIcon(":/res/remindBtn.png"));
    tipsBtn->setIconSize(QSize(100,100));
    connect(tipsBtn, &QPushButton::clicked,[=](){
        if(this->onLoginPlayer->getPlayMap().HasAnswer()){
            QString tips = onLoginPlayer->getPlayMap().getTips(sliceToPut_Kind_Record, targetSlice_NumberInArray_Record,
                                                               sliceToPut_PosX_Record, sliceToPut_PosY_Record);
            QWidget *tipWidget = new QWidget(nullptr);
            QLabel *tipLabel = new QLabel(tipWidget);
            tipLabel->setText(tips);
            tipLabel->setStyleSheet("font-family: 'Arial'; font-size: 16pt;");
            tipLabel->move(50,250);

            QPushButton *confirmBtn = new QPushButton(tipWidget);
            confirmBtn->setFixedSize(200,109);
            confirmBtn->move(100,450);
            confirmBtn->setFlat(true);
            confirmBtn->setIcon(QIcon(":/res/confirm.png"));
            confirmBtn->setIconSize(QSize(200,109));
            connect(confirmBtn,&QPushButton::clicked,tipWidget,&QWidget::close);


            tipWidget->setStyleSheet("QWidget {background-image: url(:/res/提示框.png);background-repeat: no-repeat;background-position: center;}");
            tipWidget->setFixedSize(400,600);
            tipWidget->show();

        }
        else{
            if( ! onLoginPlayer->getPlayMap().HasAnswer()){
                MyDialog *dialog = new MyDialog(nullptr);
                dialog->show();
                map.convertMapToElement(playMode);
                int solveWays = this->onLoginPlayer->getPlayMap().solveWays();

                if(solveWays != 0)
                    onLoginPlayer->getPlayMap().setHasAnswer(true);
                dialog->updateLabelText(solveWays);
            }

        }
    });

    // exitGame = new QPushButton(this);
    // exitGame->setText("退出游戏");
    // exitGame->setFixedSize(70,60);

    hideTargetSlice = new QLabel(this);
    hideTargetSlice->setPixmap(QPixmap(HIDETARGETSLICE_PATH));
    hideTargetSlice->move(120,-60);
    hideTargetSlice->setFixedSize(480,660);


    // 创建QScrollArea
    scrollArea = new QScrollArea(this);
    scrollArea->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);//不允许滚动条自动扩充大小，当StartBtn隐藏时
    scrollArea->setFixedSize(SCROLLWIDGET_WIDTH + 20, SCROLLWIDGET_HEIGHT -300);//略宽显示好，略短能滚动
    // 创建容器Widget
    SliceToPutWidget = new QWidget;
    SliceToPutWidget->setFixedWidth(SCROLLWIDGET_WIDTH); // 设置宽度，可按需调整
    SliceToPutWidget->setFixedHeight(SCROLLWIDGET_HEIGHT);
    //创建布局
    sliceToputLayout = new QVBoxLayout(SliceToPutWidget); // 垂直布局

    // 设置布局并关联ScrollArea
    SliceToPutWidget->setLayout(sliceToputLayout);
    scrollArea->setWidget(SliceToPutWidget);

    targetSliceLayout = new QGridLayout();

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(returnGameSceneBtn,0,0,1,1);
    mainLayout->addWidget(startBtn,2,0,1,1);
    mainLayout->addWidget(tipsBtn,0,8,1,1);
    mainLayout->addWidget(scrollArea,0,7,7,1);
    mainLayout->addWidget(helpBtn,4,8,1,1);
    mainLayout->addLayout(targetSliceLayout,0,1,6,6);//占位
    mainLayout->addWidget(withdrawBtn,2,8,1,1);
    mainLayout->addWidget(timeLable,6,4,1,3);
    this->setLayout(mainLayout);


}


void playWidget::cleanWidget()
{
    //重置时间
    elapsedTime = 0;
    //删除可放置的切片
    for(int i = 0; i<7; i++){
        if(SliceToPut[i] != nullptr){
            delete SliceToPut[i];
            SliceToPut[i] = nullptr;
        }
    }

    //清空存储步骤的向量
    sliceToPut_Kind_Record.clear();
    sliceToPut_PosX_Record.clear();
    sliceToPut_PosY_Record.clear();
    targetSlice_NumberInArray_Record.clear();
}

void playWidget::restart()//游戏以及选择模式的关键函数
{
    userDefined = false;
    SliceToPutWidget->setFixedSize(SCROLLWIDGET_WIDTH, SCROLLWIDGET_HEIGHT);
    //选择的是固定关卡模式
    if(playMode == practiceMode || playMode == competitionMode){
        //从文件中加载了地图的信息，但是还没有对应到每个Slice对象，还没有给其设置路径,那map还需要函数
        this->onLoginPlayer->getPlayMap().loadSliceFromFile(playMode);
        this->onLoginPlayer->getPlayMap().convertMapToElement(playMode);
        this->onLoginPlayer->getPlayMap().defaultSliceToPut();
        //让每个slice对象根据自身种类载入图片
        this->onLoginPlayer->getPlayMap().setSliceToPutPixmap();
        this->onLoginPlayer->getPlayMap().setTargetSlicePixmap(playMode);
        //加载可视化的页面选项
        this->loadSliceToPut();
        this->loadTargetSlice();
        this->loadSliceHasPutOn();
        hideTargetSlice->hide();
        //开始计时
        timer->start(10);//每秒触发一次
        for(int i = 0; i < 36; i++){
            connect(targetSlice[i],&DroppableLabel::TargetSliceChanged,this,&playWidget::updateTargetSlice);
            connect(targetSlice[i],&DroppableLabel::SliceToPutDropped,this,&playWidget::updateSliceToPut);
        }
        if(this->onLoginPlayer->getPlayMap().canBeSolved()){
            QMessageBox msg;

            msg.setText("这张地图系统判定是有解的，可以点击提示哦");
            msg.exec();
        }
        else{
            QMessageBox msg;
            msg.setText("这张地图似乎无解，可以点击提示让系统深度判定并给出提示哦");
            msg.exec();
            this->onLoginPlayer->getPlayMap().setHasAnswer(false);
        }
    }

    if(playMode == endlessMode){
        qDebug() << "btnClicked";
        //从文件中加载了地图的信息，但是还没有对应到每个Slice对象，还没有给其设置路径,那map还需要函数
        this->onLoginPlayer->getPlayMap().loadSliceRandomly();
        this->onLoginPlayer->getPlayMap().convertMapToElement(practiceMode);
        this->onLoginPlayer->getPlayMap().setHasAnswer(true);
        this->onLoginPlayer->getPlayMap().defaultSliceToPut();
        //让每个slice对象根据自身种类载入图片
        this->onLoginPlayer->getPlayMap().setSliceToPutPixmap();
        this->onLoginPlayer->getPlayMap().setTargetSlicePixmap(endless_playMode);
        //加载可视化的页面选项
        this->loadSliceToPut();
        this->loadTargetSlice();
        this->loadSliceHasPutOn();
        hideTargetSlice->hide();
        //开始计时
        timer->start(10);//每秒触发一次
        for(int i = 0; i < 36; i++){
            connect(targetSlice[i],&DroppableLabel::TargetSliceChanged,this,&playWidget::updateTargetSlice);
            connect(targetSlice[i],&DroppableLabel::SliceToPutDropped,this,&playWidget::updateSliceToPut);
            //在map对象里写一个随机生成的函数，通过该玩家调用
        }
    }
}

bool playWidget::isAnswer()
{

    for(int i = 0; i< 36; i++){
        int hasDropOn = targetSlice[i]->getHasDropOn();
        if(playMode == practiceMode || (playMode == endlessMode && endless_playMode == practiceMode)){
            switch (targetSlice[i]->getSliceKind()) {
            case 0:
                if(hasDropOn != 0)
                    return false;
                break;
            case 1://把switch的两种情况写在一起，简洁一些
            case 3:
                if(hasDropOn != 1 && hasDropOn !=3)
                    return false;
                break;
            case 2:
                if(hasDropOn != 2)
                    return false;
                break;
            case 4:
                if(hasDropOn != 4)
                    return false;
            }
        }
        if(playMode == competitionMode || ( playMode == endlessMode && endless_playMode == competitionMode)){
            switch (targetSlice[i]->getSliceKind()) {
            case 0:
            case 2:
                if(hasDropOn != 0 && hasDropOn !=2)
                    return false;
                break;
            case 1://把switch的两种情况写在一起，简洁一些
            case 3:
                if(hasDropOn != 1 && hasDropOn !=3)
                    return false;
                break;
            case 4:
                if(hasDropOn != 4)
                    return false;
            }
        }
    }
    return true;
}

void playWidget::updatePlayerRecord()//根据玩家索引号找到目标文件中存储的记录
{
    if(playMode == practiceMode){
        if(onLoginPlayer->getAccount() != "游客"){
            onLoginPlayer->getPracticeRecord().updateRecord(elapsedTime);
            //下面这个writeTofile要修改一下，有成功次数就修改，没有成功过就添加到末尾
            onLoginPlayer->getPracticeRecord().writeToFile(PRACTICE_RECORD_PATH,onLoginPlayer->getIndex());
        }
        else{
            onLoginPlayer->getPracticeRecord().updateRecord(elapsedTime);
            onLoginPlayer->getPracticeRecord().writeToFile(TOURISTPLAYER_RECORD_PATH,0);//游客默认索引号吧
        }
    }
    if(playMode == competitionMode){
        if(onLoginPlayer->getAccount() != "游客"){
            qDebug() << "updateTofile";
            onLoginPlayer->getCompetitionRecord().updateRecord(elapsedTime);
            //下面这个writeTofile要修改一下，有成功次数就修改，没有成功过就添加到末尾
            onLoginPlayer->getCompetitionRecord().writeToFile(COMPETITION_RECORD_PATH,onLoginPlayer->getIndex());
        }
        else{
            onLoginPlayer->getCompetitionRecord().updateRecord(elapsedTime);
            onLoginPlayer->getCompetitionRecord().writeToFile(TOURISTPLAYER_RECORD_PATH,1);//游客默认比赛为1，只有一个游客
        }
    }

    if(playMode == endlessMode){
        if(onLoginPlayer->getAccount() != "游客"){
            if(endless_playMode == practiceMode){
                onLoginPlayer->getEndlessPracticeRecord().updateRecord(elapsedTime);
                //下面这个writeTofile要修改一下，有成功次数就修改，没有成功过就添加到末尾
                onLoginPlayer->getEndlessPracticeRecord().writeToFile(ENDLESSPRACTICE_RECORD_PATH,onLoginPlayer->getIndex());
            }
            if(endless_playMode == competitionMode){
                onLoginPlayer->getEndlessCompetitonRecord().updateRecord(elapsedTime);
                //下面这个writeTofile要修改一下，有成功次数就修改，没有成功过就添加到末尾
                onLoginPlayer->getEndlessCompetitonRecord().writeToFile(ENDLESSCOMPETITION_RECORD_PATH,onLoginPlayer->getIndex());
            }
        }
        else{
            onLoginPlayer->getCompetitionRecord().updateRecord(elapsedTime);
            onLoginPlayer->getCompetitionRecord().writeToFile(TOURISTPLAYER_RECORD_PATH,2);//游客默认比赛为2，只有一个游客，随意一点啦
        }
    }

}

void playWidget::reShowWidget()
{

    for(int i = 0; i<7; i++){
        if(SliceToPut[i] != nullptr){
            delete SliceToPut[i];
            sliceToputLayout->removeWidget(SliceToPut[i]);
            SliceToPut[i] = nullptr;
        }
    }
    cleanWidget();
    SliceToPutWidget->setFixedSize(SCROLLWIDGET_WIDTH,SCROLLWIDGET_HEIGHT);
    hideTargetSlice->show();
    hideTargetSlice->raise();
    userDefined = false;
    elapsedTime = 0;
    QString timeString = QString("%1:%2:%3").arg(0,2,10,QChar('0'))
                             .arg(0,2,10,QChar('0'))
                             .arg(0,2,10,QChar('0'));

    timeLable->setText(timeString);
    timer->stop();
}

void playWidget::updateTime()
{
    elapsedTime += 1; // 毫秒累加

    int minutes=(elapsedTime/(100*60))%60;
    int seconds=(elapsedTime/100)%60;
    int milliseconds=elapsedTime%100;

    QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                             .arg(seconds,2,10,QChar('0'))
                             .arg(milliseconds,2,10,QChar('0'));
    timeLable->setText(timeString);
    timeLable->setStyleSheet("QLabel {""color: #00FFFF;""}");
}

void playWidget::withdraw()
{

    if( !sliceToPut_PosY_Record.empty() ){//用一个判断就好，都是同步操作
        //下列函数会导致一次重置，切片全部回来，不对
        updateSliceToPut(sliceToPut_Kind_Record.at(sliceToPut_Kind_Record.size() -1 ), 1);//注意size要减一
        //该处可以正常debug出东西，下面的update函数出问题了,修好了，-1在括号外，但撤回操作还是有问题，怎么一次撤回次数这么多
        //原来是下列update函数的问题，又向数组中加入了一次元素
        updateTargetSlice(sliceToPut_Kind_Record.at(sliceToPut_Kind_Record.size() -1),
                          targetSlice_NumberInArray_Record.at(targetSlice_NumberInArray_Record.size() -1),
                          sliceToPut_PosX_Record.at(sliceToPut_PosX_Record.size() -1),
                          sliceToPut_PosY_Record.at(sliceToPut_PosY_Record.size() -1) , -1);

        sliceToPut_Kind_Record.pop_back();
        sliceToPut_PosX_Record.pop_back();
        sliceToPut_PosY_Record.pop_back();//用resize重新分配内存太麻烦了，用一个int记录一下吧
        targetSlice_NumberInArray_Record.pop_back();
    }
    else{
        QMessageBox::warning(nullptr, "警告", "当前已经是初始状态，不可撤回");
    }
}

void playWidget::updateTargetSlice(int sliceKind,int posInArray, int pos_x, int pos_y, int delta)//在最后附一个delta，避免撤回操作要重新写函数
{
    if(delta>0){//只有放置切片才入数组，避免步骤重叠
        sliceToPut_Kind_Record.push_back(sliceKind);
        sliceToPut_PosX_Record.push_back(pos_x);
        sliceToPut_PosY_Record.push_back(pos_y);
        targetSlice_NumberInArray_Record.push_back(posInArray);
    }
    switch (sliceKind) {
    case 1:
        targetSlice[posInArray]->addSlicePutOn(delta);
        SliceHasPutOn[posInArray]->setText(QString::number( targetSlice[posInArray]->getHasDropOn() ));
        break;
    case 2:

        //该图片矩形框左上角：
        if(pos_x < SLICECHECKCENTER && pos_y < SLICECHECKCENTER){
            targetSlice[posInArray - 6]->addSlicePutOn(delta);
            targetSlice[posInArray - 1]->addSlicePutOn(delta);
            targetSlice[posInArray - 7]->addSlicePutOn(delta);
            targetSlice[posInArray]->addSlicePutOn(delta);
        }
        //该图片矩形框右上角//这里为什么和认知的右上角、左下角有区别，不太清楚，给point初始赋值调了一下，目前和认知相符
        if(pos_x > SLICECHECKCENTER && pos_y < SLICECHECKCENTER){
            targetSlice[posInArray + 1]->addSlicePutOn(delta);
            targetSlice[posInArray - 6]->addSlicePutOn(delta);
            targetSlice[posInArray - 5]->addSlicePutOn(delta);
            targetSlice[posInArray]->addSlicePutOn(delta);
        }
        //该图片矩形左下角
        if(pos_x < SLICECHECKCENTER && pos_y > SLICECHECKCENTER){
            targetSlice[posInArray - 1]->addSlicePutOn(delta);
            targetSlice[posInArray + 5]->addSlicePutOn(delta);
            targetSlice[posInArray + 6]->addSlicePutOn(delta);
            targetSlice[posInArray]->addSlicePutOn(delta);
        }
        //该图片矩形右下角
        if(pos_x > SLICECHECKCENTER && pos_y >SLICECHECKCENTER){
            targetSlice[posInArray + 1]->addSlicePutOn(delta);
            targetSlice[posInArray + 6]->addSlicePutOn(delta);
            targetSlice[posInArray + 7]->addSlicePutOn(delta);
            targetSlice[posInArray]->addSlicePutOn(delta);
        }
        updateTargetSliceLabel();
        break;
    case 3://不管在该图片矩形哪个位置都一样
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                targetSlice[posInArray + (6*i) +j]->addSlicePutOn(delta);
            }
        }
        updateTargetSliceLabel();
        break;
    case 4:
        //该图片矩形框左上角：
        if(pos_x < SLICECHECKCENTER && pos_y < SLICECHECKCENTER){
            for(int i = -2; i<2; i++){
                for(int j = -2; j<2; j++){
                    targetSlice[posInArray +(6*i)+j]->addSlicePutOn(delta);
                }
            }
        }
        //该图片矩形框右上角
        if(pos_x > SLICECHECKCENTER && pos_y < SLICECHECKCENTER){
            for(int i = -2; i<2; i++){
                for(int j = -1; j<3; j++){
                    targetSlice[posInArray + (6*i)+j]->addSlicePutOn(delta);
                }
            }
        }
        //该图片矩形左下角
        if(pos_x < SLICECHECKCENTER && pos_y > SLICECHECKCENTER){
            for(int i = -1; i<3; i++){
                for(int j = -2; j<2; j++){
                    targetSlice[posInArray + (6*i) +j]->addSlicePutOn(delta);
                }
            }
        }
        //该图片矩形右下角
        if(pos_x > SLICECHECKCENTER && pos_y >SLICECHECKCENTER){
            for( int i = -1; i<3; i++){
                for(int j = -1; j<3; j++){
                    targetSlice[posInArray + (6*i)+j]->addSlicePutOn(delta);
                }
            }
        }
        updateTargetSliceLabel();
    }
    if(isAnswer()){
        VictoryWidget *victoryWidget = new VictoryWidget();
        victoryWidget->setFixedSize(600,300);
        victoryWidget->show();
        connect(victoryWidget,&VictoryWidget::toRank,[=](){
            victoryWidget->close();
            emit toRank();
        });

        connect(victoryWidget,&VictoryWidget::selectOtherMode,[=](){
            victoryWidget->close();
            selectOtherMode();
        });
        connect(victoryWidget,&VictoryWidget::restart,[=](){

            victoryWidget->close();
            cleanWidget();
            restart();
        });

        this->timer->stop();
        //后续根据是自定义的还是原来的进行胜利页面的描绘
        if(!userDefined){//非用户自定义的再记录
            updatePlayerRecord();
        }
        else{//用户玩得出来再把关卡写进文件，什么关卡对应什么文件，
            writeCustomMapToFile();
        }

    }
}

void playWidget::updateSliceToPut(int sliceKind, int change)
{
    //都优先删除、增加前面的吧，不行，整个操作是栈，优先删除前面要优先返回后面，且确保每次只返回一个
    switch (sliceKind) {
    case 1:
        if(change == -1){
            if(SliceToPut[5] != nullptr){
                //sliceToputLayout->removeWidget(SliceToPut[5]);//没用
                delete SliceToPut[5];
                SliceToPut[5] = nullptr;
            }
            else if(SliceToPut[6] != nullptr){
                delete SliceToPut[6];
                SliceToPut[6] = nullptr;
            }
        }
        if( change == 1 ){
            if(SliceToPut[6] == nullptr){//此处不能用else if语句，会导致一次撤回，回归两个切片，
                //既然放置的切片在上述语句中，在数组里是有顺序的，那么按照顺序添加即可，要用倒序，即6在5前检验，6为空5一定为空，6不为空时，检验5,直接用return掉就行
                SliceToPut[6] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[6]->setPictureSize(1);
                SliceToPut[6]->setPixmap(QPixmap(SLICETOPUT1));
                SliceToPut[6]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[6]);
                return;
            }

            if(SliceToPut[5] == nullptr){
                SliceToPut[5] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[5]->setPictureSize(1);
                SliceToPut[5]->setPixmap(QPixmap(SLICETOPUT1));
                SliceToPut[5]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[5]);
            }
        }
        break;
    case 2:
        if(change == -1){
            if(SliceToPut[3] != nullptr){
                delete SliceToPut[3];
                SliceToPut[3] = nullptr;
            }
            else if(SliceToPut[4] != nullptr){
                delete SliceToPut[4];
                SliceToPut[4] = nullptr;
            }
        }
        if( change == 1 ){
            if(SliceToPut[4] == nullptr){
                SliceToPut[4] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[4]->setPictureSize(2);
                SliceToPut[4]->setPixmap(QPixmap(SLICETOPUT2));
                SliceToPut[4]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[4]);
                return;
            }
            if(SliceToPut[3] == nullptr){
                SliceToPut[3] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[3]->setPictureSize(2);
                SliceToPut[3]->setPixmap(QPixmap(SLICETOPUT2));
                SliceToPut[3]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[3]);
            }
        }
        break;
    case 3:
        if(change == -1){
            if(SliceToPut[1] != nullptr){
                delete SliceToPut[1];
                SliceToPut[1] = nullptr;
            }
            else if(SliceToPut[2] != nullptr){
                delete SliceToPut[2];
                SliceToPut[2] = nullptr;
            }
        }
        if( change == 1 ){
            if(SliceToPut[2] == nullptr){
                SliceToPut[2] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[2]->setPictureSize(3);
                SliceToPut[2]->setPixmap(QPixmap(SLICETOPUT3));
                SliceToPut[2]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[2]);
                return;
            }
            if(SliceToPut[1] == nullptr){
                SliceToPut[1] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[1]->setPictureSize(3);
                SliceToPut[1]->setPixmap(QPixmap(SLICETOPUT3));
                SliceToPut[1]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[1]);
            }
        }
        break;
    case 4:
        if(change == -1){
            if(SliceToPut[0] != nullptr){
                delete SliceToPut[0];
                SliceToPut[0] = nullptr;
            }
        }
        if( change == 1 ){
            if(SliceToPut[0] == nullptr){
                SliceToPut[0] = new DraggableLabel(SliceToPutWidget);
                SliceToPut[0]->setPictureSize(4);
                SliceToPut[0]->setPixmap(QPixmap(SLICETOPUT4));
                SliceToPut[0]->setFixedSize(80,80);
                sliceToputLayout->addWidget(SliceToPut[0]);
            }
        }
        break;
    }

    //更新滚动条显示窗口的大小
    //不用判断是增还是减，通过size就足够了
    int multiple = sliceToPut_Kind_Record.size();
    SliceToPutWidget->setFixedSize(SCROLLWIDGET_WIDTH,SCROLLWIDGET_HEIGHT - multiple * (SLICEHEIGHT - 3) );

}

void playWidget::updateTargetSliceLabel()
{
    for(int i = 0; i < 36; i++){
        SliceHasPutOn[i]->setText(QString::number( targetSlice[i]->getHasDropOn() ));
    }
}

void playWidget::startWithOthersMap()//不设，也加入记录，毕竟是对的
{
    //清空、重置页面
    cleanWidget();
    for(int i = 0; i<7; i++){
        if(SliceToPut[i] != nullptr){
            delete SliceToPut[i];
            sliceToputLayout->removeWidget(SliceToPut[i]);
            SliceToPut[i] = nullptr;
        }
    }

    hideTargetSlice->hide();
    elapsedTime = 0;
    QString timeString=QString("%1:%2:%3").arg(0,2,10,QChar('0'))
                             .arg(0,2,10,QChar('0'))
                             .arg(0,2,10,QChar('0'));

    timeLable->setText(timeString);
    timer->stop();

    //重新开始
    onLoginPlayer->getPlayMap().loadSliceFromOther(playMode);
    onLoginPlayer->getPlayMap().defaultSliceToPut();
    //载入图片
    onLoginPlayer->getPlayMap().setSliceToPutPixmap();
    onLoginPlayer->getPlayMap().setTargetSlicePixmap(playMode);
    //加载可视化的页面选项
    loadSliceToPut();
    loadTargetSlice();
    loadSliceHasPutOn();
    //
    timer->start(10);//每秒触发一次
    for(int i = 0; i < 36; i++){
        connect(targetSlice[i],&DroppableLabel::TargetSliceChanged,this,&playWidget::updateTargetSlice);
        connect(targetSlice[i],&DroppableLabel::SliceToPutDropped,this,&playWidget::updateSliceToPut);
    }
}

void playWidget::startByCustomInput()
{
    //创建自定义的对话框对象
    class inputDialog *inputMap = new class inputDialog();
    inputMap->input();
    inputMap->show();
    //连接对话框的信号到当前窗口
    connect(inputMap,&inputDialog::accepted,[=](){
        if(inputMap->checkData()){//如果数据没有输入错误
            //清空、重置页面
            for(int i = 0; i<7; i++){
                if(SliceToPut[i] != nullptr){
                    delete SliceToPut[i];
                    sliceToputLayout->removeWidget(SliceToPut[i]);
                    SliceToPut[i] = nullptr;
                }
            }
            cleanWidget();
            inputMap->close();
            hideTargetSlice->hide();
            elapsedTime = 0;
            QString timeString=QString("%1:%2:%3").arg(0,2,10,QChar('0'))
                                     .arg(0,2,10,QChar('0'))
                                     .arg(0,2,10,QChar('0'));

            timeLable->setText(timeString);
            timer->stop();
            //设置游戏状态：
            userDefined = true;
            //返回表格输入
            int *userInput = inputMap->getDataFromTable();

            //输入到玩家的地图对象
            onLoginPlayer->getPlayMap().loadSliceFromInput(userInput);
            this->onLoginPlayer->getPlayMap().convertMapToElement(playMode);

            if(this->onLoginPlayer->getPlayMap().canBeSolved()){
                QMessageBox msg;
                msg.setText("这张地图系统判定为有解，可以点击提示哦");
                msg.exec();
            }
            else this->onLoginPlayer->getPlayMap().setHasAnswer(false);

            onLoginPlayer->getPlayMap().defaultSliceToPut();
            //载入图片
            onLoginPlayer->getPlayMap().setSliceToPutPixmap();
            onLoginPlayer->getPlayMap().setTargetSlicePixmap(playMode);
            //加载可视化的页面选项
            loadSliceToPut();
            loadTargetSlice();
            loadSliceHasPutOn();
            //
            timer->start(10);//每秒触发一次
            for(int i = 0; i < 36; i++){
                connect(targetSlice[i],&DroppableLabel::TargetSliceChanged,this,&playWidget::updateTargetSlice);
                connect(targetSlice[i],&DroppableLabel::SliceToPutDropped,this,&playWidget::updateSliceToPut);
            }
        }
    });
}

void playWidget::showCustom()
{

    mainLayout->addWidget(Custom,2,0,1,1);
    Custom->setText("重新自定义");
    Custom->setFixedSize(100,80);
    Custom->show();
    connect(Custom,&QPushButton::clicked,this,&playWidget::recustom);

    startBtn->hide();
}

void playWidget::loadSliceToPut()
{
    for(int i =0; i<7 ; i++)
    {
        if(!onLoginPlayer->getPlayMap().getSliceToPut(i).hasPut())//如果没放就给它可视化出来，先开始写错了，应该要取反
        {
            SliceToPut[i] = new DraggableLabel(SliceToPutWidget);//创建可视化Label对象
            SliceToPut[i]->setFixedSize(80,80);
            SliceToPut[i]->setPictureSize(onLoginPlayer->getPlayMap().getSliceToPut(i).getSliceToPutKind());
            QPixmap pixmap(onLoginPlayer->getPlayMap().getSliceToPut(i).getSliceToPutRoad());
            SliceToPut[i]->setPixmap(pixmap);//以上均是成功的，但为什么没有加载到屏幕上呢
            sliceToputLayout->addWidget(SliceToPut[i]);
            sliceToputLayout->update();
        }
    }

}

void playWidget::loadTargetSlice()
{
    for(int i=0; i<36; i++)
    {
        this->targetSlice[i] = new DroppableLabel(this);
        targetSlice[i]->setPosInGrid(i);
        QPixmap pixmap(onLoginPlayer->getPlayMap().getTargetSlice(i).getSlicePixmapRoad());
        targetSlice[i]->setPixmap(pixmap);
        targetSlice[i]->move(120 + (80 * targetSlice[i]->getPosInGrid_X() ),
                             10 + (80 * targetSlice[i]->getPosInGrid_Y() ));
        targetSlice[i]->setFixedSize(80,80);
        targetSlice[i]->setSliceKind(onLoginPlayer->getPlayMap().getTargetSlice(i).getSliceKind());
        targetSlice[i]->show();
    }
}

void playWidget::loadSliceHasPutOn()
{
    for(int i = 0; i < 36; i++)
    {
        this->SliceHasPutOn[i] = new QLabel(this);
        QFont font = QFont();
        font.setPointSize(16);//设置字体大小为24
        SliceHasPutOn[i]->setFont(font);
        SliceHasPutOn[i]->setText(QString::number(onLoginPlayer->getPlayMap().getTargetSlice(i).getSliceHasPutOn()));
        SliceHasPutOn[i]->move(180 + (80 * targetSlice[i]->getPosInGrid_X() ),
                               10 + (80 * targetSlice[i]->getPosInGrid_Y() ) );
        SliceHasPutOn[i]->setFixedSize(24,24);
        SliceHasPutOn[i]->show();
    }
}


void playWidget::customMode()
{
    class selectModeDialog *selectDialog = new class selectModeDialog(this);
    connect(selectDialog, &selectModeDialog::othersMapButtonClicked, [=](){
        selectDialog->close();
        startWithOthersMap();
    });
    connect(selectDialog, &selectModeDialog::customMapButtonClicked,[=](){
        selectDialog->close();
        startByCustomInput();
    });
    selectDialog->show();
}

void playWidget::writeCustomMapToFile()
{
    if(playMode == practiceMode){
        QFile practiceFile(USERDEFINED_RPRATICEMAP_PATH);
        if(practiceFile.open(QIODevice::WriteOnly | QIODevice::Append)){
            QDataStream in(&practiceFile);
            for(int i = 0; i < 36; i++){
                in << onLoginPlayer->getPlayMap().getTargetSlice(i).getSliceKind();
            }
            practiceFile.close();
        }
    }
    else if(playMode == competitionMode){
        QFile competitionFile(USERDEFINED_RPRATICEMAP_PATH);
        if(competitionFile.open(QIODevice::WriteOnly | QIODevice::Append)){
            QDataStream in(&competitionFile);
            for(int i = 0; i < 36; i++){
                in << onLoginPlayer->getPlayMap().getTargetSlice(i).getSliceKind();
            }
            competitionFile.close();
        }
    }
}

rankWidget::rankWidget(QWidget *parent)
    : QWidget(parent)
{
    // 创建表格
    tableWidget = new QTableWidget(this);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许编辑

    tableWidget->setFixedSize(680,450);

    QFont font("华文行楷", 14);

    returnBtn = new QPushButton(this);
    returnBtn->setIcon(QIcon(":/res/returnBtn.png"));
    returnBtn->setFixedSize(100,150);
    returnBtn->setIconSize(QSize(100,150));
    returnBtn->setFlat(true);


    practiceRankBtn = new QPushButton("查看练习模式排行榜",this);
    practiceRankBtn->setStyleSheet("QPushButton {"
                                   "background-color: rgb(91,145,130);"
                                   "color: black;"
                                   "font-family: 'SimKai'; /* 行楷字体可能不可用，这里用楷体代替 */"
                                   "font-size: 14px;"
                                   "padding: 5px 10px;"
                                   "border: none;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: rgb(120,145,130);"
                                   "border: 2px solid #666666;"
                                   "}"
                                   );
    practiceRankBtn->setFixedSize(200,120);

    competitionRankBtn = new QPushButton("查看比赛模式排行榜",this);
    competitionRankBtn->setStyleSheet("QPushButton {"
                                      "background-color: rgb(91,145,130);"
                                      "color: black;"
                                      "font-family: 'SimKai'; /* 行楷字体可能不可用，这里用楷体代替 */"
                                      "font-size: 14px;"
                                      "padding: 5px 10px;"
                                      "border: none;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "background-color: rgb(120,145,130);"
                                      "border: 2px solid #666666;"
                                      "}"
                                      );
    competitionRankBtn->setFixedSize(200,120);
    endlessRankBtn = new QPushButton("查看无尽模式排行榜",this);
    endlessRankBtn->setStyleSheet("QPushButton {"
                                  "background-color: rgb(91,145,130);"
                                  "color: black;"
                                  "font-family: 'SimKai'; /* 行楷字体可能不可用，这里用楷体代替 */"
                                  "font-size: 14px;"
                                  "padding: 5px 10px;"
                                  "border: none;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: rgb(120,145,130);"
                                  "border: 2px solid #666666;"
                                  "}"
                                  );
    endlessRankBtn->setFixedSize(200,120);

    fastestMode = new QRadioButton("按照单局最快排序",this);
    fastestMode->setStyleSheet(
        "QRadioButton:checked {"
        "    background-color: yellow;"
        "    color: blue;"
        "}"
        );

    fastestMode->setFont(font);
    averageMode = new QRadioButton("按照平均用时排序",this);
    averageMode->setStyleSheet(
        "QRadioButton:checked {"
        "    background-color: yellow;"
        "    color: blue;"
        "}"
        );
    averageMode->setFont(font);
    successMode = new QRadioButton("按照成功次数排序",this);
    successMode->setStyleSheet(
        "QRadioButton:checked {"
        "    background-color: yellow;"
        "    color: blue;"
        "}"
        );
    successMode->setFont(font);
    selectSortMode = new QButtonGroup(this);
    QButtonGroup *selectSortMode = new QButtonGroup(this);
    //对应表头顺序
    selectSortMode->addButton(fastestMode, 2); // 给按钮1设置ID 0
    selectSortMode->addButton(averageMode, 1); // 给按钮2设置ID 1
    selectSortMode->addButton(successMode, 0); // 给按钮3设置ID 2



    connect(fastestMode, &QRadioButton::clicked, [=](){
        sortRank(3);
    });
    connect(averageMode,&QRadioButton::clicked, [=](){
        sortRank(2);
    });
    connect(successMode,&QRadioButton::clicked, [=](){
        sortRank(1);
    });
    connect(practiceRankBtn,&QPushButton::clicked,[=](){
        loadContent(PRACTICE_RECORD_PATH);
    });
    connect(competitionRankBtn,&QPushButton::clicked,[=](){
        loadContent(COMPETITION_RECORD_PATH);
    });
    connect(endlessRankBtn,&QPushButton::clicked,[=](){
        QWidget *selectMode = new QWidget();
        QLabel *intro = new QLabel("请选择您要查看的模式",selectMode);
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
            loadContent(ENDLESSPRACTICE_RECORD_PATH);
            selectMode->close();
        });
        connect(competition,&QPushButton::clicked,[=](){
            loadContent(ENDLESSCOMPETITION_RECORD_PATH);
            selectMode->close();
        });

    });

    // 更新表格内容

    // 设置布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(tableWidget,1,1,4,4);

    mainLayout->addWidget(practiceRankBtn,1,5,1,1);
    mainLayout->addWidget(competitionRankBtn,3,5,1,1);
    mainLayout->addWidget(endlessRankBtn,5,5,1,1);

    mainLayout->addWidget(returnBtn,0,0,2,1);
    mainLayout->addWidget(fastestMode,0,1,1,1);
    mainLayout->addWidget(averageMode,0,3,1,1);
    mainLayout->addWidget(successMode,0,5,1,1);

    QLabel *put = new QLabel(this);
    mainLayout->addWidget(put,11,0,5,9);
    setLayout(mainLayout);

    // 连接信号到槽函数
    connect(returnBtn, &QPushButton::clicked, this, &rankWidget::returnToGameScene);

}

void rankWidget::loadContent(const QString &filename)
{
    //清空
    while (tableWidget->rowCount() > 0) { // 当还有行时
        tableWidget->removeRow(0); // 删除第一行（索引为0）
    }
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"用户名", "成功次数", "平均时间", "最快时间"});

    // 获取表头对象
    QHeaderView *horizontalHeader = tableWidget->horizontalHeader();
    // 设置每一列的宽度，这里以像素为单位
    horizontalHeader->resizeSection(0, 150);
    horizontalHeader->resizeSection(1, 180);
    horizontalHeader->resizeSection(2, 180);
    horizontalHeader->resizeSection(3, 180);

    //先载入玩家
    int playerAmount = -1;
    QFile playerFile(ACCOUNTLISTROAD);
    if(playerFile.open(QIODevice::ReadOnly)){
        Player player;
        QDataStream inPlayer(&playerFile);
        for(int i = 0; !playerFile.atEnd();i++){
            inPlayer >> player;
            playerAmount ++;
            // 动态插入行
            int newRow = tableWidget->rowCount();
            tableWidget->insertRow(newRow);//插入行的索引

            // 更新单元格的数据
            QTableWidgetItem *item = new QTableWidgetItem(player.getAccount());
            tableWidget->setItem(newRow, 0, item);
        }
        playerFile.close();
    }

    QFile recordFile(filename);
    if(recordFile.open(QIODevice::ReadOnly)){
        GameRecord record;
        int successTime;

        QDataStream inRecord(&recordFile);
        for(int index = 0; index <= playerAmount; index++){
            recordFile.seek(0);
            while (!recordFile.atEnd()) {
                inRecord >> record;
                if(record.getIndex() == index){
                    successTime = record.getSuccessTimes();
                    qDebug() << record.getAverageTime();
                    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(record.getSuccessTimes()));
                    QTableWidgetItem *item2 = new QTableWidgetItem(record.convertTimeToString(record.getAverageTime()));
                    QTableWidgetItem *item3 = new QTableWidgetItem(record.convertTimeToString(record.getfastestTime()));

                    // 将QTableWidgetItem数组插入到表中
                    tableWidget->setItem(index, 1, item1);
                    tableWidget->setItem(index, 2, item2);
                    tableWidget->setItem(index, 3, item3);
                }
            }
        }
        recordFile.close();
    }

}


void rankWidget::swapTableWidgetRows(int fromRow, int toRow)
{
    if (fromRow == toRow || fromRow < 0 || toRow < 0 || fromRow >= tableWidget->rowCount() || toRow >= tableWidget->rowCount()) {
        qDebug() << "Invalid row indices";
        return;
    }

    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QTableWidgetItem *fromItem = tableWidget->takeItem(fromRow, col);
        QTableWidgetItem * toItem = tableWidget->takeItem(toRow, col);

        // 交换两行的值
        tableWidget->setItem(toRow, col, fromItem);
        tableWidget->setItem(fromRow, col, toItem);
    }
}

void rankWidget::sortRank(int mode)
{
    int compareIndex = tableWidget->rowCount();//如果有空白行就移到末尾，下面的第二层循环相应减少

    for (int row = 0; row < compareIndex; ++row) {
        int maxIndex = row;
        QTableWidgetItem *item = tableWidget->item(row, mode);
        if(!item){//该单元格数据为空
            swapTableWidgetRows(row, compareIndex);//将没有数据的和最后一行交换
            compareIndex --;//比较的目标行数减一
            row = 0;//重新从第一行开始判断
            continue;//退出循环
        }
        //int originalValue = item->data(Qt::DisplayRole).toInt();
        QString originalValue = item->text();
        for(int i = row + 1; i < compareIndex; i++){
            QTableWidgetItem *item2 = tableWidget->item(i, mode);
            if(!item2){//该单元格数据为空
                swapTableWidgetRows(i, compareIndex);//将没有数据的和最后一行交换
                compareIndex --;//比较的目标行数减一
                continue;//跳过该行，继续寻找
            }
            //两个单元格都存在数据：这里没有检验转换int是否成功因为已经知道类型了

            //int nextValue = item2->data(Qt::DisplayRole).toInt();
            QString nextValue = item2->text();
            if(mode == 1){//成功次数，在第二列
                if(nextValue > originalValue){
                    originalValue = nextValue;
                    maxIndex = i;//找最大的数据
                }
            }
            else{//其他的都是时间，升序
                if(nextValue < originalValue){
                    originalValue = nextValue;
                    maxIndex = i;//找最大的数据
                }
            }
        }
        //正常执行完，然后交换最大成功次数
        swapTableWidgetRows(row,maxIndex);
    }
}


VictoryWidget::VictoryWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化UI组件
    victoryLabel = new QLabel("恭喜您获胜！", this);
    viewRankingButton = new QPushButton("查看排行榜", this);
    viewRankingButton->setFixedSize(150,150);

    continueGameButton = new QPushButton("继续游戏", this);
    continueGameButton->setFixedSize(150,150);

    selectModeButton = new QPushButton("选择其他模式", this);
    selectModeButton->setFixedSize(150,150);
    gridLayout = new QGridLayout(this);

    // 设置网格布局
    gridLayout->addWidget(victoryLabel, 0, 0, 1, 3, Qt::AlignCenter); // 胜利信息居中跨越三列
    gridLayout->addWidget(viewRankingButton, 1, 0);
    gridLayout->addWidget(continueGameButton, 1, 1);
    gridLayout->addWidget(selectModeButton, 1, 2);
    setLayout(gridLayout);

    // 连接信号与槽
    connect(viewRankingButton, &QPushButton::clicked, this, &VictoryWidget::toRank);
    connect(continueGameButton, &QPushButton::clicked, this, &VictoryWidget::restart);
    connect(selectModeButton, &QPushButton::clicked, this, &VictoryWidget::selectOtherMode);

}

VictoryWidget::~VictoryWidget() {}



void swapTableWidgetRows(QTableWidget *tableWidget, int fromRow, int toRow) {
    if (fromRow == toRow || fromRow < 0 || toRow < 0 || fromRow >= tableWidget->rowCount() || toRow >= tableWidget->rowCount()) {
        qDebug() << "Invalid row indices";
        return;
    }

    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QTableWidgetItem *fromItem = tableWidget->takeItem(fromRow, col);
        QTableWidgetItem * toItem = tableWidget->takeItem(toRow, col);

        // 交换两行的值
        tableWidget->setItem(toRow, col, fromItem);
        tableWidget->setItem(fromRow, col, toItem);
    }
}

void playWidget::setEndlessPlayMode(int input)
{
    endless_playMode = input;
}
