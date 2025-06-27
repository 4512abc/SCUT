#include "Ranking.h"
#include "ui_Ranking.h"
Ranking::Ranking(QWidget *parent,Player *onlinePlayer)
    : QWidget(parent)
    , ui(new Ui::Ranking),m_player(onlinePlayer)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);

    time_model=new QStandardItemModel(this);
    score_model=new QStandardItemModel(this);

    //默认1开始，下载十二个关卡的数据
    for(int i=1;i<=12;i++)
    {
        loadData(i);
    }

    //多个地图选项布局，对combox进行初始化
    QList<QString> com_list;
    for(int i=1;i<=12;i++)
    {
        com_list.append(QString("%1").arg(i));
    }
    ui->chooseMap->addItems(com_list);
    ui->chooseMap->setCurrentIndex(0);


    ui->view->setModel(time_model);                                                 //默认设置当前model为time_model
    connect(ui->timeBtn,&QPushButton::clicked,this,&Ranking::updateTimeModel);      //槽函数，点击时间按钮会生成时间排行榜
    connect(ui->scoreBtn,&QPushButton::clicked,this,&Ranking::updateScoreModel);    //槽函数，点击分数按钮会生成分数排行榜

    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //设置水平滚动条隐藏
    ui->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //设置竖直滚动条隐藏
    ui->view->setEditTriggers(QAbstractItemView::NoEditTriggers);       //设置为无法编辑，防止修改数据
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //设置水平方向铺满排行榜框
    ui->view->verticalHeader()->setVisible(false);

    //设置背景
    QImage background(":/images/resource/picture/背景.jpg");
    background=background.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(background));
    this->setPalette(palette);
}

void Ranking::updateTimeModel()
{
    QString currentIndex=ui->chooseMap->currentText();      //获取当前combox的页面编号
    bool ok=false;
    qDebug()<<"showRanking"<<currentIndex;
    int level=currentIndex.toInt(&ok);
    qDebug()<<"排行榜更新成功"<<ok;
    if(level==0||m_player->getUserName()=="tourist")        //如果是游客模式，则不能查看排行榜，或者当前获取需要更新的关卡编号为0，则返回
    {
        return;
    }
    std::sort(playerData[level].begin(),playerData[level].end(),    //按照时间进行排序
              [](const myData &a,const myData &b)
              {
                  return a.time<b.time;});

    time_model->clear();                                    //对原来的model清空
    time_model->setHorizontalHeaderLabels(QStringList()<<"用户名"<<"时间");
    int cnt=0;
    for(int i=0;i<playerData[level].size();i++)                 //重新填充model的内容
    {
        int time=playerData[level][i].time;
        int minutes=(time/(100*60))%60;
        int seconds=(time/100)%60;
        int milliseconds=time%100;
        QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                                 .arg(seconds,2,10,QChar('0'))
                                 .arg(milliseconds,2,10,QChar('0'));
        QStandardItem *name_item=new QStandardItem(QString(playerData[level][i].m_name));           //用户名
        QStandardItem *time_item=new QStandardItem(QString(timeString));     //游戏时间
        name_item->setTextAlignment(Qt::AlignHCenter);
        name_item->setSizeHint(QSize(100,50));
        time_item->setTextAlignment(Qt::AlignHCenter);
        time_item->setSizeHint(QSize(100,50));
        time_model->setItem(cnt,0,name_item);       //设置坐标
        time_model->setItem(cnt,1,time_item);       //设置坐标
        cnt++;
    }
    emit time_model->dataChanged(time_model->index(0, 0), time_model->index(cnt-1, 1));     //发送信号，对time_model进行更新
    ui->view->setModel(time_model);     //使用新的time_model
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //设置水平方向铺满排行榜框
}

