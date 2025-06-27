#include "musicPlayer.h"
#include <QRandomGenerator>
#include <QAudioDevice>
musicPlayer::musicPlayer(QWidget *parent)
    : QWidget{parent},m_currentIndex(0),sortMode(true),loopMode(false),randomMode(false)
{
    main_layout=new QVBoxLayout(this);
    menu_layout=new QHBoxLayout;
    button_layout=new QHBoxLayout;
    listWidget=new QListWidget(this);

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

    listWidget->setStyleSheet("QListWidget {"
                              "     background: rgba(255, 255, 255, 150);"
                              "     border: 2px solid white;"
                              "     border-radius: 10px;"
                              "     color: white;"
                              "     font-family: 'Microsoft YaHei';"
                              "     font-weight: bold;"
                              "     font-size: 20px"
                              "}");
    musicSchedule=new QHBoxLayout;
    current=new QLabel("00:00",this);
    current->setStyleSheet("QLabel { "
                           "padding: 10px; "
                           "background-color: transparent; "
                           "color: white; "
                           "font-size: 18px; "
                           "font-family: 'Microsoft YaHei';"
                           "}");

    total=new QLabel("00:00",this);
    total->setStyleSheet("QLabel { "
                         "padding: 10px; "
                         "background-color: transparent; "
                         "color: white; "
                         "font-size: 18px; "
                         "font-family: 'Microsoft YaHei';"
                         "}");

    volume_layout=new QHBoxLayout;
    volume=new QLabel("音量调节",this);
    volume->setStyleSheet("QLabel { "
                          "border: red; "
                          "border-radius: 15px; "
                          "padding: 10px; "
                          "background-color: white; "
                          "color: #333333; "
                          "font-size: 18px; "
                          "font-family: 'Microsoft YaHei';"
                          "}");


    scheduleSlider=new QSlider(Qt::Horizontal);     //播放进度条
    volumeSlider=new QSlider(Qt::Horizontal);       //音量进度条

    volume_layout=new QHBoxLayout;
    volume_layout->addWidget(volume);
    volume_layout->addWidget(volumeSlider);

    musicSchedule->addWidget(current);
    musicSchedule->addWidget(total);
    musicSchedule->addWidget(scheduleSlider);

    addMusicBtn=new QPushButton("添加歌曲",this);      //导入资源
    QIcon icon1(":/icons/resource/icons/添加歌曲.png");
    addMusicBtn->setIcon(icon1);
    addMusicBtn->setIconSize(QSize(30,30));
    addMusicBtn->setStyleSheet(globalStylesheet);

    removeBtn=new QPushButton("去除歌曲",this);    //移除歌曲
    QIcon icon2(":/icons/resource/icons/去除歌曲.png");
    removeBtn->setIcon(icon2);
    removeBtn->setIconSize(QSize(30,30));
    removeBtn->setStyleSheet(globalStylesheet);

    clearBtn=new QPushButton("清空歌曲",this);     //清空歌曲
    QIcon icon3(":/icons/resource/icons/清空歌曲.png");
    clearBtn->setIcon(icon3);
    clearBtn->setIconSize(QSize(30,30));
    clearBtn->setStyleSheet(globalStylesheet);

    lastBtn=new QPushButton("上一首",this);      //上一曲
    QIcon icon4(":/icons/resource/icons/上一曲.png");
    lastBtn->setIcon(icon4);
    lastBtn->setIconSize(QSize(30,30));
    lastBtn->setStyleSheet(globalStylesheet);

    playBtn=new QPushButton("开始",this);      //播放
    QIcon icon5(":/icons/resource/icons/音乐.png");
    playBtn->setIcon(icon5);
    playBtn->setIconSize(QSize(30,30));
    playBtn->setStyleSheet(globalStylesheet);

    nextBtn=new QPushButton("下一首",this);      //下一曲
    QIcon icon6(":/icons/resource/icons/下一曲.png");
    nextBtn->setIcon(icon6);
    nextBtn->setIconSize(QSize(30,30));
    nextBtn->setStyleSheet(globalStylesheet);

    modeBtn=new QPushButton("列表循环",this);       //播放模式
    QIcon icon8(":/icons/resource/icons/列表循环.png");
    modeBtn->setIcon(icon8);
    modeBtn->setIconSize(QSize(30,30));
    modeBtn->setStyleSheet(globalStylesheet);

    //调整menu布局：添加音乐，去除音乐，清空音乐列表
    menu_layout->addStretch(1);
    menu_layout->addWidget(addMusicBtn);
    menu_layout->addStretch(1);
    menu_layout->addWidget(removeBtn);
    menu_layout->addStretch(1);
    menu_layout->addWidget(clearBtn);
    menu_layout->addStretch(1);
    menu_layout->addWidget(modeBtn);
    menu_layout->addStretch(1);

    //调整按钮布局：上一首歌曲，播放，下一首歌曲
    button_layout->addStretch(2);
    button_layout->addWidget(lastBtn);
    button_layout->addStretch(1);
    button_layout->addWidget(playBtn);
    button_layout->addStretch(1);
    button_layout->addWidget(nextBtn);
    button_layout->addStretch(2);

    //总布局调整
    main_layout->addStretch(1);
    main_layout->addWidget(listWidget);
    main_layout->addStretch(1);
    main_layout->addLayout(musicSchedule);
    main_layout->addStretch(1);
    main_layout->addLayout(volume_layout);
    main_layout->addStretch(1);
    main_layout->addLayout(menu_layout);
    main_layout->addLayout(button_layout);
    main_layout->addStretch(1);

    main_layout->addStretch(1);

    connect(addMusicBtn,&QPushButton::clicked,this,&musicPlayer::onFileButtonClicked);      //导入音乐调用的槽函数
    connect(playBtn,&QPushButton::clicked,this,&musicPlayer::playMusic);                    //播放音乐调用的槽函数
    connect(lastBtn,&QPushButton::clicked,this,&musicPlayer::lastMusic);                    //播放上一首音乐调用的槽函数
    connect(nextBtn,&QPushButton::clicked,this,&musicPlayer::nextMusic);                    //播放下一首音乐调用的槽函数
    connect(listWidget,&QListWidget::doubleClicked,this,&musicPlayer::switchMusic);         //双击音乐菜单中的歌曲，切换音乐调用的槽函数

    connect(modeBtn,&QPushButton::clicked,this,&musicPlayer::setMode);                      //模式设置按钮：对应切换播放模式的槽函数
    connect(clearBtn,&QPushButton::clicked,this,&musicPlayer::clearMusic);                  //对应去除音乐的槽函数
    connect(removeBtn,&QPushButton::clicked,this,&musicPlayer::removeMusic);                //对应清空音乐列表的槽函数

    m_audioOutput=new QAudioOutput(this);       //output对象
    m_audioOutput->setVolume(0.5);               //设置默认播放的音量
    m_mediaPlayer=new QMediaPlayer(this);       //媒体播放对象
    m_mediaPlayer->setAudioOutput(m_audioOutput);



    //获取当前的总播放时长，更新播放显示的标签（对应总时长）
    connect(m_mediaPlayer,&QMediaPlayer::durationChanged,this,[=](qint64 duration)
            {
                total->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
                scheduleSlider->setRange(0,duration);
            }
            );

    //获取当前的播放时长，更新播放显示的标签（对应的是当前的播放位置）
    connect(m_mediaPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 position)
            {
                current->setText(QString("%1:%2").arg(position/1000/60,2,10,QChar('0')).arg(position/1000%60,2,10,QChar('0')));
                scheduleSlider->setValue(position);
            }
            );

    //当音乐播放结束时，根据选择的播放模式切换到下一首播放的歌曲
    connect(m_mediaPlayer,&QMediaPlayer::mediaStatusChanged,this,&musicPlayer::handleMediaStatusChanged);

    //拖动播放进度条滑块，根据进度条的位置，修改播放的进度（也就是接下来要从哪里开始继续播放）
    connect(scheduleSlider,&QSlider::sliderMoved,m_mediaPlayer,&QMediaPlayer::setPosition);

    //拖动音量进度条滑块，拖动滑块，改变音量
    volumeSlider->setRange(0,100);
    volumeSlider->setSliderPosition(50);
    connect(volumeSlider,&QSlider::sliderMoved,this,&musicPlayer::changeVolume);

    QString folderPath=":/music/resource/music";
    QDir dir(folderPath);
    if(dir.exists())
    {
        QStringList fileList=dir.entryList(QDir::Files);
        for(auto &item:fileList)
        {
            QString newFile="qrc"+folderPath+'/'+item;
            qDebug()<<newFile;
            playList.append(QUrl(newFile));             //转换成QUrl格式（保证能够被其他组件使用时：路径的正确性和跨平台的兼容性），并且导入到playlist中
            QFileInfo fileInfo(newFile);
            listWidget->addItem(fileInfo.fileName());                   //添加到界面文件列表
        }
        listWidget->setCurrentRow(0);
        m_mediaPlayer->setSource(QUrl(playList[0]));
    }
    return;
}

