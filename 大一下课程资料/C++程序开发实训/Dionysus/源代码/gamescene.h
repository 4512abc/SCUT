#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPalette>
#include <QBrush>
#include <QColor>
#include <QStandardItemModel>
#include <QTableView>
#include <QStackedWidget>
#include <QTimer>
#include <QTime>
#include <QCloseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QScrollArea>
#include <QRadioButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QRegularExpression>
#include <QButtonGroup>
#include "DragAndDrop.h"
#include "player.h"
#include "map.h"
#include "myController.h"
#include "helpwidget.h"
class VictoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VictoryWidget(QWidget *parent = nullptr);
    ~VictoryWidget();
private:
    QLabel *victoryLabel;
    QPushButton *viewRankingButton;
    QPushButton *continueGameButton;
    QPushButton *selectModeButton;
    QGridLayout *gridLayout;

signals:
    void restart();
    void toRank();
    void selectOtherMode();
};

class rankWidget : public QWidget
{
    Q_OBJECT
public:
    explicit rankWidget(QWidget *parent = nullptr);
    ~rankWidget(){}
    void setOnLoginPlayer(Player &player){onLoginPlayer = &player;}
    void loadContent(const QString& filename);

    void swapTableWidgetRows(int fromRow, int toRow);
private:
    Player *onLoginPlayer;

    QTableWidget *tableWidget;

    QPushButton *returnBtn;
    QGridLayout *mainLayout;
    QLabel *onLoginRecord;
    QPushButton *practiceRankBtn;
    QPushButton *competitionRankBtn;
    QButtonGroup *selectSortMode;
    QRadioButton *fastestMode;
    QRadioButton *averageMode;
    QRadioButton *successMode;
    QPushButton *endlessRankBtn;

signals:
    void returnToGameScene();

public slots:
    void sortRank(int mode);
};
#include <QApplication>
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QTableWidgetItem>



class playWidget : public QWidget
{
    Q_OBJECT
public:
    explicit playWidget(QWidget *parent = nullptr);
    void setOnLoginPlayer(Player &player){onLoginPlayer = &player;}
    void setPlayMode(int fromSignal){playMode = fromSignal;}
    void setUserDefined(bool a){userDefined = a;}
    void customMode();
    void writeCustomMapToFile();

    void loadSliceToPut();
    void loadTargetSlice();
    void loadSliceHasPutOn();

    void cleanWidget();
    void restart();
    bool isAnswer();
    void updatePlayerRecord();
    void reShowWidget();
    void setEndlessPlayMode(int);


private:
    Player *onLoginPlayer;
    long long elapsedTime = 0;
    int playMode = practiceMode;
    bool userDefined = 0;//检测用户是否自定义了地图，调用不同的存储模式
    int stepsInVector = -1;//要初始化为-1而非0
    QVector<int> sliceToPut_Kind_Record;
    QVector<int> sliceToPut_PosX_Record;
    QVector<int> sliceToPut_PosY_Record;//每个update函数实施加入相应向量就可以比较容易地实现撤回了
    QVector<int> targetSlice_NumberInArray_Record;//多个数组，还是为了能够较好的匹配update函数
    Map map;

    int endless_playMode = practiceMode;//这里后续再设置吧

    //QPushButton *player_definedMapBtn;
    QPushButton *returnGameSceneBtn;
    QPushButton *helpBtn;
    QLabel *usedTime;
    QPushButton *Custom;
    QPushButton *tipsBtn;
    QPushButton *withdrawBtn;
    QPushButton *startBtn;//点击后本身隐藏，开始计时，加载可视化的地图。
    //QPushButton *exitGame;
    QGridLayout *mainLayout;
    QGridLayout *targetSliceLayout;//能有方法那也行，哈希映射什么的再学吧，最后决定直接设置坐标，滚蛋！用来占占位置得了
    QLabel *hideTargetSlice;
    QLabel *timeLable;
    QLabel *introTime;
    QTimer *timer;
    QScrollArea *scrollArea;
    DraggableLabel *SliceToPut[7];
    DroppableLabel *targetSlice[36];
    QLabel *SliceHasPutOn[36];
    QWidget *SliceToPutWidget;
    QVBoxLayout *sliceToputLayout;


public slots:
    void updateTime();
    void withdraw();
    void updateTargetSlice(int sliceKind,int posInArray, int pos_x, int pos_y, int delta);//delta对应相应增减任意值
    void updateSliceToPut(int sliceKind,int change);//change = -1为删除，= 1为增加，后面撤回用
    void updateTargetSliceLabel();//写一个，for循环时间多一些，但是避免代码行数太多，拥杂
    void startWithOthersMap();
    void startByCustomInput();
    void showCustom();
signals:
    void returnToGameScene();
    void recustom();
    void selectOtherMode();
    void toRank();
};

class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(QWidget *parent = nullptr);
    ~gameWidget(){}
    void setOnLoginPlayer(Player &player){onLoginPlayer = &player;}

signals:
    void returnToMainPage();
    void ToPractice();
    void ToCompetition();
    void ToRankWidget();
    void loginOutSignal();
    void ToEndless();
    void ToCustom();

private:
    Player *onLoginPlayer;

    QPushButton *practiceBtn;
    QPushButton *competitionBtn;
    QPushButton *GradesRankBtn;
    QPushButton *LogOutBtn;
    QPushButton *endlessBtn;
    QPushButton *player_definedBtn;
    QPushButton *returnButton;
    QLabel *titleLable;//不想要了，在首页介绍一下就好，换其他图吧
    QLabel *poem1;
    QLabel *poem2;

    QGridLayout *mainLayout;


};

#endif // GAMEWIDGET_H