void Ranking::updateScoreModel()
{
    QString currentIndex=ui->chooseMap->currentText();      //获取当前combox的页面编号
    bool ok=false;
    qDebug()<<"showRanking"<<currentIndex;
    int level=currentIndex.toInt(&ok);
    qDebug()<<"排行榜更新成功"<<ok;
    if(level==0||m_player->getUserName()=="tourist")        //如果是游客模式，则不能查看排行榜，或者当前获取需要更新的关卡编号为0，则返回
    {
        return;
    }
    std::sort(playerData[level].begin(),playerData[level].end(),    //按照分数进行排序
              [](const myData &a,const myData &b)
              {
                  return a.score>b.score;});

    score_model->clear();                                   //对原来的model清空
    score_model->setHorizontalHeaderLabels(QStringList()<<"用户名"<<"分数");
    int cnt=0;
    for(const auto &item:playerData[level])                 //重新填充model的内容
    {
        QStandardItem *name_item=new QStandardItem(QString(item.m_name));           //用户名
        QStandardItem *score_item=new QStandardItem(QString::number(item.score));   //分数
        name_item->setTextAlignment(Qt::AlignHCenter);
        name_item->setSizeHint(QSize(100,50));
        score_item->setTextAlignment(Qt::AlignHCenter);
        score_item->setSizeHint(QSize(100,50));
        score_model->setItem(cnt,0,name_item);      //设置坐标
        score_model->setItem(cnt,1,score_item);     //设置坐标
        cnt++;
    }
    emit score_model->dataChanged(score_model->index(0, 0), score_model->index(cnt-1, 1));      //发送信号，对score_model进行更新
    ui->view->setModel(score_model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //设置水平方向铺满排行榜框
}

void Ranking::loadData(const int level)
{
    //下载文件数据
    QString fileName=QString("./Ranking%1.bin").arg(level);
    QFile file(fileName);
    QDataStream in(&file);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"错误 无法打开文件进行读取 并生成排行榜";
        return;
    }
    qDebug()<<"排行榜文件夹打开成功";
    while(!in.atEnd())
    {
        myData temp;
        in>>temp.m_name>>temp.time>>temp.score;
        playerData[level].push_back(temp);
    }
    file.close();

}

void Ranking::updateData(const int levelNeedUpdate)
{
    //更新文件数据
    int level=levelNeedUpdate;
    if(level==0||m_player->getUserName()=="tourist")
    {
        return;
    }
    QString fileName=QString("./Ranking%1.bin").arg(level);
    QFile file(fileName);
    QDataStream in(&file);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"错误 无法打开文件 对排行榜进行修改";
        return;
    }
    qDebug()<<"打开文件成功 并且开始修改";
    for(const auto &item: playerData[level])
    {
        in<<item.m_name<<item.time<<item.score;
    }
    file.close();
}

void Ranking::updateRanking(const int levelNeedUpdate)
{
    if(m_player->getUserName()=="tourist")
    {
        return;
    }
    //更新playerData
    int level=levelNeedUpdate;
    myData temp;        //设置将要更新的用户信息
    temp.m_name=m_player->getUserName();
    temp.time=m_player->getTime(level);
    temp.score=500-m_player->getSteps(level)-m_player->getBackSteps(level)*10;

    bool checkOK=false;     //判断是否存在
    qDebug()<<"before update level"<<level<<"size: "<<playerData[level].size();
    for(int i=0;i<playerData[level].size();i++)
    {
        if(temp.m_name==playerData[level][i].m_name)
        {
            if(temp.time<playerData[level][i].time)     //如果当前的游戏记录比之前的更好
            {
                playerData[level][i].time=temp.time;    //更新游戏记录
                checkOK=true;                           //标记为：已经存在
            }
            else if(temp.score>playerData[level][i].score)
            {
                playerData[level][i].score=temp.score;
                checkOK=true;
            }
            else
            {
                checkOK=true;                           //标记为：已经存在
            }
        }
        if(checkOK) break;
    }

    if(!checkOK)    playerData[level].push_back(temp);  //没有检查到，说明是新用户

    qDebug()<<"排行榜更新成功";
    qDebug()<<"after update level"<<level<<"size: "<<playerData[level].size();
}

Ranking::~Ranking()
{
    delete ui;
    if(time_model!=nullptr)
    {
        delete time_model;
        time_model=nullptr;
    }
    if(score_model!=nullptr)
    {
        delete score_model;
        score_model=nullptr;
    }
}