void musicPlayer::onFileButtonClicked()
{
    QString path=QDir::homePath();//获取用户目录.
    QString title= "选择音频文件";
    QString filter="音频文件(* .mp3 *.wav * .wma) ;;mp3文件(* .mp3);;wav文件(* .wav); ;wma文件(*. .wma);;所有文件(*.*)";

    QStringList fileList=QFileDialog::getOpenFileNames(this,title,path,filter);     //获取导入的音频文件列表

    if(fileList.empty())        //如果导入的音频文件为空，则返回
    {
        return;
    }

    for(auto &item:fileList)
    {
        QString newFile=item;
        playList.append(QUrl::fromLocalFile (newFile));             //转换成QUrl格式（保证能够被其他组件使用时：路径的正确性和跨平台的兼容性），并且导入到playlist中
        qDebug()<<playList.back();
        QFileInfo fileInfo(newFile);
        listWidget->addItem(fileInfo.fileName());                   //添加到界面文件列表
    }
    listWidget->setCurrentRow(0);                                   //设置当前的播放列表歌曲：默认为第一首歌曲
}

void musicPlayer::playMusic()
{
    if(playList.empty())        //特判playList为空的清空，防止误触按钮导致程序崩溃
    {
        return;
    }

    switch(m_mediaPlayer->playbackState())
    {
    case QMediaPlayer::PlaybackState::StoppedState:         //如果是处于停止播放状态
    {
        //1、获取当前获得的行号
        m_currentIndex=listWidget->currentRow();
        //2、播放对应行号的音乐
        m_mediaPlayer->setSource(playList[m_currentIndex]);
        m_mediaPlayer->play();

        //3、改变icon
        QIcon icon(":/icons/resource/icons/播放.png");
        playBtn->setIcon(icon);
        playBtn->setText("播放");
        playBtn->setIconSize(QSize(40,40));
        break;
    }
    case QMediaPlayer::PlaybackState::PlayingState:         //如果是处于正在播放的状态
    {
        //如果现在正在播放，则暂停音乐
        m_mediaPlayer->pause();
        QIcon icon(":/icons/resource/icons/暂停.png");
        playBtn->setIcon(icon);
        playBtn->setText("暂停");
        playBtn->setIconSize(QSize(40,40));
        break;
    }
    case QMediaPlayer::PlaybackState::PausedState:          //如果是处于暂停播放的状态
    {
        //如果现在是暂停的，则继续播放音乐
        m_mediaPlayer->play();
        QIcon icon(":/icons/resource/icons/播放.png");
        playBtn->setIcon(icon);
        playBtn->setText("播放");
        playBtn->setIconSize(QSize(40,40));
        break;
    }
    }
}

