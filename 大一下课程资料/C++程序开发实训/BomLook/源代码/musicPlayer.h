#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QSlider>
#include <QSpacerItem>
#include <QMediaPlayer>
#include <QLabel>
#include <QAudioOutput>
class musicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit musicPlayer(QWidget *parent = nullptr);
public slots:
    void onFileButtonClicked();                                         //添加歌曲
    void playMusic();                                                   //播放音乐
    void lastMusic();                                                   //跳转到上一首歌曲
    void nextMusic();                                                   //跳转到下一首歌曲
    void removeMusic();                                                 //去除选定的歌曲
    void clearMusic();                                                  //清空歌曲的列表
    void switchMusic(const QModelIndex &);                              //切换歌曲
    void changeVolume(const float);                                     //调节音量
    void setMode();                                                     //连接播放模式的函数，用于设置播放的模式
private:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);    //用于解决播放结束时，接下来应该如何播放
    void setLoopMode();                                                 //设置单曲循环模式
    void setSortMode();                                                 //设置顺序播放模式
    void setRandomMode();                                               //设置随机播放模式
    QVBoxLayout *main_layout;                                           //主布局
    QHBoxLayout *menu_layout;                                           //菜单布局：包括了：添加、去除、清空、播放模式
    QHBoxLayout *button_layout;                                         //按钮布局：包括了：上一首、继续播放、下一首
    QListWidget *listWidget;                                            //播放列表：用于显示歌曲菜单
    QSlider *scheduleSlider;                                            //播放的进度条
    QSlider *volumeSlider;                                              //音量的进度条
    QList<QUrl> playList;                                               //播放列表：用于存储歌曲的路径
    QAudioOutput *m_audioOutput;                                        //管理音频的输出
    QMediaPlayer *m_mediaPlayer;                                        //管理音频的播放
    QLabel *current;                                                    //当前的音乐播放进度标签
    QLabel *total;                                                      //目前播放歌曲的总进度标签
    QLabel *volume;                                                     //音量
    QHBoxLayout *musicSchedule;                                         //用于描述播放进度的布局
    QHBoxLayout *volume_layout;                                         //调节音量的布局
    int m_currentIndex;                                                 //目前播放歌曲的编号

    QPushButton *addMusicBtn;                                           //添加音乐按钮
    QPushButton *lastBtn;                                               //上一首歌曲按钮
    QPushButton *nextBtn;                                               //下一首歌曲按钮
    QPushButton *playBtn;                                               //继续播放按钮
    QPushButton *removeBtn;                                             //去除选中的按钮
    QPushButton *clearBtn;                                              //清空歌曲的按钮
    QPushButton *modeBtn;                                               //选择模式的按钮
    bool sortMode;                                                      //顺序模式
    bool loopMode;                                                      //单曲循环模式
    bool randomMode;                                                    //随机模式
};

#endif // MUSICPLAYER_H
