#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHboxLayout>
#include <QPalette>
#include <QBrush>
#include <QLabel>
#include <QTimer>
#include <QStackedWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
#include "gamescene.h"
#include "setwidget.h"
#include "helpwidget.h"
#include "accountwidget.h"
#include "myController.h"
#include "player.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    Player &getOnloginPlayer();//提供给其他窗口当前玩家的接口，其他窗口可以利用指针来改变该用户数据成员；

private:
    Player onLoginPlayer;//直接为对象，不写指针了，要不其他窗口的指针是指向指针

    QLabel *lable;
    MyPushButton *startButton;
    QPushButton *helpButton;
    QPushButton *quitButton;
    QGridLayout *mainLayout;

    QWidget *mainPage;
    setWidget *setW;
    accountWidget *accountW;
    helpWidget *helpW;
    gameWidget *gameW;
    rankWidget *rankwidget;
    playWidget *playwidget;
    QStackedWidget *stackedWidget;
    QSoundEffect music;




public slots:
    void showSetWidget();
    void showStartWidget();
    void showHelpWidget();
    void returnToMainPage();
    void startPlayGameWithAccount();//槽函数要与信号函数参数列表一致才可以传参
    void startPlayGame();
    void showPracticeWidget();
    void showCompetitionWidget();//这两个页面不属于mainscene里面了
    void showRankWidget();
    void showEndlessWidget();
    void showCustomWidget();
signals:
    void reviseLayout();
};
#endif