void musicPlayer::lastMusic()
{
    if(playList.empty())        //特判playList为空的清空，防止误触按钮导致程序崩溃
    {
        return;
    }
    m_currentIndex=(m_currentIndex-1+playList.size())%playList.size();
    listWidget->setCurrentRow(m_currentIndex);
    m_mediaPlayer->setSource(playList[m_currentIndex]);
    m_mediaPlayer->play();
}

void musicPlayer::nextMusic()
{
    if(playList.empty())        //特判playList为空的清空，防止误触按钮导致程序崩溃
    {
        return;
    }
    m_currentIndex=(m_currentIndex+1)%playList.size();      //防止下标越界
    listWidget->setCurrentRow(m_currentIndex);
    m_mediaPlayer->setSource(playList[m_currentIndex]);
    m_mediaPlayer->play();
}

void musicPlayer::switchMusic(const QModelIndex &index)
{
    if(playList.empty())        //特判playList为空的清空，防止误触按钮导致程序崩溃
    {
        return;
    }
    m_currentIndex=index.row();
    listWidget->setCurrentRow(m_currentIndex);
    m_mediaPlayer->setSource(playList[m_currentIndex]);
    m_mediaPlayer->play();

}

void musicPlayer::removeMusic()
{
    if(playList.empty())        //特判playList为空的清空，防止误触按钮导致程序崩溃
    {
        return;
    }
    int index=listWidget->currentRow();
    QListWidgetItem *item=listWidget->takeItem(index);
    delete item;
    if(m_mediaPlayer->source()==playList.at(index))         //如果选中的恰好是当前正在播放的音乐，那么会停止播放
    {
        m_mediaPlayer->stop();
    }
    playList.removeAt(index);
}

void musicPlayer::clearMusic()
{
    if(playList.empty())        //特判playList为空的清空，防止误触按钮导致程序崩溃
    {
        return;
    }
    m_mediaPlayer->stop();
    playList.clear();
    listWidget->clear();
}

void musicPlayer::changeVolume(const float volume)          //调节音量
{
    m_audioOutput->setVolume(volume/100);
    m_mediaPlayer->setAudioOutput(m_audioOutput);
}

void musicPlayer::setLoopMode()                             //设置为循环模式
{
    loopMode=true;
    randomMode=false;
    sortMode=false;
    modeBtn->setText("单曲循环");
    QIcon icon(":/icons/resource/icons/单曲循环.png");
    modeBtn->setIcon(icon);
    modeBtn->setIconSize(QSize(30,30));
}

void musicPlayer::setRandomMode()                           //设置为随机播放模式
{
    randomMode=true;
    loopMode=false;
    sortMode=false;
    modeBtn->setText("随机播放");
    QIcon icon(":/icons/resource/icons/随机播放.png");
    modeBtn->setIcon(icon);
    modeBtn->setIconSize(QSize(30,30));
}

void musicPlayer::setSortMode()                             //设置为顺序播放模式
{
    sortMode=true;
    loopMode=false;
    randomMode=false;
    modeBtn->setText("列表循环");
    QIcon icon(":/icons/resource/icons/列表循环.png");
    modeBtn->setIcon(icon);
    modeBtn->setIconSize(QSize(30,30));
}

void musicPlayer::setMode()                                 //对应的设置播放模式的槽函数
{
    if(loopMode && !sortMode && !randomMode)
    {
        setSortMode();
    }
    else if(!loopMode && sortMode && !randomMode)
    {
        setRandomMode();
    }
    else if(!loopMode && !sortMode && randomMode)
    {
        setLoopMode();
    }
}

void musicPlayer::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)        //对应的根据当前的播放模式，切换到下一首歌曲的播放模式
{
    if(status==QMediaPlayer::EndOfMedia)
    {
        if(loopMode)
        {
            m_mediaPlayer->setPosition(0);
            m_mediaPlayer->play();
        }
        else if(sortMode)
        {
            m_currentIndex=(m_currentIndex+1)%playList.size();
            m_mediaPlayer->setSource(playList[m_currentIndex]);
            listWidget->setCurrentRow(m_currentIndex);
            m_mediaPlayer->play();
        }
        else
        {
            m_currentIndex=QRandomGenerator::global()->bounded(playList.size());
            listWidget->setCurrentRow(m_currentIndex);
            m_mediaPlayer->setSource(playList[m_currentIndex]);
            m_mediaPlayer->play();
        }
    }
}

